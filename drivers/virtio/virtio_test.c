#include <linux/virtio.h>
#include <linux/virtio_test.h>
#include <linux/swap.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/oom.h>
#include <linux/wait.h>
#include <linux/mm.h>
#include <linux/mount.h>
#include <linux/magic.h>


struct virtio_test {
    struct virtio_device *vdev;
    struct virtqueue *print_vq;

    struct work_struct print_val_work;
    bool stop_update;
    atomic_t stop_once;

    /* Waiting for host to ack the pages we released. */
    wait_queue_head_t acked;

    __virtio32 num[256];
};

static struct virtio_device_id id_table[] = {
    { VIRTIO_ID_TEST, VIRTIO_DEV_ANY_ID },
    { 0 },
};

static struct virtio_test *vb_dev;

static void test_ack(struct virtqueue *vq)
{
    struct virtio_test *vb = vq->vdev->priv;
    printk("virttest get ack\n");
    unsigned int len;
    virtqueue_get_buf(vq, &len);
}

static int init_vqs(struct virtio_test *vb)
{
    struct virtqueue *vqs[1];
    vq_callback_t *callbacks[] = { test_ack };
    static const char * const names[] = { "print"};
    int err, nvqs;

    nvqs = virtio_has_feature(vb->vdev, VIRTIO_TEST_F_CAN_PRINT) ? 1 : 0;
    /* wait qemu notify to callbacks */
    err = virtio_find_vqs(vb->vdev, nvqs, vqs, callbacks, names, NULL);
    if (err)
        return err;

    vb->print_vq = vqs[0];

    return 0;
}

static void remove_common(struct virtio_test *vb)
{
    /* Now we reset the device so we can clean up the queues. */
    vb->vdev->config->reset(vb->vdev);

    vb->vdev->config->del_vqs(vb->vdev);
}

static void virttest_remove(struct virtio_device *vdev)
{
    struct virtio_test *vb = vdev->priv;

    remove_common(vb);
    cancel_work_sync(&vb->print_val_work);
    kfree(vb);
    vb_dev = NULL;
}

static int virttest_validate(struct virtio_device *vdev)
{
    return 0;
}

static void print_val_func(struct work_struct *work)
{
    struct virtio_test *vb;
    struct scatterlist sg;

    vb = container_of(work, struct virtio_test, print_val_work);
    printk("virttest get config change\n");

    struct virtqueue *vq = vb->print_vq;
    vb->num[0]++;
    sg_init_one(&sg, &vb->num[0], sizeof(vb->num[0]));

    /* We should always be able to add one buffer to an empty queue. */
    virtqueue_add_outbuf(vq, &sg, 1, vb, GFP_KERNEL);
    /* notify qemu */
    virtqueue_kick(vq);
}

static void virttest_changed(struct virtio_device *vdev)
{
    struct virtio_test *vb = vdev->priv;
    printk("virttest virttest_changed\n");
    if (!vb->stop_update) {
        //atomic_set(&vb->stop_once, 0);
        queue_work(system_freezable_wq, &vb->print_val_work);
    }
}

static int virttest_probe(struct virtio_device *vdev)
{
    struct virtio_test *vb;
    int err;

    printk("******create virttest\n");
    if (!vdev->config->get) {
        return -EINVAL;
    }

    vdev->priv = vb = kmalloc(sizeof(*vb), GFP_KERNEL);
    if (!vb) {
        err = -ENOMEM;
        goto out;
    }
    vb->num[0] = 0;
    vb->vdev = vdev;
    INIT_WORK(&vb->print_val_work, print_val_func);

    vb->stop_update = false;

    init_waitqueue_head(&vb->acked);
    err = init_vqs(vb);
    if (err)
        goto out_free_vb;

    virtio_device_ready(vdev);

    atomic_set(&vb->stop_once, 0);
    vb_dev = vb;

    return 0;

out_free_vb:
    kfree(vb);
out:
    return err;
}

static unsigned int features[] = {
    VIRTIO_TEST_F_CAN_PRINT,
};

static struct virtio_driver virtio_test_driver = {
    .feature_table = features,
    .feature_table_size = ARRAY_SIZE(features),
    .driver.name =  KBUILD_MODNAME,
    .driver.owner = THIS_MODULE,
    .id_table = id_table,
    .validate = virttest_validate,
    .probe =    virttest_probe,
    .remove =   virttest_remove,
    .config_changed = virttest_changed,
};

module_virtio_driver(virtio_test_driver);
MODULE_DEVICE_TABLE(virtio, id_table);
MODULE_DESCRIPTION("Virtio test driver");
MODULE_LICENSE("GPL");
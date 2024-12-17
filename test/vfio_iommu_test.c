void main(){
    int container, group, device, i;
    struct vfio_group_status group_status =
                                    { .argsz = sizeof(group_status) };
    struct vfio_iommu_type1_info iommu_info = { .argsz = sizeof(iommu_info) };
    struct vfio_iommu_type1_dma_map dma_map = { .argsz = sizeof(dma_map) };
    struct vfio_device_info device_info = { .argsz = sizeof(device_info) };

    /* Create a new container */
    container = open("/dev/vfio/vfio", O_RDWR);

    if (ioctl(container, VFIO_GET_API_VERSION) != VFIO_API_VERSION)
            /* Unknown API version */

    if (!ioctl(container, VFIO_CHECK_EXTENSION, VFIO_TYPE1_IOMMU))
            /* Doesn't support the IOMMU driver we want. */

    /* Open the group */
    group = open("/dev/vfio/26", O_RDWR);

    /* Test the group is viable and available */
    ioctl(group, VFIO_GROUP_GET_STATUS, &group_status);

    if (!(group_status.flags & VFIO_GROUP_FLAGS_VIABLE))
            /* Group is not viable (ie, not all devices bound for vfio) */

    /* Add the group to the container */
    ioctl(group, VFIO_GROUP_SET_CONTAINER, &container);

    /* Enable the IOMMU model we want */
    ioctl(container, VFIO_SET_IOMMU, VFIO_TYPE1_IOMMU);

    /* Get addition IOMMU info */
    ioctl(container, VFIO_IOMMU_GET_INFO, &iommu_info);

    /* Allocate some space and setup a DMA mapping */
    dma_map.vaddr = mmap(0, 1024 * 1024, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    dma_map.size = 1024 * 1024;
    dma_map.iova = 0; /* 1MB starting at 0x0 from device view */
    dma_map.flags = VFIO_DMA_MAP_FLAG_READ | VFIO_DMA_MAP_FLAG_WRITE;

    ioctl(container, VFIO_IOMMU_MAP_DMA, &dma_map);

    /* Get a file descriptor for the device */
    device = ioctl(group, VFIO_GROUP_GET_DEVICE_FD, "0000:06:0d.0");

    /* Test and setup the device */
    ioctl(device, VFIO_DEVICE_GET_INFO, &device_info);

    for (i = 0; i < device_info.num_regions; i++) {
            struct vfio_region_info reg = { .argsz = sizeof(reg) };

            reg.index = i;

            ioctl(device, VFIO_DEVICE_GET_REGION_INFO, &reg);

            /* Setup mappings... read/write offsets, mmaps
            * For PCI devices, config space is a region */
    }

    for (i = 0; i < device_info.num_irqs; i++) {
            struct vfio_irq_info irq = { .argsz = sizeof(irq) };

            irq.index = i;

            ioctl(device, VFIO_DEVICE_GET_IRQ_INFO, &irq);

            /* Setup IRQs... eventfds, VFIO_DEVICE_SET_IRQS */
    }

    /* Gratuitous device reset and go... */
    ioctl(device, VFIO_DEVICE_RESET);
}


我们知道在client 在通过 mbox_send_message 给controller发送数据的时候必须指定channel。例如下面的code
	dc_sync->mbox = (&dc_sync->cl, 0);
	/* Populate data packet */
	/* sp.abc = 123; etc */
	/* Send message to remote in blocking mode */
	mbox_send_message(dc_sync->mbox, &sp);
	/* At this point 'sp' has been sent */

目前kernel提供了两种方法得到mailbox的channel
struct mbox_chan *mbox_request_channel_byname(struct mbox_client *cl,const char *name);
struct mbox_chan *mbox_request_channel(struct mbox_client *cl, int index);

使用完成后调用mbox_free_channel 释放channel，这样别人就可以继续使用这个channel
void mbox_free_channel(struct mbox_chan *chan); /* may sleep */

其中 mbox_request_channel_byname 是 mbox_request_channel 的一个包装。所以这里直接看看 mbox_request_channel
struct mbox_chan *mbox_request_channel(struct mbox_client *cl, int index)
{
	struct device *dev = cl->dev;
	struct mbox_controller *mbox;
	struct of_phandle_args spec;
	struct mbox_chan *chan;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&chan->lock, flags);
	chan->msg_free = 0;
	chan->msg_count = 0;
	chan->active_req = NULL;
	chan->cl = cl;
	init_completion(&chan->tx_complete);

	//初始化chan，并最终startup
	ret = chan->mbox->ops->startup(chan);
	if (ret) {
		dev_err(dev, "Unable to startup the chan (%d)\n", ret);
		mbox_free_channel(chan);
		chan = ERR_PTR(ret);
	}
}

以之前的arm_mhu.c 中定义的mbox_chan_ops为例
static const struct mbox_chan_ops mhu_ops = {
	.send_data = mhu_send_data,
	.startup = mhu_startup,
	.shutdown = mhu_shutdown,
	.last_tx_done = mhu_last_tx_done,
};

static int mhu_startup(struct mbox_chan *chan)
{
	struct mhu_link *mlink = chan->con_priv;
	u32 val;
	int ret;

	val = readl_relaxed(mlink->tx_reg + INTR_STAT_OFS);
	writel_relaxed(val, mlink->tx_reg + INTR_CLR_OFS);
	原来就是注册了一个中断，其回调函数是 mhu_rx_interrupt
	ret = request_irq(mlink->irq, mhu_rx_interrupt,
			  IRQF_SHARED, "mhu_link", chan);
	if (ret) {
		dev_err(chan->mbox->dev,
			"Unable to acquire IRQ %d\n", mlink->irq);
		return ret;
	}

	return 0;
}
这个中断函数如下：
当client 给controller 通过mbox_send_message发送数据后，arm_mhu 会产生一个中断给cotroller。
static irqreturn_t mhu_rx_interrupt(int irq, void *p)
{
	struct mbox_chan *chan = p;
	struct mhu_link *mlink = chan->con_priv;
	u32 val;

	val = readl_relaxed(mlink->rx_reg + INTR_STAT_OFS);
	if (!val)
		return IRQ_NONE;
	controller调用mbox_chan_received_data 就可以得到client发送来的数据
	mbox_chan_received_data(chan, (void *)&val);

	writel_relaxed(val, mlink->rx_reg + INTR_CLR_OFS);

	return IRQ_HANDLED;
}
void mbox_chan_received_data(struct mbox_chan *chan, void *mssg)
{
	读去数据后，调用client的rx_callback 通知client
	/* No buffering the received data */
	if (chan->cl->rx_callback)
		chan->cl->rx_callback(chan->cl, mssg);
}


controller接收数据的flow 清楚了，再看看client是如何调用 mbox_send_message 发送数据的
mbox_send_message->msg_submit
	if (chan->cl->tx_prepare)
		chan->cl->tx_prepare(chan->cl, data);
	/* Try to submit a message to the MBOX controller */
	err = chan->mbox->ops->send_data(chan, data);
	if (!err) {
		chan->active_req = data;
		chan->msg_count--;
	}
最终还是调用controll而的send_data 发送数据，本例controller的send_data函数为mhu_send_data
static int mhu_send_data(struct mbox_chan *chan, void *data)
{
	struct mhu_link *mlink = chan->con_priv;
	u32 *arg = data;
	就是写controller的一个寄存器就行了，client写了之后后触发中断，controller会在中断中读到数据，并通过mbox_chan_received_data 通知client已经读取数据了
	writel_relaxed(*arg, mlink->tx_reg + INTR_SET_OFS);

	return 0;
}

//原文链接：https://blog.csdn.net/tiantao2012/article/details/78030580

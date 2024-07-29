内核和用户空间的消息传递-事件通知 （2）

tea1896

于 2016-06-01 09:56:07 发布

阅读量3.9k
 收藏 8

点赞数
分类专栏： 嵌入式linux 文章标签： 内核 用户 通知
版权

嵌入式linux
专栏收录该内容
22 篇文章0 订阅
订阅专栏
事件通知机制不仅可用户用户态两个线程之间同步，还可以用于内核空间和用户空间同步。


方法如下：

1.在用户层

a. 创建一个文件描述符

int event_fd = -1;
event_fd = eventfd ( 0, EFD_NONBLOCK | EFD_SEMAPHORE );

b.将文件描述符通过ioctl传递给内核 

enable_message_notification_info.event_fd       = event_fd;
ioctl ( fmb_fd, FMB_API_ENABLE_MESSAGE_NOTIFICATION, &enable_message_notification_info );

c.将事件通知的文件描述符，加入文件描述集，然后用select监控

fd_set read_fds;

while(1)

{

//.将这个文件描述符加入set,然后select监控队列

FD_ZERO ( &read_fds );
FD_SET ( event_fd , &read_fds );
result = select ( max_fd + 1, &read_fds, NULL, NULL, NULL );

。。。

// 如果有事件触发

if ( FD_ISSET ( message_thread_param_p->fd_receive_message_notification, &read_fds ) )

 {
  uint32_t message_id;
  uint32_t message_param[FMB_MESSAGE_PARAM_SIZE];

  //清空
  result = eventfd_read ( message_thread_param_p->fd_receive_message_notification, &eventfd_value );
  ASSERT_APP ( result == 0, "ERR: eventfd_read" );
 //事件处理     

 ...  ...  

}

}


2.在内核空间：

a. 通过ioctl得到文件描述符，转换为eventfd_ctx

struct eventfd_ctx* eventfd_ctx_p;
eventfd_ctx_p = eventfd_ctx_fdget ( event_fd );

b.在需要发送消息的地方调用以下接口：

eventfd_signal ( queue_p->notification_info.eventfd_ctx_p, 1 );

c.回收这个消息的资源

eventfd_ctx_put ( queue_p->notification_info.eventfd_ctx_p );
————————————————

版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
原文链接：https://blog.csdn.net/tea1896/article/details/51553438



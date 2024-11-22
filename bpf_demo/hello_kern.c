#include <linux/bpf.h>
#include "bpf_helpers.h"
#define SEC(NAME) __attribute__((section(NAME), used))

SEC("tracepoint/syscalls/sys_enter_execve")
// SEC("fentry/virtio_queue_rq")
int bpf_prog(void *ctx){
	char msg[] = "JinRong's first bpf program!\n";
	bpf_trace_printk(msg, sizeof(msg));
	return 0;
}

char _license[] SEC("license") = "GPL";
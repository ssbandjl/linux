#!/usr/local/bin/bpftrace
#include <linux/sched.h>

BEGIN
{
	printf("Tracing nanosecond time in off-CPU stacks. Ctrl-C to end.\n");
}

// kernel/sched/core.c -> static struct rq *finish_task_switch(struct task_struct *prev)
kprobe:finish_task_switch
{
	// record previous thread sleep time
	$prev = (struct task_struct *)arg0;
	if ($1 == 0 || $prev->tgid == $1) {
		@start[$prev->pid] = nsecs;
	}

	// get the current thread start time
	$last = @start[tid];
	if ($last != 0) {
		@[kstack, ustack, comm] = sum(nsecs - $last);
		delete(@start[tid]);
	}
}

END
{
	clear(@start);
}


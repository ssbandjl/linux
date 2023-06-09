bpftrace -e 'kprobe:fail_path { printf("bt:%s\n", kstack); }'
#
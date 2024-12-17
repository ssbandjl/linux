/* Describes what we need from a read */
struct read_descriptor {
    int fd;
    char *buf;
    unsigned long long pos;
    unsigned long long size;
    int result;
};

/*
 * given an array of struct read_descriptors, dispatch them in the
 * io_uring
 */
int
dispatch_reads(struct io_uring *ring, struct read_descriptor *descv, int nr_desc)
{
    int i;
    for (i = 0; i < nr_desc; i++) {
        struct io_uring_sqe *sqe;
        struct read_descriptor *desc = &descv[i];
        sqe = io_uring_get_sqe(ring);
        /* Each operation will have a special prep function */
        io_uring_prep_read(sqe, desc->fd, desc->buf, desc->size, desc->pos);
        /*
         * Whatever value we put here will be reflected when it is
         * ready. This is how we know which read we are talking about
         */
        io_uring_sqe_set_data(sqe, desc);
    }
    /* For all of the reads above, there will be only one system call! */
    return io_uring_submit(ring);
}



/*
 * Consume reads that are available and returns how many were consumed.
 * System calls issued: ZERO!
 */
unsigned
consume_reads(struct io_uring *ring)
{
    unsigned completed;
    unsigned head;
    struct io_uring_cqe *cqe;

    io_uring_for_each_cqe(ring, head, cqe) {
        completed++;
        /* Remember what we passed in io_uring_sqe_set_data?. It's here */
        struct read_descriptor *desc = (struct read_descriptor*)cqe->user_data;
        desc->result = cqe->res;
    }
    io_uring_cq_advance(ring, completed);
}


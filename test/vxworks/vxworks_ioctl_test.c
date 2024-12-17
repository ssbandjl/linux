
int main(int argc, char *argv[])
{
    int fd;
    int ret;
    char *wbuf = "I Love embedded system!\n";
    char rbuf[256];
    fd = open("/dev/fsdev", O_RDWR, 0);
    if (fd < 0) {
        perror("fsdev");
        return -1;
    }
    ret = write(fd, wbuf, strlen(wbuf) + 1);
    if (ret < 0) {
        perror("fsdev");
        close(fd);
        return ret;
    }
    ret = read(fd, rbuf, sizeof(rbuf));
    if (ret < 0) {
        perror("fsdev");
        close(fd);
        return ret;
    }
    printf("read data: %s", rbuf);
    close(fd);
}



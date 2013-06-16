#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define DROIDCON_DEV "/dev/droidcon"
#define MAX_SIZE 1024


ssize_t droidcon_getdata(void *buf, size_t count)
{
    int fd = open(DROIDCON_DEV, O_RDONLY);
    ssize_t ret = read(fd, buf, count);
    close(fd);
    return ret;
}


ssize_t droidcon_putdata(const void *buf, size_t count)
{
    int fd = open(DROIDCON_DEV, O_WRONLY);
    ssize_t ret = write(fd, buf, count);
    close(fd);
    return ret;
}

void droidcon_clear(void)
{
    int fd = open(DROIDCON_DEV, O_WRONLY);
    write(fd, 0, 0);
}

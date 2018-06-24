#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "../lib/tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    int fd;
    char *buf = "testing123";
    off_t offset = 0;

    fd = open("seek.dat", O_RDWR | O_CREAT | O_TRUNC,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
        S_IROTH | S_IWOTH);

    if (fd == -1)
        errExit("open");

    if (write(fd, buf, 10) == -1)
        errExit("write 1");

    if ((offset = lseek(fd, 10000, SEEK_END)) == -1)
        errExit("seek");

    if (write(fd, buf, 10) == -1)
        errExit("write 2");
}

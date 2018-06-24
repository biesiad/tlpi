#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int
main(int argc, char *argv[])
{
    int outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    if (argc == 3 && strcmp(argv[2], "-p")) {
        openFlags = O_CREAT | O_WRONLY | O_APPEND;
        outputFd = open(argv[2], openFlags, filePerms);

        if (outputFd == -1)
            errExit("opening file %s", argv[2]);
    } else {
        openFlags = O_CREAT | O_WRONLY | O_TRUNC;
        outputFd = open(argv[1], openFlags, filePerms);

        if (outputFd == -1)
            errExit("opening file %s", argv[2]);
    }

    // read from STDIN
    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
        // write to the file
        if (write(outputFd, buf, numRead) != numRead)
            fatal("couldn't write whole buffer");

        // write to STDOUT
        if (write(STDOUT_FILENO, buf, numRead) != numRead)
            fatal("couldn't write whole buffer");
    }

    if (numRead == -1)
        errExit("read");

    if (close(outputFd) == -1)
        errExit("close output");

    exit(EXIT_SUCCESS);
}

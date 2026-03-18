#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>

void init_hugepage(void) {
    const char* path = "/sys/kernel/mm/hugepages/hugepages-1048576kB/nr_hugepages";
    const char* hp_req = "1\n";

    printf("Allocating hugepage...\n");
    int32_t fd = open(path, O_WRONLY);
    if (fd == -1) {
        fprintf(stderr, "init_hugepage: open() failed\n");
        exit(1);
    }

    ssize_t n = write(fd, hp_req, 2);
    if (n == -1) {
        fprintf(stderr, "init_hugepage: write() failed\n");
        close(fd);
        exit(1);
    }

    close(fd);
}

int __attribute__((weak)) main(void) {
    init_hugepage();
    printf("Done.\n");
}

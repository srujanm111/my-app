#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#define INVALID ((void*)0xaaaaaaaaaaaaaaaa)

static void test(int fd, void *buf, size_t count) {
    ssize_t ret = read(fd, buf, count);
    printf("ret\t%d\t%p\t%zu\tresult=%zd, errno=%d\n", fd, buf, count, ret, errno);
}

int main(void) {
    // to test EOF behaviors, vary the size of `asd.txt` accordingly
    int fd = open("asd.txt", O_RDONLY);
    if (fd < 0) {
        perror("open\n");
        return 1;
    }
    test(-1, NULL, 0);
    test(-1, NULL, 8);
    test(-1, INVALID, 0);
    test(-1, INVALID, 8);
    test(fd, INVALID, 0);
    test(fd, INVALID, 8);
    test(fd, NULL, 0);
    test(fd, NULL, 8);
    return 0;
}
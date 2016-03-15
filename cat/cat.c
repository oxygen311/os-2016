#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

int const BUF_SIZE = 1024;

int main(int argc, char **argv) {
    char buf[BUF_SIZE];
    int read_len;
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("OPEN ERROR\nBut you can write in console");
        fd = 0;
    }

    while (1) {
        read_len = read(fd, buf, BUF_SIZE);
        if (read_len == 0) {
            break;
        }
        if (read_len < 0) {
            if (errno == EINTR) {
                perror("Error");
                continue;
            } else
                return read_len;
        }
        int cur_len = 0;
        while (read_len - cur_len > 0) {
            int wr_len = write(1, buf + cur_len, read_len - cur_len);
            if (wr_len < 0) {
                if (errno == EINTR) {
                    perror("Error");
                    continue;
                }
                else {
                    return wr_len;
                }
            }
            cur_len += wr_len;
        }
    }
    return 0;
}

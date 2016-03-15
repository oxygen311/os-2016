#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

int const BUF_SIZE = 1024;

int main(int argc, char **argv) {
    char buf[BUF_SIZE];
    int i;
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("OPEN ERROR\nBut you can write in console");
        fd = 0;
    }

    while (i = read(fd, buf, BUF_SIZE)) {
        if (i < 0) {
            if (errno == EINTR) {
                perror("Error");
                continue;
            }
            else
                return i;
        }

        int wr = write(1, buf, i);
        if (wr < 0) {
            if (errno == EINTR) {
                perror("Error");
                continue;
            }
            else
                return wr;
        }
    }


    return 0;
}

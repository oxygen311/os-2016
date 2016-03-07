#include <unistd.h>
int const BUF_SIZE = 1024;

int main() {
  char buf[BUF_SIZE];
  int i;
  while ((i = read(0, buf, BUF_SIZE)) > 0)
    write(1, buf, i);
  return 0;
}

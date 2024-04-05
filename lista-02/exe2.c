#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  pid_t f1, f2;

  f1 = fork();
  if (f1 != 0) {
    f2 = fork();
    if (f2 == 0) {
      puts("F");
      puts("P");
    } else {
      puts("R");
      puts("Z");
    }
  } else {
    puts("S");
    puts("Q");
  }
  return 0;
}

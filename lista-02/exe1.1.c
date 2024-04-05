#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t child_pid[3];
  int i;

  printf("Pai A; PID: %d; PID pai: %d\n", getpid(), getppid());

  for (i = 0; i < 3; i++) {
    child_pid[i] = fork();

    if (child_pid[i] == 0) {
      char letter = 'B' + i;
      printf("Fio %c; PID: %d; PID Pai: %d\n", letter, getpid(), getppid());
      return 0;
    } else if (child_pid[i] < 0) {
      fprintf(stderr, "Fork failed\n");
      return child_pid[i];
    }
  }

  // Parent process waits for all child processes to terminate, to avoid
  // orphaned processes
  for (i = 0; i < 3; i++) {
    int status;
    waitpid(child_pid[i], &status, 0);
  }

  return 0;
}

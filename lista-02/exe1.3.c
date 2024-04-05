#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t child_pid[4];
  int i;

  printf("Pai A; PID: %d; PID Pai: %d\n", getpid(), getppid());
  child_pid[0] = fork();

  if (child_pid[0] == 0) {
    printf("Fio B; PID: %d; PID Pai: %d\n", getpid(), getppid());
    return 0;
  } else {
    child_pid[1] = fork();
    if (child_pid[1] == 0) {
      printf("Fio C; PID: %d; PID Pai: %d\n", getpid(), getppid());
      child_pid[2] = fork();
      if (child_pid[2] == 0) {
        printf("Fio D; PID: %d; PID Pai: %d\n", getpid(), getppid());
        return 0;
      } else {
        child_pid[3] = fork();
        if (child_pid[3] == 0) {
          printf("Fio E; PID: %d; PID Pai: %d\n", getpid(), getppid());
          return 0;
        }
      }
    }
  }

  // Parent process waits for all child processes to terminate, to avoid
  // orphaned processes
  for (i = 0; i < 4; i++) {
    int status;
    waitpid(child_pid[i], &status, 0);
  }

  return 0;
}

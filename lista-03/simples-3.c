#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

void *square(void *arg) {
  long tid = (long)arg;
  long squared_num = tid * tid;

  pthread_exit((void *)squared_num);
}

int main(int argc, char **argv) {
  pthread_t threads[NUM_THREADS];
  int rc;
  long t;
  void *thread_return;

  for (t = 0; t < NUM_THREADS; t++) {
    printf("Nova thread: %ld\n", t);
    rc = pthread_create(&threads[t], NULL, square, (void *)t);
    if (rc) {
      printf("ERRO - rc = %d\n", rc);
      exit(-1);
    }

    rc = pthread_join(threads[t], &thread_return);
    printf("Quadrado: %ld\n", (long)thread_return);
  }
  pthread_exit(NULL);
}

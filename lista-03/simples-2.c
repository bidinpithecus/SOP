#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

void* PrintHello(void *arg) {
  long tid = (long)arg;
  printf("Thread %ld\n", tid);
  pthread_exit(NULL);
}

void* PrintSquare(void* arg) {
  long tid = (long)arg;
  printf("Thread %ld;\tQuadrado: %ld\n", tid, tid * tid);
  pthread_exit(NULL);
}

int main (int argc, char **argv) {
  pthread_t threads[NUM_THREADS];
  pthread_t threads_2[NUM_THREADS + 3];
  int rc;
  long t;

  for (t = 0; t < NUM_THREADS + 3; t++) {
    printf("Nova thread de quadrado: %ld\n", t);
    rc = pthread_create(&threads_2[t], NULL, PrintSquare, (void *)t);
    if (rc) {
      printf("ERRO - rc = %d\n", rc);
      exit(-1);
    }

    if (t < NUM_THREADS) {
      printf("Nova thread normal: %ld\n", t);
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
      if (rc) {
        printf("ERRO - rc = %d\n", rc);
        exit(-1);
      }
    }
  }
  pthread_exit(NULL);
}

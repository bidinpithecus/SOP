#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define T_PAR 1
#define T_IMPAR 2

#define NELEM 2000000

int v[NELEM] = {0};

int conta(void* arg) {
  int i, total = 0;

  for (i = 0; i < NELEM; i++) {
    if ((arg == T_PAR) && ((v[i] % 2) == 0))
      total++;
    else if ((arg == T_IMPAR) && ((v[i] % 2) != 0))
      total++;
  }
  return total;
}

int main(int argc, char *argv[]) {
  int vetor[NELEM], i, pares, impares, rc;
  struct timeval tv_ini, tv_fim;
  unsigned long time_diff, sec_diff, usec_diff, msec_diff;

  srandom(time(NULL));
  for (i = 0; i < NELEM; i++) {
    vetor[i] = (int)random();
  }

  /* marca o tempo de inicio */
  rc = gettimeofday(&tv_ini, NULL);
  if (rc != 0) {
    perror("erro em gettimeofday()");
    exit(1);
  }

  /* faz o processamento de interesse */
  pares = conta((void*)T_PAR);
  impares = conta((void*)T_IMPAR);

  /* marca o tempo de final */
  rc = gettimeofday(&tv_fim, NULL);
  if (rc != 0) {
    perror("erro em gettimeofday()");
    exit(1);
  }
  /* calcula a diferenca entre os tempos, em usec */
  time_diff = (1000000L * tv_fim.tv_sec + tv_fim.tv_usec) -
              (1000000L * tv_ini.tv_sec + tv_ini.tv_usec);
  /* converte para segundos + microsegundos (parte fracionaria) */
  sec_diff = time_diff / 1000000L;
  usec_diff = time_diff % 1000000L;

  /* converte para msec */
  msec_diff = time_diff / 1000;

  printf("O vetor tem %d numeros pares e %d numeros impares.\n", pares,
         impares);
  printf("Tempo de execucao: %lu.%03lu mseg\n", msec_diff, usec_diff % 1000);
  return 0;
}

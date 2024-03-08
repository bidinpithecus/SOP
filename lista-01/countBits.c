#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Insira um numero como argumento da execucao\n");
    return 1;
  }

  const int original_num = atoi(argv[1]);
  int num = original_num;
  int bit_count = 0;

  while (num != 0) {
    bit_count += num & 1;
    num >>= 1;
  }

  printf("O numero %d possui %d bits em 1\n", original_num, bit_count);

  return 0;
}

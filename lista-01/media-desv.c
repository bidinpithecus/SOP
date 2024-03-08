#include <stdio.h>
#include <math.h>

int main() {
  int numero;
  int quantidade = 0;
  long long soma = 0;
  long long soma_quadrados = 0;
  double media, desvio_padrao;

  printf("Digite uma sequência de números inteiros (digite -1 para terminar):\n");

  while (1) {
    scanf("%d", &numero);

    if (numero == -1) break;

    quantidade++;
    soma += numero;
    soma_quadrados += numero * numero;
  }

  if (quantidade == 0) {
    printf("Nenhum número foi inserido.\n");
    return 1;
  }

  media = (double)soma / quantidade;
  desvio_padrao = sqrt((double)soma_quadrados / quantidade - media * media);

  printf("Média: %.2lf\n", media);
  printf("Desvio padrão: %.2lf\n", desvio_padrao);

  return 0;
}

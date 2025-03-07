#include <stdio.h>

int main () {

  int n; //numero dado pelo usuario (n!)
  int fat; //fatorial do numero
  int num = 0; //numero dado ao usuario
  int i;
    
  printf("Digite o numero:");
  scanf("%d", &n);
  num = n;

  for (i = n-1;i > 1; i--) {
    fat = n * i;
    n = fat;
  }

  printf("o fatorial de %d eh %d: ",num,fat);

  return 0;

}
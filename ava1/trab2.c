#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tmatrixdin{
  int linhas;
  int colunas;
  double **dadosmat;
} tma;

double aleatorio(int min, int max){
  double r;
  r = (double) rand()/RAND_MAX;
  return (double)(min + r*(max-min));
}

tma *geraMatriz(int lin, int col, double min, double max){
  
  double **mat = (double **) malloc(lin * sizeof(double *));

  for (int i = 0; i < lin; i++) {
        mat[i] = (double *) malloc(col * sizeof(double));
    }
  
  for (int i = 0; i < lin; i++) {
      for (int j = 0; j < col; j++) {
        mat[i][j] = aleatorio(min, max);
      }
  }
  
  tma *matriz = (tma *) malloc(sizeof(tma));
  matriz->linhas = lin;
  matriz->colunas = col;
  matriz->dadosmat = mat;
    
  return matriz;
}

void salvaMat(char *nomeArq, tma *m){
  FILE *arq = fopen(nomeArq, "w");
  
  for (int i = 0; i < m->linhas ; i++) {
    for (int j = 0; j < m->colunas; j++) {
      
        fprintf(arq, "%.2lf ", m->dadosmat[i][j]);
      }
    fprintf(arq, "\n");
  }
}

int main(void) {

  int linhas, colunas, minimo, maximo;
  
  printf("Digite o número de linhas e colunas da matriz: ");
  scanf("%d %d", &linhas, &colunas);

  printf("Digite a faixa que os valores tem que ter dentro da matriz: ""minimo"" ""maximo"" ");
  scanf("%d %d", &minimo, &maximo);
  
  tma *matriz = geraMatriz(linhas, colunas, minimo, maximo);

  salvaMat("saidaExerc2.txt", matriz);
  
  return 0;
}
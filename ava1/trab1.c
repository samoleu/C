#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Veiculo{
    char placa[50];
    char modelo[50];
    char marca[50];
    char quilometragem[50];
}Veiculo;

Veiculo* loadBdveiculos(char *nomearq){
    FILE *arq = fopen(nomearq, "r");
    Veiculo *vec;
  
    int i = 0;

    char linha[50] = {};

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return NULL;
    }
  
    vec = (Veiculo*) malloc(150 *sizeof(Veiculo));

    if (vec == NULL) {
        printf("Erro ao alocar memoria\n");
        fclose(arq);
        return NULL;
    }

    while (fgets(linha, 100, arq) != NULL) {
      
      sscanf(linha, "%s/", vec[i].placa);
      fgets(linha, 100, arq);
      sscanf(linha, "%s",vec[i].modelo);
      fgets(linha, 100, arq);
      sscanf(linha, "%s",vec[i].marca);
      fgets(linha, 100, arq);
      sscanf(linha, "%s",vec[i].quilometragem);
        
      i++;
    }
  
    fclose(arq);

    return vec;
}

void filtro(Veiculo *vec, char *marcaReq){

  char nomeArquivo[50];
  int i =0;

  strcat(nomeArquivo,marcaReq);
  strcat(nomeArquivo,".txt");
  
  FILE *arqSaida = fopen(marcaReq, "w");
  
  for (i = 0; i < 150; i++) {
        if (strcmp(vec[i].marca, marcaReq) == 0) {
            fprintf(arqSaida, "%s,%s,%s,%s\n", vec[i].placa, vec[i].modelo, vec[i].marca, vec[i].quilometragem);
        }
    }
  fclose(arqSaida);
}


int main(){
  char *marcas[4] = {"FIAT", "TOYOTA", "FORD", "RENAULT"};
  
  char nomearq[] = "bdveiculos.txt";
  Veiculo* vec = loadBdveiculos(nomearq);

  
  for (int i = 0; i < 4; i++) {
        filtro(vec, marcas[i]);
    }
  
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tadhm.h"
#include "tadlista.h"

t_hashmap carregadi(char *nomearq){
	t_hashmap hm = cria_hm_tam(250);
	//t_hashmap teste = cria_hm_tam();
	char linha[1024];
	char *chave;
	char *item;
	char *token;
	FILE *arquivo = fopen(nomearq, "r");
    while (!feof(arquivo)) {
		fgets(linha,1024,arquivo);
		chave = (char *)malloc(64 * sizeof(char));
		item = (char *)malloc(64 * sizeof(char));
        linha[strcspn(linha, "\n")] = '\0';
        token = strtok(linha, ",");
		strcpy(chave,token);
        while (token != NULL) {
            strcpy(item,token);
            token = strtok(NULL, ",");
			
        }
		addDado(hm,chave,item);
		printf("%s | %s\n",chave,item);
    }

    fclose(arquivo);
	return hm;
}

/*t_hashmap invertedi(t_hashmap paramdi){
	
	
	return hm;
}

t_hashmap combinadi(t_hashmap diA, t_hashmap diB){
	
	
	return hm;
}

t_hashmap salvadi(t_hashmap di, char *nomearq){
	
	
	return hm;
}
*/
int main(){
	char *teste;
	teste = (char *)malloc(64 * sizeof (char));
	t_hashmap dic = carregadi("di-pt-en.txt");
	teste = getDado(dic,"publico");
	if (teste == NULL){
		puts("Palavra não encontrada. Tente novamente!!");
	}
    else {
		// printf("\nPalavra: %s",teste);
	}
	
	
	return 0;
}
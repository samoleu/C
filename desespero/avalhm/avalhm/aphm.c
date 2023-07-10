/*  CODIGO FEITO POR: PEDRO TAVARES (20222bsi0032) e SAMUEL FERREIRA (20221bsi0480)  */

#include "tadlista.h"
#include "tadhm.h"
#include <stdio.h>
#include <string.h>


t_hashmap carregadi(char *nomearq) {
    
    FILE *arquivo = fopen(nomearq, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!!\n");
        return NULL; 
    }
    t_hashmap dicionario = cria_hm_tam(256);

    char linha[64];
    int i=1;
    
    while (!feof(arquivo)) {

        fgets(linha,64,arquivo);
            
        linha[strcspn(linha, "\n")] = '\0';

        char* chave = (char*)malloc(sizeof(char)*32);
        char* valor = (char*)malloc(sizeof(char)*32);
        
        char* token;
        token = strtok(linha, ",");
        strcpy(chave, token);
        token = strtok(NULL, ",");
        strcpy(valor, token);

        dicionario = addDado(dicionario, chave, valor);
        
        i++;
    }
    
    fclose(arquivo);

    return dicionario;
}


t_hashmap invertedi(t_hashmap dicionario){
    
    Lista chaves = keys(dicionario);
    t_hashmap dic_invertido = cria_hm();

    for (int i=0; i< lenLista(chaves); i++){
        addDado(dic_invertido, getDado(dicionario, dadoLista(chaves,i)) , dadoLista(chaves,i));
    }
    return dic_invertido;
}


t_hashmap combinadi(t_hashmap dicA,   t_hashmap dicB) {
    
    Lista chaves_dicA = keys(dicA);
    Lista chaves_dicB = keys(dicB);

    t_hashmap dic_combinado = cria_hm();
    /* Verifica se os dicionarios tem as mesmas chaves, enquanto combina os mesmos */
    for(int i=0; i< lenLista(chaves_dicA); i++) {
        for(int j=0; j< lenLista(chaves_dicB); j++) {           
            
            int boolean = strcmp(dadoLista(chaves_dicA,i), dadoLista(chaves_dicB,j));  

            if(boolean == 0) { 
                dic_combinado = addDado( dic_combinado, getDado(dicA, dadoLista(chaves_dicA,i)),  getDado(dicB, dadoLista(chaves_dicB,j)));
            }
        }
    } 
    return dic_combinado;
}

t_hashmap salvadi(t_hashmap dicionario, char *nomearq){
    FILE *arquivo = fopen(nomearq, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!!\n");
        return NULL; 
    }
    Lista chaves_dic = keys(dicionario);
    for(int i=0; i< lenLista(chaves_dic); i++) {
        
        char* palavra = dadoLista(chaves_dic, i);
        palavra = strcat(strcat( strcat(palavra,","), getDado(dicionario, dadoLista(chaves_dic, i))),"\n");
        fputs(palavra,arquivo);
    }
    fclose(arquivo);
    return dicionario;
}

int main() {

    /* parte I */
    t_hashmap dic_PT_EN = carregadi("di-pt-en.txt");
    t_hashmap dic_PT_FR = carregadi("di-pt-fr.txt");
    t_hashmap dic_PT_ES = carregadi("di-pt-es.txt");

    /* parte II */
    t_hashmap dic_EN_PT = invertedi(dic_PT_EN);
    t_hashmap dic_FR_PT = invertedi(dic_PT_FR);
    t_hashmap dic_ES_PT = invertedi(dic_PT_FR);
    
    t_hashmap dic_EN_FR = combinadi(dic_PT_EN,dic_PT_FR);
    t_hashmap dic_ES_FR = combinadi(dic_PT_ES,dic_PT_FR);
    t_hashmap dic_FR_ES = combinadi(dic_PT_FR,dic_PT_ES);

    /* parte III */
    t_hashmap dic_Master = cria_hm();
    addDado(dic_Master, "pt-en", dic_PT_EN);
    addDado(dic_Master, "pt-fr", dic_PT_FR);
    addDado(dic_Master, "pt-es", dic_PT_ES);
    addDado(dic_Master, "en-pt", dic_EN_PT);
    addDado(dic_Master, "en-fr", dic_EN_FR);
    addDado(dic_Master, "es-pt", dic_ES_PT);
    addDado(dic_Master, "es-fr", dic_ES_FR);
    addDado(dic_Master, "fr-es", dic_FR_ES);
    addDado(dic_Master, "fr-pt", dic_FR_PT);
    
    /* parte IV */
    printf("----------------------------------------------");
    while(1){
        
        char idiomaRaiz[4] = "";
        char idiomaAlvo[4] = ""; 
        char palavra[32] = "";
        
        
        printf("\nED TRANSLATOR VERS%cO 1.0",199);
        printf("\nCASO QUEIRA SAIR A QUALQUER MOMENTO ESCREVA - [FIM]");
        printf("\nTRADUZIR DO IDIOMA (pt,en,fr,es): ");
        scanf("%s",idiomaRaiz);
        if(strcmp(idiomaRaiz,"FIM") == 0) {printf("aa"); break;}
        printf("PARA O IDIOMA(pt,en,fr,es): ");
        scanf("%s",idiomaAlvo);
        if(strcmp(idiomaAlvo,"FIM") == 0) {printf("bb"); break;}
        printf("ENTRE COM A PALAVRA TRADU%c%cO: ",128,199);
        scanf("%s",palavra);
        if(strcmp(palavra,"FIM") == 0) {printf("cc"); break;}
        
        t_hashmap dicionario_usuario = getDado(dic_Master, strcat(strcat(idiomaRaiz,"-"),idiomaAlvo));

        if(getDado(dicionario_usuario, palavra) != NULL)
            printf("\nTRADU%c%cO: %s",128, 199, getDado(dicionario_usuario, palavra));
        else
            printf("\nTRADU%c%cO: %s",128, 199, "Palavra nao existe");
        printf("\n----------------------------------------------");
    }

    return 0;
}
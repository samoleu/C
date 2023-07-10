#include "tadlista.h"
#include "tadhm.h"

int fh3 (char *palavra, int tam_vet_armazenam) {
    int soma = 0;
    for (int i = 0; i<strlen(palavra);i++) {
        soma = soma * i + palavra[i] * (i+1);
    }
    return soma % tam_vet_armazenam;
}

t_hashmap cria_hm(){
    t_hashmap hashmap = malloc(sizeof(struct cabec_hm));
	hashmap->vet_lista = malloc (sizeof(Lista) * TAM_VET_ARMAZENAM);
	hashmap->tam_vet_lista = TAM_VET_ARMAZENAM;
	
    for(int i = 0; i < TAM_VET_ARMAZENAM; i++) {
        hashmap->vet_lista[i] = NULL;
    }
    return hashmap;
}

t_hashmap cria_hm_tam(int quant_dados){
    long tam_vet_armazem = quant_dados/FATOR_DE_CARGA;
	t_hashmap hashmap = malloc(sizeof(struct cabec_hm));
    hashmap->vet_lista = malloc(sizeof(Lista) * tam_vet_armazem);
	hashmap->tam_vet_lista = tam_vet_armazem;
	
    for(int i = 0; i < tam_vet_armazem; i++) {
        hashmap->vet_lista[i] = NULL;
    }
    return hashmap;
}

t_item getItem (t_hashmap t_hashmap, char *key){
    long num_hash = fh3(key,t_hashmap->tam_vet_lista);
    
    if(t_hashmap->vet_lista[num_hash] == NULL) { return NULL; }    
    else{
        Lista lista = t_hashmap->vet_lista[num_hash];
        t_item item = NULL;
        int i = 0;
        for (i=0;i<lenLista(lista);i++){
            item = dadoLista(lista,i);
            if(strcmp(item->key,key) == 0)
                break;
        }
        
        if(i<lenLista(lista)) { return item; }
        else { return NULL; }
    }
}

t_hashmap addDado(t_hashmap t_hashmap, char *key, t_dado dado){
    t_item item;

    long num_hash = fh3(key,t_hashmap->tam_vet_lista);
    item = getItem(t_hashmap, key);

    if (item == NULL) {
        item = malloc(sizeof(struct tipo_item));
        item->key = key;
        item->valor = dado;
        if(t_hashmap->vet_lista[num_hash] == NULL)
            t_hashmap->vet_lista[num_hash] = criaLista();
        appendLista(t_hashmap->vet_lista[num_hash],item);
    }
    else { item->valor = dado; }
	
    return t_hashmap;
}

t_dado getDado (t_hashmap t_hashmap, char *key){
    t_item item = getItem(t_hashmap, key);
    
    if (item == NULL) { return NULL; }     
    else { return item->valor; }
        
}

Lista keys (t_hashmap t_hashmap){
    
    Lista lista = criaLista();
    for (int i = 0; i < t_hashmap->tam_vet_lista;i++){
        if(t_hashmap->vet_lista[i] != NULL){
            for(int j = 0; j < lenLista(t_hashmap->vet_lista[i]); j++){
                t_item item = dadoLista(t_hashmap->vet_lista[i],j);
                appendLista(lista,item->key);
            }
        }
    }
    return lista;
}
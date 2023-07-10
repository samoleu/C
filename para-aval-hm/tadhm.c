#include "tadlista.h"
#include "tadhm.h"

int fh3 (char *s, int d){
    int soma = 0;
    for (int i = 0; i<strlen(s);i++){
        soma = soma * i + s[i] * (i+1);
    }
    return soma%d;
}
t_hashmap cria_hm(){
    t_hashmap hm = malloc(sizeof(struct cabec_hm));
	hm->vet_lista = malloc (sizeof(Lista) * TAM_VET_ARMAZENAM);
	hm->tam_vet_lista = TAM_VET_ARMAZENAM;
	
    for(int i = 0; i < TAM_VET_ARMAZENAM; i++)
        hm->vet_lista[i] = NULL;
    return hm;
}

t_hashmap cria_hm_tam(int quant_dados){
    long tam_vet_armazen = quant_dados/FATOR_DE_CARGA;
	t_hashmap hm = malloc(sizeof(struct cabec_hm));
    hm->vet_lista = malloc(sizeof(Lista) * tam_vet_armazen);
	hm->tam_vet_lista = tam_vet_armazen;
	
    for(int i = 0; i < tam_vet_armazen; i++)
        hm->vet_lista[i] = NULL;
    return hm;
}
t_item getItem (t_hashmap hm, char *k){
    long h = fh3(k,hm->tam_vet_lista);
    if(hm->vet_lista[h] == NULL){
        return NULL;
	}
    else{
        Lista lst = hm->vet_lista[h];
        t_item it = NULL;
        int i = 0;
        for (i=0;i<lenLista(lst);i++){
            it = dadoLista(lst,i);
            if(strcmp(it->key,k) == 0)
                break;
        }
        if(i<lenLista(lst)){
            return it;
		}
        else{
            return NULL;
        }
    }

}
t_hashmap addDado(t_hashmap hm, char *k, t_dado dado){
    t_item it;
    
    long h = fh3(k,hm->tam_vet_lista);
    it = getItem(hm, k);
    if (it == NULL){
        it = malloc(sizeof(struct tipo_item));
        it->key =k;
        it->valor = dado;
        if(hm->vet_lista[h] == NULL)
            hm->vet_lista[h] = criaLista();
        appendLista(hm->vet_lista[h],it);
    }
    else{
        it->valor = dado;
    }
	return hm;
}

t_dado getDado (t_hashmap hm, char *k){
    t_item it = getItem(hm, k);
    if (it == NULL)
        return NULL;
    else
        return it->valor;
}



Lista keys (t_hashmap hm){
    Lista lst = criaLista();
    for (int i = 0; i < hm->tam_vet_lista;i++){
        if(hm->vet_lista[i] != NULL){
            for(int j = 0; j < lenLista(hm->vet_lista[i]); j++){
                t_item it = dadoLista(hm->vet_lista[i],j);
                appendLista(lst,it->key);
            }
        }
    
    }
    return lst;
}
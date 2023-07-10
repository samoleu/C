#include "tadlista.h"
#include <stdio.h>
#include <stdlib.h>

int lenLista(Lista lst){
   return lst->tamlista;
}

Lista criaLista(void) {
    Lista a = (Lista)malloc(sizeof(tcabec));
    if (a == NULL) return NULL;
    a->prim = NULL;
    a->ult = NULL;
    a->tamlista = 0;
    return a;
}

Lista appendLista(Lista lst,t_dado dado) {
    
    tnoh nonovo = (tnoh)malloc(sizeof(struct tipo_noh));
    if (nonovo == NULL) return NULL;

    nonovo->dado = dado;

    if (lst->tamlista == 0) {
        nonovo->ant = NULL;
        lst->prim = nonovo;
        lst->ult = nonovo;
    } 
    else {
        lst->ult->prox = nonovo;
        nonovo->ant = lst->ult;
        lst->ult = nonovo;
    }
    nonovo->prox = NULL;
    lst->tamlista += 1;
    return lst;
}

Lista insereLista(Lista lst, t_dado dd, int pos) {

    if (pos > lst->tamlista || pos < 0) {
        return NULL; }
    if(lst->tamlista == 0 || pos == lst->tamlista+1) {
        lst = appendLista(lst,dd);
        return lst;
    }
    else  {
        tnoh index = lst->prim;
        
        for (int i = 0; i < pos; i++) {
            if (index == NULL) {
                return NULL;
                }

            index = index->prox;
        }
    
        tnoh nonovo = (tnoh)malloc(sizeof(struct tipo_noh));
        
        if (nonovo == NULL) { return NULL; }
        if (pos == 0) {

        nonovo->dado = dd;
        nonovo->ant = NULL;
        nonovo->prox = index;
        index->ant = nonovo;
        lst->prim = nonovo;
        }
        else {
        nonovo->dado = dd;
        nonovo->ant = index->ant;
        nonovo->prox = index;
        (index->ant)->prox = nonovo;
        index->ant = nonovo;
        }
        lst->tamlista += 1;
    }
    return lst;
}

t_dado dadoLista(Lista lst, int pos) {
  
    if (pos > lst->tamlista || pos < 0)
        return NULL;

    tnoh index = lst->prim;
    if (index == NULL) return NULL;

    for (int i = 0; i < pos; i++) {
        index = index->prox;
        if (index == NULL) return NULL;
    }
    return index->dado;
}

t_dado removeLista(Lista lst, int pos) {
    
    if (pos > lst->tamlista || pos < 0) {
        return lst;
    }

    tnoh index = lst->prim;
    t_dado dado_removido = NULL;

    for (int i = 0; i < pos; i++) {
        if (index == NULL) {
            return NULL;
            }
        index = index->prox;
    }
    if (pos == 0) {
        index->prox->ant = index->ant;
        lst->prim = index->prox;
        lst->tamlista--;
        dado_removido = lst->prim->dado;
        free(index);
        return dado_removido;
    }
    if (pos == lst->tamlista-1) {
        index->ant->prox = index->prox;
        lst->ult = index->ant;
        dado_removido = lst->ult->dado;
        lst->tamlista--;
        free(index);
        return dado_removido;
    }
    else {
        index->prox->ant = index->ant;
        index->ant->prox = index->prox;
        dado_removido = index->dado;
        lst->tamlista--;
        free(index);
        return dado_removido;
    }

}

Lista limpaLista(Lista lst) {
    if (lst->tamlista == 0) {
        return lst;
    }
    tnoh index = lst->prim;

    for (int i = 0; i < lst->tamlista; ++i) {

        free(index->dado);
        index = index->prox;
        free(index->ant);

        if (i == lst->tamlista-1) {
            free(index->dado);
            free(index);
        }
    }

    lst->tamlista = 0;
    lst->prim = NULL;
    lst->ult = NULL;

    return lst;
}

Lista destroiLista(Lista lst) {
    lst = limpaLista(lst);
    free(lst);
    return NULL;
}




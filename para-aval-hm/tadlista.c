#include <stdlib.h>
#include "tadlista.h"

int lenLista(Lista lst){
	return lst -> tamlista;
}
Lista criaLista (){
	//Inicializando uma lista
	Lista lst = NULL;
	// Inicializando uma lista vazia
	lst = (tcabec *)malloc(sizeof(tcabec));
	lst -> tamlista = 0;
	lst -> prim = NULL;
	lst -> ult = NULL;
	return lst;
}

//Função para adicionar elemento ao final da lista
Lista appendLista(Lista lst, t_dado d){
	tnoh no = (tnoh)malloc(sizeof(tnoh));
		no -> dado = d;
		no -> prox = NULL;
	if (lenLista(lst) == 0){
		no -> ant = NULL;
		lst -> prim = no;
		lst -> ult = no;
		(lst->tamlista)++;
	}
	else {
		no -> ant = lst -> ult;
		lst -> ult -> prox = no;
		lst -> ult = no;
		(lst->tamlista)++;
	}

	return lst;
}

Lista insereLista(Lista lst, t_dado dd, int pos){
	if((pos < 0) || (pos > ((lst->tamlista))))
		return NULL;
	else if(lst->tamlista == 0 || pos == ((lst->tamlista)))
		appendLista(lst, dd);
	else if(pos == 0){
		tnoh no = (tnoh )malloc(sizeof(tnoh));
		no -> dado = dd;
		no -> prox = lst->prim;
		no -> ant = NULL;
		lst->prim->ant = no;
		lst->prim = no;
		(lst->tamlista)++;
	}
	else{
		tnoh aux = lst->prim;
		for (int i = 0; i < pos; i++)
			aux = aux->prox;
		tnoh no = (tnoh)malloc(sizeof(tnoh));
		no -> dado = dd;
		no -> prox = aux;
		no -> ant = aux -> ant;
		aux -> ant -> prox = no;
		aux -> ant = no;
		(lst->tamlista)++;
	}
	return lst;
}
t_dado dadoLista(Lista lst, int pos){
	tnoh cursor;
	if((pos < 0 ) ||(pos >= lst->tamlista))
		return NULL;
	cursor = lst -> prim;
	for (int contpos = 0; contpos < pos; contpos++)
		cursor = cursor -> prox;
	return (cursor -> dado);
}

t_dado removeLista(Lista lst, int pos){
	if((pos < 0) || (pos >= lst->tamlista)){
		return NULL;
	}
	
	t_dado bkp = lst->prim->dado;
	if(lst->tamlista == 1){
		//Quando só tem um item na lista
		
		free(lst->prim);
		lst->prim = NULL;
		lst->ult = NULL;
	}
	else if(pos == 0){
		// Retira a primeira posição, mas ela não é a única posição da lista
		lst->prim = lst->prim->prox;
		free(lst->prim->ant);
		
		lst->prim->ant = NULL;
		
	}
	else if(pos == (lst->tamlista)-1){
		//Retirar a última posição, mas ela não é a única posição da lista
		bkp = lst->ult->dado;
		
		lst->ult = lst->ult->ant;
		free(lst->ult->prox);
		lst->ult->prox = NULL;
	}
	else{
		//Retirar uma posição do meio da lista
		tnoh aux = lst->prim;
		for(int i = 0; i < pos; i++){
			aux = aux->prox;
		}
		
		bkp = aux->dado;
		
		tnoh antes = aux->ant;
		tnoh depois = aux->prox;
		
		antes->prox = depois;
		depois->ant = antes;
		
		free(aux);
	}
	
	(lst->tamlista)--;
	
	return bkp;
}

Lista limpaLista(Lista lst)
{
    for (int i = lenLista(lst); i >= 0; i--)
        free(removeLista(lst, i));
    return lst;
}

Lista destroiLista(Lista lst)
{
    limpaLista(lst);
    free(lst);
    return NULL;
}
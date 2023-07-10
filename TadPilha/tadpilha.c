#include "./tadpilha.h"

Pilha criaPilha(){
  return criaLista();
}

Pilha push(Pilha p, t_dado dd){
  appendLista(p,dd);
  return p;
}

t_dado pop(Pilha p){
  t_dado dado = removeLista(p,lenLista(p)-1);
  return dado;
}

t_dado pickPilha(Pilha p){
  t_dado dado = dadoLista(p,lenLista(p)-1);
  return dado;
}

int pilhaVazia(Pilha p){
  return lenLista(p) == 0;
}

Pilha destroiPilha(Pilha p){
  destroiLista(p);
  return NULL;
}
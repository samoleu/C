#ifndef ___BSI_ED_2023_1___PILHA

#define ___BSI_ED_2023_1___PILHA

#include "./tadlista.h"

typedef Lista Pilha;

Pilha criaPilha();
Pilha push(Pilha p, t_dado dd);
t_dado pop(Pilha p);
t_dado pickPilha(Pilha p);
int pilhaVazia(Pilha p);
Pilha destroiPilha(Pilha p);

#endif
#include "tadlista.h"
#include <stdio.h>
#include <stdlib.h>

typedef void *t_dado;

typedef struct tipo_noh {
  struct tipo_noh *ant;
  struct tipo_noh *prox;
  t_dado dado;
} *tnoh;

typedef struct {
  int tamlista;
  tnoh prim;
  tnoh ult;
} tcabec;

typedef tcabec *Lista;

typedef Lista Pilha;

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
        dado_removido = index->prox->dado;
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

char precedence(char op) {
    if (strcmp(op,"+") || strcmp(op,"-")) {
        return 1;
    }
    if (strcmp(op,"*") || strcmp(op,"/")) {
        return 2;
    }
    return 0;
}

int applyOp(int a, int b, char op) {
    if (strcmp(op,"+")) return a + b;
    if (strcmp(op,"-")) return a - b;
    if (strcmp(op,"*")) return a * b;
    if (strcmp(op,"/")) return a / b;
}

int isdigit(char c) {
    int i = 0;
    while (i < 10) {
        if (strcmp(c,(char)i) == 0 ) {
            return 0;
        }  
        i++; 
    }
    return 1;
}

int evaluate(char* tokens) {
    Pilha values = criaPilha();
    Pilha ops = criaPilha();
    int i = 0;

    while (tokens[i] != '\0') {
        if (strcmp(tokens[i], ' ')) {
            i++;
            continue;
        } else if (strcmp(tokens[i],'(')) {
            push(ops, (t_dado)'(');
        } else if (isdigit(tokens[i])) {
            int val = 0;
            while (isdigit(tokens[i])) {
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }
            push(values, (t_dado)val);
            i--;
        } else if (tokens[i] == ')') {
            while (!pilhaVazia(ops) && *(char*)pickPilha(ops) != '(') {
                int val2 = (int)pop(values);
                int val1 = (int)pop(values);
                char op = *(char*)pop(ops);
                push(values, (t_dado)applyOp(val1, val2, op));
            }
            pop(ops); // descartar o '('
        } else {
            while (!pilhaVazia(ops) && precedence(*(char*)pickPilha(ops)) >= precedence(tokens[i])) {
                int val2 = (int)pop(values);
                int val1 = (int)pop(values);
                char op = *(char*)pop(ops);
                push(values, (t_dado)applyOp(val1, val2, op));
            }
            push(ops, (t_dado)tokens[i]);
        }
        i++;
    }

    while (!pilhaVazia(ops)) {
        int val2 = (int)pop(values);
        int val1 = (int)pop(values);
        char op = *(char*)pop(ops);
        push(values, (t_dado)applyOp(val1, val2, op));
    }

    int result = (int)dadoLista(values, 0);
    destroiPilha(values);
    destroiPilha(ops);

    return result;
}

int main() {
    printf(evaluate("10 + 2 * 6"));
    printf(evaluate("100 * 2 + 12"));
    printf(evaluate("100 * ( 2 + 12 )"));
    printf(evaluate("100 * ( 2 + 12 ) / 14"));
}
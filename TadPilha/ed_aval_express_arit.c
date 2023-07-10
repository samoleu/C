#include <stdio.h>
#include <string.h>
#include "tadpilha.h"
#include "tadlista.h"


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
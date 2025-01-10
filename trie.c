#include "trie.h"

#include <stdlib.h>

#define tamanho 26

No* criarNo() {
    No* novoNo = (No*)malloc(sizeof(No));

    if (novoNo) {
        novoNo->final = 0;
        for (int i = 0; i < tamanho; i++) {
            novoNo->letras[i] = NULL;
        }
    }

    return novoNo;
}

void inserirPalavra(No* raiz, char* palavra) {
    No* atual = raiz;

    while (*palavra) {
        int indice = *palavra - 'a';

        if (atual->letras[indice] == NULL) {
            atual->letras[indice] = criarNo();
        }

        atual = atual->letras[indice];
        palavra++;
    }

    atual->final = 1;
}

int buscarPalavra(No* raiz, char* palavra) {
    No* atual = raiz;

    while (*palavra) {
        int indice = *palavra - 'a';
        if (atual->letras[indice] == NULL) {
            return 0;
        }
        atual = atual->letras[indice];
    }

    return atual->final;
}

void liberar(No* raiz) {
    for (int i = 0; i < tamanho; i++) {
        liberar(raiz->letras[i]);
    }
    free(raiz);
}

#include "trie.h"
#include <stdlib.h>
#define tamanho 26

Trie* criarTrie() {
    Trie* novaTrie = (Trie*)malloc(sizeof(Trie));

    if (novaTrie) {
        novaTrie->final = 0;
        for (int i = 0; i < tamanho; i++) {
            novaTrie->letras[i] = NULL;
        }
    }

    return novaTrie;
}

void inserirTrie(Trie* raiz, const char* palavra) {
    Trie* atual = raiz;

    while (*palavra) {
        int indice = *palavra - 'a';

        if (atual->letras[indice] == NULL) {
            atual->letras[indice] = criarTrie();
        }

        atual = atual->letras[indice];
        palavra++;
    }

    atual->final = 1;
}

int buscarPalavra(Trie* raiz, const char* palavra) {
    Trie* atual = raiz;

    while (*palavra) {
        int indice = *palavra - 'a';
        if (atual->letras[indice] == NULL) {
            return 0;
        }
        atual = atual->letras[indice];
        palavra++;
    }

    return atual->final;
}

void liberarTrie(Trie* raiz) {
    if (raiz) {
        for (int i = 0; i < tamanho; i++) {
            liberarTrie(raiz->letras[i]);
        }
        free(raiz);
    }
}


/*
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
    if (raiz) {
        for (int i = 0; i < tamanho; i++) {
            liberar(raiz->letras[i]);
        }
        free(raiz);
    }
}
*/
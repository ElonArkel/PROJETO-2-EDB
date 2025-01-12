#include "trie.h"

#include <stdio.h>
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

    return atual && atual->final;
}

void liberarTrie(Trie* raiz) {
    if (raiz) {
        for (int i = 0; i < tamanho; i++) {
            liberarTrie(raiz->letras[i]);
        }
        free(raiz);
    }
}

void removerTrie(Trie* raiz, const char* palavra) {
    Trie* atual = raiz;

    while (*palavra) {
        int indice = *palavra - 'a';
        if (atual->letras[indice] == NULL) {
            return;
        }
        atual = atual->letras[indice];
        palavra++;
    }

    if (atual->final) {
        atual->final = 0;
    }
}

void imprimirTrie(Trie* raiz) {
    for (int i = 0; i < tamanho; i++) {
        if (raiz->letras[i]) {
            printf("%c ", i + 'a');
            imprimirTrie(raiz->letras[i]);
        }
    }
}
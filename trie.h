#ifndef TRIE_H
#define TRIE_H

typedef struct No {
    struct No *letras[26];
    int final;
} No;

No *criarNo();
void inserirPalavra(No* raiz, char* palavra);
int buscarPalavra(No* raiz, char* palavra);

#endif
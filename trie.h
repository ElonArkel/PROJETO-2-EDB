#ifndef TRIE_H
#define TRIE_H
#define ALFABETO 26
typedef struct Trie {
    struct Trie *letras[ALFABETO];
    int final;
} Trie;

Trie* criarTrie();
void inserirTrie(Trie* raiz, const char* palavra);
int buscarPalavra(Trie* raiz, const char* palavra);
void liberarTrie(Trie* raiz);

/*
typedef struct No {
    struct No *letras[26];
    int final;
} No;

No *criarNo();
void inserirPalavra(No* raiz, char* palavra);
int buscarPalavra(No* raiz, char* palavra);
void liberar(No* raiz);

*/

#endif
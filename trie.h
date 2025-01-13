#ifndef TRIE_H
#define TRIE_H

#define ALFABETO 26

typedef struct Trie {
    struct Trie* letras[ALFABETO];
    int final;
} Trie;

Trie* criarTrie();

void inserirTrie(Trie* raiz, const char* palavra);
int buscarPalavra(Trie* raiz, const char* palavra);
void liberarTrie(Trie* raiz);
void imprimirTrie(Trie* raiz);
void removerTrie(Trie* raiz, const char* palavra);

#endif
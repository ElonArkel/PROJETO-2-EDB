#ifndef JOGO_H
#define JOGO_H
#include "avl.h"
#include "trie.h"
#define MAX 100

extern char tabuleiro[MAX][MAX];
extern int tamanho_tabuleiro;

void lerTabuleiro(const char *arquivo);
void lerPalavras(const char *arquivo, Trie* raiz);
void buscarPalavras(Trie* trie, ArvAVL *avl);


#endif
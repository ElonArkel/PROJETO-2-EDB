#ifndef JOGO_H
#define JOGO_H
#include "avl.h"
#include "trie.h"

void lerTabuleiro(const char *arquivo);
void lerPalavras(const char *arquivo, Trie *raiz);
void buscarPalavras(Trie *trie, ArvAVL **avl);
void imprimirResultado(ArvAVL *avl);

#endif
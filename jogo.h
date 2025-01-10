#ifndef JOGO_H
#define JOGO_H
#include "avl.h"
#include "trie.h"

typedef struct {
    char** tabuleiro;
    int linhas;
    int colunas;
    No* trie;  // apontar pro nó raiz da trie
    ArvAVL* avl;
} Jogo;

Jogo* criarJogo();
void destruirJogo(Jogo* jogo);
void lerTabuleiro(Jogo* jogo);
void lerPalavras(Jogo* jogo);
int buscarPalavras(Jogo* jogo);
void imprimirResultado(Jogo* jogo);

void buscarPalavraNaPosicao(Jogo* jogo, int x, int y, const char* palavra, int dx, int dy);
int validarPosicao(Jogo* jogo, int x, int y);

#endif
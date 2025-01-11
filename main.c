#include "jogo.h"
#include "jogo.c"
#include <stdio.h>

int main() {
    
    Trie* trie = criarTrie();
    ArvAVL* avl = NULL;

    lerTabuleiro("tabuleiro.txt");
    lerPalavras("palavras.txt", trie);
    buscarPalavras(trie, &avl);
    imprimirResultado(avl);

    liberarArvore(avl);
    liberarTrie(trie);
    
    return 0;

    /*
    // Jogo *cacaPalavra = criarJogo();
    // lerTabuleiro(cacaPalavra);
    // lerPalavras(cacaPalavra);
    printf("rodou!\n");
    return 0;
    */
}
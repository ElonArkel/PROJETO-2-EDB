#include <stdio.h>

#include "jogo.h"

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
}
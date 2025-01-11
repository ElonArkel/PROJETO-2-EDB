#include <stdio.h>

#include "jogo.h"

int main() {
    Trie* trie = criarTrie();
    ArvAVL* avl = NULL;

    lerTabuleiro("tabuleiro.txt");      // ok
    lerPalavras("palavras.txt", trie);  // ok
    buscarPalavras(trie, &avl);
    imprimirResultado(avl);

    liberarArvore(avl);
    liberarTrie(trie);

    return 0;
}
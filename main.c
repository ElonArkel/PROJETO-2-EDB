#include <stdio.h>

#include "jogo.h"

int main() {
    Trie* trie = criarTrie();
    ArvAVL* avl = NULL;

    lerTabuleiro("tabuleiro.txt");
    printf("\ntabuleiro carregado.\n");

    lerPalavras("palavras.txt", trie);
    printf("\npalavras carregadas.\n");

    int seletor = 0;
    while (seletor != 4) {
        printf("\nCaça Palavras\n");
        printf("1 - buscar palavras\n");
        printf("2 - imprimir resultado\n");
        printf("3 - remover palavras\n");
        printf("4 - sair\n");

        scanf("%d", &seletor);

        switch (seletor) {
            case 1:
                buscarPalavras(trie, &avl);
                break;
            case 2:
                imprimirResultado(avl);
                break;
            case 3:
                // remover palavra desejada
                break;
            case 4:
                printf("\nEncerrando...\n\n");
                break;
            default:
                printf("\nOpcao invalida\n");
                break;
        }
    }

    liberarArvore(avl);
    liberarTrie(trie);

    return 0;
}
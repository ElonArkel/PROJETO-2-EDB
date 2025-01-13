#include <stdio.h>

#include "jogo.h"

int main() {
    Trie* trie = criarTrie();
    ArvAVL* avl = NULL;

    lerTabuleiro("tabuleiro.txt");
    printf("\ntabuleiro carregado...");
    lerPalavras("palavras.txt", trie);
    printf("\npalavras carregadas...\n");

    int seletor = 0;
    while (seletor != 4) {
        printf("\n-Caça-Palavras-\n");
        printf("1 - buscar palavras\n");
        printf("2 - imprimir resultado\n");
        printf("3 - remover palavras\n");
        printf("4 - sair\n");

        scanf("%d", &seletor);

        switch (seletor) {
            case 1:
                buscarPalavras(trie, &avl);
                printf("\ntabuleiro percorrido, palavras armazenadas\n");
                break;
            case 2:
                imprimirResultado(avl);
                break;
            case 3:
                printf("Deseja remover palavra:\n");
                printf("1 - encontrada (avl)\n");
                printf("2 - para procurar (trie)\n");
                scanf("%d", &seletor);

                char palavra[50];
                printf("Insira a palavra: ");
                scanf("%s", palavra);
                if (seletor == 1) {
                    removerAVL(avl, palavra);
                    printf("\nPalavra encontrada removida\n");
                } else if (seletor == 2) {
                    removerTrie(trie, palavra);
                    printf("\nPalavra de busca removida\n");
                } else {
                    seletor = -1;
                    printf("\nOpcao invalida\n");
                }

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
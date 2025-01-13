#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"
#include "trie.h"

#define MAX 100
char tabuleiro[MAX][MAX];
int tamanho_tabuleiro;

void lerTabuleiro(const char *arquivo) {
    FILE *file = fopen(arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    } else {
        fscanf(file, "%d", &tamanho_tabuleiro);
        for (int i = 0; i < tamanho_tabuleiro; i++) {
            for (int j = 0; j < tamanho_tabuleiro; j++) {
                fscanf(file, " %c", &tabuleiro[i][j]);
                tabuleiro[i][j] = tolower(tabuleiro[i][j]);
            }
        }
    }

    fclose(file);
}

void lerPalavras(const char *arquivo, Trie *raiz) {
    FILE *file = fopen(arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    } else {
        char palavra[50];
        while (fscanf(file, "%s", palavra) != EOF) {
            for (int i = 0; palavra[i] != '\0'; i++) {
                palavra[i] = tolower(palavra[i]);
            }
            inserirTrie(raiz, palavra);
        }
    }

    fclose(file);
}

void buscarPalavras(Trie *trie, ArvAVL **avl) {
    char palavra[50];

    // Horizontal da esquerda pra direita
    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            for (int k = j; k < tamanho_tabuleiro; k++) {
                strncpy(palavra, &tabuleiro[i][j], k - j + 1);
                palavra[k - j + 1] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirAVL(*avl, palavra);
                }
            }
        }
    }

    // Horizontal da direita pra esquerda

    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = tamanho_tabuleiro - 1; j >= 0; j--) {
            int len = 0;
            for (int k = j; k >= 0; k--) {
                palavra[len++] = tabuleiro[i][k];
                palavra[len] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirAVL(*avl, palavra);
                }
            }
        }
    }

    // Vertical de cima para baixo

    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            for (int k = j; k < tamanho_tabuleiro; k++) {
                int len = k - j + 1;
                for (int n = 0; n < len; n++) {
                    palavra[n] = tabuleiro[j + n][i];
                }
                palavra[len] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirAVL(*avl, palavra);
                }
            }
        }
    }

    // Vertical de baixo para cima

    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = tamanho_tabuleiro - 1; j >= 0; j--) {
            int len = 0;
            for (int k = j; k >= 0; k--) {
                palavra[len++] = tabuleiro[k][i];
                palavra[len] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirAVL(*avl, palavra);
                }
            }
        }
    }

    // Diagonal superior esquerda para inferior direita

    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            int x = i, y = j, len = 0;
            while (x < tamanho_tabuleiro && y < tamanho_tabuleiro) {
                palavra[len++] = tabuleiro[x][y];
                palavra[len] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirAVL(*avl, palavra);
                }
                x++;
                y++;
            }
        }
    }

    // Diagonal superior direita para inferior esquerda

    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            int x = i, y = j, len = 0;
            while (x < tamanho_tabuleiro && y >= 0) {
                palavra[len++] = tabuleiro[x][y];
                palavra[len] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirAVL(*avl, palavra);
                }
                x++;
                y--;
            }
        }
    }

    // Diagonal inferior esquerda para superior direita

    for (int i = tamanho_tabuleiro; i >= 0; i--) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            int x = i, y = j, len = 0;
            while (x >= 0 && y < tamanho_tabuleiro) {
                palavra[len++] = tabuleiro[x][y];
                palavra[len] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirAVL(*avl, palavra);
                }
                x--;
                y++;
            }
        }
    }

    // Diagonal inferior direita para superior esquerda

    for (int i = tamanho_tabuleiro - 1; i >= 0; i--) {
        for (int j = tamanho_tabuleiro - 1; j >= 0; j--) {
            int x = i, y = j, len = 0;
            while (x >= 0 && y >= 0) {
                palavra[len++] = tabuleiro[x][y];
                palavra[len] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    *avl = inserirAVL(*avl, palavra);
                }
                x--;
                y--;
            }
        }
    }
}

void removerPalavras(Trie *trie, ArvAVL **avl) {
    ArvAVL *aux = *avl;
    while (aux != NULL) {
        removerTrie(trie, aux->palavra);
        aux = aux->dir;
    }
    liberarArvore(*avl);
    *avl = NULL;
}

void imprimirResultado(ArvAVL *avl) {
    printf("\nPalavras encontradas:\n");
    imprimirArvoreEmOrdem(avl);
}
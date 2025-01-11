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
            inserirTrie(raiz, palavra);
        }
    }

    fclose(file);
}

void buscarPalavras(Trie *trie, ArvAVL **avl) {
    char palavra[50];
    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            for (int k = j; k < tamanho_tabuleiro; k++) {
                strncpy(palavra, &tabuleiro[i][j], k - j + 1);
                palavra[k - j + 1] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    // *avl = inserirAVL(*avl, palavra);
                }
                
            }
        }
    }

    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            for (int k = j; k < tamanho_tabuleiro; k++) {
                int len = k - j + 1;
                for (int n = 0; n < len; n++) {
                    palavra[n] = tabuleiro[j + n][i];
                }
                palavra[len] = '\0';
                if (buscarPalavra(trie, palavra)) {
                    // *avl = inserirAVL(*avl, palavra);
                    printf("entrou\n");
                }
            }
        }
    }

    //Diagonal superior esquerda para inferior direita

    for(int i = 0; i < tamanho_tabuleiro; i++){
        for(int j = 0; j < tamanho_tabuleiro; j++){
            int x = i, y = j, len = 0;
            while(x < tamanho_tabuleiro && y < tamanho_tabuleiro){
                palavra[len++] = tabuleiro[x++][y++];
                palavra[len] = '\0';
                if(buscarPalavra(trie, palavra)){
                    // *avl = inserirAVL(*avl, palavra);
                    printf("entrou\n");
                }
                x++;
                y++;
            }
        }
    }
    
    //Diagonal superior direita para inferior esquerda

    for(int i = 0; i < tamanho_tabuleiro; i++){
        for(int j = 0; j < tamanho_tabuleiro; j++){
            int x = i, y = j, len = 0;
            while(x < tamanho_tabuleiro && y >= 0){
                palavra[len++] = tabuleiro[x++][y--];
                palavra[len] = '\0';
                if(buscarPalavra(trie, palavra)){
                    // *avl = inserirAVL(*avl, palavra);
                    printf("entrou\n");
                }
                x++;
                y--;
            }
        }
    }
    
}

void imprimirResultado(ArvAVL *avl) {
    printf("Palavras encontradas:\n");
    imprimirArvoreEmOrdem(avl);
}

/*
typedef struct {
    char** tabuleiro;
    int linhas;
    int colunas;
    No* trie;  //apontar pro nó raiz da trie
    ArvAVL* avl;
} Jogo;

Jogo* criarJogo()
{
    Jogo* jogo = (Jogo*)malloc(sizeof(Jogo));
    jogo->tabuleiro = NULL;
    jogo->linhas = 0;
    jogo->colunas = 0;
    jogo->trie = criarNo();
    jogo->avl = (ArvAVL*)malloc(sizeof(ArvAVL));
    criar_ArvAVL(jogo->avl);
    return jogo;
}

void destruirJogo(Jogo* jogo)
{
    for (int i = 0; i < jogo->linhas; i++)
    {
        free(jogo->tabuleiro[i]);
    }
    free(jogo->tabuleiro);
    free(jogo->avl);
    liberar(jogo->trie);
    free(jogo);
}

void lerTabuleiro(Jogo* jogo)
{
    FILE* file = fopen("../tabuleiro.txt", "r");
    if (file == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    else{
        fscanf(file, "%d %d", &jogo->linhas, &jogo->colunas);
        jogo->tabuleiro = (char**)malloc(jogo->linhas * sizeof(char*));
        for (int i = 0; i < jogo->linhas; i++){
            jogo->tabuleiro[i] = (char*)malloc(jogo->colunas * sizeof(char));
            for (int j = 0; j < jogo->colunas; j++){
                fscanf(file, " %c", &jogo->tabuleiro[i][j]);
            }
        }
    }
    fclose(file);
}

void lerPalavras(Jogo* jogo)
{
    FILE* file = fopen("../palavras.txt", "r");
    if (file == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    else{
        char palavra[100];
        while (fscanf(file, "%s", palavra) != EOF){
            inserirPalavra(jogo->trie, palavra);
            Insere_ArvAVL(jogo->avl, palavra);
        }
    }
    fclose(file);
}

int buscarPalavras(Jogo* jogo)
{
    int encontradas = 0;
    for(int i = 0; i < jogo->linhas; i++){
        for(int j = 0; j < jogo->colunas; j++){
            for(int dx = -1; dx <= 1; dx++){
                for(int dy = -1; dy <= 1; dy++){
                    if(dx == 0 && dy == 0){
                        continue;
                    }
                    buscarPalavraNaPosicao(jogo, i, j, "", dx, dy);
                }
            }
        }
    }
    return encontradas;
}

void buscar_ArvAVL(ArvAVL *raiz, char* palavra)
{
    if (*raiz == NULL){
        return;
    }
    if (strcmp(palavra, (*raiz)->info) == 0){
        return 1;
    }
    if (strcmp(palavra, (*raiz)->info) < 0){
        buscar_ArvAVL(&(*raiz)->esq, palavra);
    }
    else{
        buscar_ArvAVL(&(*raiz)->dir, palavra);
    }
}

void buscarPalavraNaPosicao(Jogo* jogo, int x, int y, const char* palavra, int dx, int dy)
{
    if (!validarPosicao(jogo, x, y)){
        return;
    }
    char novaPalavra[100];
    strcpy(novaPalavra, palavra);
    novaPalavra[strlen(novaPalavra)] = jogo->tabuleiro[x][y];
    novaPalavra[strlen(novaPalavra) + 1] = '\0';
    if (buscarPalavra(jogo->trie, novaPalavra)){
        buscar_ArvAVL(jogo->avl, novaPalavra);
    }
    buscarPalavraNaPosicao(jogo, x + dx, y + dy, novaPalavra, dx, dy);
}

int validarPosicao(Jogo* jogo, int x, int y)
{
    return x >= 0 && x < jogo->linhas && y >= 0 && y < jogo->colunas;
} */
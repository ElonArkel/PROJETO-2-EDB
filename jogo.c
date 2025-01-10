#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "trie.h"

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
    jogo->trie = criarTrie();
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
    destruirTrie(jogo->trie);
    free(jogo);
}

void lerTabuleiro(Jogo* jogo, const char* filename)
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

void lerPalavras(Jogo* jogo, const char* filename)
{
    FILE* file = fopen("../palavras.txt", "r");
    if (file == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    else{
        char palavra[100];
        while (fscanf(file, "%s", palavra) != EOF){
            insereTrie(jogo->trie, palavra);
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

void buscarPalavraNaPosicao(Jogo* jogo, int x, int y, const char* palavra, int dx, int dy)
{
    if(x < 0 || x >= jogo->linhas || y < 0 || y >= jogo->colunas){
        return;
    }
    char* novaPalavra = (char*)malloc((strlen(palavra) + 2) * sizeof(char));
    strcpy(novaPalavra, palavra);
    novaPalavra[strlen(palavra)] = jogo->tabuleiro[x][y];
    novaPalavra[strlen(palavra) + 1] = '\0';
    if(buscarTrie(jogo->trie, novaPalavra)){
        if(buscar_ArvAVL(jogo->avl, novaPalavra)){
            printf("Palavra encontrada: %s\n", novaPalavra);
        }
    }
    buscarPalavraNaPosicao(jogo, x + dx, y + dy, novaPalavra, dx, dy);
    free(novaPalavra);
}

int validarPosicao(Jogo* jogo, int x, int y)
{
    return x >= 0 && x < jogo->linhas && y >= 0 && y < jogo->colunas;
}
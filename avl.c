#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

struct NO
{
    int info;
    int alt;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL *raiz;

int altura_NO(struct NO *no)
{
    if (no == NULL)
        return -1;
    else
        return no->alt;
}

int fatorBalanceamento_NO(struct NO *no)
{
    return labs(altura_no(no->esq) - altura_no(no->dir)); // função labs retorna valor absoluto
}

int maior(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

int estaVazia(ArvAVL *raiz)
{
    if (raiz == NULL)
        return 1;
    if (*raiz == NULL)
        return 1;
    return 0;
}

void RotacaoLL(ArvAVL *raiz)
{ // rotação a esquerda
    struct NO *no;
    no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = (*raiz);
    (*raiz)->alt = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;
    no->alt = maior(altura_NO(no->esq), (*raiz)->alt) + 1;
    (*raiz) = no;
}

void RotacaoRR(ArvAVL *raiz)
{ // rotação a direita
    struct NO *no;
    no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = (*raiz);
    (*raiz)->alt = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;
    no->alt = maior(altura_NO(no->dir), (*raiz)->alt) + 1;
    (*raiz) = no;
}

void RotacaoLR(ArvAVL *raiz)
{ // rotação dupla a esquerda
    RotacaoRR(&(*raiz)->esq);
    RotacaoLL(raiz);
}

void RotacaoRL(ArvAVL *raiz)
{ // rotação dupla a direita
    RotacaoLL(&(*raiz)->dir);
    RotacaoRR(raiz);
}

int Insere_ArvAVL(ArvAVL *raiz, int valor)
{
    int res;
    if (*raiz == NULL)
    {
        struct NO *novo;
        novo = (struct NO *)malloc(sizeof(struct NO));
        if (novo == NULL)
            return 0;

        novo->info = valor;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if (valor < atual->info){
        if ((res = Insere_ArvAVL(&(atual->esq), valor)) == 1){
            if (fatorBalanceamento_NO(atual) >= 2){
                if (valor < (*raiz)->esq->info){
                    RotacaoLL(raiz);
                }
                else{
                    RotacaoLR(raiz);
                }
            }
        }
    }
    else{
        if (valor > atual->info){
            if ((res = Insere_ArvAVL(&(atual->dir), valor)) == 1){
                if (fatorBalanceamento_NO(atual) >= 2){
                    if ((*raiz)->dir->info < valor){
                        RotacaoRR(raiz);
                    }
                    else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }
        else{
            printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->alt = maior(altura_NO(atual->esq), altura_NO(atual->dir)) + 1;

    return res;
}

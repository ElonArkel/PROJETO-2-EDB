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

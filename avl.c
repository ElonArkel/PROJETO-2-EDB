#include "avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maior(int x, int y) {
    if (x > y)
        return x;
    else
        return y;
}

int altura(ArvAVL *no) {
    if (no == NULL) {
        return -1;
    } else {
        return no->altura;
    }
}

int fatorBalanceamento(ArvAVL *no) {
    if (no == NULL) {
        return 0;
    }

    return altura(no->esq) - altura(no->dir);
}

ArvAVL *criarArvAVL(const char *palavra) {
    ArvAVL *novo = (ArvAVL *)malloc(sizeof(ArvAVL));
    strcpy(novo->palavra, palavra);
    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

ArvAVL *rotacaoDireita(ArvAVL *no) {
    ArvAVL *aux = no->esq;
    ArvAVL *aux2 = aux->dir;

    aux->dir = no;
    no->esq = aux2;

    no->altura = 1 + maior(altura(no->esq), altura(no->dir));
    aux->altura = 1 + maior(altura(aux->esq), altura(aux->dir));
    return aux;
}

ArvAVL *rotacaoEsquerda(ArvAVL *no) {
    ArvAVL *aux1 = no->dir;
    ArvAVL *aux2 = aux1->esq;

    aux1->esq = no;
    no->dir = aux2;

    no->altura = 1 + maior(altura(no->esq), altura(no->dir));
    aux1->altura = 1 + maior(altura(aux1->esq), altura(aux1->dir));
    return aux1;
}

ArvAVL *balancearNo(ArvAVL *no) {
    int balanceamento = fatorBalanceamento(no);

    // rotação simples direita
    if (balanceamento > 1 && fatorBalanceamento(no->esq) >= 0) {
        return rotacaoDireita(no);
    }
    // rotação dupla direita
    if (balanceamento > 1 && fatorBalanceamento(no->esq) < 0) {
        no->esq = rotacaoEsquerda(no->esq);

        return rotacaoDireita(no);
    }

    // rotação simples esquerda
    if (balanceamento < -1 && fatorBalanceamento(no->dir) <= 0) {
        return rotacaoEsquerda(no);
    }

    // rotação dupla esquerda
    if (balanceamento < -1 && fatorBalanceamento(no->dir) > 0) {
        no->dir = rotacaoDireita(no->dir);

        return rotacaoEsquerda(no);
    }

    return no;
}

ArvAVL *inserirAVL(ArvAVL *raiz, const char *palavra) {
    if (raiz == NULL) {
        return criarArvAVL(palavra);
    }
    if (strcmp(palavra, raiz->palavra) < 0) {
        raiz->esq = inserirAVL(raiz->esq, palavra);
    } else if (strcmp(palavra, raiz->palavra) > 0) {
        raiz->dir = inserirAVL(raiz->dir, palavra);
    } else {
        return raiz;
    }
    raiz->altura = 1 + maior(altura(raiz->esq), altura(raiz->dir));
    return balancearNo(raiz);
}

ArvAVL *removerAVL(ArvAVL *raiz, const char *palavra) {
    if (raiz == NULL) {
        return raiz;
    }
    if (strcmp(palavra, raiz->palavra) < 0) {
        raiz->esq = removerAVL(raiz->esq, palavra);
    } else if (strcmp(palavra, raiz->palavra) > 0) {
        raiz->dir = removerAVL(raiz->dir, palavra);
    } else {
        if (raiz->esq == NULL || raiz->dir == NULL) {
            ArvAVL *temp = raiz->esq ? raiz->esq : raiz->dir;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            ArvAVL *temp = raiz->dir;
            while (temp->esq != NULL) {
                temp = temp->esq;
            }
            strcpy(raiz->palavra, temp->palavra);
            raiz->dir = removerAVL(raiz->dir, temp->palavra);
        }
    }
    if (raiz == NULL) {
        return raiz;
    }
    raiz->altura = 1 + maior(altura(raiz->esq), altura(raiz->dir));
    return balancearNo(raiz);
}

void imprimirArvoreEmOrdem(ArvAVL *raiz) {
    if (raiz != NULL) {
        imprimirArvoreEmOrdem(raiz->esq);
        printf("%s\n", raiz->palavra);
        imprimirArvoreEmOrdem(raiz->dir);
    }
}

void liberarArvore(ArvAVL *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}
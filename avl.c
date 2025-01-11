#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

int maior(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

int altura(ArvAVL* no){
    if(no == NULL){
        return -1;
    }
    else{
        return no->altura;
    }
}

int fatorBalanceamento(ArvAVL* no){
    return labs(altura(no->esq) - altura(no->dir));
}

ArvAVL* criarArvAVL(const char* palavra){
    ArvAVL* novo = (ArvAVL*)malloc(sizeof(ArvAVL));
    strcpy(novo->palavra, palavra);
    novo->altura = 1;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

ArvAVL* rotacaoDireita(ArvAVL* no){
    ArvAVL* aux = no->esq;
    no->esq = aux->dir;
    aux->dir = no;
    no->altura = 1 + maior(altura(no->esq), altura(no->dir));
    aux->altura = 1 + maior(altura(aux->esq), no->altura);
    return aux;
}

ArvAVL* rotacaoEsquerda(ArvAVL* no){
    ArvAVL* aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    no->altura = 1 + maior(altura(no->esq), altura(no->dir));
    aux->altura = 1 + maior(altura(aux->dir), no->altura);
    return aux;
}

ArvAVL* balancearNo(ArvAVL* no){
    int balanceamento = fatorBalanceamento(no);
    if(balanceamento > 1){
        if(altura(no->esq->esq) > altura(no->esq->dir)){
            no = rotacaoDireita(no);
        }
        else{
            no->esq = rotacaoEsquerda(no->esq);
            no = rotacaoDireita(no);
        }
    }
    else if(balanceamento < -1){
        if(altura(no->dir->dir) > altura(no->dir->esq)){
            no = rotacaoEsquerda(no);
        }
        else{
            no->dir = rotacaoDireita(no->dir);
            no = rotacaoEsquerda(no);
        }
    }
}

ArvAVL* inserirAVL(ArvAVL* raiz, const char* palavra){
    if(raiz == NULL){
        return criarArvAVL(palavra);
    }
    if(strcmp(palavra, raiz->palavra) < 0){
        raiz->esq = inserirAVL(raiz->esq, palavra);
    }
    else if(strcmp(palavra, raiz->palavra) > 0){
        raiz->dir = inserirAVL(raiz->dir, palavra);
    }
    else{
        return raiz;
    }
    raiz->altura = 1 + maior(altura(raiz->esq), altura(raiz->dir));
    return balancearNo(raiz);
}

void imprimirArvoreEmOrdem(ArvAVL* raiz){
    if(raiz != NULL){
        imprimirArvoreEmOrdem(raiz->esq);
        printf("%s\n", raiz->palavra);
        imprimirArvoreEmOrdem(raiz->dir);
    }
}

void liberarArvore(ArvAVL* raiz){
    if(raiz != NULL){
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

/*
struct NO
{
    int info;
    int alt;
    struct NO *esq;
    struct NO *dir;
};

struct NO* procuraMenor(struct NO *atual)
{
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

ArvAVL *raiz;

void criar_ArvAVL(ArvAVL *raiz)
{
    *raiz = NULL;
}

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

ArvAVL Insere_ArvAVL(ArvAVL *raiz, int valor)
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

ArvAVL Remove_ArvAVL(ArvAVL *raiz, int valor)
{
    if (*raiz == NULL){
        printf("Valor não existe!!\n");
        return 0;
    }

    int res;
    if(valor < (*raiz)->info){
        if((res = Remove_ArvAVL(&(*raiz)->esq, valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
        }
    }

    if( valor > (*raiz)->info){
        if((res = Remove_ArvAVL(&(*raiz)->dir, valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
    }

    if((*raiz)->info == valor){
        if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){
            struct NO *VelhoNo = (*raiz);
            if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
            free(VelhoNo);
        }
        else{
            struct NO *temp = procuraMenor((*raiz)->dir);
            (*raiz)->info = temp->info;
            Remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
        return 1;
    }
    return res;
}

void imprimirArvoreEmOrdem(ArvAVL *raiz)
{
    if (*raiz != NULL)
    {
        imprimirArvoreEmOrdem(&((*raiz)->esq));
        printf("%d\n", (*raiz)->info);
        imprimirArvoreEmOrdem(&((*raiz)->dir));
    }
}  */
#ifndef AVL_H
#define AVL_H
typedef struct ArvAVL{
    char palavra[50];
    int altura;
    struct ArvAVL *esq, *dir;
} ArvAVL;

ArvAVL* criarArvAVL(const char* palavra);
ArvAVL* inserirAVL(ArvAVL* raiz, const char* palavra);
ArvAVL* removerAVL(ArvAVL* raiz, const char* palavra);
void imprimirArvoreEmOrdem(ArvAVL *raiz);
void liberarArvore(ArvAVL* raiz);

/*
void criar_ArvAVL(ArvAVL *raiz);
int altura_NO(struct NO *no);
int fatorBalanceamento_NO(struct NO *no);
int maior(int x, int y);
int estaVazia(ArvAVL *raiz);
void RotacaoLL(ArvAVL *raiz); // rotação a esquerda
void RotacaoRR(ArvAVL *raiz); // rotação a direita
void RotacaoLR(ArvAVL *raiz); // rotação dupla a esquerda
void RotacaoRL(ArvAVL *raiz); // rotação dupla a direita
ArvAVL Insere_ArvAVL(ArvAVL *raiz, int valor);
ArvAVL Remove_ArvAVL(ArvAVL *raiz, int valor);
void imprimirArvoreEmOrdem(ArvAVL *raiz);   */ 

#endif
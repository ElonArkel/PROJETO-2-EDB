#ifndef AVL_H
#define AVL_H
typedef struct NO *ArvAVL;

int altura_NO(struct NO *no);
int fatorBalanceamento_NO(struct NO *no);
int maior(int x, int y);
int estaVazia(ArvAVL *raiz);
void RotacaoLL(ArvAVL *raiz); // rotação a esquerda
void RotacaoRR(ArvAVL *raiz); // rotação a direita
void RotacaoLR(ArvAVL *raiz); // rotação dupla a esquerda
void RotacaoRL(ArvAVL *raiz); // rotação dupla a direita

#endif

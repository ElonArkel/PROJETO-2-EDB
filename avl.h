#ifndef AVL_H
#define AVL_H
typedef struct ArvAVL {
    char palavra[50];
    int altura;
    struct ArvAVL *esq, *dir;
} ArvAVL;

ArvAVL* criarArvAVL(const char* palavra);
ArvAVL* inserirAVL(ArvAVL* raiz, const char* palavra);
// ArvAVL* removerAVL(ArvAVL* raiz, const char* palavra);
void imprimirArvoreEmOrdem(ArvAVL* raiz);
void liberarArvore(ArvAVL* raiz);

#endif
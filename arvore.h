//pego apartir do pseudo codigo no PDF do livro de algoritmos 
#ifndef ARVORE_H
#define ARVORE_H

#define MAX_TAM 51

typedef enum{
    PRETO = 0,
    VERMELHO = 1
} Cor;

typedef struct{
    char nome[MAX_TAM]; //MAX_TAM = 51
    int idade;
} Pessoa;

typedef struct no{
    Pessoa pessoa; 
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    Cor cor;
} NoArvoreRN;

typedef struct{
    NoArvoreRN* raiz;
} ArvoreRubroNegra;


NoArvoreRN* criaNoArvore(Pessoa* pessoa);
ArvoreRubroNegra* alocarArvore();
void desalocarArvoreRecursivo(NoArvoreRN* no);
void desalocarArvore(ArvoreRubroNegra* arvore);
void rotacaoEsquerda(ArvoreRubroNegra** arvore, NoArvoreRN* x);
void rotacaoDireita(ArvoreRubroNegra** arvore, NoArvoreRN* x);
void insereArvore(ArvoreRubroNegra* arvore, NoArvoreRN* z);
void balancear(ArvoreRubroNegra** arvore, NoArvoreRN* z);
void printInOrder(ArvoreRubroNegra* arvore);
void printInOrderRecursivo(NoArvoreRN* no);

#endif  // ARVORE_H
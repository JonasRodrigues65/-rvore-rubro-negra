//pego apartir do pseudo codigo no PDF do livro de algoritmos 
#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

NoArvoreRN* criaNoArvore(Pessoa* pessoa){
    NoArvoreRN* novoNo = (NoArvoreRN*)malloc(sizeof(NoArvoreRN));
    if(novoNo != NULL){
        strcpy(novoNo->pessoa.nome, pessoa->nome);
        novoNo->pessoa.idade = pessoa->idade;
        // Inicializa os outros campos do nó
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
        novoNo->pai = NULL;
        novoNo->cor = VERMELHO; // ou outra cor padrão, dependendo da sua implementação
    }
    return novoNo;
}

ArvoreRubroNegra* alocarArvore(){
    ArvoreRubroNegra* novaArvore = (ArvoreRubroNegra*) malloc(sizeof(ArvoreRubroNegra));
    if (novaArvore != NULL) {
        novaArvore->raiz = NULL;
    }
    return novaArvore;
}

void desalocarArvoreRecursivo(NoArvoreRN* no){
    if (no != NULL) {
        desalocarArvoreRecursivo(no->esquerda);
        desalocarArvoreRecursivo(no->direita);
        free(no);
    }

}

void desalocarArvore(ArvoreRubroNegra* arvore){
    desalocarArvoreRecursivo(arvore->raiz);
    free(arvore);
}

void rotacaoEsquerda(ArvoreRubroNegra** arvore, NoArvoreRN* x){
    NoArvoreRN* y = x->direita; // Armazenamos o nó direito de x em y
    x->direita = y->esquerda; // A subárvore esquerda de y se torna a subárvore direita de x

    // Se a subárvore esquerda de y não for nula, ajustamos seu pai para ser x
    if(y->esquerda != NULL){
        y->esquerda->pai = x;
    }

    y->pai = x->pai; // O pai de y recebe o pai de x

    // Se x não tem pai, isso significa que x é a raiz da árvore
    // Então, atualizamos a raiz da árvore para ser y
    if(x->pai == NULL){
        (*arvore)->raiz = y;
    }
    // Se x é filho esquerdo de seu pai, ajustamos o filho esquerdo do pai de x para ser y
    else if(x == x->pai->esquerda){
        x->pai->esquerda = y;
    }
    // Se x é filho direito de seu pai, ajustamos o filho direito do pai de x para ser y
    else{
        x->pai->direita = y;
    }

    y->esquerda = x;  // Tornamos x a subárvore esquerda de y
    x->pai = y; // O pai de x agora é y
}

//simetrico a da rotacao esquerda
void rotacaoDireita(ArvoreRubroNegra** arvore, NoArvoreRN* x){
    NoArvoreRN* y = x->esquerda; //depois de criar um y,
    x->esquerda = y->direita; // transformamos a sub-arvore a direita do y na sub arvore a esquerda de x
    if(y->direita != NULL){
        y->direita->pai = x;
    }
    y->pai = x->pai; //ligamos o pai de x para o y
    if(x->pai == NULL){
        (*arvore)->raiz = y;
    }
    else if(x == x->pai->direita){
        x->pai->direita = y;
    }
    else{
        x->pai->esquerda = y;
    }
    y->direita = x;  //colando x a direita do y
    x->pai = y;   
}


//Estou com duvida se realmente precisamos usar ponteiro de pointeiro, em arvores binarias
//usamos os ponteriros de ponteiros
void insereArvore(ArvoreRubroNegra* arvore, NoArvoreRN* z){ //analizar depois se é nescessario a alocacao do Nó
    NoArvoreRN* y = NULL;
    NoArvoreRN* x = arvore->raiz; 
    while(x != NULL){
        y = x;
        //observacao, aqui tratamos se for menor vai para ESQUERDA, se for IGUAL ou maior vai para a DIREITA
        if(z->pessoa.idade < x->pessoa.idade){
            x = x->esquerda;
        }
        else{
            x = x->direita;
        }
    }
    z->pai = y;
    if(y == NULL){
        arvore->raiz = z;// se y for nulo, significa que nossa arvore raiz é nula, então inserimos o nosso no na propria raiz
    }
//se valor desse novo no for menor que o valor da idade do no pai (y), o novo nó é inserido como filho esquerdo de y
    else if(z->pessoa.idade < y->pessoa.idade){
        y->esquerda = z;
    }
    else{// se não for menor ele é inserido a direia, mesmo se for igual
        y->direita = z;
    }
    //aqui inicializamos esse no, mostrnado pra onde a sua esquerda e deireita apontam, e colocando ele como vermelho
    z->esquerda = NULL;
    z->direita = NULL;
    z->cor = VERMELHO; 
    balancear(&arvore, z);
} 


void balancear(ArvoreRubroNegra **arvore, NoArvoreRN *z){
    NoArvoreRN *y;
    while(z != (*arvore)->raiz && z->pai->cor == VERMELHO){
        if(z->pai == z->pai->pai->esquerda){//Esta condição verifica se o pai do nó z é o filho esquerdo do pai do pai de z
            y = z->pai->pai->direita;
            if(y != NULL && y->cor == VERMELHO){
                z->pai->cor = PRETO;//estamos fazendo uma especie de rotacao
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            }
            else{
                if(z == z->pai->direita){
                    z = z->pai;                 
                    rotacaoEsquerda(arvore, z); // Rotaciona à esquerda em torno de z
                }
                z->pai->cor = PRETO;                 
                z->pai->pai->cor = VERMELHO;              
                rotacaoDireita(arvore, z->pai->pai); 
            }
        }
        else{
            y = z->pai->pai->esquerda;
            if(y != NULL && y->cor == VERMELHO){
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            }
            else{
                if(z == z->pai->esquerda){
                    z = z->pai;
                    rotacaoDireita(arvore, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoEsquerda(arvore, z->pai->pai);
            }
        }
    }
    (*arvore)->raiz->cor = PRETO;
}

void printInOrderRecursivo(NoArvoreRN* no) {
    if (no != NULL){
        printInOrderRecursivo(no->esquerda);
        printf("Nome: %s\n", no->pessoa.nome);
        printf("Idade: %d\n", no->pessoa.idade);
        printInOrderRecursivo(no->direita);
    }
}

void printInOrder(ArvoreRubroNegra* arvore) {
    printf("Dados inOrder:\n");
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("Árvore vazia\n");
        return;
    }

    printInOrderRecursivo(arvore->raiz);
}



/* void printInOrderRecursivo(NoArvoreRN* no){
    if (no == NULL){
        return;
    }
    printInOrderRecursivo(no->esquerda);
    printf("Nome: %s\n", no->pessoa.nome);
    printf("Idade: %d\n", no->pessoa.idade);
    printInOrderRecursivo(no->direita);
}
 */
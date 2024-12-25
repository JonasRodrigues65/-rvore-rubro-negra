//pego apartir do pseudo codigo no PDF do livro de algoritmos 
#include <stdio.h>
#include "arvore.h"

int main(){
    //Uma árvore vermelho-preto com n nós internos tem, no máximo, a altura 2 lg(n + 1).
    //Entrada das variaveis
    //printf("\n\nAte então a funçao de balanceamento esta sendo inutilizada\n\n");
    ArvoreRubroNegra* arvore = alocarArvore();
    Pessoa pessoa;
    NoArvoreRN* novoNo;
    int opcode;
    int n_pessoas; //numero de pessoas a serem inseridas
    do{
        //printf("\n\n0 - Sair do loop\n1 - Inserção\n2 - Impressão\n\n");
        scanf("%d", &opcode);
        if(opcode == 0){
            break;
        }

        if(opcode == 1){//para fazer a inserção na arvore
            //printf("Entre com o numero de pessoas para inserir na arvore\n");
            scanf("%d", &n_pessoas);
            for(int rubro = 0; rubro < n_pessoas; rubro++){
                //aqui vamos fazer a insercao da nossas pessoas 
                scanf("%s", pessoa.nome);
                scanf("%d", &pessoa.idade);
                novoNo = criaNoArvore(&pessoa);
                insereArvore(arvore, novoNo);
            }  
        }

        if(opcode == 2){
            //imprimeArvoreCompleta( arvore);
            printInOrder(arvore); //pesquisar depois, mas o printInOrder deve ser o buscacentral
        }
    }while(opcode != 0); //podemos trocar pelo while mas o primeiro condicional como opcode == pode sair do loop
    desalocarArvore(arvore);
    return 0;
}
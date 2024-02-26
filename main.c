#include <stdio.h>
#include <stdlib.h>

#include "tabelaHash.h"

int main(){
	imprimirDadosAlunos();

    int M;

    printf("insira um inteiro positivo que representará o tamanho da tabela.\n");
    scanf("%d",&M);

    struct nodoHash* tabela = gerarTabelaHash(M);
    char opcao;
    int valor;
    struct nodoHash* retorno = NULL;

    scanf("%c", &opcao);
    while(opcao != 'f'){
        switch(opcao){
            case 'f':
                //finalizar
                break;
            case 'i':
                scanf("%d", &valor);
                inserir(tabela, M ,valor);
                break;
            case 'b':
                scanf("%d", &valor);
                retorno = buscar(tabela, M , valor);
                if(retorno){
                    printf("Valor encontrado: %d\n", retorno->chave);
                }else{
                    printf("Valor nao encontrado!\n");
                }
                break;
            case 'l':
                imprimirTabelaHash(tabela,M);
                break;
            case 'r':
                //verifica se o valor esta na tabela, se estiver o remove
                scanf("%d", &valor);
                retorno = buscar(tabela, M , valor);
                if(retorno){
                    excluir(tabela, M,retorno);
                    break;
                }
                printf("falha ao remover.\n");
                break;
        }
        scanf(" %c", &opcao);
    }

    liberarTabelaHash(tabela,M);
    free(tabela);

    return 0;
}
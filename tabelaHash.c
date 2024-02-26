#include "tabelaHash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void matarProgramaFaltaMemoria() {
    fputs("Falha ao alocar memoria.\n", stderr);
    exit(1);
}

struct aluno* getAluno1() {
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if (!retorno) matarProgramaFaltaMemoria();
    retorno->nome = malloc(sizeof("Bruno Vila Lobus Strapasson"));  // sizeof conta o \0
    if (!retorno->nome)
        matarProgramaFaltaMemoria();
    retorno->nomeDinf = malloc(sizeof("bvls21"));
    if (!(retorno->nomeDinf))
        matarProgramaFaltaMemoria();

    strcpy(retorno->nome, "Bruno Vila Lobus Strapasson");
    strcpy(retorno->nomeDinf, "bvls21");
    retorno->grr = 20215522;

    return retorno;
}

struct aluno* getAluno2() {
    return NULL;
}

void imprimirDadosAlunos() {
    struct aluno* aluno = getAluno1();

    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    aluno = getAluno2();
    if (!aluno) return;

    printf("...E... \n\n");
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);
}

// inicializa a tabela com uma lista vazia em cada posição do vetor
struct nodoHash* gerarTabelaHash(size_t tamTabela){
	struct nodoHash* tabela = (struct nodoHash*)malloc(tamTabela * sizeof(struct nodoHash));
    if (!tabela){
        printf("Erro ao alocar a tabela hash.\n");
        return NULL;
    }

    for(size_t i = 0;i < tamTabela; i++){
        tabela[i].chave = -9999;
        tabela[i].anterior = NULL;
        tabela[i].proximo = NULL;
    }

	return tabela;
}

// função de hash
int funcaohash(int mat,int M){
    int hash = mat % M;
    if (hash < 0) {
        hash += M;
    }
    return hash;
}

struct nodoHash* inserir(struct nodoHash tabelaHash[], size_t tamTabela, int chave){
    int pos = funcaohash(chave,tamTabela); // calcula a posicao onde devemos inserir o elemento

    struct nodoHash* lista = &tabelaHash[pos];
    if (lista != NULL) {
        if (buscar(tabelaHash,tamTabela,chave)) { // verificando se a chave já existe
            printf("falha ao inserir %d \n", chave);
            return tabelaHash;
        }
    }

    struct nodoHash* novoNodo = malloc(sizeof(struct nodoHash));
    if (novoNodo == NULL) {
        printf("Erro alocação memória!\n");
        exit(1);
    }
    novoNodo->chave = chave;
    novoNodo->proximo = NULL;

    while (lista->proximo != NULL) {
        lista = lista->proximo;
    }

    lista->proximo = novoNodo;
    novoNodo->anterior = lista;

    return tabelaHash;
}

void liberarTabelaHash(struct nodoHash tabelaHash[], size_t tamTabela){
    int i;
    struct nodoHash* proximo;
    for (i = 1; i < tamTabela; i++) {
        struct nodoHash* lista = &tabelaHash[i];
        proximo = lista->proximo;
        lista = proximo;
        while (lista != NULL) {   
            proximo = lista->proximo;
            free(lista);
            lista = proximo;
        }
    }
}

void imprimirTabelaHash(struct nodoHash tabelaHash[], size_t tamTabela){
    int i;
    for (i = 0; i < tamTabela ; i++){
        printf("%d ", i);
        // Percorre lista imprimindo-a
        struct nodoHash* lista = &tabelaHash[i];
        lista = lista->proximo;
        while (lista != NULL) {
                printf("[%d] -> ", lista->chave);
            lista = lista->proximo;
        }
        printf("NULL\n");
    }
}

struct nodoHash* buscar(struct nodoHash tabelaHash[], size_t tamTabela, int chave){
    int pos = funcaohash(chave,tamTabela); // calcula a posicao onde o elemento deveria estar

    struct nodoHash* lista = &tabelaHash[pos];

    while (lista != NULL) {
        if (lista->chave == chave) {
            //valor encontrado
            return lista;
        }
        lista = lista->proximo;
    }

    //valor não encontrado
    return NULL;
}

void excluir(struct nodoHash tabelaHash[], size_t tamTabela, struct nodoHash* nodo){
    int pos = funcaohash(nodo->chave,tamTabela);

    if (nodo->anterior == NULL) {
        tabelaHash[pos].proximo = nodo->proximo;
        if (nodo->proximo != NULL) {
            nodo->proximo->anterior = NULL;
        }
    } else {
        nodo->anterior->proximo = nodo->proximo;
        if (nodo->proximo != NULL) {
            nodo->proximo->anterior = nodo->anterior;
        }
    }
    free(nodo);
}
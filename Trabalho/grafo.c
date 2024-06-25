#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"


//lista de adjacência
struct no{

    int vertice;
    No* proximo_vertice;

};

//grafo
struct grafo{
    int num_vertice;
    No* lista_adjacencia[MAX_VERTICES];
};

Grafo* criarGrafo(int numero_vertice){

    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));

    if(grafo == NULL){
        printf("Memoria Insuficiente.");
        exit(1);
    }

    grafo->num_vertice = numero_vertice;

    for(int i = 0; i < numero_vertice; i++){
        grafo->lista_adjacencia[i] = NULL;
    }

    return grafo;
}

void adicionarAresta(Grafo* grafo, int origem, int destino) {
    // Verifica se a aresta já existe na direção origem -> destino
    No* atual = grafo->lista_adjacencia[origem];
    while (atual != NULL) {
        if (atual->vertice == destino) {
            printf("Aresta de %d para %d já existe.\n", origem, destino);
            return;
        }
        atual = atual->proximo_vertice;
    }

    // Verifica se a aresta já existe na direção destino -> origem
    atual = grafo->lista_adjacencia[destino];
    while (atual != NULL) {
        if (atual->vertice == origem) {
            printf("Aresta de %d para %d já existe.\n", destino, origem);
            return;
        }
        atual = atual->proximo_vertice;
    }

    // Se não existe a aresta em nenhuma das direções, adiciona-a na direção origem -> destino
    No* adjacencia = (No*)malloc(sizeof(No));
    if (adjacencia == NULL) {
        printf("Memoria Insuficiente.");
        exit(1);
    }

    adjacencia->vertice = destino;
    adjacencia->proximo_vertice = grafo->lista_adjacencia[origem];

    grafo->lista_adjacencia[origem] = adjacencia;
}


void imprimirGrafo(Grafo* grafo){

    int i = 0;

    while(i < grafo->num_vertice){
        No* adjacentia_temporaria = grafo->lista_adjacencia[i];
        printf("O vertice %d faz ligacao com: \n", i);

        while (adjacentia_temporaria != NULL){
            printf("%d, ", adjacentia_temporaria->vertice);
            adjacentia_temporaria = adjacentia_temporaria->proximo_vertice;
        }

        printf("NULL \n");
        
        i++;
    }
}

void verificarEImprimirTodasBidirecionais(Grafo* grafo) {
    int numero_vertices = grafo->num_vertice;

    // Verifica para cada par de vértices (i, j) onde i < j
    for (int i = 0; i < numero_vertices; i++) {
        No* adjacente_temporario = grafo->lista_adjacencia[i];

        while (adjacente_temporario != NULL) {
            int j = adjacente_temporario->vertice;

            // Verifica se existe a ligação i -> j
            if (existeAresta(grafo, i, j)) {
                printf("Existe a ligacao %d -> %d logo, exite a ligacao %d -> %d\n", i, j, j, i);
            }

            adjacente_temporario = adjacente_temporario->proximo_vertice;
        }
    }
}

void gerarGrafoAleatorio(Grafo* grafo, int numerto_aresta){

    int numero_vertice = grafo->num_vertice;
    int arestas_adicionadas = 0;

    while (arestas_adicionadas < numerto_aresta){

        int origem = rand() % numero_vertice;
        int destino = rand() % numero_vertice;

        if(origem != destino && !existeAresta(grafo, origem, destino)){
            adicionarAresta(grafo, origem, destino);
            arestas_adicionadas++;
        }
    }
}

int existeAresta(Grafo* grafo, int origem, int destino) {
    // Verifica se existe a aresta de origem para destino
    No* atual = grafo->lista_adjacencia[origem];
    while (atual != NULL) {
        if (atual->vertice == destino) {
            return 1;
        }
        atual = atual->proximo_vertice;
    }

    // Verifica se existe a aresta de destino para origem
    atual = grafo->lista_adjacencia[destino];
    while (atual != NULL) {
        if (atual->vertice == origem) {
            return 1;
        }
        atual = atual->proximo_vertice;
    }

    return 0;
}

void liberarGrafo(Grafo* grafo) {
    if (grafo == NULL) {
        return;
    }

    for (int i = 0; i < grafo->num_vertice; i++) {
        No* atual = grafo->lista_adjacencia[i];
        while (atual != NULL) {
            No* proximo = atual->proximo_vertice;
            free(atual);
            atual = proximo;
        }
    }
    free(grafo);
}

int maxArestas(int n) {
    return n * (n - 1) / 2;
}



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

void adicionarAresta(Grafo* grafo, int origem, int destino){

    No* adjacencia = (No*)malloc(sizeof(No));

    if(adjacencia == NULL){
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
        printf("Lista de adjacencia do vertice %d: \n", i);

        while (adjacentia_temporaria != NULL){
            printf("%d -> ", adjacentia_temporaria->vertice);
            adjacentia_temporaria = adjacentia_temporaria->proximo_vertice;
        }

        printf("NULL \n");
        
        i++;
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

int existeAresta(Grafo* grafo, int origem, int destino){
    No* atual = grafo->lista_adjacencia[origem];

    while(atual != NULL){
        if(atual->vertice == destino){
            return 1;
        }

        atual = atual->proximo_vertice;
    }

    return 0;
}

void liberarGrafo(Grafo* grafo) {
    if (grafo == NULL) {
        return; // Verifica se o grafo é NULL
    }

    // Desaloca cada lista de adjacência
    for (int i = 0; i < grafo->num_vertice; i++) {
        No* atual = grafo->lista_adjacencia[i];
        while (atual != NULL) {
            No* proximo = atual->proximo_vertice;
            free(atual); // Libera o nó atual
            atual = proximo;
        }
    }

    // Libera a estrutura do grafo em si
    free(grafo);
}

int maxArestas(int n) {
    return n * (n - 1) / 2;
}


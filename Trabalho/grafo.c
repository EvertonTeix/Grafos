#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafo.h"

// lista de adjacência
struct no
{
    int vertice;
    No *proximo_vertice;
};

// grafo
struct grafo
{
    int num_vertice;
    int* visitado;  // Array para marcar os vértices visitados
    int* na_pilha;  // Array para marcar os vértices na pilha de recursão
    int* ciclo;      // Array para armazenar os vértices do ciclo
    int ciclo_indice; 
    No *lista_adjacencia[MAX_VERTICES];
};

Grafo* criarGrafo(int num_vertice) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if (grafo == NULL) {
        printf("Erro ao alocar memória para o grafo.\n");
        exit(1);
    }

    grafo->num_vertice = num_vertice;
    grafo->visitado = (int*)malloc(num_vertice * sizeof(int));
    if (grafo->visitado == NULL) {
        printf("Erro ao alocar memória para o vetor visitado.\n");
        free(grafo);  // Libera a memória alocada para o grafo
        exit(1);
    }

    grafo->na_pilha = (int*)malloc(num_vertice * sizeof(int));
    if (grafo->na_pilha == NULL) {
        printf("Erro ao alocar memória para o vetor na_pilha.\n");
        free(grafo->visitado);  // Libera a memória alocada para o vetor visitado
        free(grafo);  // Libera a memória alocada para o grafo
        exit(1);
    }

    grafo->ciclo = (int*)malloc(num_vertice * sizeof(int));
    if (grafo->ciclo == NULL) {
        printf("Erro ao alocar memória para o vetor ciclo.\n");
        free(grafo->na_pilha);  // Libera a memória alocada para o vetor na_pilha
        free(grafo->visitado);  // Libera a memória alocada para o vetor visitado
        free(grafo);  // Libera a memória alocada para o grafo
        exit(1);
    }

    grafo->ciclo_indice = 0;

    for (int i = 0; i < num_vertice; i++) {
        grafo->lista_adjacencia[i] = NULL;
        grafo->visitado[i] = 0;
        grafo->na_pilha[i] = 0;
        grafo->ciclo[i] = -1;
    }

    return grafo;
}


void adicionarAresta(Grafo *grafo, int origem, int destino)
{
    // Verifica se a aresta já existe na direção origem -> destino
    if (existeAresta(grafo, origem, destino))
    {
        return;
    }

    // Verifica se a aresta já existe na direção destino -> origem (para grafos não dirigidos)
    if (existeAresta(grafo, destino, origem))
    {
        return;
    }

    // Adiciona a aresta origem -> destino
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL)
    {
        printf("Memoria Insuficiente.\n");
        exit(1);
    }
    novo_no->vertice = destino;
    novo_no->proximo_vertice = grafo->lista_adjacencia[origem];
    grafo->lista_adjacencia[origem] = novo_no;

    // Adiciona a aresta destino -> origem (para grafos não dirigidos)
    novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL)
    {
        printf("Memoria Insuficiente.\n");
        exit(1);
    }
    novo_no->vertice = origem;
    novo_no->proximo_vertice = grafo->lista_adjacencia[destino];
    grafo->lista_adjacencia[destino] = novo_no;
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

void imprimirGrafo(Grafo *grafo)
{
    for (int i = 0; i < grafo->num_vertice; i++)
    {
        No *adjacencia_temporaria = grafo->lista_adjacencia[i];
        printf("O vertice %d faz ligacao com: \n", i);

        while (adjacencia_temporaria != NULL)
        {
            printf("%d, ", adjacencia_temporaria->vertice);
            adjacencia_temporaria = adjacencia_temporaria->proximo_vertice;
        }
    }
}

int existeAresta(Grafo *grafo, int origem, int destino)
{
    No *atual = grafo->lista_adjacencia[origem];
    while (atual != NULL)
    {
        if (atual->vertice == destino)
        {
            return 1;
        }
        atual = atual->proximo_vertice;
    }
    return 0;
}

void liberarGrafo(Grafo *grafo)
{
    if (grafo == NULL)
    {
        return;
    }

    for (int i = 0; i < grafo->num_vertice; i++)
    {
        No *atual = grafo->lista_adjacencia[i];
        while (atual != NULL)
        {
            No *proximo = atual->proximo_vertice;
            free(atual);
            atual = proximo;
        }
    }
    free(grafo->ciclo);
    free(grafo->na_pilha);
    free(grafo->visitado);
    free(grafo);
}


int maxArestas(int n)
{
    return n * (n - 1) / 2;
}

int verificaCiclo(Grafo* grafo, int v, int pai) {

    grafo->visitado[v] = 1;
    grafo->na_pilha[v] = 1;


    grafo->ciclo[grafo->ciclo_indice++] = v;


    No* atual = grafo->lista_adjacencia[v];
    while (atual != NULL) {
        int adj = atual->vertice;

        // Se o vértice adjacente não foi visitado, faz uma chamada recursiva
        if (!grafo->visitado[adj]) {
            if (verificaCiclo(grafo, adj, v)) {
                return 1;  // Se um ciclo é encontrado
            }
        } else if (adj != pai) {
            // Se o vértice adjacente está na pilha e não é o pai, um ciclo é encontrado
            grafo->ciclo[grafo->ciclo_indice++] = adj;  // Adiciona o vértice adjacente para fechar o ciclo
            return 1;
        }

        atual = atual->proximo_vertice;
    }

    // Remove o vértice atual da pilha de recursão e do vetor ciclo
    grafo->na_pilha[v] = 0;
    grafo->ciclo[--grafo->ciclo_indice] = -1;
    return 0;
}

void pegaGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->num_vertice; i++) {
        grafo->visitado[i] = 0;
        grafo->na_pilha[i] = 0;
        grafo->ciclo[i] = -1;  // Inicializa o vetor ciclo com -1 (indicando vazio)
    }
    grafo->ciclo_indice = 0;

    for (int i = 0; i < grafo->num_vertice; i++) {
        if (!grafo->visitado[i]) {
            if (verificaCiclo(grafo, i, -1)) {
                printf("Ciclo encontrado: ");
                int ciclo_inicio = grafo->ciclo[grafo->ciclo_indice - 1];
                int j = 0;
                for (; j < grafo->ciclo_indice; j++) {
                    if (grafo->ciclo[j] == ciclo_inicio) {
                        break;
                    }
                }
                for (; j < grafo->ciclo_indice; j++) {
                    printf("%d ", grafo->ciclo[j]);
                }
                return;
            }
        }
    }
    printf("Nenhum ciclo encontrado.\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grafo.h"

int main() {
    srand(time(NULL));
    int numero_vertices;
    int numero_arestas;

    printf("Digite o numero de vertices que vc deseja: ");
    scanf("%d", &numero_vertices);

    int max_arestas = maxArestas(numero_vertices);
    printf("O numero maximo de arestas para um grafo com %d vertices e %d.\n", numero_vertices, max_arestas);

    do {
        printf("Digite o numero de arestas que vc deseja no seu grafo: ");
        scanf("%d", &numero_arestas);

        if (numero_arestas > max_arestas) {
            printf("Numero de arestas excede o maximo permitido. Tente novamente.\n");
        }
    } while (numero_arestas > max_arestas);

    Grafo* grafo = criarGrafo(numero_vertices);

    gerarGrafoAleatorio(grafo, numero_arestas);

    imprimirGrafo(grafo);

    pegaGrafo(grafo);
    
    liberarGrafo(grafo);

    return 0;
}

/*Arquivo de protótipo do tipo grafo.c*/

#define MAX_VERTICES 100
#define MAX_ARESTAS_RETORNO 500 // Valor inicial de 500 arestas de retorno


typedef struct no No;
typedef struct grafo Grafo;

/*Cria um grafo a partir do numero de vértices*/
Grafo* criarGrafo(int numero_vertice);

/*Cria um grafo a partir do numero de vértices e arestas definidas pelos usuários*/
void gerarGrafoAleatorio(Grafo* grafo, int numerto_aresta);

/*Imprime um grafo*/
void imprimirGrafo(Grafo* grafo);

/*Verifica se existe uma aresta específica no grafo*/
int existeAresta(Grafo* grafo, int origem, int destino);

/*Libera a memória alocada para o grafo*/
void liberarGrafo(Grafo* grafo);

/*Retorna o número máximo de arestas que um grafo com X vértices pode ter*/
int maxArestas(int n);

// Função para detectar ciclos no grafo
int verificaCiclo(Grafo* grafo, int v, int pai);

void pegaGrafo(Grafo* grafo);


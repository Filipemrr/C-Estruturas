#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct adjacencia {
    int vertice;
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice {
    ADJACENCIA *cab;
    int visitado;
} VERTICE;

typedef struct grafo {
    int vertices;
    VERTICE vertice[MAX_VERTICES];
} GRAFO;

GRAFO* criarGrafo(int numVertices) {
    GRAFO *g = (GRAFO*)malloc(sizeof(GRAFO));
    g->vertices = numVertices;

    for (int i = 0; i < numVertices; i++) {
        g->vertice[i].cab = NULL;
        g->vertice[i].visitado = 0;
    }

    return g;
}

void adicionarAresta(GRAFO *g, int origem, int destino) {
    ADJACENCIA *novaAresta = (ADJACENCIA*)malloc(sizeof(ADJACENCIA));
    novaAresta->vertice = destino;
    novaAresta->prox = g->vertice[origem].cab;
    g->vertice[origem].cab = novaAresta;
}

void DFS(GRAFO *g, int v) {
    printf("Visitando vértice: %d\n", v);

    g->vertice[v].visitado = 1;

    ADJACENCIA *adjacente = g->vertice[v].cab;
    while (adjacente != NULL) {
        int verticeAdjacente = adjacente->vertice;

        if (!g->vertice[verticeAdjacente].visitado) {
            DFS(g, verticeAdjacente);
        }

        adjacente = adjacente->prox;
    }
}

void DFSInicial(GRAFO *g, int verticeInicial) {
    for (int i = 0; i < g->vertices; i++) {
        g->vertice[i].visitado = 0;
    }

    DFS(g, verticeInicial);
}

int main() {
    GRAFO *grafo = criarGrafo(6);

    adicionarAresta(grafo, 0, 1);
    adicionarAresta(grafo, 0, 2);
    adicionarAresta(grafo, 1, 3);
    adicionarAresta(grafo, 2, 4);
    adicionarAresta(grafo, 3, 4);
    adicionarAresta(grafo, 3, 5);
    adicionarAresta(grafo, 4, 5);

    DFSInicial(grafo, 0);

    return 0;
}

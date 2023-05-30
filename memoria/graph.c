#include <stdio.h>
#include <stdlib.h>

struct Node {
    int dest;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjList;
};

struct Node* createNode(int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjList = (struct Node**)malloc(numVertices * sizeof(struct Node*));

    for (int i = 0; i < numVertices; i++) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Para um grafo não direcionado, adicione uma aresta inversa também
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void DFSUtil(int vertex, int visited[], struct Graph* graph) {
    visited[vertex] = 1;
    printf("Visitando vértice: %d\n", vertex);

    struct Node* adjNode = graph->adjList[vertex];
    while (adjNode != NULL) {
        int adjVertex = adjNode->dest;
        if (visited[adjVertex] == 0) {
            DFSUtil(adjVertex, visited, graph);
        }
        adjNode = adjNode->next;
    }
}

void DFS(struct Graph* graph, int startVertex) {
    int* visited = (int*)malloc(graph->numVertices * sizeof(int));//arr[tamano do grafo criado]
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0;
    }

    DFSUtil(startVertex, visited, graph);

    free(visited);
}

int main() {
    int numVertices = 6;
    struct Graph* graph = createGraph(numVertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 5);

    int startVertex = 0;
    DFS(graph, startVertex);

    return 0;
}

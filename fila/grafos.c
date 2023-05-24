void profundidade(grafo *g, int v, int contador)
{   
    printf("%d ", v);

    contador += 1;
    g->visitado[v] = contador;

    lista_adj *aux = g->lista_adj[v];

    while (aux != NULL)
    {
        if (g->visitado[aux->v] == 0)
            dfs(g, aux->v, contador);
        
        aux = aux->prox;
    }   
}

void largur(grafo *g, int v)
{

int contador = 0;

fila *q = NULL;
enfileirar(v, &q);

while (q != NULL)
{
    int desenfileirado = desenfileirar(&q);
    lista_adj *aux = g->lista_adj[desenfileirado];
    
    printf("%d ", contador);

    while (aux != NULL)
    {
        if (g->visitado[aux->v] == 0)
            enfileirar(aux->v, &q);
        
        aux = aux->prox;
    }

    contador += 1;
    g->visitado[desenfileirado] = contador;
}
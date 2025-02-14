#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void list_insert(list **L, list *x)
{
    x->next = *L;
    if (*L != NULL)
        (*L)->prev = x;
    *L = x;
    x->prev = NULL;
}

void list_delete(list **L, list *x)
{
    if (x->prev != NULL)
        x->prev->next = x->next;
    else
        *L = x->next;
    if (x->next != NULL)
        x->next->prev = x->prev;
}

list *list_search(list *L, int k)
{
    list *x = L;
    while (x != NULL && x->key != k)
        x = x->next;
    return x;
}

void print_list(list *L)
{
    list *x = L;
    while (x != NULL)
    {
        printf("%i -> ", x->key);
        x = x->next;
    }
    printf("\n");
}

list *allocate_object(int k)
{
    list *x = (list *)malloc(sizeof(struct lista_duplamente_encadeada));
    x->key = k;
    x->next = NULL;
    x->prev = NULL;
    return x;
}

void free_object(list *x)
{
    free(x);
}

grafo *graph_search(grafo *L, int k)
{
    grafo *x = L;
    while (x != NULL && x->key != k)
        x = x->next;
    return x;
}

void node_insert(grafo **G, grafo *x)
{
    x->next = *G;
    if (*G != NULL)
        (*G)->prev = x;
    *G = x;
    x->prev = NULL;
}

void node_delete(grafo **G, grafo *x)
{
    if (x->prev != NULL)
        x->prev->next = x->next;
    else
        *G = x->next;
    if (x->next != NULL)
        x->next->prev = x->prev;
}

grafo *allocate_graph(int k)
{
    grafo *x = (grafo *)malloc(sizeof(struct nos));
    x->key = k;
    x->arestas = NULL;
    x->next = NULL;
    x->prev = NULL;
    return x;
}

void free_graph(grafo *x)
{
    list *aux = x->arestas;
    while (aux != NULL)
    {
        list_delete(&x->arestas, aux);
        free_object(aux);
        aux = x->arestas;
    }
    free(x);
}

void print_graph(grafo *g)
{
    grafo *auxg = g;
    while (auxg != NULL)
    {
        printf("No: %i \n\t\t Arestas: ", auxg->key);

        list *auxl = auxg->arestas;
        while (auxl != NULL)
        {
            printf("%i -> ", auxl->key);
            auxl = auxl->next;
        }
        printf("\nGrau: %d.\n", auxg->grau);
        auxg = auxg->next;
    }
}

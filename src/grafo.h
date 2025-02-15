#ifndef GRAFO_H
#define GRAFO_H

typedef struct lista_duplamente_encadeada
{
    struct lista_duplamente_encadeada *prev;
    int key;
    struct lista_duplamente_encadeada *next;
} list;

typedef struct nos
{
    struct nos *prev;
    int key;
    int grau; // Campo para armazenar o grau do nó
    list *arestas;
    struct nos *next;
} grafo;

void list_insert(list **L, list *x); // Insere nó na lista
void list_delete(list **L, list *x);
list *list_search(list *L, int k); // Procura nó na lista
void print_list(list *L);
list *allocate_object(int k);   // Aloca nó
void free_object(list *x);
grafo *graph_search(grafo *L, int k);
void node_insert(grafo **G, grafo *x); // Insere nó
void node_delete(grafo **G, grafo *x);
grafo *allocate_graph(int k); // Aloca nó
void free_graph(grafo *x); // Libera memória alocada para nó
void print_graph(grafo *g); // Imprime grafo
void calcula_grau(grafo **G); // Calcula grau dos nós

#endif

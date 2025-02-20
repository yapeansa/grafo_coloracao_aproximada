#include <stdlib.h>
#include <limits.h>
#include "coloracao.h"
#include "grafo.h"

// Adaptação do Merge Sort visto em aula
// para ordenar os nós em ordem não crescente em relação ao grau
void merge(grafo *v, int p, int q, int r)
{
    int m = q - p + 1,
        n = r - q;
    grafo e[m + 1], d[n + 1];

    for (int i = 0; i < m; i++)
        e[i] = v[p + i];

    for (int j = 0; j < n; j++)
        d[j] = v[q + j + 1];

    e[m].grau = INT_MIN;
    d[n].grau = INT_MIN;

    int i = 0, j = 0;
    for (int k = p; k <= r; k++)
    {
        if (e[i].grau <= d[j].grau)
        {
            v[k] = d[j];
            j++;
        }
        else
        {
            v[k] = e[i];
            i++;
        }
    }
}

void merge_sort(grafo *v, int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        merge_sort(v, p, q);
        merge_sort(v, q + 1, r);
        merge(v, p, q, r);
    }
}

int contando_cores(grafo **cores, int nodes)
{
    int quantidade = 0;

    for (int i = 0; i < nodes; i++)
        if (cores[i] != NULL)
            quantidade++;

    return quantidade;
}

int coloracao(int nodes, grafo *vet)
{
    int n_de_cores = 0;
    grafo *aux = NULL;
    list *aux2 = NULL;
    // Ordena vetor de nós em ordem não crescente em relação ao grau
    merge_sort(vet, 0, nodes - 1);

    grafo *cores[nodes]; // Definindo vetor de cores

    // Inicializando vetor de cores
    for (int i = 0; i < nodes; i++)
        cores[i] = NULL;

    // Colorindo o primeiro nó com a primeira cor
    node_insert(&cores[0], allocate_graph(vet[0].key));

    // Colorindo os demais nós
    int j = 1;
    while (j < nodes)
    {
        aux2 = vet[j].arestas; // Lista de adjacência do nó
        int r;

        // Percorre as cores
        int i = 0;
        while (i < nodes)
        {
            aux = cores[i];
            // Se a cor estiver vazia, insere o nó
            if (cores[i] == NULL)
            {
                r = i;
                node_insert(&cores[r], allocate_graph(vet[j].key));
                j++;
                break;
            }
            // Senão, verifica se o nó adjacente é igual a algum nó da cor
            else
            {
                while (aux != NULL)
                {
                    // Se for adjacente a algum nó da cor, passa para a próxima cor
                    if (list_search(aux2, aux->key) != NULL)
                    {
                        i++;
                        break;
                    }
                    aux = aux->next;
                }
                // Se não for adjacente a nenhum nó da cor, insere o nó
                if (aux == NULL)
                {
                    r = i;
                    node_insert(&cores[r], allocate_graph(vet[j].key));
                    j++;
                    break;
                }
            }
        }
    }

    n_de_cores = contando_cores(cores, nodes);

    return n_de_cores;
}

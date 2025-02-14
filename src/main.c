#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"

FILE *arq_entrada;

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

int main(void)
{
    grafo *head = NULL, *aux = NULL;
    list *aux2 = NULL;

    int nodes, edges;    // Variáveis utilizadas para armazenar número de nós e arestas
    int orig, dest;      // Variáveis utilizadas para armazenar nós de origem e destino
    int numero_de_cores; // Variável utilizada para exibir o número de cores utilizadas
    grafo *vet;          // Um vetor auxiliar para armazenar os nós

    arq_entrada = fopen("entrada.txt", "r"); // Abre arquivo de entrada

    // Verifica se o arquivo foi aberto corretamente
    if (arq_entrada == NULL)
    {
        printf("Um erro ocorreu ao tentar abrir o arquivo 'grafo.txt'.\n");
        exit(1); // Encerra o programa
    }

    fscanf(arq_entrada, "%d", &nodes); // Lê número de nós
    printf("Número de nós: %d\n", nodes);

    // Construção do grafo

    // Inserindo nós
    for (int i = 1; i <= nodes; i++)
        node_insert(&head, allocate_graph(i));

    fscanf(arq_entrada, "%d", &edges); // Lê número de arestas
    printf("Número de arestas: %d\n", edges);

    // Inserindo arestas
    for (int i = 1; i <= edges; i++)
    {
        fscanf(arq_entrada, "%d %d", &orig, &dest); // Lê origem e destino
        aux = graph_search(head, orig);
        if (aux != NULL)
        {
            list_insert(&aux->arestas, allocate_object(dest));
            aux = graph_search(head, dest);
            if (aux != NULL)
                list_insert(&aux->arestas, allocate_object(orig));
        }
    }

    calcula_grau(&head); // Calcula grau dos nós

    printf("Grafo com grau:\n");
    print_graph(head);

    vet = (grafo *)malloc(nodes * sizeof(grafo)); // Aloca vetor de nós

    // Preenche vetor de nós
    int i = 0;
    aux = head;
    while (aux != NULL)
    {
        vet[i] = *aux;
        aux = aux->next;
        i++;
    }

    // Daqui em diante temos o algoritmo para a coloração do grafo

    merge_sort(vet, 0, nodes - 1); // Ordena vetor de nós em ordem não crescente em relação ao grau

    // printf("Vetor de nós ordenado por grau:\n");

    // for (int i = 0; i < nodes; i++)
    //     printf("No: %i \n\t\t Grau: %d\n", vet[i].key, vet[i].grau);

    grafo *cores[nodes]; // Vetor de cores

    for (int i = 0; i < nodes; i++)
        cores[i] = NULL;

    node_insert(&cores[0], allocate_graph(vet[0].key)); // Insere primeiro nó no vetor de cores

    int j = 1;
    while (j < nodes)
    {
        aux2 = vet[j].arestas;
        int r;

        int i = 0;
        while (i < nodes)
        {
            aux = cores[i];
            if (cores[i] == NULL)
            {
                r = i;
                node_insert(&cores[r], allocate_graph(vet[j].key));
                j++;
                i++;
                break;
            }
            else
            {
                while (aux != NULL)
                {
                    if (list_search(aux2, aux->key) != NULL)
                    {
                        i++;
                        break;
                    }
                    aux = aux->next;
                }
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

    // Contagem de cores utilizadas
    numero_de_cores = contando_cores(cores, nodes);

    printf("\nNúmero de cores utilizadas (aproximadamente): %d\n", numero_de_cores);

    // printf("Cor 1:\n");
    // print_graph(cores[0]);
    // printf("Cor 2:\n");
    // print_graph(cores[1]);
    // printf("Cor 3:\n");
    // print_graph(cores[2]);
    // printf("Cor 4:\n");
    // print_graph(cores[3]);
    // printf("Cor 5:\n");
    // print_graph(cores[4]);

    fclose(arq_entrada); // Fecha arquivo de entrada
}

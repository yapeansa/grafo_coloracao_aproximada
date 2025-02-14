#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"

FILE *arq_entrada; // Ponteiro para arquivo de entrada

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

void calcula_grau(grafo **G)
{
    grafo *auxg = *G;
    while (auxg != NULL)
    {
        int grau = 0;
        list *auxl = auxg->arestas;
        while (auxl != NULL)
        {
            grau++;
            auxl = auxl->next;
        }
        auxg->grau = grau;
        auxg = auxg->next;
    }
}

// Preenchendo vetor auxiliar
void preenche_vetor(grafo *head, grafo *vet)
{
    grafo *aux = head;
    int i = 0;
    while (aux != NULL)
    {
        vet[i] = *aux;
        aux = aux->next;
        i++;
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

    n_de_cores = contando_cores(cores, nodes);

    return n_de_cores;
}

int main(void)
{
    grafo *head = NULL, *aux = NULL;
    list *aux2 = NULL;

    int nodes, edges;    // Variáveis utilizadas para armazenar número de nós e arestas
    int orig, dest;      // Variáveis utilizadas para armazenar nós de origem e destino
    int numero_de_cores; // Variável utilizada para exibir o número de cores utilizadas
    grafo *vet;          // Um vetor auxiliar para armazenar os nós e ordená-los em relação ao grau

    arq_entrada = fopen("entrada.txt", "r"); // Abre arquivo 'entrada.txt' para leitura

    // Verifica se o arquivo foi aberto corretamente
    if (arq_entrada == NULL)
    {
        printf("Um erro ocorreu ao tentar abrir o arquivo 'entrada.txt'.\n");
        exit(-1); // Encerra o programa
    }

    fscanf(arq_entrada, "%d", &nodes); // Lê número de nós
    printf("Número de nós: %d\n", nodes);

    fscanf(arq_entrada, "%d", &edges); // Lê número de arestas
    printf("Número de arestas: %d\n", edges);

    // Construção do grafo

    // Inserindo nós
    for (int i = 1; i <= nodes; i++)
        node_insert(&head, allocate_graph(i));

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

    // Função para calcular o grau dos nós
    calcula_grau(&head);

    printf("Grafo:\n\n");
    print_graph(head); // Imprime grafo

    // Definindo um vetor auxiliar para armazenar os nós
    vet = (grafo *)malloc(nodes * sizeof(grafo)); // Aloca vetor de nós

    // Preenchendo vetor auxiliar
    preenche_vetor(head, vet);

    // Algoritmo para a coloração do grafo e contagem de cores utilizadas
    numero_de_cores = coloracao(nodes, vet);

    // Exibindo o número de cores utilizadas
    printf("\nColoração:");
    printf("\nNúmero de cores utilizadas (aproximadamente): %d\n", numero_de_cores);

    free(vet);           // Libera memória alocada para vetor de nós
    free_graph(head);    // Libera memória alocada para grafo
    fclose(arq_entrada); // Fecha arquivo de entrada
}

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "coloracao.h"

FILE *arq_entrada; // Ponteiro para arquivo de entrada

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

int main(void)
{
    grafo *head = NULL, *aux = NULL;
    // list *aux2 = NULL;

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
    printf("\nNúmero aproximado de cores necessárias: %d\n", numero_de_cores);

    free(vet);           // Libera memória alocada para vetor de nós
    free_graph(head);    // Libera memória alocada para grafo
    fclose(arq_entrada); // Fecha arquivo de entrada
}

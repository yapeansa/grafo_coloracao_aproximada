#ifndef COLORACAO_H
#define COLORACAO_H
#include "grafo.h"

void preenche_vetor(grafo *head, grafo *vet);
void merge(grafo *v, int p, int q, int r);
void merge_sort(grafo *v, int p, int r);
int contando_cores(grafo **cores, int nodes);
int coloracao(int nodes, grafo *vet);

#endif // COLORACAO_H

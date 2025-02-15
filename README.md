# Algoritmo de Coloração Aproximada

## Definições

### k-coloração

Sejam $G(N,A)$ um grafo e $C$ um conjunto de cores. Seja $LA(v) = \\{i \in \mathbb{N}\\,\mid\\,i \text{ é adjacente ao nó }v\\}$ (lista de adjacência). Uma coloração de $G$ é uma atribuição de alguma cor de $C$ para cada vértice de $G$ de tal modo que a dois vértices adjacentes sejam atribuídas cores diferentes. Diz-se que $G$ é $k$-colorível se os vértices de $G$ podem ser coloridos com $k$ cores.

### Número cromático do grafo G

O número cromático de $G$, denotado por $x(G)$ é o menor número $k$ tal que existe uma $k$-coloração de $G$.

## Caracterização

Dado um grafo $G(N,A)$, encontrar o seu número cromático $x(G)$ é uma tarefa complexa. Este problema é classificado como do tipo NP-completo, isto é, um problema de difícil solução. Como alternativa, recorre-se frequentemente a algoritmos aproximados, pois eles oferecem uma "boa" solução. Esta solução, no entanto, não é necessariamente a melhor solução para o problema.

## Algoritmo aproximado

- Iniciação do Algoritmo: ordenar os nós de G numa ordem não crescente em relação ao seu grau.
- $C_1 = C_2 = \ldots = C_n = \emptyset$.
- Colorir $v_1$ com a cor $1$; incluir $v_1$ em $C_1$.
- Para $j = 2, \ldots, n$ efetuar
    - $r = \min\\{i \mid LA(v_j)\\,\cap\\,C_{i}=\emptyset\\}$.
    - Colorir $v_{j}$ com a cor $r$; incluir $v_{j}$ em $C_{r}$.

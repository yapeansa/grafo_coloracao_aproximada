# Algoritmo de Coloração Aproximada

- Iniciação do Algoritmo: ordenar os nós de G numa ordem não crescente em relação ao seu grau.
- $C_1 = C_2 = \ldots = C_n = \emptyset$.
- Colorir $v_1$ com a cor $1$; incluir $v_1$ em $C_1$.
- Para $j = 2, \ldots, n$ efetuar
    - $r = \min\{i \mid A(v_j)\,\cap\,C_{i}=\emptyset\}$.
    - Colorir $v_{j}$ com a cor $r$; incluir $v_{j}$ em $C_{r}$.

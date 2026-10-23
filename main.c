#include <stdio.h>
#include "ListaSequencial.h"

static void imprime_lista(Lista *li) {
    struct produto p;
    int n = tamanho_lista(li);

    printf("Lista com %d produto(s):\n", n);
    for (int i = 1; i <= n; i++) {
        busca_lista_pos(li, i, &p);
        printf("  [%d] cod=%-4d nome=%-12s preco=%.2f\n",
               i, p.codigo, p.nome, p.preco);
    }
}

int main(void) {
    Lista *li = cria_lista();

    struct produto p1 = {101, "Caderno", 12.50f};
    struct produto p2 = {102, "Caneta",   2.30f};
    struct produto p3 = {104, "Mochila", 89.90f};
    struct produto p4 = {103, "Borracha", 1.20f};

    insere_lista_final(li, p1);
    insere_lista_final(li, p2);
    insere_lista_ordenada(li, p3);
    insere_lista_ordenada(li, p4);

    imprime_lista(li);

    printf("\ntamanho_lista: %d\n", tamanho_lista(li));
    printf("lista_vazia:   %d\n", lista_vazia(li));
    printf("lista_cheia:   %d\n", lista_cheia(li));


    /* Q1 */
    printf("\nQ1\n");
    printf("lista_tem_espaco(li, 5): %d\n", lista_tem_espaco(li, 5));

    /* Q2 */
    printf("\nQ2\n");
    printf("soma_precos: %.2f\n", soma_precos(li));

    /* Q3 */
    printf("\nQ3\n");
    struct produto encontrado;
    if (busca_por_nome(li, "Mochila", &encontrado))
        printf("busca_por_nome achou cod=%d\n", encontrado.codigo);

    /* Q4 */
    printf("\nQ4\n");
    struct produto p5 = {105, "Estojo", 25.00f};
    insere_lista_decrescente(li, p5);
    imprime_lista(li);

    /* Q5 */
    printf("\nQ5\n");
    struct produto removido;
    if (remove_mais_caro(li, &removido))
        printf("remove_mais_caro removeu cod=%d preco=%.2f\n",
               removido.codigo, removido.preco);
    imprime_lista(li);

    /* Q6 */
    printf("\nQ6\n");
    printf("conta_faixa_preco(1, 20): %d\n", conta_faixa_preco(li, 1.0f, 20.0f));

    /* Q7 */
    printf("\nQ7\n");
    printf("remove_abaixo_de(10): %d removidos\n", remove_abaixo_de(li, 10.0f));
    imprime_lista(li);

    /* Q8 */
    printf("\nQ8\n");
    Lista *outra = cria_lista();
    insere_lista_final(outra, p1);

    struct produto p6 = {106, "Regua", 3.50f};
    insere_lista_final(outra, p6);

    int inseridos = mescla_listas(li, outra);
    printf("mescla_listas inseriu %d produto(s)\n", inseridos);

    libera_lista(outra);
    imprime_lista(li);

    libera_lista(li);
    return 0;
}

#include <stdio.h>
#include "ListaSequencial.h"

static struct produto mk(int codigo, const char *nome, float preco) {
    struct produto p;
    p.codigo = codigo;
    snprintf(p.nome, sizeof(p.nome), "%s", nome);
    p.preco = preco;
    return p;
}

/* Imprime a lista usando apenas a interface publica:
   qtd=3: 101 Caderno (12.50) | 102 Caneta (2.30) | ... */
static void imprime(const char *rotulo, Lista *li) {
    int i, n = tamanho_lista(li);
    struct produto p;
    printf("  %-24s qtd=%d:", rotulo, n);
    if (n <= 0) {
        printf(" (vazia)\n");
        return;
    }
    for (i = 1; i <= n; i++) {
        busca_lista_pos(li, i, &p);
        printf(" %s%d %s (%.2f)", i > 1 ? "| " : "", p.codigo, p.nome, p.preco);
    }
    printf("\n");
}

/* Monta uma lista com os produtos dados, inserindo no final. */
static Lista* monta(const struct produto *v, int n) {
    Lista *li = cria_lista();
    for (int i = 0; i < n; i++)
        insere_lista_final(li, v[i]);
    return li;
}

static void titulo(const char *t) {
    printf("\n%s\n", t);
}

int main(void) {
    /* lista usada na maioria dos testes: 4 produtos, 105.90 no total */
    struct produto base[] = {
        {101, "Caderno",  12.50f},
        {102, "Caneta",    2.30f},
        {104, "Mochila",  89.90f},
        {103, "Borracha",  1.20f}
    };
    Lista *li, *li2;

    /* ---------- Questao 1 ---------- */
    titulo("Q1 - lista_tem_espaco (MAX = 100, a lista tem 4)");
    {
        li = monta(base, 4);
        printf("  espaco para 96: %d (esperado 1)\n", lista_tem_espaco(li, 96));
        printf("  espaco para 97: %d (esperado 0)\n", lista_tem_espaco(li, 97));
        printf("  espaco para 0:  %d (esperado 1)\n", lista_tem_espaco(li, 0));
        printf("  NULL:           %d (esperado 0)\n", lista_tem_espaco(NULL, 1));
        libera_lista(li);
    }

    /* ---------- Questao 2 ---------- */
    titulo("Q2 - soma_precos");
    {
        li = monta(base, 4);
        imprime("lista", li);
        printf("  soma: %.2f (esperado 105.90)\n", soma_precos(li));
        libera_lista(li);

        li = cria_lista();
        printf("  vazia: %.2f (esperado 0.00)\n", soma_precos(li));
        libera_lista(li);
    }

    /* ---------- Questao 3 ---------- */
    titulo("Q3 - busca_por_nome");
    {
        struct produto achado;
        li = monta(base, 4);
        imprime("lista", li);
        if (busca_por_nome(li, "Mochila", &achado))
            printf("  \"Mochila\" -> cod=%d preco=%.2f (esperado 104 e 89.90)\n",
                   achado.codigo, achado.preco);
        printf("  \"Lapis\"   -> %d (esperado 0)\n",
               busca_por_nome(li, "Lapis", &achado));
        libera_lista(li);

        li = cria_lista();
        printf("  lista vazia -> %d (esperado 0)\n",
               busca_por_nome(li, "Mochila", &achado));
        libera_lista(li);
    }

    /* ---------- Questao 4 ---------- */
    titulo("Q4 - insere_lista_decrescente (por preco)");
    {
        li = cria_lista();
        insere_lista_decrescente(li, mk(101, "Caderno", 12.50f));
        imprime("insere 12.50", li);
        insere_lista_decrescente(li, mk(104, "Mochila", 89.90f));
        imprime("insere 89.90 (inicio)", li);
        insere_lista_decrescente(li, mk(102, "Caneta", 2.30f));
        imprime("insere 2.30 (final)", li);
        insere_lista_decrescente(li, mk(105, "Estojo", 25.00f));
        imprime("insere 25.00 (meio)", li);
        libera_lista(li);
    }

    /* ---------- Questao 5 ---------- */
    titulo("Q5 - remove_mais_caro");
    {
        struct produto removido;
        int r;
        li = monta(base, 4);
        imprime("antes", li);
        r = remove_mais_caro(li, &removido);
        printf("  devolve %d, removeu cod=%d preco=%.2f (esperado 1, 104 e 89.90)\n",
               r, removido.codigo, removido.preco);
        imprime("depois", li);
        libera_lista(li);

        li = cria_lista();
        printf("  lista vazia: %d (esperado 0)\n", remove_mais_caro(li, &removido));
        libera_lista(li);
    }

    /* ---------- Questao 6 ---------- */
    titulo("Q6 - conta_faixa_preco");
    {
        li = monta(base, 4);
        imprime("lista", li);
        printf("  faixa 1.00 a 20.00:   %d (esperado 3)\n",
               conta_faixa_preco(li, 1.0f, 20.0f));
        printf("  faixa 2.30 a 12.50:   %d (esperado 2, limites inclusos)\n",
               conta_faixa_preco(li, 2.30f, 12.50f));
        printf("  faixa 100.00 a 200.00: %d (esperado 0)\n",
               conta_faixa_preco(li, 100.0f, 200.0f));
        libera_lista(li);

        li = cria_lista();
        printf("  lista vazia: %d (esperado 0)\n",
               conta_faixa_preco(li, 0.0f, 1000.0f));
        libera_lista(li);
    }

    /* ---------- Questao 7 ---------- */
    titulo("Q7 - remove_abaixo_de");
    {
        struct produto baratos[] = {
            {1, "A", 1.0f}, {2, "B", 2.0f}, {3, "C", 3.0f}
        };
        struct produto fim[] = {
            {1, "A", 5.0f}, {2, "B", 1.0f}, {3, "C", 2.0f}, {4, "D", 20.0f}
        };
        int r;

        li = monta(base, 4);
        imprime("antes", li);
        r = remove_abaixo_de(li, 10.0f);
        printf("  abaixo de 10.00: removeu %d (esperado 2)\n", r);
        imprime("depois", li);
        libera_lista(li);

        li = monta(fim, 4);
        imprime("baratos seguidos", li);
        r = remove_abaixo_de(li, 10.0f);
        printf("  abaixo de 10.00: removeu %d (esperado 3)\n", r);
        imprime("depois", li);
        libera_lista(li);

        li = monta(baratos, 3);
        r = remove_abaixo_de(li, 10.0f);
        printf("  todos baratos: removeu %d (esperado 3)\n", r);
        imprime("depois", li);
        libera_lista(li);

        li = monta(base, 4);
        printf("  nenhum abaixo de 0.50: removeu %d (esperado 0)\n",
               remove_abaixo_de(li, 0.50f));
        libera_lista(li);
    }

    /* ---------- Questao 8 ---------- */
    titulo("Q8 - mescla_listas");
    {
        struct produto dest[] = {
            {101, "Caderno", 12.50f}, {105, "Estojo", 25.00f}
        };
        struct produto orig[] = {
            {101, "Caderno", 12.50f}, {106, "Regua", 3.50f}
        };
        int r;

        li = monta(dest, 2);
        li2 = monta(orig, 2);
        imprime("destino antes", li);
        imprime("origem", li2);
        r = mescla_listas(li, li2);
        printf("  inseriu %d (esperado 1: o 101 ja existe)\n", r);
        imprime("destino depois", li);
        imprime("origem depois", li2);
        libera_lista(li2);

        li2 = cria_lista();
        printf("  origem vazia: %d (esperado 0)\n", mescla_listas(li, li2));
        libera_lista(li2);
        printf("  NULL: %d (esperado 0)\n", mescla_listas(li, NULL));
        libera_lista(li);

        /* destino cheio: nada pode ser inserido */
        li = cria_lista();
        for (int i = 0; i < MAX; i++)
            insere_lista_final(li, mk(1000 + i, "Item", 1.0f));
        li2 = monta(orig, 2);
        r = mescla_listas(li, li2);
        printf("  destino cheio: inseriu %d, tam=%d (esperado 0 e %d)\n",
               r, tamanho_lista(li), MAX);
        libera_lista(li2);
        libera_lista(li);
    }

    printf("\n");
    return 0;
}
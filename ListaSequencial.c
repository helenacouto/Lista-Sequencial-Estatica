#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaSequencial.h"

/* qtd guarda quantas posicoes de dados estao ocupadas e, ao mesmo
   tempo, indica a proxima posicao livre no final da lista.
   As posicoes de qtd ate MAX-1 existem na memoria, mas nao
   pertencem a lista. */
struct lista {
    int qtd;
    struct produto dados[MAX];
};

/* ------------------------------------------------------------
   Criacao e destruicao
   ------------------------------------------------------------ */

Lista* cria_lista(void) {
    Lista *li;
    li = (Lista*) malloc(sizeof(struct lista));
    if (li != NULL)
        li->qtd = 0;
    return li;
}

void libera_lista(Lista* li) {
    free(li);
}

/* ------------------------------------------------------------
   Informacoes de estado
   ------------------------------------------------------------ */

int tamanho_lista(Lista* li) {
    if (li == NULL)
        return -1;
    return li->qtd;
}

int lista_cheia(Lista* li) {
    if (li == NULL)
        return -1;
    return (li->qtd == MAX);
}

int lista_vazia(Lista* li) {
    if (li == NULL)
        return -1;
    return (li->qtd == 0);
}

/* ------------------------------------------------------------
   Insercao
   ------------------------------------------------------------ */

int insere_lista_inicio(Lista* li, struct produto p) {
    int i;
    if (li == NULL)
        return 0;
    if (li->qtd == MAX)           /* teste de estouro */
        return 0;
    /* copia do fim para o inicio, para nao sobrescrever um valor
       antes de ele ser copiado */
    for (i = li->qtd - 1; i >= 0; i--)
        li->dados[i + 1] = li->dados[i];
    li->dados[0] = p;
    li->qtd++;
    return 1;
}

int insere_lista_final(Lista* li, struct produto p) {
    if (li == NULL)
        return 0;
    if (li->qtd == MAX)           /* teste de estouro */
        return 0;
    li->dados[li->qtd] = p;      /* qtd e a primeira posicao livre */
    li->qtd++;
    return 1;
}

int insere_lista_ordenada(Lista* li, struct produto p) {
    int k, i = 0;
    if (li == NULL)
        return 0;
    if (li->qtd == MAX)           /* teste de estouro */
        return 0;
    /* procura a primeira posicao com codigo maior ou igual */
    while (i < li->qtd && li->dados[i].codigo < p.codigo)
        i++;
    /* abre espaco na posicao i */
    for (k = li->qtd - 1; k >= i; k--)
        li->dados[k + 1] = li->dados[k];
    li->dados[i] = p;
    li->qtd++;
    return 1;
}

/* ------------------------------------------------------------
   Remocao
   ------------------------------------------------------------ */

int remove_lista_inicio(Lista* li) {
    int k;
    if (li == NULL)
        return 0;
    if (li->qtd == 0)             /* teste de lista vazia */
        return 0;
    /* na remocao a copia anda do inicio para o fim */
    for (k = 0; k < li->qtd - 1; k++)
        li->dados[k] = li->dados[k + 1];
    li->qtd--;
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL)
        return 0;
    if (li->qtd == 0)             /* teste de lista vazia */
        return 0;
    li->qtd--;                    /* nenhum elemento e deslocado */
    return 1;
}

int remove_lista(Lista* li, int cod) {
    int k, i = 0;
    if (li == NULL)
        return 0;
    if (li->qtd == 0)             /* teste de lista vazia */
        return 0;
    while (i < li->qtd && li->dados[i].codigo != cod)
        i++;
    if (i == li->qtd)             /* elemento nao encontrado */
        return 0;
    for (k = i; k < li->qtd - 1; k++)
        li->dados[k] = li->dados[k + 1];
    li->qtd--;
    return 1;
}

int remove_lista_otimizado(Lista* li, int cod) {
    int i = 0;
    if (li == NULL)
        return 0;
    if (li->qtd == 0)             /* teste de lista vazia */
        return 0;
    while (i < li->qtd && li->dados[i].codigo != cod)
        i++;
    if (i == li->qtd)             /* elemento nao encontrado */
        return 0;
    li->qtd--;                    /* qtd passa a indicar o ultimo elemento */
    li->dados[i] = li->dados[li->qtd];
    return 1;                     /* a ordem da lista foi alterada */
}

/* ------------------------------------------------------------
   Busca
   ------------------------------------------------------------ */

int busca_lista_pos(Lista* li, int pos, struct produto *p) {
    if (li == NULL || p == NULL || pos <= 0 || pos > li->qtd)
        return 0;
    *p = li->dados[pos - 1];     /* posicao 1 da lista = indice 0 */
    return 1;
}

int busca_lista_cod(Lista* li, int cod, struct produto *p) {
    int i = 0;
    if (li == NULL || p == NULL)
        return 0;
    while (i < li->qtd && li->dados[i].codigo != cod)
        i++;
    if (i == li->qtd)             /* elemento nao encontrado */
        return 0;
    *p = li->dados[i];
    return 1;
}

/*=========== QUESTÃO 1 ===========*/
int lista_tem_espaco(Lista* li, int n) {
    if (li == NULL) return 0;

    return (tamanho_lista(li) + n <= MAX);
}

/*=========== QUESTÃO 2 ===========*/
float soma_precos(Lista* li) {
    if (li == NULL) return 0;

    float soma = 0.0f;

    for (int i = 0; i < li->qtd; i++) {
        soma += li->dados[i].preco;
    }

    return soma;
}

/*=========== QUESTÃO 3 ===========*/
int busca_por_nome(Lista* li, char *nome, struct produto *p) {
    if (li == NULL) return 0;

    for (int i = 0; i < li->qtd; i++) {
        if (!strcmp(li->dados[i].nome, nome)) {
            *p = li->dados[i];
            return 1;
        }
    }

    return 0;
}

/*=========== QUESTÃO 4 ===========*/
int insere_lista_decrescente(Lista* li, struct produto p) {
    if (li == NULL)
        return 0;
    if (li->qtd == MAX)
        return 0;

    int k, i = 0;
    while (i <= li->qtd - 1 && li->dados[i].preco > p.preco)
        i++;

    for (k = li->qtd - 1; k >= i; k--)
        li->dados[k + 1] = li->dados[k];

    li->dados[i] = p;
    li->qtd++;
    return 1;
}

/*=========== QUESTÃO 5 ===========*/
int remove_mais_caro(Lista* li, struct produto *removido) {
    if (li == NULL)
        return 0;
    if (li->qtd == 0)
        return 0;

    float maior = li->dados[0].preco;
    int idx = 0;
    for (int i = 1; i < li->qtd; i++) {
        if (li->dados[i].preco > maior) {
            maior = li->dados[i].preco;
            idx = i;
        }
    }

    *removido = li->dados[idx];
    li->qtd--;
    li->dados[idx] = li->dados[li->qtd];
    return 1;
}

/*=========== QUESTÃO 6 ===========*/
int conta_faixa_preco(Lista* li, float min, float max) {
    if (li == NULL) return 0;

    int cont = 0;
    for (int i = 0; i < li->qtd; i++) {
        if (li->dados[i].preco >= min && li->dados[i].preco <= max) 
            cont++;
    }

    return cont;
}

/*=========== QUESTÃO 7 ===========*/
int remove_abaixo_de(Lista* li, float precoMinimo) {
    if (li == NULL)
        return 0;
    if (li->qtd == 0)
        return 0;

    int cont = 0;
    for (int i = 0; i < li->qtd; i++) {
        if (li->dados[i].preco < precoMinimo) {
            while (li->dados[i].preco < precoMinimo) {
                li->qtd--;
                cont++;

                if (i != li->qtd) {
                    li->dados[i] = li->dados[li->qtd];    
                } else break;
            }
        }
    }

    return cont;
}

/*=========== QUESTÃO 8 ===========*/
int mescla_listas(Lista* destino, Lista* origem) {
    if (destino == NULL || origem == NULL)
        return 0;
    if (origem->qtd == 0)
        return 0;

    int cont = 0;
    for (int i = 0; i < origem->qtd; i++) {
        struct produto p;
        if (busca_lista_cod(destino, origem->dados[i].codigo, &p) == 0) {
            int ok = insere_lista_final(destino, origem->dados[i]);
            if (ok) cont++;
        }

        if (lista_cheia(destino)) break;
    }

    return cont;
}
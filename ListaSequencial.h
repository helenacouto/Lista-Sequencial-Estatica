#ifndef LISTA_SEQUENCIAL_H
#define LISTA_SEQUENCIAL_H

/* Numero maximo de elementos da lista, fixado em tempo de compilacao. */
#define MAX 100

/* Tipo do elemento armazenado na lista. */
struct produto {
    int   codigo;
    char  nome[30];
    float preco;
};

/* Tipo opaco: o usuario da biblioteca so pode declarar Lista *li. */
typedef struct lista Lista;

/* --- criacao e destruicao ---------------------------------- */

/* Aloca e inicializa uma lista vazia.
   Devolve o ponteiro da lista, ou NULL se a alocacao falhar. */
Lista* cria_lista(void);

/* Libera a memoria da lista. */
void libera_lista(Lista* li);

/* --- informacoes de estado --------------------------------- */

/* Devolve a quantidade de elementos, ou -1 se li for NULL. */
int tamanho_lista(Lista* li);

/* Devolve 1 se a lista esta cheia, 0 caso contrario, -1 se li for NULL. */
int lista_cheia(Lista* li);

/* Devolve 1 se a lista esta vazia, 0 caso contrario, -1 se li for NULL. */
int lista_vazia(Lista* li);

/* --- insercao ----------------------------------------------
   Todas devolvem 1 em caso de sucesso e 0 caso contrario
   (lista invalida ou lista cheia). ------------------------- */

/* Insere na posicao 0, deslocando os demais elementos. Custo O(n). */
int insere_lista_inicio(Lista* li, struct produto p);

/* Insere na primeira posicao livre do final. Custo O(1). */
int insere_lista_final(Lista* li, struct produto p);

/* Insere mantendo a lista ordenada de forma crescente por codigo.
   Custo O(n). */
int insere_lista_ordenada(Lista* li, struct produto p);

/* --- remocao -----------------------------------------------
   Todas devolvem 1 em caso de sucesso e 0 caso contrario
   (lista invalida, lista vazia ou elemento inexistente). --- */

/* Remove o elemento da posicao 0, deslocando os demais. Custo O(n). */
int remove_lista_inicio(Lista* li);

/* Remove o ultimo elemento. Custo O(1). */
int remove_lista_final(Lista* li);

/* Remove o elemento de codigo cod preservando a ordem. Custo O(n). */
int remove_lista(Lista* li, int cod);

/* Remove o elemento de codigo cod copiando o ultimo elemento para a
   posicao liberada. Movimenta um unico elemento, mas ALTERA A ORDEM da
   lista. A busca continua sendo O(n). */
int remove_lista_otimizado(Lista* li, int cod);

/* --- busca -------------------------------------------------
   Copiam o elemento encontrado para *p e devolvem 1; devolvem 0
   quando a busca falha. ------------------------------------ */

/* Busca pela posicao na lista, contada a partir de 1. Custo O(1). */
int busca_lista_pos(Lista* li, int pos, struct produto *p);

/* Busca pelo conteudo do campo codigo. Custo O(n). */
int busca_lista_cod(Lista* li, int cod, struct produto *p);

/*=========== ATIVIDADE ===========*/
int   lista_tem_espaco(Lista* li, int n);
float soma_precos(Lista* li);
int   busca_por_nome(Lista* li, char *nome, struct produto *p);
int   insere_lista_decrescente(Lista* li, struct produto p);
int   remove_mais_caro(Lista* li, struct produto *removido);
int   conta_faixa_preco(Lista* li, float min, float max);
int   remove_abaixo_de(Lista* li, float precoMinimo);
int   mescla_listas(Lista* destino, Lista* origem);

#endif /* LISTA_SEQUENCIAL_H */
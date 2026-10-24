# Lista de exercícios: Lista sequencial estática

Resolução da lista de exercícios da **Aula 05** da disciplina **Estrutura de Dados**
(Departamento de Informática, UFPB), sobre a lista sequencial estática, em C.

## Sobre a atividade

Uma atividade da disciplina é uma **lista de exercícios** construída sobre uma biblioteca
que o professor apresenta em aula. Em vez de escrever um programa do zero, o trabalho é
**estender a biblioteca**: cada questão pede uma nova função, e todas seguem as mesmas regras.

1. A função é escrita dentro do arquivo `.c` da biblioteca.
2. O protótipo é acrescentado ao arquivo `.h`.
3. A função é testada a partir do `main.c`.

A lista sequencial estática guarda os elementos em um vetor de tamanho fixo (`MAX = 100`)
e um contador `qtd` com a quantidade de posições ocupadas. As funções precisam ficar dentro
do `.c` porque o tipo da lista é **opaco**: a `struct lista` só existe no `.c`, e por isso
nenhuma função que acessa `qtd` e `dados` compila fora dele.

### Questões

| Questão | Função | O que faz |
|---|---|---|
| 1 | `lista_tem_espaco` | Informa se cabem mais `n` elementos na lista sem ultrapassar `MAX` |
| 2 | `soma_precos` | Devolve a soma dos preços de todos os produtos da lista |
| 3 | `busca_por_nome` | Busca um produto pelo nome e copia o encontrado para `*p` |
| 4 | `insere_lista_decrescente` | Insere mantendo a lista ordenada de forma decrescente por preço |
| 5 | `remove_mais_caro` | Remove o produto de maior preço e o devolve em `*removido` |
| 6 | `conta_faixa_preco` | Conta os produtos com preço entre `min` e `max`, limites inclusos |
| 7 | `remove_abaixo_de` | Remove todos os produtos com preço abaixo de um mínimo e devolve quantos foram removidos |
| 8 | `mescla_listas` | Insere na lista de destino os produtos da origem cujo código ainda não existe nela, e devolve quantos foram inseridos |

## Biblioteca base

A biblioteca de partida (`ListaSequencial.h` e `ListaSequencial.c`) é do
**Prof. Daniel Faustino Lacerda de Souza** e vem da pasta `01-lista-sequencial-estatica`
do repositório da disciplina:
[github.com/Ensino-UFPB/exemplosed1](https://github.com/Ensino-UFPB/exemplosed1).

Ela traz criação e destruição da lista, inserção (início, final e ordenada), remoção
(início, final, por código e a versão otimizada) e busca (por posição e por código).

**Adaptação:** os exercícios trabalham com produtos, então, no lugar do `struct aluno` da
biblioteca original, a lista guarda um `struct produto`. O restante do código da base é o
do professor, com apenas estes renomes:

| Original | Neste repositório |
|---|---|
| `struct aluno` (`matricula`, `nome`, `n1`, `n2`, `n3`) | `struct produto` (`codigo`, `nome`, `preco`) |
| `busca_lista_mat` | `busca_lista_cod` |
| parâmetros `mat` e `al` | `cod` e `p` |

O que foi acrescentado por mim está marcado nos arquivos:

- no `.h`, pela seção `ATIVIDADE`;
- no `.c`, pelos comentários `QUESTÃO N`, no final do arquivo.

## Organização do repositório

```
.
├── ListaSequencial.h       interface: tipo opaco e protótipos (base do professor + atividade)
├── ListaSequencial.c       implementação: base do professor + funções das questões
├── main.c                  programa de testes das questões
├── Makefile                compilação separada dos módulos
└── README.md
```

## Como compilar e executar

```bash
make        # gera o executável ./teste
./teste     # executa os testes
make clean  # remove os .o e o executável
```

Sem o `make`, a compilação manual é:

```bash
gcc -Wall -Wextra -std=c11 -o teste ListaSequencial.c main.c
```

O único requisito é um compilador C com suporte a C11 (`gcc` ou `clang`). Para procurar
vazamentos de memória:

```bash
valgrind --leak-check=full ./teste
```

## Como os testes funcionam

O `main.c` tem um bloco por questão. Cada bloco monta uma lista, imprime o estado dela
antes e depois da operação, no formato `qtd=2: 101 Caderno (12.50) | 104 Mochila (89.90)`,
e confere casos de borda (lista vazia, `NULL`, lista cheia, limites de faixa). Ao lado de
cada resultado aparece o valor esperado, para a conferência ser imediata.

O `main.c` usa apenas o que está declarado no `.h`: em nenhum ponto ele acessa os campos
`qtd` ou `dados`.

## Convenções

- **Tipo opaco:** a `struct lista` é definida apenas no `.c`.
- **Compilação limpa:** o código compila com `gcc -Wall -Wextra -std=c11` sem avisos.
- **Retorno:** inserção e remoção devolvem `1` em caso de sucesso e `0` caso contrário.
  `tamanho_lista`, `lista_cheia` e `lista_vazia` devolvem `-1` quando o ponteiro da lista
  é `NULL`.
- **Comentários sem acentuação** nos arquivos `.c` e `.h` da biblioteca base, para evitar
  problemas de codificação em editores com outra página de código. Os arquivos
  `README.md` usam acentuação normal.
- **Nomes em português**, iguais aos dos slides e das listas de exercícios.

## Referências

- BACKES, A. R. *Algoritmos e estruturas de dados em linguagem C*. Rio de Janeiro: LTC, 2023.
- TENENBAUM, A. M.; LANGSAM, Y.; AUGENSTEIN, M. J. *Estruturas de dados usando C*. São Paulo: Makron Books, 1995.
- CORMEN, T. H. et al. *Algoritmos: teoria e prática*. 3. ed. Rio de Janeiro: Elsevier, 2012.

## Autoria

Atividade resolvida por Helena Couto, estudante de Ciência de Dados e Inteligência
Artificial na UFPB. A biblioteca base e o enunciado da lista são do Prof. Daniel Faustino
Lacerda de Souza.
#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

typedef struct estrutura
{
    int *vetorPrincipal[TAM];
    int tamanho[TAM];
    int espacosOcupados[TAM];
} estrutura;

estrutura ESTRUTURA;

void initEstrutura(estrutura *ESTRUTURA)
{
    for (int i = 0; i < TAM; i++)
    {
        ESTRUTURA->vetorPrincipal[i] = NULL;
        ESTRUTURA->tamanho[i] = 0;
        ESTRUTURA->espacosOcupados[i] = 0;
    }
}

void initEstruturaAux(estrutura *ESTRUTURA, int posicao)
{
    for (int i = 0; i < ESTRUTURA->tamanho[posicao]; i++)
        *(ESTRUTURA->vetorPrincipal[posicao] + i) = __INT_MAX__;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > TAM)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    int retorno = 0;
    // a posicao pode já existir estrutura auxiliar
    if (ESTRUTURA.vetorPrincipal[posicao - 1] && retorno == 0)
        retorno = JA_TEM_ESTRUTURA_AUXILIAR;

    // se posição é um valor válido {entre 1 e 10}
    if ((ehPosicaoValida(posicao)) == POSICAO_INVALIDA && retorno == 0)
        retorno = POSICAO_INVALIDA;

    // o tamanho nao pode ser menor que 1
    if (tamanho < 1 || (tamanho > TAM) && (retorno == 0))
        retorno = TAMANHO_INVALIDO;

    // deu tudo certo, crie

    // o tamanho ser muito grande
    int *estruturaAuxiliar = malloc(tamanho * sizeof(int));
    if (!estruturaAuxiliar && retorno == 0)
    {
        retorno = SEM_ESPACO_DE_MEMORIA;
    }
    else if (retorno == 0)
    {
        posicao--;
        ESTRUTURA.vetorPrincipal[posicao] = estruturaAuxiliar;
        ESTRUTURA.tamanho[posicao] = tamanho;
        initEstruturaAux(&ESTRUTURA, posicao);

        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0;

    int index_a_ser_preenchido = 0;

    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        posicao_invalida = 1;

    if (posicao_invalida)
        retorno = POSICAO_INVALIDA;
    else
    {
        posicao--;
        // testar se existe a estrutura auxiliar
        if (ESTRUTURA.vetorPrincipal[posicao])
        {
            for (int i = 0; i < ESTRUTURA.tamanho[posicao]; i++)
            {
                if (*(ESTRUTURA.vetorPrincipal[posicao] + i) != __INT_MAX__)
                    index_a_ser_preenchido++;

                // printf("\nLAÇO FOR *(ESTRUTURA.vetorPrincipal[posicao]+i: %d\n", *(ESTRUTURA.vetorPrincipal[posicao]+i));
            }

            if (ESTRUTURA.espacosOcupados[posicao] < ESTRUTURA.tamanho[posicao])
                temEspaco = 1;
            else
                temEspaco = 0;

            if (temEspaco)
            {
                // insere
                //  printf("\nindex_a_ser_preenchido: %d\n",index_a_ser_preenchido);
                //  printf("\n*(ESTRUTURA.vetorPrincipal[posicao]+index_a_ser_preenchido): %d\n", *(ESTRUTURA.vetorPrincipal[posicao]+index_a_ser_preenchido));
                *(ESTRUTURA.vetorPrincipal[posicao] + index_a_ser_preenchido) = valor;
                // printf("\n*(ESTRUTURA.vetorPrincipal[posicao]+index_a_ser_preenchido): %d\n", *(ESTRUTURA.vetorPrincipal[posicao]+index_a_ser_preenchido));
                ESTRUTURA.espacosOcupados[posicao]++;
                // printf("\nESTRUTURA.espacosOcupados[posicao]: %d\n", ESTRUTURA.espacosOcupados[posicao]);
                retorno = SUCESSO;
            }
            else
            {
                retorno = SEM_ESPACO;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    index_a_ser_preenchido = 0;
    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    int retorno = 0;

    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        retorno = POSICAO_INVALIDA;
    else
    {
        posicao--;

        if (ESTRUTURA.vetorPrincipal[posicao])
        {
            int TAM_COPIA = ESTRUTURA.espacosOcupados[posicao];

            if (TAM_COPIA == 0)
                retorno = ESTRUTURA_AUXILIAR_VAZIA;

            else
            {
                int i = (ESTRUTURA.espacosOcupados[posicao] - 1);

                *(ESTRUTURA.vetorPrincipal[posicao] + i) = __INT_MAX__;
                ESTRUTURA.espacosOcupados[posicao]--;

                retorno = SUCESSO;
            }
        }
        else
            retorno = SEM_ESTRUTURA_AUXILIAR;
    }

    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int retorno = 0;

    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        retorno = POSICAO_INVALIDA;
    else
    {
        posicao--;

        if (ESTRUTURA.vetorPrincipal[posicao])
        {
            int TAM_COPIA = ESTRUTURA.espacosOcupados[posicao];

            if (TAM_COPIA == 0)
                retorno = ESTRUTURA_AUXILIAR_VAZIA;

            else
            {
                int sim = 1, nao = 0;
                int ocupados = (ESTRUTURA.espacosOcupados[posicao] - 1);
                int encontrado = nao;
                int i;

                for (i = ocupados; i >= 0; i--)
                {
                    if (valor == *(ESTRUTURA.vetorPrincipal[posicao] + i))
                    {
                        encontrado = sim;
                        break;
                    }
                }
                if (encontrado)
                {
                    // DEBUG ONLY
                    /*
                        printf("\nANTES DA EXCLUSAO\n");
                        for (int i = 0; i < ESTRUTURA.espacosOcupados[posicao]; i++)
                        {
                            printf("%d", *(ESTRUTURA.vetorPrincipal[posicao]+i));
                            if ((i+1) < ESTRUTURA.espacosOcupados[posicao])
                                printf(" ");
                        }
                    */
                    // DEBUG ONLY END
                    if (i == ocupados)
                    {
                        *(ESTRUTURA.vetorPrincipal[posicao] + i) = __INT_MAX__;
                        ESTRUTURA.espacosOcupados[posicao]--;

                        retorno = SUCESSO;
                    }
                    else if (i < ocupados)
                    {
                        int aux;
                        while (i < ocupados)
                        {
                            int proximo = i + 1, atual = i;
                            *(ESTRUTURA.vetorPrincipal[posicao] + atual) = *(ESTRUTURA.vetorPrincipal[posicao] + proximo);
                            i++;
                        }
                        ESTRUTURA.espacosOcupados[posicao]--;
                        retorno = SUCESSO;
                    }

                    // DEBUG ONLY
                    /*
                        printf("\nDEPOIS DA EXCLUSAO\n");
                        for (int i = 0; i < ESTRUTURA.espacosOcupados[posicao]; i++)
                        {
                            printf("%d", *(ESTRUTURA.vetorPrincipal[posicao]+i));
                            if ((i+1) < ESTRUTURA.espacosOcupados[posicao])
                                printf(" ");
                        }
                    */
                    // DEBUG ONLY END
                }
                else
                    retorno = NUMERO_INEXISTENTE;
            }
        }
        else
            retorno = SEM_ESTRUTURA_AUXILIAR;
    }

    // printf("Retorno: %d, resultado: ", retorno);
    return retorno;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = 0;

    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        retorno = POSICAO_INVALIDA;
    else
    {
        posicao--;
        if (ESTRUTURA.vetorPrincipal[posicao])
        {
            for (int i = 0; i < ESTRUTURA.espacosOcupados[posicao]; i++)
                vetorAux[i] = *(ESTRUTURA.vetorPrincipal[posicao] + i);
            // printf("\nGET DADOS *(ESTRUTURA.vetorPrincipal[%d]+%d): %d\n", posicao, i, *(ESTRUTURA.vetorPrincipal[posicao]+i));
            // printf("\nGET DADOS vetorAux[%d]: %d\n", i,vetorAux[i]);

            retorno = SUCESSO;
        }
        else
            retorno = SEM_ESTRUTURA_AUXILIAR;
    }

    // printf("Retorno: %d, resultado: ", retorno);
    return retorno;
}

// qsort help

// int compare(const void *x_void, const void *y_void)
// {
//     int x = *(int *)x_void;
//     int y = *(int *)y_void;
//     return x - y;
// }

// qsort help

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = 0;

    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        retorno = POSICAO_INVALIDA;
    else
    {
        posicao--;
        if (ESTRUTURA.vetorPrincipal[posicao])
        {
            int tamanhoVetor = ESTRUTURA.espacosOcupados[posicao];

            for (int i = 0; i < tamanhoVetor; i++)
            {
                vetorAux[i] = *(ESTRUTURA.vetorPrincipal[posicao] + i);
            }

            for (int i = 0; i < tamanhoVetor - 1; i++)
            {
                for (int j = 0; j < tamanhoVetor - i - 1; j++)
                {
                    if (vetorAux[j] > vetorAux[j + 1])
                    {
                        int temp = vetorAux[j];
                        vetorAux[j] = vetorAux[j + 1];
                        vetorAux[j + 1] = temp;
                    }
                }
            }

            // qsort(vetorAux, tamanhoVetor, sizeof(int), compare);

            retorno = SUCESSO;
        }
        else
            retorno = SEM_ESTRUTURA_AUXILIAR;
    }

    // printf("Retorno: %d, resultado: ", retorno);
    return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = 0;
    int temNumeros = 0;

    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < ESTRUTURA.espacosOcupados[i]; j++)
        {
            if (*(ESTRUTURA.vetorPrincipal[i] + j) != __INT_MAX__)
            {
                temNumeros++;
            }
        }
    }

    if (temNumeros)
    {
        for (int i = 0, k = 0; i < TAM; i++)
        {
            if (ESTRUTURA.vetorPrincipal[i])
            {
                int tamanhoVetor = ESTRUTURA.espacosOcupados[i];

                for (int j = 0; j < tamanhoVetor; j++)
                {
                    vetorAux[k] = *(ESTRUTURA.vetorPrincipal[i] + j);
                    k++;
                }
            }
        }
    }

    retorno = temNumeros ? SUCESSO : TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

    return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = 0;
    int temNumeros = 0;
    int tamanhoVetorAux = 0;

    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < ESTRUTURA.espacosOcupados[i]; j++)
        {
            if (*(ESTRUTURA.vetorPrincipal[i] + j) != __INT_MAX__)
            {
                temNumeros++;
            }
        }
    }

    if (temNumeros)
    {
        for (int i = 0; i < TAM; i++)
        {
            if (ESTRUTURA.vetorPrincipal[i])
            {
                int tamanhoVetor = ESTRUTURA.espacosOcupados[i];

                for (int j = 0; j < tamanhoVetor; j++)
                {
                    vetorAux[tamanhoVetorAux] = *(ESTRUTURA.vetorPrincipal[i] + j);
                    tamanhoVetorAux++;
                }
            }
        }
        for (int i = 0; i < tamanhoVetorAux - 1; i++)
        {
            for (int j = 0; j < tamanhoVetorAux - i - 1; j++)
            {
                if (vetorAux[j] > vetorAux[j + 1])
                {
                    int aux = vetorAux[j];
                    vetorAux[j] = vetorAux[j + 1];
                    vetorAux[j + 1] = aux;
                }
            }
        }
    }

    retorno = temNumeros ? SUCESSO : TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

    return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    int retorno = 0;

    // printf("\n-------------TAMANHO-----------------");

    // printf("\nposição do usuário (antes): %d\n", posicao);

    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        retorno = POSICAO_INVALIDA;
    else
    {
        posicao--;
        // printf("\nposição do usuário (depois): %d\n", posicao);
        // printf("\nESTRUTURA.vetorPrincipal[%d] == ", posicao);
        // if (!ESTRUTURA.vetorPrincipal[posicao]) printf("NULL\n");

        // else printf("%p, %d", ESTRUTURA.vetorPrincipal[posicao], *ESTRUTURA.vetorPrincipal[posicao]);

        // printf("\nESTRUTURA.tamanho[%d] == %d", posicao, ESTRUTURA.tamanho[posicao]);
        // printf("\nESTRUTURA.espacosOcupados[%d] == %d", posicao, ESTRUTURA.espacosOcupados[posicao]);

        if (!ESTRUTURA.vetorPrincipal[posicao])
            retorno = SEM_ESTRUTURA_AUXILIAR;

        else
        {
            int tamanhoAntigo = ESTRUTURA.tamanho[posicao];

            // printf("\ntamanhoAntigo == %d   novoTamanho == %d\n", tamanhoAntigo, novoTamanho);
            // printf("\ntamanhoAntigo + novoTamanho == %d\n", (tamanhoAntigo + novoTamanho));
            if ((tamanhoAntigo + novoTamanho) < 1)
                retorno = NOVO_TAMANHO_INVALIDO;

            else
            {
                int subtrairEspacos = 0;
                subtrairEspacos = (tamanhoAntigo - (tamanhoAntigo + novoTamanho));
                ESTRUTURA.vetorPrincipal[posicao] = realloc(ESTRUTURA.vetorPrincipal[posicao], (tamanhoAntigo + novoTamanho) * sizeof(int));
                if (!ESTRUTURA.vetorPrincipal[posicao])
                {
                    retorno = SEM_ESPACO_DE_MEMORIA;
                    // printf("\n\n\nNULL sem espaço\n\nn");
                }
                else
                {
                    ESTRUTURA.tamanho[posicao] -= subtrairEspacos;

                    if (ESTRUTURA.espacosOcupados[posicao] > ESTRUTURA.tamanho[posicao])
                    {
                        ESTRUTURA.espacosOcupados[posicao] = ESTRUTURA.tamanho[posicao];
                    }
                    // printf("\nposição do usuário (depois): %d\n", posicao);
                    // printf("\nESTRUTURA.vetorPrincipal[%d] == ", posicao);
                    // if (!ESTRUTURA.vetorPrincipal[posicao]) printf("NULL\n");

                    // else printf("%p, %d", ESTRUTURA.vetorPrincipal[posicao], *ESTRUTURA.vetorPrincipal[posicao]);

                    // printf("\nESTRUTURA.tamanho[%d] == %d", posicao, ESTRUTURA.tamanho[posicao]);
                    // printf("\nESTRUTURA.espacosOcupados[%d] == %d", posicao, ESTRUTURA.espacosOcupados[posicao]);
                    retorno = SUCESSO;
                }
            }
        }
    }

    // printf("Retorno: %d, resultado: ", retorno);

    return retorno;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    int retorno = 0;
    int qtdElementos = 0;

    // printf("\n-------------QTD-----------------\n");

    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        retorno = POSICAO_INVALIDA;
    else
    {
        posicao--;
        if (!ESTRUTURA.vetorPrincipal[posicao])
            retorno = SEM_ESTRUTURA_AUXILIAR;

        else
        {
            if (ESTRUTURA.espacosOcupados[posicao] == 0)
                retorno = ESTRUTURA_AUXILIAR_VAZIA;

            else
            {
                for (int i = 0; i < ESTRUTURA.espacosOcupados[posicao]; i++)
                {
                    if (*(ESTRUTURA.vetorPrincipal[posicao] + i) != __INT_MAX__)
                        qtdElementos++;
                }
                retorno = qtdElementos;
            }
        }
    }

    // printf("Retorno: %d, resultado: ", retorno);

    return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    int temNumero = 0;
    No *Head = malloc(sizeof(No));

    if (!Head)
        return NULL;

    Head->conteudo = __INT_MAX__;
    Head->prox = NULL;

    No *node = Head;




    for (int i = 0; i < TAM; i++)
    {
        if (ESTRUTURA.espacosOcupados[i] > 0)
        {
            for (int j = 0; j < ESTRUTURA.espacosOcupados[i]; j++)
            {
                // printf("\nHead->conteudo: %d\n", Head->conteudo);
                // printf("Head->prox: %p\n", Head->prox);

                // printf("\nnode->prox: %p\n", node->prox);
                No *newNode = malloc(sizeof(No));

                if (!newNode)
                    return NULL;

                newNode->conteudo = *(ESTRUTURA.vetorPrincipal[i] + j);
                newNode->prox = NULL;
                // printf("\nnewNode->conteudo: %d\n", newNode->conteudo);
                // printf("newNode->prox: %p\n", newNode->prox);
                node->prox = newNode;
                node = newNode;
                // printf("\n&node: %p\n", &node);
                // printf("\nnode->conteudo: %d\n", node->conteudo);
                // printf("node->prox: %p\n", node->prox);

                // printf("\nHead->prox: %p\n", Head->prox);
                temNumero++;
            }
        }
    }

    if (temNumero)
    {
        return Head;
    }

    free(Head); // Free allocated memory if there's no content
    return NULL;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    int i = 0;
    No *current = inicio->prox; // Avança para o primeiro nó válido, ignorando o nó cabeçalho

    for (int j = 0; j < ESTRUTURA.espacosOcupados[2]; j++)
        {
            printf("\nESTRUTURA.vetorPrincipal[2] + %d: %d\n", j, *(ESTRUTURA.vetorPrincipal[2] + j));
        }

        for (int j = 0; j < ESTRUTURA.espacosOcupados[5]; j++)
        {
            printf("\nESTRUTURA.vetorPrincipal[5] + %d: %d\n", j, *(ESTRUTURA.vetorPrincipal[5] + j));
        }

    while (current)
    {
        // printf("\n\n\n\ncurrent->conteudo: ");
        printf(" %d,", current->conteudo);
        vetorAux[i] = current->conteudo;
        current = current->prox;
        i++;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No *temp;

    while (*inicio != NULL)
    {
        temp = *inicio;
        *inicio = (*inicio)->prox;
        free(temp);
    }
    return;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa

*/

void inicializar()
{
    initEstrutura(&ESTRUTURA);
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    for (int i = 0; i < TAM; i++)
    {
        if (ESTRUTURA.vetorPrincipal[i])
        {
            free(ESTRUTURA.vetorPrincipal[i]);
            ESTRUTURA.vetorPrincipal[i] = NULL;
        }
    }
}
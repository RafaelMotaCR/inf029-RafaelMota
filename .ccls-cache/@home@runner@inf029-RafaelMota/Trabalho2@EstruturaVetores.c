#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

typedef struct ls{
  int * ls;
  int tan;
  int qtd;
} estrutura;

estrutura vetorPrincipal[TAM];

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

int validaPsc(int pos){
    return (pos >= 0 && pos < TAM);
}


int existeEstruturaAuxiliar(int pos){
  if(!validaPsc(pos)){
    return 0;
  }
  return !(vetorPrincipal[pos].ls == NULL);
}


void isort(int * input, int tan){
  for(int i = 1; i < tan; i ++){
    int j = i - 1;
    int key = input[i];
    while(j >= 0 && key < input[j]){
      input[j + 1] = input[j];
      j--;
    }
    input[j + 1] = key;
  }
}


int numeroDeElementos(){
  int totalElementos = 0;
  for(int index = 0; index < 10; index ++){
    for(int icont = 0; icont < vetorPrincipal[index].qtd; icont ++){
        totalElementos ++;
    }
  }
  return totalElementos;
}


void insertLL(No * L, int key){
  No * newNode = malloc(sizeof(No));
  newNode -> conteudo = key;
  newNode -> prox = NULL;
  No * x = L;
  if(x -> prox == NULL){
    x -> prox = newNode;
  }
  else{
    while(x -> prox != NULL){
      x = x -> prox;
    }
    x -> prox = newNode;
  }
}


int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    posicao -= 1;
    // na posicao pode já existir estrutura auxiliar
    if(existeEstruturaAuxiliar(posicao)){
      return JA_TEM_ESTRUTURA_AUXILIAR;
    }

    // se posição é um valor válido {entre 1 e 10}
    if(!validaPsc(posicao)){
      return POSICAO_INVALIDA;
    } 

    // o tamanho nao pode ser menor que 1
    if(tamanho < 1){
      return TAMANHO_INVALIDO;
    }
    // o tamanho ser muito grande
    int * ptr = (int*)malloc(tamanho * sizeof(int));
    if(ptr == NULL){
      return SEM_ESPACO_DE_MEMORIA;
    }
    else{
       // deu tudo certo, crie
      free(ptr);
      vetorPrincipal[posicao].ls = (int*)malloc(tamanho * sizeof(int));
      vetorPrincipal[posicao].tan = tamanho;
    }
    return SUCESSO;
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
    posicao -= 1;

    if (!validaPsc(posicao)){
        return POSICAO_INVALIDA;
    }
    else{
        // testar se existe a estrutura auxiliar
        if (existeEstruturaAuxiliar(posicao)){
            if ((vetorPrincipal[posicao].tan) > vetorPrincipal[posicao].qtd){
                vetorPrincipal[posicao].ls[vetorPrincipal[posicao].qtd] = valor;
                vetorPrincipal[posicao].qtd ++;
                return SUCESSO;
            }
            else {
              return SEM_ESPACO;
            }
        }
        else{
            return SEM_ESTRUTURA_AUXILIAR;
        }
    }
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
  posicao -= 1;
  if(!validaPsc(posicao)){
    return POSICAO_INVALIDA;
  }
  if(!existeEstruturaAuxiliar(posicao)){
    return SEM_ESTRUTURA_AUXILIAR;
  }
  else{
    if(vetorPrincipal[posicao].qtd == 0){
     return ESTRUTURA_AUXILIAR_VAZIA;
    }
    else{
      vetorPrincipal[posicao].ls[vetorPrincipal[posicao].qtd] = 0;
      vetorPrincipal[posicao].qtd --;
      return SUCESSO;
    }
  }
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
  int founded = 0;
  posicao -= 1;
  
  if(!validaPsc(posicao)){
    return POSICAO_INVALIDA;
  }
  if(!existeEstruturaAuxiliar(posicao)){
    return SEM_ESTRUTURA_AUXILIAR;
  }
  if(vetorPrincipal[posicao].qtd == - 1){
    return ESTRUTURA_AUXILIAR_VAZIA;
  }
  for(int index = 0; index < vetorPrincipal[posicao].tan; index ++){
    if(vetorPrincipal[posicao].ls[index] == valor){
      founded = 1;
      break;
    }
  }
  if(!founded){
    return NUMERO_INEXISTENTE;
  }
  for(int index = 0 ; index <= vetorPrincipal[posicao].qtd; index++){
    if(vetorPrincipal[posicao].ls[index] == valor){
      vetorPrincipal[posicao].ls[index] = vetorPrincipal[posicao].ls[index + 1];
      vetorPrincipal[posicao].ls[index + 1] = valor;
    }
  }
  vetorPrincipal[posicao].qtd --;
  return SUCESSO;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}


/*int compare(const void *x_void, const void *y_void)
{
  int x = *(int *)x_void;
  int y = *(int *)y_void;
  return x - y;
}

qsort(vetor, tamanhovetor, compare);
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
  posicao -= 1;
  if(!validaPsc(posicao)){
    return POSICAO_INVALIDA;
  }
  if(!existeEstruturaAuxiliar(posicao)){
    return SEM_ESTRUTURA_AUXILIAR;
  }
  for(int index = 0; index < vetorPrincipal[posicao].qtd; index ++){
    vetorAux[index] =  vetorPrincipal[posicao].ls[index];
  }
  return SUCESSO;
}

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
  posicao -= 1;
  if(!validaPsc(posicao)){
    return POSICAO_INVALIDA;
  }
  if(!existeEstruturaAuxiliar(posicao)){
    return SEM_ESTRUTURA_AUXILIAR;
    }
  for(int index = 0; index < vetorPrincipal[posicao].qtd; index ++){
    vetorAux[index] =  vetorPrincipal[posicao].ls[index];
  }
  isort(vetorAux, vetorPrincipal[posicao].qtd);
  return SUCESSO;
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
  int estaoVazias = 1;
  for(int index = 0; index < 10; index ++){
    if(vetorPrincipal[index].qtd > 0){
      estaoVazias = 0;
      break;
    }
  }
  if(estaoVazias){
    return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
  }
  for(int index = 0, vetIndex = 0; index < 10; index ++){
    for(int icont = 0; icont < vetorPrincipal[index].qtd; icont ++){
      vetorAux[vetIndex] = vetorPrincipal[index].ls[icont];
      vetIndex ++;
    }
  }
  return SUCESSO;
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
  int vetIndex = 0;
  switch(getDadosDeTodasEstruturasAuxiliares(vetorAux)){
    case TODAS_ESTRUTURAS_AUXILIARES_VAZIAS:{
      return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
      break;
    }
    case SUCESSO:{
      isort(vetorAux, numeroDeElementos());
      return SUCESSO;
     break;
      return SUCESSO;
    }
  }
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
  posicao -= 1;
  int tiNovo = vetorPrincipal[posicao].tan + novoTamanho;
  if(!validaPsc(posicao)){
    return POSICAO_INVALIDA;
  }
  if(!existeEstruturaAuxiliar(posicao)){
    return SEM_ESTRUTURA_AUXILIAR;
  }
  if(tiNovo < 1){
    return NOVO_TAMANHO_INVALIDO;
  }
  if(novoTamanho < 0){
    for(int icont = 0; icont <= tiNovo;icont ++){
      excluirNumeroDoFinaldaEstrutura(posicao + 1);
    }
  }
  if(novoTamanho < vetorPrincipal[posicao].tan && novoTamanho > 0){
    vetorPrincipal[posicao].ls = realloc(vetorPrincipal[posicao].ls, novoTamanho);
    vetorPrincipal[posicao].tan = novoTamanho;
  }
  vetorPrincipal[posicao].ls = realloc(vetorPrincipal[posicao].ls, tiNovo);
  vetorPrincipal[posicao].tan = tiNovo;
  if(vetorPrincipal[posicao].ls == NULL){
    return SEM_ESPACO_DE_MEMORIA;
  }
  return SUCESSO;
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
  posicao -= 1;
  if(!validaPsc(posicao)){
    return POSICAO_INVALIDA;
  }
  if(!existeEstruturaAuxiliar(posicao)){
    return SEM_ESTRUTURA_AUXILIAR;
  }
  if(vetorPrincipal[posicao].qtd == 0){
    return ESTRUTURA_AUXILIAR_VAZIA;
  }
  return vetorPrincipal[posicao].qtd;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
  int vet[50];
  No * head = malloc(sizeof(No));
  head -> prox = NULL;
  switch(getDadosDeTodasEstruturasAuxiliares(vet)){
    case TODAS_ESTRUTURAS_AUXILIARES_VAZIAS:{
      return NULL;
    }
    case SUCESSO:{
      int holder = numeroDeElementos();
      for(int index = 0; index < holder; index ++){
        insertLL(head, vet[index]);
      }
      printf("\n");
    }
  } 
  return head;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
  No * x = inicio;
  int index = 0;
  x = x -> prox;
  while(x != NULL){
    vetorAux[index] = x -> conteudo;
      x = x -> prox;
      index ++;
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
  No * tmp;
  No * x = *inicio;
  while(x != NULL){
    tmp = x;
    x = x -> prox;
    free(tmp);
  }
  *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
  for(int index = 0; index < 10; index ++){
    vetorPrincipal[index].ls = NULL;
    vetorPrincipal[index].qtd = 0;
    vetorPrincipal[index].tan = 0;
  }
  //vetorPrincipal = malloc((10 * sizeof(estrutura)));
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
  for(int index = 0; index < 10; index ++){
    free(vetorPrincipal[index].ls);
  }
}

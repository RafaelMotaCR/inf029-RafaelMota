#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifndef escolaV3
#define escolaV3

// Definição dos tipos de dados

typedef struct
{
  char nome[50];
  char sexo;
  char cpf[15];
  int matricula;
  int idade;
  int id;
  int qtd_disciplinas;
  struct
  {
    int dia;
    int mes;
    int ano;
  } psdata;
} pessoa;

typedef struct
{
  pessoa *professor;
  char nome[7]; // matei
  int codigo;   // matei
  int alunos_cadastrados[40];
  int total_alunos_cadastrados;
  int semestre; // matei
} disciplina;

// Prótotipos das funções

void cadastra_cpf(pessoa *entrada);
void cadastra_idade(pessoa *entrada);
void cadastra_matricula(pessoa *entrada, int posicao);
void cadastra_nome(pessoa *entrada);
void cadastra_sexo(pessoa *entrada);
void cadastro_atualizacao(pessoa *entrada);
void cadastro_exclusao(pessoa *lista_pessoas, int posicao, int *total_pessoas);
void cadastro_novo(pessoa *nova_pessoa, int *total_pessoas);
void disciplina_aluno_exclusao(disciplina *entrada, pessoa *lista_alunos, int total_alunos);
int disciplina_aluno_existe(disciplina *entrada, int matricula);
int disciplina_aluno_valido(pessoa *lista_alunos, int total_alunos, int matricula);
void disciplina_aluno_insercao(disciplina *entrada, pessoa *lista_alunos, int total_alunos);
void disciplina_codigo(disciplina *entrada, int posicao);
void disciplina_exibicao(disciplina *entrada, int total_disciplinas, pessoa *lista_alunos, int total_alunos, int total);
void disciplina_nome(disciplina *entrada);
void disciplina_professor(disciplina *entrada, pessoa *lista_professores, int total_professores);
void disciplina_semestre(disciplina *entrada);
void exibe_pessoa(int numero, pessoa entrada);
char leia_char(char texto[]);
int leia_int_curto(char texto[]);
int leia_int_longo(char texto[]);
void limpa_buffer();
void menu_aluno();
void menu_atualizacao();
void menu_busca();
void menu_disciplinas();
void menu_listagem(pessoa lista_pessoas[], int total_pessoas);
void menu_principal();
void menu_professor();
void ordem_alfabetica(pessoa *lista_pessoas, int total_pessoas);
void ordem_aniversario(int *total1, int *total2, pessoa *lista1, pessoa *lista2);
void ordem_busca(int *total1, int *total2, pessoa *lista1, pessoa *lista2);
void ordem_cadastro(pessoa *lista_pessoas, int total_pessoas);
void ordem_disciplinas(pessoa *lista_pessoas, int total_pessoas);
void ordem_nascimento(pessoa lista_pessoas[], int total_pessoas);
void ordem_sexo(pessoa *lista_pessoas, int total_pessoas);
void titulo(char string[], char simbolo, int linha);
int valida_cpf(char *cpf);

// Funções de manipulação de dados

// Função para digitação e validação de CPF

void cadastra_cpf(pessoa *entrada)
{
  char cpf_formatado[15];
  while (1)
  {

    // Variáveis de verificação

    char cpf[15];
    int conta_pontos = 0;
    int conta_trav = 0;
    int digitos = 0;
    int valido = 0;

    // Entrada de dados inciais

    printf("> CPF: ");
    fgets(cpf, 15, stdin);
    int pos = strcspn(cpf, "\n");
    cpf[pos] = '\0';

    // Realiza a contagem de pontos, números e travessões

    for (int i = 0; cpf[i] != '\0'; ++i)
    {
      if (cpf[i] == '.')
      {
        conta_pontos++;
      }
      else if (cpf[i] == '-')
      {
        conta_trav++;
      }
      else if (cpf[i] >= 48 && cpf[i] <= 57)
      {
        digitos++;
      }
      else
      {
        printf("> Algum dos digitos eh invalido! Utilize apenas numeros, pontos e travessoes!\n");
        break;
      }
    }

    // Se o CPF digitado possuir 11 digitos, mas nenhum travessao ou ponto, a função irá formatá-lo para o padrão.

    if (digitos == 11 && conta_pontos == 0 && conta_trav == 0)
    {
      for (int i = 0, cont = 0, j = 0; cpf[i] != '\0'; ++i, j++)
      {
        if (cont != 3 && cont != 7)
        {
          cpf_formatado[j] = cpf[i];
          cont++;
        }
        else if (cont == 7)
        {
          cpf_formatado[j] = '-';
          cont++;
          --i;
        }
        else
        {
          if (i == 3)
          {
            cpf_formatado[i] = '.';
            cont = 0;
          }
          else
          {
            cpf_formatado[i + 1] = '.';
            cont++;
          }
          i--;
        }
      }
      valido = 1;
    }

    // Se o CPF digitado possuir o número correto de digitos, pontos e travessões, será dado como válido.

    else if (conta_trav == 1 && conta_pontos == 2 && digitos == 11)
    {
      strcpy(cpf_formatado, cpf);
      valido = 1;
    }

    // Se o CPF digitado não cumprir aos requisitos, será solicitada uma nova digitação.

    else
    {
      printf("> O CPF digitado eh invalido! Tente novamente!\n");
    }
    // Se o CPF for comprovado como válido, a função encerra o laço de repetição.

    if (valido == 1)
    {
      cpf_formatado[14] = '\0';
      if (!valida_cpf(cpf_formatado))
      {
        printf("> O CPF digitado eh invalido! Tente novamente!\n");
        continue;
      }
      else
      {
        break;
      }
    }
  }

  // A "pessoa" passada como parâmetro recebe o CPF validado

  printf("> O CPF digitado foi: %s.\n", cpf_formatado);
  strcpy(entrada->cpf, cpf_formatado);
}

// Função que determina idade

void cadastra_idade(pessoa *entrada)
{

  // Declaração das variáveis

  int dia, mes, ano;

  // Determina o ano atual

  time_t currentTime;
  time(&currentTime);
  struct tm *localTime = localtime(&currentTime);
  int ano_atual = localTime->tm_year + 1900;

  // Faz o resto das coisas

  while (1)
  {
    dia = leia_int_longo("> Dia de nascimento: ");
    if (!(dia > 0 && 31 >= dia))
    {
      printf("> Dia invalido! tente novamente!\n");
    }
    else
    {
      break;
    }
  }
  while (1)
  {
    mes = leia_int_longo("> Mes de nascimento: ");
    if (!(mes > 0 && 12 >= mes))
    {
      printf("> Mes invalido! tente novamente!\n");
    }
    else
    {
      break;
    }
  }
  while (1)
  {
    ano = leia_int_longo("> Ano de nascimento: ");
    if ((!(ano > 0 && 1920 <= ano)) || (ano >= ano_atual))
    {
      printf("> Ano invalido! tente novamente!\n");
    }
    else
    {
      break;
    }
  }
  entrada->psdata.dia = dia;
  entrada->psdata.mes = mes;
  entrada->psdata.ano = ano;
  entrada->idade = ano_atual - ano;
  if (dia < 10 && mes < 10)
  {
    printf("> Data de nascimento fornecida: 0%d/0%d/%d.\n", dia, mes, ano);
  }
  else if (dia > 10 && mes < 10)
  {
    printf("> Data de nascimento fornecida: %d/0%d/%d.\n", dia, mes, ano);
  }
  else if (dia < 10 && mes > 10)
  {
    printf("> Data de nascimento fornecida: 0%d/%d/%d.\n", dia, mes, ano);
  }
  else
  {
    printf("> Data de nascimento fornecida: %d/%d/%d.\n", dia, mes, ano);
  }
}

// Função que determina a matrícula

void cadastra_matricula(pessoa *entrada, int posicao)
{
  entrada->matricula = posicao + 1;
  printf("> Matricula definida como: %d.\n", posicao + 1);
}

// Função que captura e registra o nome, além de validar

void cadastra_nome(pessoa *entrada)
{
  char nome[50];
  int valido = 0;
  while (1)
  {
    printf("> Nome: ");
    fgets(nome, 50, stdin);
    int pos = strcspn(nome, "\n");
    nome[pos] = '\0';
    if (strlen(nome) < 5)
    {
      printf("> O nome deve ter ao menos 5 caracteres!\n");
      continue;
    }
    for (int i = 0; i < strlen(nome); ++i)
    {
      if (nome[0] >= 'a' && nome[0] <= 'z')
      {
        nome[0] = nome[0] - 32;
      }
      if ((!(nome[i] >= 'a' && nome[i] <= 'z')) && (!(nome[i] >= 'A' && nome[i] <= 'Z')))
      {
        if (nome[i] == 32)
        {
          if (nome[i + 1] >= 'a' && nome[i + 1] <= 'z')
          {
            nome[i + 1] = nome[i + 1] - 32;
          }
          continue;
        }
        valido = 0;
        break;
      }
      else
      {
        valido = 1;
      }
    }
    if (!valido)
    {
      printf("> O nome nao pode conter acentos ou caracteres especiais!\n");
      continue;
    }
    else
    {
      break;
    }
  }
  printf("> \"%s\" foi definido como nome.\n", nome);
  strcpy(entrada->nome, nome);
}

// Função que captura e valida o sexo digitado pelo usuário

void cadastra_sexo(pessoa *entrada)
{
  char validacao[5];
  char sexo;
  while (1)
  {
    printf("> Sexo [F/M]: ");
    fgets(validacao, 5, stdin);
    int pos = strcspn(validacao, "\n");
    validacao[pos] = '\0';
    if (strlen(validacao) > 1)
    {
      printf("> O sexo deve conter apenas um caractere, seu maldito!\n");
      fflush(stdin);
      continue;
    }
    else
    {
      sexo = validacao[0];
    }
    if (sexo == 'm' || sexo == 'f')
    {
      sexo -= 32;
      printf("> Sexo [%c] registrado com sucesso!\n", sexo);
      break;
    }
    else if (sexo == 'M' || sexo == 'F')
    {
      printf("> Sexo [%c] registrado com sucesso!\n", sexo);
      break;
    }
    else
    {
      printf("> O sexo digitado (%c) eh invalido! Tente novamente!\n", sexo);
      continue;
    }
  }
  entrada->sexo = sexo;
}

// Funções de cadastro e exclusão

// Função de atualização de cadastro

void cadastro_atualizacao(pessoa *entrada)
{
  int sair = 0;
  while (!sair)
  {
    titulo(entrada->nome, '-', 0);
    menu_atualizacao();
    int escolha = leia_int_curto("> Sua escolha: ");
    limpa_buffer();
    switch (escolha)
    {
    case 0:
    {
      sair = 1;
      continue;
      break;
    }
    case 1:
    {
      cadastra_cpf(entrada);
      break;
    }
    case 2:
    {
      cadastra_idade(entrada);
      break;
    }
    case 3:
    {
      cadastra_nome(entrada);
      break;
    }
    case 4:
    {
      cadastra_sexo(entrada);
      break;
    }
    case 5:
    {
      titulo("LISTANDO PESSOAS", '-', 1);
      exibe_pessoa(1, *entrada);
      continue;
      break;
    }
    default:
    {
      titulo("OPCAO INVALIDA!", '~', 0);
      continue;
      break;
    }
    }
    titulo("PESSOA ATUALIZADA COM SUCESSO", '-', 0);
  }
}

// Função de exclusão de cadastro

void cadastro_exclusao(pessoa *lista_pessoas, int posicao, int *total_pessoas)
{
  char texto[50];
  sprintf(texto, "> Apagando cadastro de %s...", lista_pessoas[posicao]);
  titulo(texto, '-', 0);
  // Utilizando um flag para separar o apagado dos demais

  lista_pessoas[posicao].idade = 200;

  // Criando uma cópia para usar durante o bubblesort

  pessoa copia;
  for (int total = *total_pessoas; total > 0; --total)
  {
    for (int i = 0; i < total; ++i)
    {
      if (lista_pessoas[i].idade == 200)
      {
        copia = lista_pessoas[i + 1];
        lista_pessoas[i + 1] = lista_pessoas[i];
        lista_pessoas[i] = copia;
      }
    }
  }

  (*total_pessoas)--;
}

// Função de criação de cadastro

void cadastro_novo(pessoa *nova_pessoa, int *total_pessoas)
{
  limpa_buffer();
  titulo("ESSA EH UMA STRING MUITO GRANDE RAPAZES KKK", '=', 1);
  cadastra_nome(nova_pessoa);
  titulo("ESSA EH UMA STRING MUITO GRANDE RAPAZES KKK", '=', 1);
  cadastra_cpf(nova_pessoa);
  titulo("ESSA EH UMA STRING MUITO GRANDE RAPAZES KKK", '=', 1);
  cadastra_matricula(nova_pessoa, *total_pessoas);
  titulo("ESSA EH UMA STRING MUITO GRANDE RAPAZES KKK", '=', 1);
  cadastra_sexo(nova_pessoa);
  titulo("ESSA EH UMA STRING MUITO GRANDE RAPAZES KKK", '=', 1);
  cadastra_idade(nova_pessoa);
  titulo("ESSA EH UMA STRING MUITO GRANDE RAPAZES KKK", '=', 1);
  if (!nova_pessoa->id)
  {
    if (nova_pessoa->sexo == 'F')
    {
      titulo("ALUNA ACADASTRADA COM SUCESSO!", '-', 0);
    }
    else
    {
      titulo("ALUNO CADASTRADO COM SUCESSO!", '-', 0);
    }
  }
  else
  {
    if (nova_pessoa->sexo == 'F')
    {
      titulo("PROFESSORA CADASTRADA COM SUCESSO!", '-', 0);
    }
    else
    {
      titulo("PROFESSOR CADASTRADO COM SUCESSO!", '-', 0);
    }
  }
  nova_pessoa->qtd_disciplinas = 0;
  (*total_pessoas)++;
}

void disciplina_aluno_exclusao(disciplina *entrada, pessoa *lista_alunos, int total_alunos)
{
  int matricula;
  int etapa = 0;
  int sair = 0;
  char escolha_aluno_exclusao;
  while (!sair)
  {
    switch (etapa)
    {
    case 0:
    {
      titulo("EXCLUINDO ALUNO DE DISCIPLINA", '-', 0);
      printf("[0] - SAIR\n");
      printf("[1] - EXCLUIR ALUNO POR MATRICULA\n");
      printf("[2] - VER ALUNOS E EXCLUIR\n");
      titulo("EXCLUINDO ALUNO EM DISCIPLINA", '-', 1);
      escolha_aluno_exclusao = leia_char("> Sua escolha: ");
      switch (escolha_aluno_exclusao)
      {
      case '0':
      {
        sair = 1;
        break;
      }
      case '1':
      {
        etapa = 1;
        break;
      }
      case '2':
      {
        titulo("LISTANDO PESSOAS", '-', 1);
        disciplina_exibicao(entrada, 1, lista_alunos, total_alunos, 0);
        etapa = 1;
        break;
      }
      default:
      {
        titulo("OPCAO INVALIDA!", '~', 0);
        break;
      }
      }
      break;
    }
    case 1:
    {
      matricula = leia_int_longo("> Digite a matricula do aluno: ");
      if (!disciplina_aluno_valido(lista_alunos, total_alunos, matricula))
      {
        titulo("NAO EXISTE ALUNO COM A MATRICULA DIGITADA!", '~', 0);
      }
      else
      {
        etapa = 2;
      }
      break;
    }
    case 2:
    {
      if (disciplina_aluno_existe(entrada, matricula))
      {
        char texto[100];
        if (lista_alunos[matricula - 1].sexo == 'M')
        {
          sprintf(texto, "> Deseja excluir %s como aluno de %s?", lista_alunos[matricula - 1].nome, entrada->nome);
        }
        else
        {
          sprintf(texto, "> Deseja excluir %s como aluna de %s?", lista_alunos[matricula - 1].nome, entrada->nome);
        }
        titulo(texto, '=', 0);
        printf("[0] - CANCELAR\n");
        printf("[1] - CONFIRMAR\n");
        printf("[2] - DIGITAR NOVAMENTE\n");
        titulo(texto, '=', 1);
        escolha_aluno_exclusao = leia_char("> Sua escolha: ");
        switch (escolha_aluno_exclusao)
        {
        case '0':
        {
          etapa = 0;
          break;
        }
        case '1':
        {
          int aux;
          for (int index1 = entrada->total_alunos_cadastrados - 1; index1 > 0; index1--)
          {
            for (int index2 = 0; index2 < index1; index2++)
            {
              if (entrada->alunos_cadastrados[index2] == matricula)
              {
                aux = entrada->alunos_cadastrados[index2 + 1];
                entrada->alunos_cadastrados[index2 + 1] = entrada->alunos_cadastrados[index2];
                entrada->alunos_cadastrados[index2] = aux;
              }
            }
          }
          entrada->total_alunos_cadastrados--;
          titulo("ALUNO EXCLUIDO COM SUCESSO!", '=', 0);
          etapa = 0;
          break;
        }
        case '2':
        {
          etapa = 1;
          break;
        }
        }
      }
      else
      {
        titulo("NAO EXISTE UM ALUNO COM A MATRICULA DIGITADA!", '~', 0);
        etapa = 1;
      }
      break;
    }
    }
  }
}

int disciplina_aluno_existe(disciplina *entrada, int matricula)
{
  int valido = 1;
  for (int i = 0; i < entrada->total_alunos_cadastrados; i++)
  {
    if (matricula == entrada->alunos_cadastrados[i])
    {
      valido = 0;
      break;
    }
  }
  if (valido)
  {
    return 0;
  }
  return 1;
}

void disciplina_aluno_insercao(disciplina *entrada, pessoa *lista_alunos, int total_alunos)
{
  int matricula = 0;
  int etapa = 0;
  int sair = 0;
  char escolha_aluno_insercao;
  while (!sair)
  {
    switch (etapa)
    {
    case 0:
    {
      titulo("CADASTRANDO ALUNO EM DISCIPLINA", '-', 0);
      printf("[0] - SAIR\n");
      printf("[1] - CADASTRAR ALUNO POR MATRICULA\n");
      printf("[2] - VER ALUNOS E CADASTRAR\n");
      titulo("CADASTRANDO ALUNO EM DISCIPLINA", '-', 1);
      escolha_aluno_insercao = leia_char("> Sua escolha: ");
      switch (escolha_aluno_insercao)
      {
      case '0':
      {
        sair = 1;
        break;
      }
      case '1':
      {
        etapa = 1;
        break;
      }
      case '2':
      {
        titulo("LISTANDO PESSOAS", '-', 1);
        ordem_cadastro(lista_alunos, total_alunos);
        etapa = 1;
        break;
      }
      default:
      {
        titulo("OPCAO INVALIDA!", '~', 0);
        break;
      }
      }
      break;
    }
    case 1:
    {
      matricula = leia_int_longo("> Digite a matricula do aluno: ");
      if (!disciplina_aluno_valido(lista_alunos, total_alunos, matricula))
      {
        titulo("NAO EXISTE ALUNO COM A MATRICULA DIGITADA!", '~', 0);
      }
      else
      {
        etapa = 2;
      }
      break;
    }
    case 2:
    {
      if (!disciplina_aluno_existe(entrada, matricula))
      {
        char texto[100];
        if (lista_alunos[matricula - 1].sexo == 'M')
        {
          sprintf(texto, "> Deseja cadastrar %s como aluno de %s?", lista_alunos[matricula - 1].nome, entrada->nome);
        }
        else
        {
          sprintf(texto, "> Deseja cadastrar %s como aluna de %s?", lista_alunos[matricula - 1].nome, entrada->nome);
        }
        titulo(texto, '=', 0);
        printf("[0] - CANCELAR\n");
        printf("[1] - CONFIRMAR\n");
        printf("[2] - DIGITAR NOVAMENTE\n");
        titulo(texto, '=', 1);
        escolha_aluno_insercao = leia_char("> Sua escolha: ");
        switch (escolha_aluno_insercao)
        {
        case '0':
        {
          etapa = 0;
          break;
        }
        case '1':
        {
          entrada->alunos_cadastrados[entrada->total_alunos_cadastrados] = matricula;
          entrada->total_alunos_cadastrados += 1;
          lista_alunos[matricula - 1].qtd_disciplinas += 1;
          titulo("ALUNO CADASTRADO COM SUCESSO!", '=', 0);
          etapa = 0;
          break;
        }
        case '2':
        {
          etapa = 1;
          break;
        }
        }
      }
      else
      {
        titulo("JA EXISTE UM ALUNO COM A MATRICULA DIGITADA!", '~', 0);
        etapa = 1;
      }
      break;
    }
    }
  }
}

int disciplina_aluno_valido(pessoa *lista_alunos, int total_alunos, int matricula)
{
  int valido = 0;
  for (int i = 0; i < total_alunos; i++)
  {
    if (lista_alunos[i].matricula == matricula)
    {
      valido = 1;
      break;
    }
  }
  if (!valido)
  {
    return 0;
  }
  return 1;
}

void disciplina_cadastro_alteracao(disciplina *lista_disciplinas, int total_disciplina, pessoa *lista_alunos, int total_alunos, pessoa *lista_professores, int total_professores)
{
  int sair = 0;
  int etapa = 0;
  int codigo_disciplina = 0;
  char escolha_aluno_exclusao;
  while (!sair)
  {
    switch (etapa)
    {
    case 0:
    {
      titulo("COMO SELECIONAR A DISCIPLINA?", '-', 0);
      printf("[0] - SAIR\n");
      printf("[1] - DIGITAR O CODIGO DA DISCIPLINA\n");
      printf("[2] - VER TODAS AS DISCIPLINAS\n");
      titulo("COMO SELECIONAR A DISCIPLINA?", '-', 1);
      escolha_aluno_exclusao = leia_char("> Sua escolha: ");
      switch (escolha_aluno_exclusao)
      {
      case '0':
      {
        sair = 1;
        break;
      }
      case '1':
      {
        etapa = 1;
        break;
      }
      case '2':
      {
        disciplina_exibicao(lista_disciplinas, total_disciplina, lista_alunos, total_alunos, 1);
        etapa = 1;
      }
      break;
      }
    }
    case 1:
    {
      titulo("COMO SELECIONAR A DISCIPLINA?", '-', 1);
      codigo_disciplina = leia_int_longo("> Digite o codigo da disciplina: ");
      if (codigo_disciplina > 0 && codigo_disciplina <= total_disciplina)
      {
        etapa = 2;
      }
      else
      {
        titulo("NAO EXISTE DISCIPLINA COM O CODIGO DIGITADO!", '~', 0);
      }
      break;
    }
    case 2:
    {
      titulo("ATUALIZACAO DE DISCIPLINA", '-', 0);
      printf("[0] - SAIR\n");
      printf("[1] - ESCOLHER OUTRA DISCIPLINA\n", lista_disciplinas[codigo_disciplina - 1].nome);
      printf("[2] - INSERIR ALUNO NA DISCIPLINA %s\n", lista_disciplinas[codigo_disciplina - 1].nome);
      printf("[3] - REMOVER ALUNO DA DISCIPLINA %s\n", lista_disciplinas[codigo_disciplina - 1].nome);
      printf("[4] - TROCAR O NOME DA DISCIPLINA %s \n", lista_disciplinas[codigo_disciplina - 1].nome);
      printf("[5] - TROCAR O SEMESTRE DA DISCIPLINA %s\n", lista_disciplinas[codigo_disciplina - 1].nome);
      printf("[6] - TROCAR O PROFESSOR DA DISCIPLINA %s\n", lista_disciplinas[codigo_disciplina - 1].nome);
      titulo("O QUE DEJEJA FAZER?", '-', 1);
      escolha_aluno_exclusao = leia_char("> Sua escolha: ");
      titulo("O QUE DEJEJA FAZER?", '-', 1);
      switch (escolha_aluno_exclusao)
      {
      case '0':
      {
        sair = 1;
        break;
      }
      case '1':
      {
        etapa = 0;
        break;
      }
      case '2':
      {
        disciplina_aluno_insercao(&lista_disciplinas[codigo_disciplina - 1], lista_alunos, total_alunos);
        sair = 1;
        break;
      }
      case '3':
      {
        disciplina_aluno_exclusao(&lista_disciplinas[codigo_disciplina - 1], lista_alunos, total_alunos);
        break;
      }
      case '4':
      {
        limpa_buffer();
        disciplina_nome(&lista_disciplinas[codigo_disciplina - 1]);
        break;
      }
      case '5':
      {
        disciplina_semestre(&lista_disciplinas[codigo_disciplina - 1]);
        break;
      }
      case '6':
      {
        disciplina_professor(&lista_disciplinas[codigo_disciplina - 1], lista_professores, total_professores);
        break;
      }
      default:
      {
        titulo("OPCAO INVALIDA!", '~', 0);
        break;
      }
      break;
      }
    }
    }
  }
}

void disciplina_cadastro_criacao(disciplina *entrada, int *total_disciplinas, pessoa *lista_professores, int total_professores)
{
  limpa_buffer();
  titulo("CADASTRO DE NOVA DISCIPLINA", '-', 0);
  titulo("ESSA EH UMA STRING MUITO GRANDE RAPAZES KKK", '=', 1);
  disciplina_nome(entrada);
  titulo("ESSA EH UMA STRING MUITO GRANDE RAPAZES KKK", '=', 1);
  disciplina_codigo(entrada, *total_disciplinas);
  titulo("ESSA EH UMA STRING MUITO GRANDE RAPAZES KKK", '=', 1);
  ;
  disciplina_semestre(entrada);
  titulo("ESSA EH UMA STRING MUITO GRANDE RAPAZES KKK", '=', 1);
  disciplina_professor(entrada, lista_professores, total_professores);
  titulo("ESSA EH UMA STRING MUITO GRANDE RAPAZES KKK", '=', 1);
  entrada->total_alunos_cadastrados = 0;
  (*total_disciplinas)++;
}

void disciplina_cadastro_exclusao(disciplina *lista_disciplinas, int *total_disciplinas, pessoa *lista_alunos, int total_alunos)
{
  int codigo_disciplina = 0;
  int etapa = 0;
  int sair = 0;
  char escolha_disciplina_exclusao;
  while (!sair)
  {
    switch (etapa)
    {
    case 0:
    {
      titulo("EXCLUSAO DE DISCIPLINA", '-', 0);
      printf("[0] - SAIR\n");
      printf("[1] - EXCLUIR DISCIPLINA POR CODIGO\n");
      printf("[2] - VER DISCIPLINAS E EXCLUIR\n");
      titulo("EXCLUSAO DE DISCIPLINA", '-', 1);
      escolha_disciplina_exclusao = leia_char("> Sua escolha: ");
      switch (escolha_disciplina_exclusao)
      {
      case '0':
      {
        sair = 1;
        break;
      }
      case '1':
      {
        etapa = 1;
        break;
      }
      case '2':
      {
        disciplina_exibicao(lista_disciplinas, *total_disciplinas, lista_alunos, total_alunos, 1);
        etapa = 1;
        break;
      }
      default:
      {
        titulo("OPCAO INVALIDA!", '~', 0);
        break;
      }
      }
      break;
    }
    case 1:
    {
      codigo_disciplina = leia_int_longo("> Digite o codigo da disciplina: ");
      if (codigo_disciplina <= 0 || codigo_disciplina > *total_disciplinas)
      {
        titulo("NAO EXISTE DISCIPLINA COM O CODIGO DIGITADO!", '~', 0);
      }
      else
      {
        etapa = 2;
      }
      break;
    }
    case 2:
    {
      char texto[50];
      sprintf(texto, "> Deseja excluir a disciplina %s?", lista_disciplinas[codigo_disciplina - 1].nome);
      titulo(texto, '=', 0);
      printf("[0] - CANCELAR\n");
      printf("[1] - CONFIRMAR\n");
      printf("[2] - DIGITAR NOVAMENTE\n");
      titulo(texto, '=', 1);
      escolha_disciplina_exclusao = leia_char("> Sua escolha: ");
      switch (escolha_disciplina_exclusao)
      {
      case '0':
      {
        etapa = 0;
        break;
      }
      case '1':
      {
        lista_disciplinas[codigo_disciplina - 1].codigo = 200;
        disciplina aux;
        for (int index1 = *total_disciplinas - 1; index1 > 0; index1--)
        {
          for (int index2 = 0; index2 < index1; index2++)
          {
            if (lista_disciplinas[index2].codigo == 200)
            {
              aux = lista_disciplinas[index2 + 1];
              lista_disciplinas[index2 + 1] = lista_disciplinas[index2];
              lista_disciplinas[index2] = aux;
            }
          }
        }
        titulo("DISCIPLINA EXCLUIDA COM SUCESSO!", '=', 0);
        (*total_disciplinas)--;
        etapa = 0;
        break;
      }
      case '2':
      {
        etapa = 1;
        break;
      }
      }
      break;
    }
    }
  }
}

void disciplina_codigo(disciplina *entrada, int posicao)
{
  entrada->codigo = posicao + 1;
  printf("> Codigo da disciplina definido como: %d.\n", posicao + 1);
}

void disciplina_exibicao(disciplina *entrada, int total_disciplinas, pessoa *lista_alunos, int total_alunos, int total)
{
  char texto[20];
  for (int disciplina = 0; disciplina < total_disciplinas; disciplina++)
  {
    if (total)
    {
      sprintf(texto, "DISCIPLINA: %s", entrada[disciplina].nome);
      titulo(texto, '=', 0);
      printf("> Codigo: %d.\n", entrada[disciplina].codigo);
      printf("> Total de alunos: %d.\n", entrada[disciplina].total_alunos_cadastrados);
      printf("> Semestre: %d.\n", entrada[disciplina].semestre);
      if (entrada[disciplina].professor->sexo == 'M')
      {
        printf("> Professor: %s.\n", entrada[disciplina].professor->nome);
      }
      else
      {
        printf("> Professora: %s.\n", entrada[disciplina].professor->nome);
      }
    }
    titulo("ALUNOS DA DISCIPLINA:", '=', 0);
    if (entrada[disciplina].total_alunos_cadastrados > 0)
    {
      for (int i = 0, aprovados = 1; i < entrada[disciplina].total_alunos_cadastrados; i++)
      {
        for (int j = 0; j < total_alunos; j++)
        {
          if (lista_alunos[j].matricula == entrada[disciplina].alunos_cadastrados[i])
          {
            printf("> %d - %s\n# Matricula: %d.\n", aprovados, lista_alunos[j].nome, lista_alunos[j].matricula);
            titulo("ALUNOS DA DISCIPLINA:", '-', 1);
            aprovados++;
            break;
          }
        }
      }
    }
    else
    {
      titulo("A DISCIPLINA NAO POSSUI ALUNOS CADASTRADOS", '~', 0);
    }
    if (entrada[disciplina].total_alunos_cadastrados > 40)
    {
      titulo("A DISCIPLINA POSSUI MAIS DE 40 ALUNOS CADASTRADOS!", '~', 0);
    }
  }
}

void disciplina_nome(disciplina *entrada)
{
  char nome[10];
  int valido = 0;
  while (!valido)
  {
    int conta_num = 0;
    int conta_dig = 0;
    printf("> Nome da disciplina: ");
    fgets(nome, 10, stdin);
    int pos = strcspn(nome, "\n");
    nome[pos] = '\0';
    if (strlen(nome) > 6)
    {
      printf("> O nome deve ter no maximo 6 caracteres!\n");
      continue;
    }
    for (int i = 0; i < strlen(nome); ++i)
    {
      valido = 1;
      if (nome[i] >= 'a' && nome[i] <= 'z')
      {
        nome[i] -= 32;
      }
      if ((!(nome[i] >= 'A' && nome[i] <= 'Z')) && (!(nome[i] >= 48 && nome[i] <= 57)))
      {
        valido = 0;
        break;
      }
    }
    if (!valido)
    {
      printf("> O nome nao pode conter acentos ou caracteres especiais!\n");
      continue;
    }
    for (int i = 0; i < strlen(nome); i++)
    {
      if (nome[i] >= 48 && nome[i] <= 57)
      {
        conta_num++;
        continue;
      }
      else if (nome[i] >= 'A' && nome[i] <= 'Z')
      {
        conta_dig++;
      }
    }
    if (conta_num == 3 && conta_dig == 3)
    {
      valido = 1;
    }
    else
    {
      valido = 0;
      printf("> O nome precisa conter tres (3) caracteres e tres (3) numeros!\n");
      continue;
    }
  }
  printf("> \"%s\" foi definido como nome.\n", nome);
  strcpy(entrada->nome, nome);
}

void disciplina_professor(disciplina *entrada, pessoa *lista_professores, int total_professores)
{
  int escolha;
  for (int i = 0; i < total_professores; i++)
  {
    exibe_pessoa(i + 1, lista_professores[i]);
    titulo("ESCOlHA O PROFESSOR(A) DA DISCIPLINA", '-', 1);
  }
  while (1)
  {
    escolha = leia_int_longo("> Escolha o professor(a) da disciplina: ");
    if (escolha < 0 || escolha > total_professores)
    {
      printf("> Valor invalido! Digite o numero de um profesor(a) existente!\n");
      continue;
    }
    break;
  }
  escolha -= 1;
  lista_professores[escolha].qtd_disciplinas += 1;
  entrada->professor = &lista_professores[escolha];
  if (lista_professores[escolha].sexo == 'M')
  {
    printf("> %s foi definido como professor da disciplina %s.\n", lista_professores[escolha].nome, entrada->nome);
  }
  else
  {
    printf("> %s foi definida como professora da disciplina %s.\n", lista_professores[escolha].nome, entrada->nome);
  }
}

void disciplina_semestre(disciplina *entrada)
{
  int retorno;
  while (1)
  {
    int valido = 0;
    retorno = leia_int_curto("> Semestre: ");
    if (retorno > 0 && retorno < 11)
    {
      valido = 1;
    }
    if (valido)
    {
      break;
    }
    printf("> O semestre digitado (%d) e invalido!\n", retorno);
  }
  entrada->semestre = retorno;
  printf("> Semestre definido como %d!\n", retorno);
}

void exibe_pessoa(int numero, pessoa entrada)
{
  printf("%d - Nome: %s.", numero, entrada.nome);
  printf("\n\n> CPF: %s.", entrada.cpf);
  printf("\n\n> Matricula: %d.", entrada.matricula);
  printf("\n\n> Sexo: %c.", entrada.sexo);
  printf("\n\n> Idade: %d.", entrada.idade);

  if (entrada.sexo == 'F')
  {
    if (entrada.qtd_disciplinas == 1)
    {
      printf("\n\n> Cadastrada em: 1 disciplina.\n");
    }
    else if (entrada.qtd_disciplinas == 0)
    {
      printf("\n\n> Nao esta cadastrada em nenhuma disciplina.\n");
    }
    else if (entrada.qtd_disciplinas > 3)
    {
      if (entrada.id)
      {
        printf("\n\n> Cadastrada em: %d disciplinas. (Professora cadastrada em mais de tres disciplinas!)\n", entrada.qtd_disciplinas);
      }
      else
      {
        printf("\n\n> Cadastrada em: %d disciplinas. (Aluna cadastrada em mais de tres disciplinas!)\n", entrada.qtd_disciplinas);
      }
    }
    else
    {
      printf("\n\n> Cadastrada em: %d disciplinas.\n", entrada.qtd_disciplinas);
    }
  }
  else if (entrada.sexo == 'M')
  {
    if (entrada.qtd_disciplinas == 1)
    {
      printf("\n\n> Cadastrado em: 1 disciplina.\n");
    }
    else if (entrada.qtd_disciplinas == 0)
    {
      printf("\n\n> Nao esta cadastrado em nenhuma disciplina.\n");
    }
    else if (entrada.qtd_disciplinas > 3)
    {
      if (entrada.id)
      {
        printf("\n\n> Cadastrado em: %d disciplinas. (Professor cadastrado em mais de tres disciplinas!)\n", entrada.qtd_disciplinas);
      }
      else
      {
        printf("\n\n> Cadastrado em: %d disciplinas. (Aluno cadastrado em mais de tres disciplinas!)\n", entrada.qtd_disciplinas);
      }
    }
    else
    {
      printf("\n\n> Cadastrado em: %d disciplinas.\n", entrada.qtd_disciplinas);
    }
  }
}

char leia_char(char texto[])
{
  char retorno;
  limpa_buffer();
  while (1)
  {
    printf("%s", texto);
    if (scanf("%c", &retorno) == 1)
    {
      break;
    }
    printf("> Entrada invalida. Tente novamente.\n");
    limpa_buffer();
  }
  return retorno;
}

int leia_int_curto(char texto[])
{
  char retorno;
  int zero = 48;
  limpa_buffer();
  while (1)
  {
    printf("%s", texto);
    if (scanf("%c", &retorno) == 1 && (retorno - zero >= 0 && retorno - zero <= 9))
    {
      break;
    }
    printf("> Entrada invalida. Tente novamente.\n");
    limpa_buffer();
  }
  return retorno - zero;
}

int leia_int_curto_sem_buffer(char texto[])
{
  char retorno;
  int zero = 48;
  while (1)
  {
    printf("%s", texto);
    if (scanf("%c", &retorno) == 1 && (retorno - zero >= 0 && retorno - zero <= 9))
    {
      break;
    }
    printf("> Entrada invalida. Tente novamente.\n");
    limpa_buffer();
  }
  return retorno - zero;
}

int leia_int_longo(char texto[])
{
  int retorno;
  while (1)
  {
    printf("%s", texto);
    if (scanf("%d", &retorno) == 1)
    {
      break;
    }
    printf("> Entrada invalida. Tente novamente.\n");
    limpa_buffer();
  }
  return retorno;
}

/*char leia_string(int tamanho, char texto[]){
  char * retorno = malloc(tamanho * sizeof(char));
}*/

// Função simples para limpar Buffer

void limpa_buffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Função para chamar o menu de alunos

void menu_aluno()
{
  titulo("MENU ALUNO", '-', 0);
  printf("[0] - MENU PRINCIPAL\n");
  printf("[1] - ATUALIZAR ALUNO EXISTENTE\n");
  printf("[2] - CADASTRAR NOVO ALUNO\n");
  printf("[3] - EXCLUIR ALUNO EXISTENTE\n");
  printf("[4] - LISTAR TODOS OS ALUNOS\n");
  titulo("MENU ALUNO", '-', 1);
}

// Função para chamar o menu de atualização

void menu_atualizacao()
{
  printf("[0] - VOLTAR\n");
  printf("[1] - ATUALIZAR CPF\n");
  printf("[2] - ATUALIZAR DATA DE NASCIMENTO\n");
  printf("[3] - ATUALIZAR NOME\n");
  printf("[4] - ATUALIZAR SEXO\n");
  printf("[5] - VER DADOS\n");
  titulo("sua escolha", '-', 1);
}

// Função para chamar o menu de buscas

void menu_busca()
{
  titulo("MENU DE BUSCA", '-', 0);
  printf("[0] - MENU PRINCIPAL\n");
  printf("[1] - BUSCAR ANIVERSARIANTE(S) DO MES\n");
  printf("[2] - BUSCAR ALUNO OU PROFESSOR\n");
  titulo("MENU DE BUSCA", '-', 1);
}

// Função para chamar o menu de disciplinas

void menu_disciplinas()
{
  titulo("MENU DISCIPLINAS", '-', 0);
  printf("[0] - MENU PRINCIPAL\n");
  printf("[1] - ATUALIZAR UMA DISCIPLINA\n");
  printf("[2] - CRIAR NOVA DISCIPLINA \n");
  printf("[3] - EXCLUIR DISCIPLINA EXISTENTE\n");
  printf("[4] - VER DISCIPLINAS\n");
  titulo("MENU DISCIPLINAS", '-', 1);
}

// Função para chamar o menu de listagens

void menu_listagem(pessoa lista_pessoas[], int total_pessoas)
{
  char escolha_menu_listagem;
  int sair = 0;
  while (!sair)
  {
    titulo("MENU DE LISTAGEM", '-', 0);
    printf("[0] - VOLTAR\n");
    printf("[1] - LISTAR CADASTRADOS EM MENOS DE X DISCIPLINAS\n");
    printf("[2] - LISTAR POR ORDEM ALFABETICA\n");
    printf("[3] - LISTAR POR ORDEM DE CADASTRO\n");
    printf("[4] - LISTAR POR ORDEM DE NASCIMENTO\n");
    printf("[5] - LISTAR POR SEXO [M/F]\n");
    titulo("MENU DE LISTAGEM", '-', 1);
    escolha_menu_listagem = leia_char("> Sua escolha: ");
    switch (escolha_menu_listagem)
    {
    case '0':
    {
      sair = 1;
      break;
    }
    case '1':
    {
      ordem_disciplinas(lista_pessoas, total_pessoas);
      break;
    }
    case '2':
    {
      ordem_alfabetica(lista_pessoas, total_pessoas);
      break;
    }
    case '3':
    {
      if (lista_pessoas[0].id)
      {
        titulo("LISTA DE PROFESSORES", '-', 0);
      }
      else
      {
        titulo("LISTA DE ALUNOS", '-', 0);
      }
      ordem_cadastro(lista_pessoas, total_pessoas);
      break;
    }
    case '4':
    {
      ordem_nascimento(lista_pessoas, total_pessoas);
      break;
    }
    case '5':
    {
      ordem_sexo(lista_pessoas, total_pessoas);
      break;
    }
    default:
    {
      titulo("OPCAO INVALIDA!", '~', 0);
      break;
    }
    }
  }
}

// Função para chamar o meu principal

void menu_principal()
{
  titulo("MENU PRINCIPAL", '-', 0);
  printf("[0] - SAIR\n");
  printf("[1] - MENU DE ALUNOS\n");
  printf("[2] - MENU DE BUSCAS\n");
  printf("[3] - MENU DE DISCIPLINAS\n");
  printf("[4] - MENU DE PROFESSORES\n");
  titulo("MENU PRINCIPAL", '-', 1);
}

// Função para chamar o menu de professores

void menu_professor()
{
  titulo("MENU PROFESSOR", '-', 0);
  printf("[0] - MENU PRINCIPAL\n");
  printf("[1] - ATUALIZAR PROFESSOR EXISTENTE\n");
  printf("[2] - CADASTRAR NOVO PROFESSOR\n");
  printf("[3] - EXCLUIR PROFESSOR EXISTENTE\n");
  printf("[4] - LISTAR TODOS OS PROFESSORES\n");
  titulo("MENU PROFESSOR", '-', 1);
}

// Função para ordenar em ordem alfabética

void ordem_alfabetica(pessoa *lista_pessoas, int total_pessoas)
{

  pessoa lista_copia[total_pessoas];

  for (int contador = 0; contador < total_pessoas; contador++)
  {
    lista_copia[contador] = lista_pessoas[contador];
  }

  if (!lista_copia[0].id)
  {
    titulo("ALUNOS EM ORDEM ALFABETICA", '-', 0);
  }
  else
  {
    titulo("PROFESSORES EM ORDEM ALFABETICA", '-', 0);
  }

  for (int i = 1; i < total_pessoas; i++)
  {
    pessoa copia = lista_copia[i];
    int j = i - 1;

    while (j >= 0 && (strcmp(lista_copia[j].nome, copia.nome) < 0))
    {
      lista_copia[j + 1] = lista_copia[j];
      j -= 1;
    }

    lista_copia[j + 1] = copia;
  }

  for (int nome = total_pessoas - 1, conta = 1; nome >= 0; --nome, ++conta)
  {
    exibe_pessoa(conta, lista_copia[nome]);
    titulo("ORDEM ALFABETICA", '-', 1);
  }
}

// Aniversariante do mês

void ordem_aniversario(int *total1, int *total2, pessoa *lista1, pessoa *lista2)
{
  time_t tempo_atual;
  struct tm *localTime;
  time(&tempo_atual);
  localTime = localtime(&tempo_atual);
  int current_month = localTime->tm_mon + 1;

  int total_geral = *total1 + *total2;
  pessoa lista_geral[total_geral];

  for (int i = 0; i < *total1; i++)
  {
    lista_geral[i] = lista1[i];
  }

  for (int i = *total2, j = 0; i < total_geral; ++i, ++j)
  {
    lista_geral[i] = lista2[j];
  }

  titulo("ANIVERSARIANTE(S) DO MES", '=', 0);
  int proxima_posicao = 0;
  for (int contador = 0; contador < total_geral; contador++)
  {
    if (lista_geral[contador].psdata.mes == current_month)
    {
      exibe_pessoa(proxima_posicao + 1, lista_geral[contador]);
      titulo("LISTANDO PESSOAS", '-', 1);
      proxima_posicao++;
    }
  }
  if (!proxima_posicao)
  {
    printf("> Oops, parece que nao ha aniversariantes este mes!\n> Tente novamente mes que vem!\n");
  }
}

// Função para buscar e encontrar personagens

void ordem_busca(int *total1, int *total2, pessoa *lista1, pessoa *lista2)
{
  int total_geral = *total1 + *total2;
  pessoa lista_geral[total_geral];

  while (1)
  {
    char termo[50];
    int flag = 0;
    printf("> Digite o termo que deseja buscar (999 sai): ");

    // Limpa o buffer de entrada antes de ler a entrada do usuário

    limpa_buffer();

    // Proseegue a execução

    fgets(termo, 50, stdin);
    int pos = strcspn(termo, "\n");
    termo[pos] = '\0';

    // Verifica se o usuário deseja parar

    if (strcmp("999", termo) == 0)
    {
      break;
    }

    // Verfica se o termo é válido

    for (int i = 0; termo[i] != '\0'; ++i)
    {
      if (!((termo[i] >= 65 && termo[i] <= 90) || (termo[i] >= 97 && termo[i] <= 122)))
      {
        printf("> O termo nao pode conter caracteres especiais ou numeros!\n");
        flag = 1;
        break;
      }
    }

    // Se o termo não for válido, reinicia o loop

    if (flag)
    {
      continue;
    }

    // Verfica se o termo esta vazio

    else if (strcmp(" ", termo) == 0 || strcmp("\0", termo) == 0)
    {
      printf("> O termo nao pode estar em branco! Tente novamente!\n");
      continue;
    }

    // Os dois primeiros loops juntam as duas listas em uma e o terceiro a organiza em ordem alfabética

    for (int i = 0; i < *total1; i++)
    {
      lista_geral[i] = lista1[i];
    }
    for (int i = *total1, j = 0; i < total_geral; ++i, ++j)
    {
      lista_geral[i] = lista2[j];
    }

    // Utiliza-se o método insertion sort para organizar a lista em orfdem alfabética

    for (int i = 1; i < total_geral; i++)
    {
      pessoa copia = lista_geral[i];
      int j = i - 1;

      while (j >= 0 && (strcmp(lista_geral[j].nome, copia.nome) > 0))
      {
        lista_geral[j + 1] = lista_geral[j];
        j -= 1;
      }

      lista_geral[j + 1] = copia;
    }

    // Para evitar repetições acidentais, estes printfs ficam fora do próximo loop

    printf("> Resultados da busca por \"%s\":\n", termo);
    titulo("> Digite qualquer tecla para volta", '-', 1);

    // Algoritimo de busca de strings em outras strings

    for (int i = 0, aprovados = 0, valido = 0; i < total_geral; ++i)
    {
      for (int j = 0, c = 0; lista_geral[i].nome[c] != '\0'; ++c)
      {
        if (lista_geral[i].nome[c] == termo[j] || lista_geral[i].nome[c] == termo[j] - 32)
        {
          if (j == strlen(termo) - 1)
          {
            j = 0;
            ++aprovados;
            ++valido;
            break;
          }
          else
          {
            ++j;
          }
        }
        else if (j > 0 && lista_geral[i].nome[c] != termo[j])
        {
          j = 0;
        }
      }
      if (valido != 0)
      {
        if (aprovados < 10)
        {
          printf("0%d - %s.", aprovados, lista_geral[i].nome);
        }
        else
        {
          printf("%d - %s.", aprovados, lista_geral[i].nome);
        }
        if (lista_geral[i].id == 0)
        {
          if (lista_geral[i].sexo == 'M')
          {
            printf(" - Aluno.\n");
          }
          else
          {
            printf(" - Aluna.\n");
          }
        }
        else if (lista_geral[i].id == 1)
        {
          if (lista_geral[i].sexo == 'M')
          {
            printf(" - Professor.\n");
          }
          else
          {
            printf(" - Professora.\n");
          }
        }
        else
        {
          printf("\n");
        }
        valido = 0;
      }
      if ((aprovados) == 0 && (i == total_geral - 1))
      {
        printf("> Oops, parece que nao ha resultados para a sua busca!\n> Tente novamente com outros termos!\n");
      }
    }
    break;
  }
}

// Função para listar por ordem de cadastro

void ordem_cadastro(pessoa *lista_pessoas, int total_pessoas)
{
  for (int contador = 0; contador < total_pessoas; contador++)
  {
    exibe_pessoa(contador + 1, lista_pessoas[contador]);
    titulo("LISTANDO PESSOAS", '-', 1);
  }
}

void ordem_disciplinas(pessoa *lista_pessoas, int total_pessoas)
{
  int x;
  int aprovados = 1;
  titulo("> Em menos de quantas disciplinas?", '=', 0);
  x = leia_int_curto("> Sua escolha: ");
  char texto[40];
  if (lista_pessoas[0].id)
  {
    sprintf(texto, "POFESSORES EM MENOS DE %d DISCIPLINAS", x);
  }
  else
  {
    sprintf(texto, "ALUNOS EM MENOS DE %d DISCIPLINAS", x);
  }
  titulo(texto, '=', 0);
  for (int index = 0; index < total_pessoas; index++)
  {
    if (lista_pessoas[index].qtd_disciplinas < x)
    {
      exibe_pessoa(aprovados, lista_pessoas[index]);
      titulo("> Em menos de quantas disciplinas?", '-', 1);
      aprovados++;
    }
  }
  if (aprovados == 1)
  {
    if (lista_pessoas[0].id)
    {
      titulo("PARECE QUE NAO HA ALUNOS NESSAS CONDICOES", '=', 0);
    }
    else
    {
      titulo("PARECE QUE NAO HA PROFESSORES NESSAS CONDICOES", '=', 0);
    }
  }
}

// Função para listar por ordem de nascimento

void ordem_nascimento(pessoa lista_pessoas[], int total_pessoas)
{

  pessoa lista_copia[total_pessoas];
  pessoa copia;

  int sair = 0;
  char escolha_menu_nascimento;

  for (int contador = 0; contador < total_pessoas; contador++)
  {
    lista_copia[contador] = lista_pessoas[contador];
  }

  while (!sair)
  {
    titulo("ESCOLHA DE MODO", '-', 0);
    printf("[0] - VOLTAR\n");
    printf("[1] - MAIS NOVO AO MAIS VELHO\n");
    printf("[2] - MAIS VELHO AO MAIS NOVO\n");
    titulo("ESCOLHA DE MODO", '-', 1);
    escolha_menu_nascimento = leia_char("> Sua escolha: ");
    switch (escolha_menu_nascimento)
    {
    case '0':
    {
      sair = 1;
      continue;
      break;
    }
    case '1':
    {
      if (!lista_copia[0].id)
      {
        titulo("ALUNOS DO MAIS NOVO AO MAIS VELHO", '-', 0);
      }
      else
      {
        titulo("PROFESSORES DO MAIS NOVO AO MAIS VELHO", '-', 0);
        ;
      }
      for (int limite = total_pessoas - 1; limite >= 0; --limite)
      {
        for (int contador = 0; contador < limite; ++contador)
        {
          if (lista_copia[contador].psdata.ano < lista_copia[contador + 1].psdata.ano)
          {
            copia = lista_copia[contador + 1];
            lista_copia[contador + 1] = lista_copia[contador];
            lista_copia[contador] = copia;
          }
          else if ((lista_copia[contador].psdata.ano == lista_copia[contador + 1].psdata.ano) && (lista_copia[contador].psdata.mes < lista_copia[contador + 1].psdata.mes))
          {
            copia = lista_copia[contador + 1];
            lista_copia[contador + 1] = lista_copia[contador];
            lista_copia[contador] = copia;
          }
          else if ((lista_copia[contador].psdata.ano == lista_copia[contador + 1].psdata.ano) && (lista_copia[contador].psdata.mes == lista_copia[contador + 1].psdata.mes) && (lista_copia[contador].psdata.dia < lista_copia[contador + 1].psdata.dia))
          {
            copia = lista_copia[contador + 1];
            lista_copia[contador + 1] = lista_copia[contador];
            lista_copia[contador] = copia;
          }
        }
      }
      break;
    }
    case '2':
    {
      if (!lista_copia[0].id)
      {
        titulo("ALUNOS DO MAIS VELHO AO MAIS NOVO", '-', 0);
      }
      else
      {
        titulo("PROFESSORES DO MAIS VELHO AO MAIS NOVO", '-', 0);
        ;
      }
      for (int limite = total_pessoas - 1; limite >= 0; --limite)
      {
        for (int contador = 0; contador < limite; ++contador)
        {
          if (lista_copia[contador].psdata.ano > lista_copia[contador + 1].psdata.ano)
          {
            copia = lista_copia[contador + 1];
            lista_copia[contador + 1] = lista_copia[contador];
            lista_copia[contador] = copia;
          }
          else if ((lista_copia[contador].psdata.ano == lista_copia[contador + 1].psdata.ano) && (lista_copia[contador].psdata.mes > lista_copia[contador + 1].psdata.mes))
          {
            copia = lista_copia[contador + 1];
            lista_copia[contador + 1] = lista_copia[contador];
            lista_copia[contador] = copia;
          }
          else if ((lista_copia[contador].psdata.ano == lista_copia[contador + 1].psdata.ano) && (lista_copia[contador].psdata.mes == lista_copia[contador + 1].psdata.mes) && (lista_copia[contador].psdata.dia > lista_copia[contador + 1].psdata.dia))
          {
            copia = lista_copia[contador + 1];
            lista_copia[contador + 1] = lista_copia[contador];
            lista_copia[contador] = copia;
          }
        }
      }
      break;
    }
    default:
    {
      titulo("OPCAO INVALIDA!", '~', 0);
      continue;
      break;
    }
    }
    for (int i = 0; i < total_pessoas; ++i)
    {
      exibe_pessoa(i + 1, lista_copia[i]);
      printf("\n> Aniversario: (%d/%d/%d).\n", lista_copia[i].psdata.dia, lista_copia[i].psdata.mes, lista_copia[i].psdata.ano);
      titulo("LISTANDO PESSOAS", '-', 1);
    }
  }
}

// Função para listar por sexo

void ordem_sexo(pessoa *lista_pessoas, int total_pessoas)
{
  int sair = 0;
  while (!sair)
  {
    titulo("ESCOLHA DE SEXO", '-', 0);
    printf("[0] - VOLTAR\n");
    printf("[1] - FEMININO  [F]\n");
    printf("[2] - MASCULINO [M]\n");
    titulo("MENU DE BUSCA", '-', 1);
    int escolha = leia_int_curto("> Sua escolha: ");
    switch (escolha)
    {
    case 0:
    {
      sair = 1;
      break;
    }
    case 1:
    {
      if (!lista_pessoas[0].id)
      {
        titulo("ALUNAS DO SEXO FEMININO", '-', 0);
      }
      else
      {
        titulo("PROFESSORAS DO SEXO FEMININO", '-', 0);
        ;
      }
      for (int contador = 0, aprovados = 1; contador < total_pessoas; ++contador)
      {
        if (lista_pessoas[contador].sexo == 'F')
        {
          exibe_pessoa(aprovados, lista_pessoas[contador]);
          titulo("ESCOLHA DE SEXO", '-', 1);
          ++aprovados;
        }
      }
      break;
    }
    case 2:
    {
      if (lista_pessoas[0].id == 0)
      {
        titulo("ALUNOS DO SEXO MASCULINO", '-', 0);
      }
      else
      {
        titulo("PROFESSORES DO SEXO MASCULINO", '-', 0);
        ;
      }
      for (int contador = 0, aprovados = 1; contador < total_pessoas; ++contador)
      {
        if (lista_pessoas[contador].sexo == 'M')
        {
          exibe_pessoa(aprovados, lista_pessoas[contador]);
          titulo("LISTANDO PESSOAS", '-', 1);
          ++aprovados;
        }
      }
      break;
    }
    default:
    {
      titulo("OPCAO INVALIDA!", '~', 0);
      break;
    }
    }
  }
}

// Função para criar um título estilizado

void titulo(char string[], char simbolo, int linha)
{
  int tamanho_string = strlen(string) + 4;
  int cont;
  if (!linha)
  {
    for (cont = 0; cont < tamanho_string; cont++)
    {
      printf("%c", simbolo);
    }
    printf("\n  %s  \n", string);
    for (cont = 0; cont < tamanho_string; cont++)
    {
      printf("%c", simbolo);
    }
    printf("\n");
  }
  else
  {
    for (cont = 0; cont < tamanho_string; cont++)
    {
      printf("%c", simbolo);
    }
    printf("\n");
  }
}

int valida_cpf(char *cpf)
{
  const int zero = 48;
  int etapa = 0;
  int digito1 = 0;
  int digito2 = 0;
  int testado = 0;
  int multiplicador = 10;
  while (!testado)
  {
    switch (etapa)
    {
    case 0:
    {
      for (int index = 0; index < 11; index++)
      {
        if (cpf[index] >= '0' && cpf[index] <= '9')
        {
          digito1 += (cpf[index] - zero) * multiplicador;
          multiplicador--;
        }
      }

      digito1 = 11 - (digito1 % 11);
      if (digito1 >= 10)
      {
        digito1 = 0;
      }

      if ((cpf[12] - zero) != digito1)
      {
        return 0;
      }
      etapa = 1;
      multiplicador = 11;
      break;
    }
    case 1:
    {
      for (int index = 0; index < 13; index++)
      {
        if (cpf[index] >= '0' && cpf[index] <= '9')
        {
          digito2 += (cpf[index] - zero) * multiplicador;
          multiplicador--;
        }
      }

      digito2 = (digito2 * 10) % 11;
      if ((cpf[13] - zero) != digito2)
      {
        return 0;
      }
      testado = 1;
      break;
    }
    }
  }
  return 1;
}

#endif /*escolaV3*/

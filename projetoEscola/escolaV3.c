// Nome: Projeto escola.
// Objetivo: Controlar o funcionamento de uma Escola.
// Criadores: Ana Ruth, Deivison Cassimiro, Julio santos, Rafael Mota 

# define maximo 6
# include "escolaV3.h"

// Função principal/Main

int main(){

  // Declaração de variàveis

  int menu_atual = 0;
  int sair = 0;
  int total_alunos = 5;
  int total_professores = 5;
  int total_disciplinas = 1;
  int iteracao = 0;
  pessoa lista_professores[maximo];
  pessoa lista_alunos[maximo];
  disciplina lista_disciplinas[maximo];

  // Professor especial

    pessoa  professor_especial;
    strcpy(professor_especial.nome , "Renato Novais");
  strcpy(professor_especial.cpf, "918.063.736-10");
  professor_especial.matricula = 12;
  professor_especial.sexo = 'M';
  professor_especial.idade = 30;
  professor_especial.psdata.ano = 1993;
  professor_especial.psdata.mes = 05;
  professor_especial.psdata.dia = 04;
  professor_especial.id = 1;
  professor_especial.qtd_disciplinas  = 1;

  // Disciplinas de testes

  lista_disciplinas[0].professor = &professor_especial;
  lista_disciplinas[0].alunos_cadastrados[0] = 5;
  lista_disciplinas[0].alunos_cadastrados[1] = 4;
  lista_disciplinas[0].alunos_cadastrados[2] = 3;
  lista_disciplinas[0].codigo = 1;
  lista_disciplinas[0].total_alunos_cadastrados = 3;
  lista_disciplinas[0].semestre = 2;
  strcpy(lista_disciplinas[0].nome, "INF029");

    // ALuno(s) de teste:

{
  strcpy(lista_alunos[0].nome, "Luis Ribeiro");
  strcpy(lista_alunos[0].cpf, "789.853.354-14");
  lista_alunos[0].matricula = 1;
  lista_alunos[0].sexo = 'M';
  lista_alunos[0].idade = 20;
  lista_alunos[0].psdata.ano = 2003;
  lista_alunos[0].psdata.mes = 01;
  lista_alunos[0].psdata.dia = 27;
  lista_alunos[0].id = 0;
  lista_alunos[0].qtd_disciplinas = 0;

  strcpy(lista_alunos[1].nome, "Maria Josfa");
  strcpy(lista_alunos[1].cpf, "687.021.432-00");
  lista_alunos[1].matricula = 2;
  lista_alunos[1].sexo = 'F';
  lista_alunos[1].idade = 15;
  lista_alunos[1].psdata.ano = 2008;
  lista_alunos[1].psdata.mes = 12;
  lista_alunos[1].psdata.dia = 01;
  lista_alunos[1].id = 0;
  lista_alunos[1].qtd_disciplinas = 0;

  strcpy(lista_alunos[2].nome, "Ana Clara");
  strcpy(lista_alunos[2].cpf, "589.072.547-78");
  lista_alunos[2].matricula = 3;
  lista_alunos[2].sexo = 'F';
  lista_alunos[2].idade = 17;
  lista_alunos[2].psdata.ano = 2006;
  lista_alunos[2].psdata.mes = 05;
  lista_alunos[2].psdata.dia = 06;
  lista_alunos[2].id = 0;
  lista_alunos[2].qtd_disciplinas = 1;

  strcpy(lista_alunos[3].nome, "Carlos Daniel");
  strcpy(lista_alunos[3].cpf, "226.464.135-54");
  lista_alunos[3].matricula = 4;
  lista_alunos[3].sexo = 'M';
  lista_alunos[3].idade = 27;
  lista_alunos[3].psdata.ano = 1996;
  lista_alunos[3].psdata.mes = 07;
  lista_alunos[3].psdata.dia = 13;
  lista_alunos[3].id = 0;
  lista_alunos[3].qtd_disciplinas = 1;

  strcpy(lista_alunos[4].nome, "Isabel Cristina");
  strcpy(lista_alunos[4].cpf, "415.357.108-36");
  lista_alunos[4].matricula = 5;
  lista_alunos[4].sexo = 'F';
  lista_alunos[4].idade = 54;
  lista_alunos[4].psdata.ano = 1969;
  lista_alunos[4].psdata.mes = 10;
  lista_alunos[4].psdata.dia = 2;
  lista_alunos[4].id = 0;
  lista_alunos[4].qtd_disciplinas = 1;

  // Professor(es) de teste

  strcpy(lista_professores[0].nome, "Pedro Maroos");
  strcpy(lista_professores[0].cpf, "215.967.346-15");
  lista_professores[0].matricula = 1;
  lista_professores[0].sexo = 'M';
  lista_professores[0].idade = 34;
  lista_professores[0].psdata.ano = 1989;
  lista_professores[0].psdata.mes = 03;
  lista_professores[0].psdata.dia = 27;
  lista_professores[0].id = 1;
  lista_professores[0].qtd_disciplinas  = 0;

  strcpy(lista_professores[1].nome, "Julia Menescau");
  strcpy(lista_professores[1].cpf, "377.942.125-01");
  lista_professores[1].matricula = 2;
  lista_professores[1].sexo = 'F';
  lista_professores[1].idade = 40;
  lista_professores[1].psdata.ano = 1983;
  lista_professores[1].psdata.mes = 05;
  lista_professores[1].psdata.dia = 06;
  lista_professores[1].id = 1;
  lista_professores[1].qtd_disciplinas  = 0;

  strcpy(lista_professores[2].nome, "Claudio Freitas");
  strcpy(lista_professores[2].cpf, "157.789.165-23");
  lista_professores[2].matricula = 3;
  lista_professores[2].sexo = 'M';
  lista_professores[2].idade = 30;
  lista_professores[2].psdata.ano = 1993;
  lista_professores[2].psdata.mes = 05;
  lista_professores[2].psdata.dia = 04;
  lista_professores[2].id = 1;
  lista_professores[2].qtd_disciplinas  = 0;

  strcpy(lista_professores[3].nome, "Raimunda Silva");
  strcpy(lista_professores[3].cpf, "578.245.267-05");
  lista_professores[3].matricula = 4;
  lista_professores[3].sexo = 'F';
  lista_professores[3].idade = 25;
  lista_professores[3].psdata.ano = 1998;
  lista_professores[3].psdata.mes = 10;
  lista_professores[3].psdata.dia = 03;
  lista_professores[3].id = 1;
  lista_professores[3].qtd_disciplinas  = 0;

  strcpy(lista_professores[4].nome, "Mathias Sants");
  strcpy(lista_professores[4].cpf, "754.731.732-45");
  lista_professores[4].matricula = 5;
  lista_professores[4].sexo = 'M';
  lista_professores[4].idade = 20;
  lista_professores[4].psdata.ano = 1998;
  lista_professores[4].psdata.mes = 10;
  lista_professores[4].psdata.dia = 27;
  lista_professores[4].id = 1;
  lista_professores[4].qtd_disciplinas  = 0;
}

  while(!sair){
      switch(menu_atual){

        // Menu principal  

        case 0:{
          menu_principal();
          int escolha_menu_principal = 0;
          if(iteracao){
              escolha_menu_principal = leia_int_curto("> Sua escolha: ");
        }
        else{
          escolha_menu_principal = leia_int_curto_sem_buffer("> Sua escolha: ");
        }
            switch(escolha_menu_principal){
                case 0:{	
                  sair = 1;
                  titulo("FINALIZANDO...", '-', 0);
                  break;
          }
            case 1:{
                menu_atual = 1;
                  break;
          }
              case 2:{
                menu_atual = 2;
                  break;
          }
              case 3:{
                  menu_atual = 3;
                  break;
          }
              case 4:{
                  menu_atual = 4;
                  break;
          }
              default:{
                  titulo("OPCAO INVALIDA!", '~', 0);
                  break;
          }
            }
            continue;
            break;
      }

      // Menu aluno 

          case 1:{
            menu_aluno();
            char escolha_menu_aluno = leia_char("> Sua escolha: ");     	
            switch(escolha_menu_aluno){
                case '0':{ // Volta ao menu principal
                  menu_atual = 0;
                  break;
          }
              case '1':{ // Atualização de alunos
            titulo("LISTANDO TODOS OS CADASTROS", '-', 0);
            ordem_cadastro(lista_alunos, total_alunos);
            while(1){
              int num_aluno = 0;
              titulo("> Escolha qual cadastro deseja atualizar: ", '-', 1);
              num_aluno = leia_int_longo("> Escolha qual cadastro deseja atualizar (0 sai): ");
              if(num_aluno == 0){
                break;
              }
              else if(num_aluno > total_alunos || 0 >= num_aluno){
                titulo("NAO EXISTE CADASTRO COM O NUMERO DIGITADO!", '-', 0);
                continue;
              }
              else{
                cadastro_atualizacao(&lista_alunos[num_aluno - 1]);
                break;
              }
            }
            break;
          }
              case '2':{ // Cadastro de alunos
                  titulo("CADASTRO DE NOVO ALUNO", '-', 0);
                  if(total_alunos < maximo){
                    lista_alunos[total_alunos].id = 0;
                    cadastro_novo(&lista_alunos[total_alunos], &total_alunos);
            }
            else{
              titulo("MAXIMO DE ALUNOS ATINGIDO!", '~', 0);
            }
            break;
          }
              case '3':{ // Exclusão de alunos
            titulo("LISTANDO TODOS OS ALUNOS", '-', 0);
            ordem_cadastro(lista_alunos, total_alunos);
                  while(1){
              int num_aluno = 0;
              titulo("> Escolha qual cadastro deseja excluir: ", '-', 1);
              num_aluno = leia_int_longo("> Escolha qual cadastro deseja excluir (0 sai): ");
              if(num_aluno == 0){
                break;
              }						
              else if(num_aluno > total_alunos || 0 >= num_aluno){
                titulo("NAO EXISTE CADASTRO COM O NUMERO DIGITADO!", '-', 0);
              }
              else{
                cadastro_exclusao(lista_alunos, num_aluno - 1, &total_alunos);
                break;
              }
            }
                  break;
          }
                case '4':{ // Visualização de alunos
                  menu_listagem(lista_alunos, total_alunos);
                  break;
              } 
              default:{
                titulo("OPCAO INVALIDA!", '~', 0);
                  break;                     
          }
            }   
            break;
        }

          // Menu de  de busca

          case 2:{
            menu_busca();
            char escolha_menu_busca = leia_char("> Sua escolha: ");
        switch(escolha_menu_busca){
              case '0':{	
                menu_atual = 0;
                break;
            }
          case '1':{
            ordem_aniversario(&total_alunos, &total_professores, lista_alunos, lista_professores);
            break;
          }
                case '2':{
            ordem_busca(&total_alunos, &total_professores, lista_alunos, lista_professores);
            break; 
          }
              default:{
            titulo("OPCAO INVALIDA!", '~', 0);
            continue;
            break;
          }
        }
        break;
      }

        // Menu de disciplinas

          case 3:{
            menu_disciplinas();
            char escolha_menu_disciplina = leia_char("> Sua escolha: ");
            switch(escolha_menu_disciplina){
                case '0':{ // Volta ao menu principal
                  menu_atual = 0;
                  limpa_buffer();
            break;
          }
          case'1':{
            disciplina_cadastro_alteracao(lista_disciplinas, total_disciplinas, lista_alunos, total_alunos, lista_professores, total_professores);
            break;
          }
          case'2':{
            if(total_disciplinas >= maximo){
              titulo("MAXIMO DE DISCIPLINAS CADASTRADAS ATINGIDO!", '=', 0);
            }
            else{
              disciplina_cadastro_criacao(&lista_disciplinas[total_disciplinas], &total_disciplinas, lista_professores, total_professores);
            }
            break;
          }
          case '3':{
            disciplina_cadastro_exclusao(lista_disciplinas, &total_disciplinas, lista_alunos, total_alunos);
            break;
          }
          case'4':{
            disciplina_exibicao(lista_disciplinas, total_disciplinas, lista_alunos, total_alunos, 1);
            break;
          }
          default:{
            titulo("OPCAO INVALIDA!", '~', 0);
            break;
          }
          }	
          break;
       }
        // Menu de professores

          case 4:{
            menu_professor();
          char escolha_menu_professor = leia_char("> Sua escolha: ");       	
            switch(escolha_menu_professor){
                case '0':{ // Volta ao menu principal
                  menu_atual = 0;
            break;
          }	
              case '1':{ // Atualização de professores
            titulo("LISTANDO TODOS OS PROFESSORES", '-', 0);
            ordem_cadastro(lista_professores, total_professores);
            while(1){
              int num_professor = 0;
              titulo("> Escolha qual cadastro deseja atualizar: ", '-', 1);
              num_professor = leia_int_longo("> Escolha qual cadastro deseja atualizar (0 sai): ");
              if(num_professor == 0){
                break;
              }
              else if(num_professor > total_professores|| 0 >= num_professor){
                titulo("NAO EXISTE CADASTRO COM O NUMERO DIGITADO!", '-', 0);
                continue;
              }
              else{
                cadastro_atualizacao(&lista_professores[num_professor - 1]);
                break;
              }
            }
            break;
          }
                case '2':{ // Cadastro de professores
                  titulo("CADASTRO DE NOVO PROFESSOR", '-', 0);
                  if(total_professores < maximo){
                    lista_professores[total_professores].id = 1;
                    cadastro_novo(&lista_professores[total_professores], &total_professores);
            }
            else{					
              titulo("MAXIMO DE PROFESSORES ATINGIDO!", '~', 0);
            }
                  break;
          }
                case '3':{ // Exclusão de professores
            titulo("LISTANDO TODOS OS professorS", '-', 0);
            ordem_cadastro(lista_professores, total_professores);
                  while(1){
              int num_professor = 0;
              titulo("> Escolha qual cadastro deseja excluir: ", '-', 1);
              num_professor = leia_int_longo("> Escolha qual cadastro deseja excluir (0 sai): ");
              if(num_professor == 0){
                break;
              }						
              else if(num_professor > total_professores || 0 >= num_professor){
                titulo("NAO EXISTE CADASTRO COM O NUMERO DIGITADO!", '-', 0);
              }
              else{
                cadastro_exclusao(lista_professores, num_professor - 1, &total_professores);
                break;
              }
            }
                  break;
          }
                case '4':{ // Visualização de professores
                menu_listagem(lista_professores, total_professores);
                break;
              } 
              default:{
                    titulo("OPCAO INVALIDA!", '~', 0);
                      break; 
              }
        }
        break;
          }
          default:{
            titulo("OPCAO INVALIDA!", '~', 0);
            break;
      }
      }
      iteracao = 1;
    }
    return 0;
}

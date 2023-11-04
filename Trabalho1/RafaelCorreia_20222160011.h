// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome:
//  email:
//  Matrícula:
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021

// #################################################
#ifndef RafaelCorreia_20222160011
#define RafaelCorreia_20222160011

typedef struct{
	int qtdDias;
	int qtdMeses;
	int qtdAnos;
	int retorno;
}DiasMesesAnos;

int isBissexto(int year);
int q1(char * input);
DiasMesesAnos q2(char * initialDate, char * finalDate);
int q3(char * stringInput, char letra, int isCaseSensitive);
int q4(char * phrase, char * word, int positions[]);
long long int q5(long long int numInput);
int q6(long long int numInput, long long int numSearch);
DiasMesesAnos strToDate(char * input);
void titulo(char * string, char simbol, int line);


#endif  // TRABALHO1_PRIMEIROULTIMONOMEMATRICULA_H

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
//  Nome: Rafael Mota Correia
//  email: rafaelmota361@gmail.com
//  Matrícula: 20222160011
//  Semestre: 2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "RafaelCorreia_20222160011.h" // Substitua pelo seu arquivo de header renomeado

int isBissexto(int year){
	return(year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}
 

int q1(char * input){
	int indexTmp;
	int day, month, year;
	for(int indexDate = 0, indexString = 0; indexDate < 3; indexDate++){
		char strTmp[5];
		for(indexTmp = 0; input[indexString] != '/' && input[indexString] != '\0'; indexString ++, indexTmp++){
			if(!(input[indexString] >= '0' && '9' >= input[indexString])){
				return 0;
			}
			strTmp[indexTmp] = input[indexString];
		} // Minor for
		indexString ++;
		strTmp[indexTmp] = '\0'; 
		switch(indexDate){
			case 0:{
				if(!(indexTmp == 1 || indexTmp == 2)){
					return 0;
				}
				day = atoi(strTmp);
				break;
			}
			case 1:{
				if(!(indexTmp == 1 || indexTmp == 2)){
					return 0;
				}
				month = atoi(strTmp);
				break;
			}
			case 2:{
				if(!(indexTmp == 2 || indexTmp == 4)){
					return 0;
				}
				if(indexTmp == 2){
					year = atoi(strTmp) + 2000;
				}
				else{
					year = atoi(strTmp);
				}
				break;
			}
		}	 // Switch
	
	} // Major for
    if (month < 1 || month > 12) {
        return 0;
    }
	else if (month == 2) {  // Fevereiro
        if(isBissexto(year)){
        	if(day > 29){
        		return 0;
			}
		}
		else{
			if(day > 28){
				return 0;
			}
		}
    }
	else if ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30)) {  // Abril, Junho, Setembro, Novembro
    	return 0;
    }
	else {  // Meses com 31 dias (Janeiro, Março, Maio, Julho, Agosto, Outubro, Dezembro)
        if(day > 31){
        	return 0;
		}
	}
	return 1; 
	
} // func


DiasMesesAnos q2(char * initialDate, char * finalDate){
	
	int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	DiasMesesAnos difference = {0};
	int mesesDiferenca = 0;
	int anosDiferenca = 0;
	int diasDiferenca = 0;
	
	// Verifica se ambas as datas são válidas
	
	if(!q1(initialDate)){ 
		difference.retorno = 2;
		return difference;
	}
	if(!q1(finalDate)){
		difference.retorno = 3;
		return difference;
	}
		
	// Armazena as datas em variáveis auxiliares
	
	DiasMesesAnos date1 = strToDate(initialDate);
	DiasMesesAnos date2 = strToDate(finalDate);
	
	// Verifica se a data inicial é maior que a final 
	
	if(date1.qtdAnos > date2.qtdAnos){
		difference.retorno = 4;
		return difference;
	}
	else if(date1.qtdAnos == date2.qtdAnos && date1.qtdMeses > date2.qtdMeses){
		difference.retorno = 4;
		return difference;
	}
	else if(date1.qtdAnos == date2.qtdAnos && date1.qtdMeses == date2.qtdMeses && date1.qtdDias >= date2.qtdDias){
		difference.retorno = 4;
		return difference;
	}

	DiasMesesAnos tmp;
	tmp = date1;
	
	if(tmp.qtdMeses == date2.qtdMeses ){
		difference.qtdAnos = date2.qtdAnos - tmp.qtdAnos ;
		difference.qtdMeses = 0;
		difference.qtdDias = date2.qtdDias - tmp.qtdDias;
		difference.retorno = 1;
		return difference;
	}
	
	int day = tmp.qtdDias;
	while(!(tmp.qtdDias == date2.qtdDias && tmp.qtdMeses == date2.qtdMeses && tmp.qtdAnos == date2.qtdAnos)) {
		if(tmp.qtdMeses != 2){
			if(day == diasNoMes[tmp.qtdMeses]){
				if(tmp.qtdMeses == 12){
					tmp.qtdAnos += 1;
					tmp.qtdMeses = 1;
					tmp.qtdDias = 1;
					anosDiferenca++;
					diasDiferenca += 1;
				}
				else{
					tmp.qtdDias = 1;
					tmp.qtdMeses += 1;
					diasDiferenca += 1;
				}
				mesesDiferenca += 1;
				tmp.qtdDias = 1;
				day = 1;
			}
			else{
			}
		}
		else{
			if(isBissexto(tmp.qtdAnos)){
				if(day == 29){
					tmp.qtdMeses += 1;
					tmp.qtdDias = 1;
					diasDiferenca += 1;
					day = 1;
				}
			}
			else{
				if(day == 28){
					tmp.qtdMeses += 1;
					tmp.qtdDias = 1;
					diasDiferenca += 1;
					day = 1;
				}
			}	
		}
		diasDiferenca += 1;
		day++;
		if(!(tmp.qtdDias == date2.qtdDias && tmp.qtdMeses == date2.qtdMeses && tmp.qtdAnos == date2.qtdAnos)){
			tmp.qtdDias ++;
		}
	}
	if(diasDiferenca == diasNoMes[date1.qtdMeses]){
		difference.qtdAnos = 0;
		difference.qtdMeses = 1;
		difference.qtdDias = 0;
		difference.retorno = 1;
		return difference;
	}
	
	if(diasDiferenca >= 30 && diasDiferenca < diasNoMes[date1.qtdMeses]){
		difference.qtdAnos = anosDiferenca;
		difference.qtdMeses = diasDiferenca % 365 / diasNoMes[date1.qtdMeses];
		difference.qtdDias = diasDiferenca % 365 % diasNoMes[date1.qtdMeses];
		difference.retorno = 1;
		return difference;
	}
	difference.qtdAnos = anosDiferenca;
	difference.qtdMeses = diasDiferenca % 365 / 30.44;
	difference.qtdDias = diasDiferenca % 365 % 30;
 	difference.retorno = 1;
	return difference;
}


int q3(char * stringInput, char word, int isCaseSensitive){ 
	int occurrences = 0;
	for(int i = 0; stringInput[i] != '\0'; i++){
		if(isCaseSensitive){
			if(stringInput[i] == word){
				occurrences ++;	
			}
			continue;
		}
		if((stringInput[i] == word) || (stringInput[i] == word - 32) || (stringInput[i] == word + 32)){
			occurrences ++;
		}
	}
	return occurrences;
}


int q4(char * phrase, char * word, int positions[]){
	int indexPsc = 0;
	int ocorrencias = 0;
	char * mapaAcentos = "áàãâéèêíìóòõôúùûç";
    char * mapaSemAcentos = "aaaaeeeiioooouuuc";
    
    for (int i = 0; word[i] != '\0'; i++) {
        for (int j = 0; mapaAcentos[j] != '\0'; j++) {
            if (word[i] == mapaAcentos[j]) {
                word[i] = mapaSemAcentos[j];
                break;
            }
            else if(word[i] == 0231 || word[i] == - 121){
            	word[i] = 'c';
			     }
        }
    }
    
	for(int indexWord = 0, indexPhrase = 0; phrase[indexPhrase] != '\0'; ++indexPhrase){
		if (indexWord > 0 && phrase [indexPhrase] != word[indexWord]){
			indexWord = 0;
		}	
		if(phrase[indexPhrase] == word[indexWord]){
			if(indexWord == strlen(word) - 1){
				ocorrencias++;
				positions[indexPsc] = indexPhrase - (strlen(word) - 2);
				indexPsc++;
				positions[indexPsc] = indexPhrase + 1;
				indexPsc++;
				indexWord = 0;
			}
			else{
				++indexWord;
			}
		}
	}
	return ocorrencias;
}


long long int q5(long long int numInput){
	
    long long int numOutput = 0;
    long long int indexMulti;
 	long long int copiaInput;
 	copiaInput = numInput;
 	
	for(indexMulti = 1; copiaInput > 0; indexMulti = indexMulti * 10) {
    	copiaInput /= 10;
    	if(!copiaInput > 0){
    		break;
		}
	}	
	
    for (; numInput > 0; indexMulti = indexMulti / 10){
    	numOutput += (numInput % 10) * indexMulti;
    	numInput /= 10;
	}
    return numOutput;
}


int q6(long long int numInput, long long int numSearch){
	
	int digits = 0;
	int foundedDigits = 0;
	int foundedTimes = 0;
	
	for(long long int tmpSearch = numSearch; tmpSearch > 0;) {
    	tmpSearch /= 10;
    	digits ++;
    	if(!tmpSearch > 0){
    		break;
		}
	}
	
	for(long long int copyInput = numInput, copySearch = numSearch; copyInput > 0;){
		int tmp = copyInput % 10;
		if(tmp == copySearch % 10){
			foundedDigits ++;
			copySearch = copySearch / 10;
			if(foundedDigits == digits){
				foundedTimes ++;
				copySearch = numSearch;
				foundedDigits = 0;
			}
		}
		else{
			foundedDigits = 0;
		}
		copyInput = copyInput / 10;
	}
	
	return foundedTimes;
}


DiasMesesAnos strToDate(char * input){
	DiasMesesAnos output = {0};
	char * slice;
	const char * separator = "/";
	slice = strtok(input, separator);
	output.qtdDias = atoi(slice);
	slice = strtok(NULL, separator);
	output.qtdMeses = atoi(slice);
	slice = strtok(NULL, separator);
	output.qtdAnos = atoi(slice);
	return output;
}

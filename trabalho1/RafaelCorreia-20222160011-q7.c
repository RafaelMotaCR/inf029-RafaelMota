# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <time.h>

#ifdef _WIN32
    # include <conio.h>
#elif __linux__
    # include <termios.h>
#endif

void bufferCLR();
int checkColumn(char input[][3]);
int checkLine(char input[][3]);
int checkMainDiagonal(char input[][3]);
int checkSecondaryDiagonal (char input [][3]);
void cleanScreen();
int mainMenu();
void moveMenu();
void printBoard(char input[][3], int x, int y);
int readShortInt(char * texto, int firstTime);
void showTurn(int input);
void title(char * string, char simbol, int line);


void bufferCLR(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int checkMainDiagonal(char input[][3]){
	if(input[0][0] == input[1][1] && input[1][1] == input[2][2] && input[2][2] != ' '){
		return 1;
	}
	return 0;
}
	

int checkSecondaryDiagonal (char input [][3]){
	if(input[2][0] == input[1][1] && input[1][1] == input[0][2] && input[1][1] != ' '){
		return 1;
	}
	return 0;
}	
	

int checkLine(char input[][3]){
	for(int x = 0, equal = 0; x < 3; x++){
		for(int y = 0; y < 3; y++){
			if(input[x][y] == input[x][y + 1] && input[x][y + 1] != ' '){
				equal += 1;
				if(equal == 2){
					return 1;
				break;	
				}
				continue;	
			}
			break;
		}
		equal = 0;
	}
	return 0;
}


int checkColumn(char input[][3]){
	for(int x = 0, equal = 0; x < 3; x++){
		for(int y = 0; y < 3; y++){
			if(input[y][x] == input[y + 1][x] && input[y][x] != ' '){
				equal += 1;
				if(equal == 2){
					return 1;
				break;	
				}	
				continue;
			}
			break;
		}
		equal = 0;
	}
	return 0;
}


void cleanScreen(){
#ifdef _WIN32
    system("cls"); 
#elif __linux__
    system("clear"); 
#else
    // Sistema operacional desconhecido, não faz nada
#endif
}


# if __linux__
char getch() {
    char buf = 0;
    struct termios old = { 0 };
    fflush(stdout);
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
    old.c_lflag    &= ~ICANON;   // local modes = Non Canonical mode
    old.c_lflag    &= ~ECHO;     // local modes = Disable echo. 
    old.c_cc[VMIN]  = 1;         // control chars (MIN value) = 1
    old.c_cc[VTIME] = 0;         // control chars (TIME value) = 0 (No time)
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) perror("read()");
    old.c_lflag    |= ICANON;    // local modes = Canonical mode
    old.c_lflag    |= ECHO;      // local modes = Enable echo. 
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror ("tcsetattr ~ICANON");
    return buf;
}
# endif


int mainMenu(){
	title("MAIN MENU", '=', 0);
	printf("[0] - Exit\n");
	printf("[1] - Multiplayer\n");
	printf("[2] - Single Player\n");
	title("MAIN MENU", '-', 1);
	return readShortInt("> Your Choice: ", 1);
}


void moveMenu(){
	title("CONTROLS", '=', 0);
	printf("[W] - Up\n");
	printf("[S] - Down\n");
	printf("[A] - Left\n");
	printf("[D] - Right\n");
	printf("[[_]] - Confirm Play\n");
	printf("[P] - Stop\n");
	title("controls", '=', 1);
	printf("> Your play: ");
}


void printBoard(char input[][3], int x, int y){
	for(int i = 0; i < 3; i++){
		printf("    |");
		for (int j = 0; j < 3; j++){
			if (j == 0 || j == 1){	
				if (j == x && i == y){
					printf(" {%c} ", input[i][j]);
				}
				else{
					printf("  %c  ", input[i][j]);
				}
				printf("|");	
			}
			else{
				if (j == x && i == y){
					printf(" {%c} ", input[i][j]);
				}
				else{
					printf("  %c  ", input[i][j]);
				}
			}
		}
		printf("|\n    ");
		if(i < 2){
			for(int k = 0; k <= 8; k ++){
				printf("--");	
			}
			printf("-");
		}
		printf("\n");
	}
}


int readShortInt(char * text, int firstTime) {
	char output;
	int zero = 48;
	if(!firstTime){
	bufferCLR();
	}
	while (1){
		printf("%s", text);
		if (scanf("%c", &output) == 1 && (output - zero >= 0 && output - zero <= 9)) {
			break; 
		}
		printf("> Invalid input. Try again!\n");
		bufferCLR();
	}
	return output - zero;
}
	

void showTurn(int input){
	char text[50];
	if(!(input % 2) || !input){
		sprintf(text,"PlAYER 1 (X) | TURN: %d.", input + 1); 
	}
	else{
		sprintf(text,"PlAYER 2 (O) | TURN: %d.", input + 1); 
	}
	title(text, '-', 0);
	printf("\n");		
}


void title(char * string, char simbol, int line){
	int stringTan;
	for(stringTan = 0; string[stringTan] != '\0'; stringTan ++){
	}
	stringTan += 4;
  	int index;
  	if(!line){
    	for(index = 0; index < stringTan; index++){
      		printf("%c", simbol);
    	}
    	
    	printf("\n| %s |\n", string);
    	
    	for(index = 0; index < stringTan; index++){
      		printf("%c", simbol);
    	}
    	printf("\n");
  	}
  	else{
    	for(index = 0; index < stringTan; index++){
      		printf("%c", simbol);
    	}
    printf("\n");
	}
}


void main(){
	
	int exit = 0;
	
	while(!exit){
		
		// Inicio da declaração de variáveis 
		
		int menu = 0;
		int round = 0;
		int gameMode = 0;
		int selection;
		int pstySelector = 1;
		int pstxSelector = 1;
		int pcy = 0;
		int pcx = 0;
		int victoria = 0;
		char gameBoard[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
	
		srand((unsigned)time(NULL));
		
		// Fim da declaração de variáveis 

		// Menu básico de seleção
		
		while(menu != 10){
			menu = mainMenu();
			switch(menu){
				case 0:{
					title("Exiting...", '=', 0);
					gameMode = 3;
					menu = 10;
					exit = 1;
					break;
				}
				case 1:{
					menu = 10;
					printf("> PvP mode choosed!\n");
					printf("> Press any key to beggin.");
					getch();
					cleanScreen();
					gameMode = 1;
					break;
				}
				case 2:{
					gameMode = 0;
					cleanScreen();
					title("SINGLE PLAYER", '=', 0);
					printf("> Choose between: 'X' or 'O':\n\n");
					printf("[1] - X.\n");
					printf("[2] - O.\n\n");
					while(1){
						selection = readShortInt("> Your choice: ", 0);
						if(selection == 1){
							printf("> Well done, you will be 'X'!\n");
							break;
						}
						else if (selection == 2){
							printf("> Well done, you will be 'O'!\n");
							break;
						}
						else{
							title("IVALID OPTION!", '=', 0);
						}
					}
					menu = 10;
					printf("> Press any key to beggin.");
					getch();
					cleanScreen();
					break;
				}
				default:{
					title("IVALID OPTION!", '=', 0);
					bufferCLR();
					break;
				}
			}
		}
		// Modo Multiplayer
		
		while(round < 10 && exit != 1){
			
			// Mostra de quem é a vez
						
			showTurn(round);

			// Imprime o gameBoard
			printBoard(gameBoard,  pstxSelector,  pstySelector);
			
			// Testa se alguém venceu na play anterior
			
			if(checkMainDiagonal(gameBoard)
				|| checkSecondaryDiagonal(gameBoard)
				||checkLine(gameBoard)
				||checkColumn(gameBoard)){
				victoria = 1;
			}
			
			// Testa se alguém já venceu o jogo
			
			if(victoria){
				if(!gameMode){
					if((round - 1) % 2  == 0){
						if(selection == 1){
							title("Player 1 (X) | Wins!", '-', 0);
						}
						else{
							title("CPU (X) | Wins!", '-', 0);
						}
					}
					else if((round - 1) % 2 != 0) {
						if(selection == 2){
							title("Player 2 (O) | Wins!", '-', 0);
						}
						else{
							title("CPU (O) | Wins!", '-', 0);
						}
					}
				}
				else{
					if((round - 1) % 2 == 0 ){
						title("Player 1 (X) | Wins!", '-', 0);
					}
					else{
						title("Player 2 (O) | Wins!", '-', 0);
					}
				}
				title("GAME ENDED!", '=', 0);
				break;
			}
			
			if(!gameMode){
				if((round % 2 == 0 && selection == 2) || (round % 2 != 0 && selection == 1)){
					cleanScreen();
					for(int change = 0; change != 1; change += 0){
						pcy = rand() % 3;
						pcx = rand() % 3;
						if(gameBoard[pcy][pcx] == ' '){
							if(selection == 1){
								gameBoard[pcy][pcx] = 'O';
							}
							else{
								gameBoard[pcy][pcx] = 'X';
							}
							change = 1;
							round += 1;
						}			
					}
					continue;
				}
			}
			
			// Torna jogável
			moveMenu();	
			for(int change = 0; change != 1;){
				char play = getch();
				if(play == 'p'){
					round = 14;
					change = 1;
					continue;
				}
				else if(play == 's' || play == 80){	
					if( pstySelector < 2){
						pstySelector += 1;
					}
					else{
						pstySelector = 0;
					}
					change = 1;
	
				}
				else if(play == 'w' || play == 72){
					if( pstySelector > 0){
						pstySelector -= 1;
					}
					else{
						pstySelector = 2;
					}
					change = 1;
				}
				else if(play == 'a' || play == 75){
					if( pstxSelector > 0){
						pstxSelector -= 1;
						change = 1;
					}
					else{
						pstxSelector = 2;
					}
					change = 1;
				}
				else if(play == 'd' || play == 77){
					if( pstxSelector < 2){
						pstxSelector += 1;
					}
					else{
						pstxSelector = 0;
					}
					change = 1;
				}
				else if(play == 32){
					if(gameBoard[pstySelector][pstxSelector] == ' '){
						if(round % 2 == 0 || round == 0){
							gameBoard[pstySelector][pstxSelector] = 'X';
						}
						else{
							gameBoard[pstySelector][pstxSelector] = 'O';
						}
					round ++;
					change = 1;
					pstxSelector = 1; 
					pstySelector = 1;
					}
				}
			}
			if(round == 14){
				printf("\n");
				title("EXITING...", '=', 0);
				continue;
			}
		 	if(round < 9){
				cleanScreen();
			}
			else{
				printf("\n");
				title("It was a draw!", '=', 0);
				round ++;
			}
		}	
		if(!exit){
			menu = 1;
			printf("> Press any key to restart.");
			getch();
			bufferCLR();
			cleanScreen();
		}
	}
}

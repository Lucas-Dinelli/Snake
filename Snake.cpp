#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>







using namespace std;










//---------------------------------------------------------------- Vari�veis globais e essenciais ------------------------------------------------------------------------------------

const int largura = 50;    // Determina qual a largura de tela do jogo.

const int altura = 28;     // Determina qual a altura de tela do jogo.

char simboloBorda = 176;  // Determina qual o caractere que ir� compor a tela do jogo.

char corpoSnake = 'o';    // Determina qual o caractere que vai representar os membros que formam o corpo da Snake.

int qtd = 1;             // Indica a quantidade de membros que est�o formando a Snake (equivalente ao tamanho da mesma).

char alimento = 208;          // Determina qual o caractere que vai representar o alimento que satisfaz a personagem. 

int linhaAlimento; int colunaAlimento;    // Vari�veis que guardam a posi��o em que o alimento se encontra na tela.

char esquerda = 'a'; char direita = 'd'; char cima = 'w'; char baixo = 's';   // Indicam quais os caracteres que, se apertados, mudar�o o movimento da Snake.

char teclaDeSaida = 27;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------















//----------------------------------------------- Vetores que guardam a posi��o em que cada membro da Snake se encontra na tela ------------------------------------------------------

int linhaSnake[100];

int colunaSnake[100];

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------














//--------------------------------------------------- Fun��o que direciona em que ponto da tela ser� apresentado o print -------------------------------------------------------------


void gotoxy(int LINHA, int COLUNA){
	
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = COLUNA;                                  
	dwPos.Y = LINHA;
	SetConsoleCursorPosition(hcon, dwPos);
	
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------















//--------------------------------------------------------------- Parte que cuida do ambiente de jogo --------------------------------------------------------------------------------


void desenharTelaDoJogo(){
	
	for(int i=0; i<largura; i++){  //(Parede de cima)
		
		cout<<simboloBorda;
		
	}
	
	
	cout<<endl;
	
	
	for(int i=0; i<altura; i++){
		
		for(int j=0; j<largura; j++){
			
			if((j==0) || (j==1)){ //(Parede da esquerda)    
			
				cout<<simboloBorda; 
				
			}
			else if((j==largura-2) || (j==largura-1)){  //(Parede da direita)
			
				cout<<simboloBorda;  
				
			}
			else{
				
				cout<<" ";  //(Vazio do meio)
				
			}
			
		}
		
		cout<<endl;
		
	}
	
	
	for(int i=0; i<largura; i++){  //(Parede de baixo)
		
		cout<<simboloBorda;
		
	}
	
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------















//------------------------------------------------ Fun��o respons�vel pela detec��o de colis�es entre certos elementos do jogo ---------------------------------------------------------

bool existeColisao(){
	
	
	bool isCollision = false;
	
	
	if((linhaSnake[0]==0) || (linhaSnake[0]==altura+1) || (colunaSnake[0]==1) || (colunaSnake[0]==largura-2)){
		
		isCollision = true;        // Bloco que detecta a colis�o da personagem com as bordas do ambiente de jogo.
		
	}
	
	
	
	for(int i=4; i<qtd; i++){
		
		if((linhaSnake[0]==linhaSnake[i]) && (colunaSnake[0]==colunaSnake[i])){
			
			isCollision = true;   // Bloco que detecta a colis�o do membro principal da personagem com outros membros que a comp�em.
			
		}
		
	}
	
	
	
	return(isCollision);
	
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------















//-------------------------------------------------------------- Parte respons�vel pelo alimento da Snake ----------------------------------------------------------------------------

int gerarNumeroAleatorio(int minimo, int maximo){
	
	int divisor = maximo-minimo+1;                                                       
	                                                                          
	srand(time(NULL));                           // Fun��o que gera um n�mero aleat�rio que esteja dentro do conjunto de n�meros passados como par�metro.
	
	return((rand() % divisor) + minimo);
	
}





void gerarAlimento(){
	
	if((linhaAlimento==linhaSnake[0]) && (colunaAlimento==colunaSnake[0])){
		
		linhaAlimento = gerarNumeroAleatorio(1, altura);
		
		colunaAlimento = gerarNumeroAleatorio(2, largura-3);
		
		qtd = qtd+1;
		
	}
	
	gotoxy(linhaAlimento, colunaAlimento);
	cout<<alimento;
	
}




//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------















//-------------------------------------------------------------------- Parte que cuida da Snake --------------------------------------------------------------------------------------

void moverPara(char sentido){
	
	
	if(sentido==esquerda){
		
		colunaSnake[0] = colunaSnake[0]-1;
		
	}
	else if(sentido==direita){
		
		colunaSnake[0] = colunaSnake[0]+1;            //Fun��o que atualiza a posi��o do membro principal da Snake de acordo com o sentido escolhido e permitido.
		
	}
	else if(sentido==cima){
		
		linhaSnake[0] = linhaSnake[0]-1;
		
	}
	else if(sentido==baixo){
		
		linhaSnake[0] = linhaSnake[0]+1;
		
	}
	
}








char direcao(char sentido){
	
	
	if(sentido==esquerda || sentido==direita){
		
		return('h');     //Dire��o horizontal (h)
		
	}
	else{                                             //Verifica em qual dire��o a personagem est� se movimentando.                          
		
		return('v');    //Dire��o vertical (v)
		
	}
	
	
}







char mudarSentido(char sentido, char tecla){
	
	
	char direcaoAtual = direcao(sentido);
	
		
	if((direcaoAtual!='h') && (tecla==esquerda || tecla==direita)){
			
		sentido = tecla;
			
	}
	else if((direcaoAtual!='v') && (tecla==cima || tecla==baixo)){
			
		sentido = tecla;
			
	}
		
	return(sentido);
}








void atualizarPosicoes(int posicao[]){ 
	
	int aux1 = posicao[0];
	
	int aux2;
	
	for(int i=1; i<=qtd; i++){      //Fun��o que atualiza o valor da posi��o de cada membro restante da Snake.
		
		aux2 = posicao[i];
		
		posicao[i] = aux1;
		
		aux1 = aux2;
		
	}
	
}






void apagarMembros(){
	
	atualizarPosicoes(linhaSnake);
	atualizarPosicoes(colunaSnake);
	gotoxy(linhaSnake[qtd], colunaSnake[qtd]);
	
	if(!(linhaSnake[qtd]==0 && colunaSnake[qtd]==0)){
		
		cout<<" ";
		
	}
	
}








void desenharSnake(char sentido){
	
	moverPara(sentido);
	gotoxy(linhaSnake[0], colunaSnake[0]);
	cout<<corpoSnake;
	
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------















//------------------------------------------------------ Fun��o que controla v�rias partes e as junta para compor o jogo --------------------------------------------------------------

void controleGeral(){  

	
	char sentido = direita;
	
	
	linhaSnake[0] = 10;
	
	colunaSnake[0] = 15;
	
	
	linhaAlimento = linhaSnake[0];
	
	colunaAlimento = colunaSnake[0];
	
	
	char tecla;
	
	bool gameOver = false;
	
		
	
	while((tecla!=teclaDeSaida) && (gameOver==false)){
		
		apagarMembros();
		
		gerarAlimento();
		
		desenharSnake(sentido);
		
		gameOver = existeColisao();
		
		gotoxy(13, largura+25);
		cout<<"Score = "<<qtd-2;
		
		if(kbhit()){
			
			tecla = getch();
			
			sentido = mudarSentido(sentido, tecla);
			
		}
		
		Sleep(120);
		
	}
	
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------





bool instruir(){
	
	char tecla;
	
	gotoxy(2, 55);
	cout<<"SNAKE";
	
	
	gotoxy(8, 43);
	cout<<". Tecla "<< cima <<" (move para cima);";
	
	gotoxy(12, 43);
	cout<<". Tecla "<< baixo <<" (move para baixo);";
	
	gotoxy(16, 43);
	cout<<". Tecla "<< esquerda <<" (move para esquerda);";
	
	gotoxy(20, 43);
	cout<<". Tecla "<< direita <<" (move para direita);";
	
	
	gotoxy(27, 89);
	cout<<"... Aperte Esc para sair <=";
	
	gotoxy(27, 2);
	cout<<"=> Aperte Enter para iniciar...";
	
	
	while(tecla!=13 && tecla!=teclaDeSaida){
		if(kbhit()){
			tecla = getch();
		}
	}
	
	if(tecla==13){
		system("cls");
		return(true);
	}
	else{
		return(false);
	}
	
}









int main(){
	
	system("color 0F");
	
	bool isToPlay = instruir();
	
	while(isToPlay){
		
		desenharTelaDoJogo();	
		
		controleGeral();
		
		gotoxy(20, largura+21);
		cout<<"Deseja reiniciar(S/N)?";
		
		char tecla;
		
		while(tecla!='s' && tecla!='S' && tecla!='n' && tecla!='N'){
			if(kbhit()){
				tecla = getch();
			}
		}
		
		if(tecla=='s' || tecla=='S'){
			system("cls");
			qtd = 1;
			tecla = '*';
		}
		else{
			isToPlay = false;
		}
	}
	
	
	return(0);
}







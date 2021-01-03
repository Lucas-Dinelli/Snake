#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>







using namespace std;










//---------------------------------------------------------------- Variáveis globais e essenciais ------------------------------------------------------------------------------------

const int largura = 50;    // Determina qual a largura de tela do jogo.

const int altura = 28;     // Determina qual a altura de tela do jogo.

char simboloBorda = 176;  // Determina qual o caractere que irá compor a tela do jogo.

char corpoSnake = 'o';    // Determina qual o caractere que vai representar os membros que formam o corpo da Snake.

int qtd = 1;             // Indica a quantidade de membros que estão formando a Snake (equivalente ao tamanho da mesma).

char alimento = 208;          // Determina qual o caractere que vai representar o alimento que satisfaz a personagem. 

int linhaAlimento; int colunaAlimento;    // Variáveis que guardam a posição em que o alimento se encontra na tela.

char esquerda = 'a'; char direita = 'd'; char cima = 'w'; char baixo = 's';   // Indicam quais os caracteres que, se apertados, mudarão o movimento da Snake.

char teclaDeSaida = 27;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------















//----------------------------------------------- Vetores que guardam a posição em que cada membro da Snake se encontra na tela ------------------------------------------------------

int linhaSnake[100];

int colunaSnake[100];

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------














//--------------------------------------------------- Função que direciona em que ponto da tela será apresentado o print -------------------------------------------------------------


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















//------------------------------------------------ Função responsável pela detecção de colisões entre certos elementos do jogo ---------------------------------------------------------

bool existeColisao(){
	
	
	bool isCollision = false;
	
	
	if((linhaSnake[0]==0) || (linhaSnake[0]==altura+1) || (colunaSnake[0]==1) || (colunaSnake[0]==largura-2)){
		
		isCollision = true;        // Bloco que detecta a colisão da personagem com as bordas do ambiente de jogo.
		
	}
	
	
	
	for(int i=4; i<qtd; i++){
		
		if((linhaSnake[0]==linhaSnake[i]) && (colunaSnake[0]==colunaSnake[i])){
			
			isCollision = true;   // Bloco que detecta a colisão do membro principal da personagem com outros membros que a compõem.
			
		}
		
	}
	
	
	
	return(isCollision);
	
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------















//-------------------------------------------------------------- Parte responsável pelo alimento da Snake ----------------------------------------------------------------------------

int gerarNumeroAleatorio(int minimo, int maximo){
	
	int divisor = maximo-minimo+1;                                                       
	                                                                          
	srand(time(NULL));                           // Função que gera um número aleatório que esteja dentro do conjunto de números passados como parâmetro.
	
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
		
		colunaSnake[0] = colunaSnake[0]+1;            //Função que atualiza a posição do membro principal da Snake de acordo com o sentido escolhido e permitido.
		
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
		
		return('h');     //Direção horizontal (h)
		
	}
	else{                                             //Verifica em qual direção a personagem está se movimentando.                          
		
		return('v');    //Direção vertical (v)
		
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
	
	for(int i=1; i<=qtd; i++){      //Função que atualiza o valor da posição de cada membro restante da Snake.
		
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















//------------------------------------------------------ Função que controla várias partes e as junta para compor o jogo --------------------------------------------------------------

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







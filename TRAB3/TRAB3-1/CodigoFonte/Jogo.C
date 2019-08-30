/***************************************************************************
*  $MCI Modulo de implementacao: Modulo Jogo
*
*  Arquivo gerado:              Jogo.c
*  Letras identificadoras:      JOG
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: 
*			DF - Daniel Machado Carneiro Faller
*			MS - Miguel Sanseverino
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes      
*       1.00   DF   02/05/2019	 Implementação do loop do jogo
*		1.01   MS	30/05/2019	 Implementação da exibição do tabuleiro
*
***************************************************************************/

/***********************************************************************
*
*  $TC Tipo de dados: JOG descritor do turno
*
*  $ED Descrição do tipo
*     Descreve uma estrutura de turno para alterar a rodada dos jogadores.
*
***********************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "Tabuleiro.h"
#include "Dado.h"
#include "DadoPontos.h"
#include "Peca.H"
#include "PecaFinalizada.h"
#include "PecasCapturadas.h"

typedef enum{

		JOG_CondRetOK				= 0,
			/* Concluiu corretamente */
		JOG_CondRetFaltouMemoria	= 1,

		JOG_CondRetTABNExiste		= 2,
			/* Tabuleiro não foi previamente criado */
		JOG_CondRetNaoEPecaCapturada= 3,

		JOG_CondRetNaoEPecaFinalizada= 4,

		JOG_CondRetInputInvalido	= 5,

		JOG_CondRetPlayerBlocked    = 6,
		
		JOG_CondRetSaveNaoExiste    = 7,

		JOG_CondRetDesistencia      = 8,

		JOG_CondRetFinalizarPartida = 9


	} JOG_tpCondRet;

/**********************************************************************/
	typedef struct turno Turno;

/**********************************************************************/

 struct turno {

         char cor ;
               /* cor do player atual */
         int mult;
               /* sentido a mover as pecas no tabuleiro*/
		 int * dados;
			   /* dados tirados */
 };
/*****  Dados encapsulados no módulo  *****/
	
	static Turno rodadaAtual = {'b',-1,NULL}; 

/***** Protótipos das funções encapuladas no módulo *****/	

	static JOG_tpCondRet JOG_IniciaJogo( );
	
	static JOG_tpCondRet JOG_MoverPeca(int dado, int origem);

	static JOG_tpCondRet JOG_AvaliaMoverPeca();
	
	static JOG_tpCondRet JOG_MudarTurno();
	
	static JOG_tpCondRet JOG_JogarDados();
	
	static JOG_tpCondRet JOG_AumentarAposta();
	
	static JOG_tpCondRet JOG_SalvaJogo(char ** vetTab, char * nome);
	
	static JOG_tpCondRet JOG_CarregaJogo( char * nome);


/*****  Código das funções exportadas pelo módulo  *****/
/***************************************************************************
*
*  Função: JOG Inicia jogo
*  ****/
JOG_tpCondRet JOG_IniciaJogo(){
	
	/*Inicializadas ao ínicio da partida*/
	char * nomeSave = (char*)malloc(sizeof(char));
	int player1Pontos = 0, player2Pontos = 0,partidas = 0;
	/*Entre loops*/
	int dobradinha = 0;
	int mudarTurno = 1, *qtdPlayer1, *qtdPlayer2;
	int vitoriaPontos;
	int contadorPartidas = 0;
	int valorRodada = 0;
	char ** vetTab  = (char**)malloc(24 * sizeof(char*));
	/*Interação com o player */
	JOG_tpCondRet leitura;
	PEC_tpPeca ** peca = (PEC_tpPeca**)malloc(sizeof(PEC_tpPeca*));
	char * opcaoJogador= (char*) malloc(sizeof(char));
	char * tempCor = (char*)malloc(sizeof(char));
	
	char inputsEsperados[6];
	
	
	
	int qtdElems;
	
	qtdPlayer1 = (int*)malloc(sizeof(int));
	qtdPlayer2 = (int*)malloc(sizeof(int));

	
	
	while(1){


		printf("Carregar jogo[C]\n");
		printf("Novo jogo[N]\n");
		strcpy(inputsEsperados,"CcNn");
		qtdElems = 4;
		while(JOG_LeInput(opcaoJogador,'c',inputsEsperados,&qtdElems) == JOG_CondRetInputInvalido);
		if(*opcaoJogador ==	'C' || *opcaoJogador ==	'c'){
			printf("\n Qual o nome do save a ser lido \n");	
			scanf(" %s",nomeSave);
			JOG_CarregaJogo(nomeSave);
			TAB_ExibeTabuleiro(vetTab);
			break;
	
		}/* if */
		if(*opcaoJogador ==	'N' || *opcaoJogador == 'n'){
			printf("Quantas partidas serao jogadas \n");
			strcpy(inputsEsperados,"CcNn");
			while(JOG_LeInput(opcaoJogador,'c',inputsEsperados,0) == JOG_CondRetInputInvalido);
			*opcaoJogador -= 48;
			partidas = (int)(*opcaoJogador) ;
		
			JOG_JogarDados();
			PECF_CriarPecaFinalizada();
			PECC_CriarPecaCapturada();
			
			TAB_CriaTabuleiro();
			DAP_CriaDadoPontos();
			break;
		}/* if */
		printf("Comando invalido \n");
	}
	PECF_ObterQuantidadeLisPF('b',qtdPlayer1);
	PECF_ObterQuantidadeLisPF('p',qtdPlayer2);


	while(contadorPartidas < partidas){
		int rodada = 0;
		printf("================================== PARTIDA %d ================================== \n",contadorPartidas);
		
		
		PECF_ResetarPecaFinalizada();
		PECF_CriarPecaFinalizada();

		PECC_ResetarPecaCapturada();
		PECC_CriarPecaCapturada();
		
		TAB_CriaTabuleiro();

		DAP_DestruirDadoPontos();
		DAP_CriaDadoPontos();

		while(*qtdPlayer1 != 15 && *qtdPlayer2 != 15){
			PECF_ObterQuantidadeLisPF('b',qtdPlayer1);
			PECF_ObterQuantidadeLisPF('p',qtdPlayer2);

			DAP_ObterValorPartida(&valorRodada);
			printf("=============================== Rodada %d  Valor:%d ================================ \n",rodada,valorRodada);
			printf("Jogador B tem %d pontos \n", player1Pontos);
			printf("Jogador P tem %d pontos \n", player2Pontos);
			mudarTurno = 1;
			TAB_ExibeTabuleiro(vetTab);
			JOG_ImprimeTabuleiro(vetTab); 
		
			if(!dobradinha){
				JOG_JogarDados();
			}
		
			if((leitura = JOG_AvaliaMoverPeca() )!= JOG_CondRetPlayerBlocked && rodadaAtual.dados[0] == rodadaAtual.dados[1] && !dobradinha){
				mudarTurno = 0;
				dobradinha = 1;
			}/* if */
			else{
				dobradinha = 0;
			}/* else */
			if(leitura == JOG_CondRetDesistencia){
				break;
			}/* if */
			if(leitura == JOG_CondRetFinalizarPartida){
				return JOG_CondRetFinalizarPartida;
			}/* if */
			PECF_ObterQuantidadeLisPF('b',qtdPlayer1);
			PECF_ObterQuantidadeLisPF('p',qtdPlayer2);
			if(*qtdPlayer1 == 15 && *qtdPlayer2 == 15){
				break;
			}/* if */
							
			if(mudarTurno){
				JOG_MudarTurno();
				printf("Passou o turno , %c \n", rodadaAtual.cor);
			}/* if */
			
			rodada++;
		}/* while */
		DAP_ObterValorPartida(&vitoriaPontos);
		vitoriaPontos = vitoriaPontos/2;
		if(vitoriaPontos == 0)
			vitoriaPontos = 1;
		if(rodadaAtual.cor == 'b'){
			if(*qtdPlayer2 == 0) player1Pontos += (vitoriaPontos) * 2;
			else player1Pontos += vitoriaPontos;
		}/* if */
		if(rodadaAtual.cor == 'p'){
			if(*qtdPlayer1 == 0) player2Pontos += (vitoriaPontos) * 2;
			else player2Pontos += vitoriaPontos;
		}/* if */
		contadorPartidas++;
	
	}/* while */

	if( player1Pontos > player2Pontos){
		printf("PLAYER 1 ganhou com %d \n ", player1Pontos);
	}/* if */
	else if( player1Pontos > player2Pontos){
		printf("PLAYER 1 ganhou com %d \n ", player1Pontos);
	}/* if */
	else{
		printf(" EMPATE \n ");
	}/* else */


	free(vetTab);
	free(tempCor);
	free(nomeSave);
	free(opcaoJogador);
	free(qtdPlayer1);
	free(qtdPlayer2);
	return JOG_CondRetOK;

}/* Fim função: JOG Inicia Jogo   */


/***************************************************************************
*
*  Função: JOG Mover Peca
*  $ED Descrição da função
*		Interage com o usuário através de mensagens para saber a posição para qual
*		a peça sera movida e a move
*	
*  $EA: Assertivas de entrada
*		O tabuleiro precisa existir
*		Lista de peças finalizadas precisa existir
*		Lista de peças capturadas precisa existir
*/
JOG_tpCondRet JOG_AvaliaMoverPeca(){
	TAB_tpCondRet estado;
	int casa;
	char leitorCasa;
	char * dado;
	int jogadaValida = 0;
	int * qtdPecasCapturadas = (int*)malloc(sizeof(int));
	char inputsEsperados[6];
	char ** vetTabuleiro;
	JOG_tpCondRet leitura;
	int qtdElems = 0;
	PEC_tpPeca ** peca = (PEC_tpPeca**)malloc(sizeof(PEC_tpPeca*));
	if(TAB_ExisteMovimento(rodadaAtual.cor,rodadaAtual.dados,rodadaAtual.mult) == TAB_CondRetPosInvalida){
		return JOG_CondRetPlayerBlocked;
	}/* if */
	dado = (char*)malloc(sizeof(char));
	vetTabuleiro = (char**)malloc(24 * sizeof(char*));
	
	do{
		PECC_ObterQuantidadeLisPC ( rodadaAtual.cor , qtdPecasCapturadas ) ;
		if(*qtdPecasCapturadas != 0){
			printf("Adicionando peça capturada de volta ao jogo \n");

			if(rodadaAtual.cor == 'p'){
				casa = 0; 
			}
			if(rodadaAtual.cor == 'b'){
				casa = 23;
			}
			printf("Escolha quais dos dados sera utilizado \n  DADO 1 : %d | DADO 2 : %d \n", rodadaAtual.dados[0], rodadaAtual.dados[1]);
			while((leitura= JOG_LeInput(dado,'c',inputsEsperados,0)) == JOG_CondRetInputInvalido);
			if(leitura == JOG_CondRetDesistencia){
				return JOG_CondRetDesistencia;
			}/* if */
			if(leitura == JOG_CondRetFinalizarPartida){
				return JOG_CondRetFinalizarPartida;
			}/* if */
			if(AdicionaCasaN(casa + (int)(*dado) -48,1,rodadaAtual.cor)!= TAB_CondRetPosInvalida){
				PECC_RemoverPecaCapturada(rodadaAtual.cor);
			}
		}
		if( *qtdPecasCapturadas == 0){
			

			jogadaValida = 1;
			printf("Dado 1: %d  Dado 2: %d \n",rodadaAtual.dados[0], rodadaAtual.dados[1]);
			printf("Escolha uma casa em que ha peca\n");
			while((leitura= JOG_LeInput(&leitorCasa,'d',inputsEsperados,&qtdElems)) == JOG_CondRetInputInvalido);
			if(leitura == JOG_CondRetDesistencia){
				return JOG_CondRetDesistencia;
			}
			if(leitura == JOG_CondRetFinalizarPartida){
				return JOG_CondRetFinalizarPartida;
			}
			casa = qtdElems;
			printf(" \n CASA:%d \n", casa);
			if(casa >= 0 && casa <= 23){
			
				printf("Escolha quais dos dados sera utilizado \n  DADO 1 : %d | DADO 2 : %d \n", rodadaAtual.dados[0], rodadaAtual.dados[1]);
				while((leitura= JOG_LeInput(dado,'c',inputsEsperados,0)) == JOG_CondRetInputInvalido);
				if(leitura == JOG_CondRetDesistencia){
					return JOG_CondRetDesistencia;
				}/* if */
				if(leitura == JOG_CondRetFinalizarPartida){
					return JOG_CondRetFinalizarPartida;
				}/* if */
			
			}/* if */
			else{
				jogadaValida = 0;
			}/* else */
			if( jogadaValida ){
				if (JOG_MoverPeca((int)(*dado) - 48,casa) == JOG_CondRetInputInvalido){
					jogadaValida = 0;
				}/* if */
			}/* if */ 
		}
	}while(!jogadaValida);
		
	TAB_ExibeTabuleiro(vetTabuleiro);
	JOG_ImprimeTabuleiro(vetTabuleiro);

	do{
		jogadaValida = 1;
		if((int)*dado - 48== 1){
			printf("\nDado 2: %d sendo utilizado \n",rodadaAtual.dados[1]);
			*dado = (char)2;
		}/* if */
		else{
			printf("\nDado 1: %d sendo utilizado \n",rodadaAtual.dados[0]);
			*dado = (char)1;
		}/* else */
		PECC_ObterQuantidadeLisPC ( rodadaAtual.cor , qtdPecasCapturadas ) ;
		if(*qtdPecasCapturadas != 0){
			if(AdicionaCasaN(casa + (int)(*dado) -48,1,rodadaAtual.cor)!= TAB_CondRetPosInvalida){
				PECC_RemoverPecaCapturada(rodadaAtual.cor);
			}/* if */
		}/* if */
		if( *qtdPecasCapturadas == 0){
			printf("Escolha uma casa em que ha peca\n");
			while((leitura= JOG_LeInput(&leitorCasa,'d',inputsEsperados,&qtdElems)) == JOG_CondRetInputInvalido);
			if(leitura == JOG_CondRetDesistencia){
				return JOG_CondRetDesistencia;
			}/* if */
			if(leitura == JOG_CondRetFinalizarPartida){
				return JOG_CondRetFinalizarPartida;
			}/* if */
			casa = qtdElems;
			if ( casa < 0 || casa > 23){
				jogadaValida = 0;
			}/* if */
			
			if(jogadaValida){
				printf(" \n CASA:%d \n", casa);
				if (JOG_MoverPeca((int)(*dado),casa) == JOG_CondRetInputInvalido){
					jogadaValida = 0;
				}/* if */
			}/* if */
			else{
				printf("Casa invalida \n");
			}/* else */
		}
	}while(!jogadaValida);
	
	free(vetTabuleiro);
	free(qtdPecasCapturadas);
	free(dado);
	free(peca);
	return JOG_CondRetOK;
}/* Fim função: JOG Mover Peca*/
/*
* $AS Assertivas de Saída
*		Peça devidamente movida
*  
 Fim Assertiva de Saida JOG_MoverPeca

**************************************************************************************************/
JOG_tpCondRet JOG_MoverPeca(int dado, int origem){
		PEC_tpPeca ** peca;
		TAB_tpCondRet estado;
		int * qtdPecasCapturadasP = (int*)malloc(sizeof(int));
		int * qtdPecasCapturadasB = (int*)malloc(sizeof(int));
		int * pecasJaFinalizadas = (int*)malloc(2 * sizeof(int));
		peca = (PEC_tpPeca**)malloc(sizeof(PEC_tpPeca*));
		
		PECF_ObterQuantidadeLisPF('b',&(*pecasJaFinalizadas));
		PECF_ObterQuantidadeLisPF('p',&(*(pecasJaFinalizadas + 1)));
		estado = TAB_MoverPeca(rodadaAtual.cor,origem, origem + rodadaAtual.dados[dado -1] * rodadaAtual.mult, peca, pecasJaFinalizadas);
			
		if (estado == TAB_CondRetPecaCapturada){
			printf("Peca capturada \n");
			PECC_AdicionaPecaCapturada(*peca);
			PECC_ObterQuantidadeLisPC ( 'b' , qtdPecasCapturadasB ) ;
			PECC_ObterQuantidadeLisPC ( 'p' , qtdPecasCapturadasP ) ;
			printf("Pecas capturadas iguais a p: %d \n",*qtdPecasCapturadasP);
			printf("Pecas capturadas iguais a b: %d \n",*qtdPecasCapturadasB);
			return JOG_CondRetOK;
		}/* if */
			
		if (estado == TAB_CondRetPecaFinalizada){
			printf("Peca finalizada \n");
			PECF_AdicionaPecaFinalizada(*peca);
			return JOG_CondRetOK;
		}/* if */

		if( estado == TAB_CondRetOK){
			printf("Movimento Valido \n");
			return JOG_CondRetOK;
		}	
	return JOG_CondRetInputInvalido;
}
/***************************************************************************
*
*  Função: JOG Jogar Dados
*  $EA: Assertivas de entrada
*		Variável rodadaAtual inicializada
*  ****/
JOG_tpCondRet JOG_JogarDados(){
	int * dados;
	DAD_tpCondRet estado;
	dados = (int *)malloc(2 * sizeof(int));
	
	if(dados == NULL){
		return JOG_CondRetFaltouMemoria;
	}/* if */
	estado = DAD_RolarDados(dados);
	if( estado == DAD_CondRetOK){
		rodadaAtual.dados = dados;
	}/* if */
	return JOG_CondRetOK;
}/* Fim função: JOG Jogar Dados */

/*
* $AS Assertivas de Saída
*		Dados salvos na variável rodadaAtual
*  
 Fim Assertiva de Saida JOG_MoverPeca

**************************************************************************************************/
/***************************************************************************
*
*  Função: JOG Mudar Turno
*  ****/
JOG_tpCondRet JOG_MudarTurno(){
	JOG_tpCondRet estado;

	if( rodadaAtual.cor == 'p'){
		rodadaAtual.cor = 'b';
	
	}/* if */
	else if( rodadaAtual.cor == 'b'){
		rodadaAtual.cor = 'p';	
	}/* if */
	
	if( rodadaAtual.mult == 1){
		rodadaAtual.mult = -1;	
	}/* if */
	else if( rodadaAtual.mult == -1){
		rodadaAtual.mult = 1;	
	}/* if */

	estado = JOG_JogarDados();
	return estado;

}/* Fim função: JOG Mudar Turno */

/***************************************************************************
*
*  Função: JOG Imprime Tabuleiro 
*  ****/
JOG_tpCondRet JOG_ImprimeTabuleiro (char ** pTab) {




	int c = 1;
	int casa, linha, linha2;
	int count = 0; // Numero de linhas printadas
	char letra = 'a';
	int *qtdPlayer1, *qtdPlayer2;
	int *qtdPlayer1Cap, *qtdPlayer2Cap;
	int valorRodada;

	qtdPlayer1	  = (int*)malloc(sizeof(int));
	qtdPlayer2	  = (int*)malloc(sizeof(int));
	qtdPlayer1Cap = (int*)malloc(sizeof(int));
	qtdPlayer2Cap = (int*)malloc(sizeof(int));

	PECF_ObterQuantidadeLisPF('b',qtdPlayer1);
	PECF_ObterQuantidadeLisPF('p',qtdPlayer2);
	PECC_ObterQuantidadeLisPC('b',qtdPlayer1Cap);
	PECC_ObterQuantidadeLisPC('p',qtdPlayer2Cap);
	

	
	



	if (pTab == NULL)
		return JOG_CondRetTABNExiste;
	printf("  ");

	for ( c = 12; c < 24; c++) {
		printf("  %d", c);
	}

	printf("\n");

	casa = 12;
	linha = 0;
	linha2 = 4;

	while (count < 11 )  { //Em cada linha

		if (count < 5)  { //Parte de cima

			printf("%c ", letra);

			while (casa < 24) {


				printf(" |%c|", pTab[casa][linha]);
				casa++;
	
			}
			casa = 12;
			count++;
			letra++;
			linha++;
			printf("\n");
			}
		else if (count == 5) { 
			printf("   -----------------------------------------------\n");
			count++;
		}
		else { //Parte de baixo

			printf("%c ", letra);
			casa = 11;

			while (casa >= 0) {
				printf(" |%c|", pTab[casa][linha2]);
				casa--;
			}
			casa = 11;
			letra++;
			linha2--;
			count++;
			printf("\n");
		}


	}
	printf("  ");
	for ( c = 11; c >= 0; c-- ) {
		if( c < 10){
			printf("  %d ", c);
		}
		else{
			printf("  %d", c);
		}
	}
	printf("\nJogador B tem pecas %d na barra e  %d pecas finalizadas \n",*qtdPlayer1Cap,*qtdPlayer1);
	printf("Jogador P tem pecas %d na barra e  %d pecas finalizadas \n",*qtdPlayer2Cap,*qtdPlayer2);
	printf("\n Vez do jogador %c \n", rodadaAtual.cor);

	printf("A - AumentarAposta\n");
	printf("F - Sair\n");
	printf("S/E - Salvar\n");


	free(qtdPlayer1Cap);
	free(qtdPlayer2Cap);
	free(qtdPlayer1);
	free(qtdPlayer2);
	return JOG_CondRetOK;
}/* Fim função: JOG Imprime Tabuleiro */

/***************************************************************************
*
*  Função: JOG Aumentar Aposta
*  ****/
JOG_tpCondRet JOG_AumentarAposta(){

	char * opcaoJogador = (char*)malloc(sizeof(char));
	char opcaoJogador2;
	char aceitar;
	DAP_tpCondRet estado;
	printf("Deseja aumentar o dado de apostas \n");
	scanf(" %c",opcaoJogador);

	if(*opcaoJogador == 'S' || *opcaoJogador == 's' ){

		estado = DAP_DobrarPontuacao( rodadaAtual.cor);
		if(estado == DAP_CondRetNaoPodeDobrar){
			printf("Jogador: %c já dobrou o valor anteriormente movimento Inváliido \n",rodadaAtual.cor);
		}/* if */
		else if(estado == DAP_CondRetOK){
			printf("Jogador: %c quer dobrar o valor da  partida \n",rodadaAtual.cor);
			if(rodadaAtual.cor == 'p'){
				opcaoJogador2 = 'b';
			}/* if */
			else{
				opcaoJogador2 = 'p';
			}/* else */
			printf("Aceitar a dobra jogador %c \n",opcaoJogador2);
			printf("S - Sim \n");
			printf("N - Não \n");
			scanf(" %c",&aceitar);
			while(aceitar != 'S' && aceitar != 's'&& aceitar != 'n' && aceitar != 'N'){
				printf("S - Sim \n");
				printf("N - Não \n");
				printf("Aceitar a dobra jogador %c \n",opcaoJogador2);
				scanf(" %c",&aceitar);
			}
			if(aceitar == 'S' || aceitar == 's'){
				return JOG_CondRetOK;
			}/* if */
			else{
				return JOG_CondRetDesistencia;
			}/* else */
		}/* else if */
		else
			printf("DAP  retornou  :%d \n",(int)(estado));
	}/* if */
	free(opcaoJogador);
	return JOG_CondRetOK;

}/* Fim função: JOG Aumentar Aposta */


/***************************************************************************
*
*  Função: JOG Salva Jogo
*  ****/
JOG_tpCondRet JOG_SalvaJogo(char**vetTab, char * nome) {

	int casa, linha, numPeca;
	char corPeca;
	FILE * save;

	PECF_tpPecaF *pPecaF;
	PECC_tpPecaC *pPecaC;

	PECC_tpCondRet estadoPC;
	PECF_tpCondRet estadoPF;
	int *nPecaBF, *nPecaPF;
	int *nPecaBC, *nPecaPC;
	
	pPecaC = (PECC_tpPecaC*)malloc(sizeof(PECC_tpPecaC*));
	pPecaF = (PECF_tpPecaF*)malloc(sizeof(PECF_tpPecaF*));

	nPecaBF = (int*)malloc(2*sizeof(int));
	nPecaBC = (int*)malloc(2*sizeof(int));
	nPecaPF = (int*)malloc(2*sizeof(int));
	nPecaPC = (int*)malloc(2*sizeof(int));

	save = fopen(nome, "w");

	PECF_ObterQuantidadeLisPF('p', nPecaPF);
	estadoPF = PECF_ObterQuantidadeLisPF('b', nPecaBF);

	PECC_ObterQuantidadeLisPC('p', nPecaPC);
	estadoPC = PECC_ObterQuantidadeLisPC('b', nPecaBC);

	fprintf(save, "tabuleiro {\n");

	casa = 0;
	numPeca = 0;
	while (casa < 24) {
		linha = 0;
		numPeca = 0;

		if ( ( vetTab[casa][linha] == 'p' ) || (vetTab[casa][linha] == 'b') ) {
			corPeca = vetTab[casa][linha];

			while( ( vetTab[casa][linha] == 'p' ) || (vetTab[casa][linha] == 'b') ){
				numPeca ++;
				linha++;
			}/* while */

			fprintf(save, "%d ",casa);
			fprintf(save, "%d ",numPeca);
			fprintf(save, "%c\n", corPeca);
		}/* if */
		casa++;
	}/* whiile */
	fprintf(save,"}\nfinalizada {\n");


	if (pPecaF != NULL) {
		fprintf(save, "p %d\nb %d\n", *nPecaPF, *nPecaBF);
	}/* if */
	else{
		return JOG_CondRetNaoEPecaFinalizada;
	}/* else */

	fprintf(save,"}\ncapturada {\n");

	if (pPecaC != NULL) {
		fprintf(save, "p %d\nb %d\n}\n", *nPecaPC, *nPecaBF);
	}/* if */

	else{
		return JOG_CondRetNaoEPecaCapturada;
	}/* else */

	free(nPecaBC);
	free(nPecaBF);
	free(nPecaPC);
	free(nPecaPF);
	fclose(save);

	return JOG_CondRetOK;
}/* Fim função JOG Salva Jogo */


/***************************************************************************
*
*  Função: JOG Carrega Jogo 
*  ****/

JOG_tpCondRet JOG_CarregaJogo( char * nome) {
	int c;
	FILE *save;
	char *corPeca;

	PEC_tpPeca **pPeca;

	corPeca = (char*)malloc(sizeof(char*));
	pPeca = (PEC_tpPeca**)malloc(sizeof(PEC_tpPeca*));

	/*if (nome[sizeof(nome) - 4] != '.') {
		nome = strcat(nome, ".txt");
	}*/

	if (fopen(nome, "r") == NULL) {
		return JOG_CondRetSaveNaoExiste;
	}
	save = fopen(nome, "r");

	while ((c = fgetc(save)) != EOF) {

		if (c == 't') {
			int	numPeca, casa, i;

			 if (fscanf(save, "abuleiro {\n%d %d %c", &casa, &numPeca, corPeca) == 3) {
				 TAB_CriaTabuleiroVazio();
				 AdicionaCasaN(casa, numPeca, *corPeca);
			 }/* if */

		}/* if */

		else if(c == 'f') {
			int numPecaF, i;
			char corPecaF;
			i = 0;
			if (fscanf(save, "inalizada {\n%c %d", &corPecaF, &numPecaF) == 2) {
				PECF_CriarPecaFinalizada();
				while (i <= numPecaF) {
					PEC_CriarPeca(pPeca, corPecaF);
					PECF_AdicionaPecaFinalizada(*pPeca);
					i++;
				}/* while */
			}/* if */
		}/* else if */

		else if(c== 'c') {
			int numPecaC, i;
			char corPecaC;

			if (fscanf(save, "capturada {\n%c %d", &corPecaC, &numPecaC) == 2) {
				PECF_CriarPecaFinalizada();
				while (i <= numPecaC) {
					PEC_CriarPeca(pPeca, corPecaC);
					PECC_AdicionaPecaCapturada(*pPeca);
					i++;
				}/* while */
			}/* if */

		}/* else if */

	}

	fclose(save);

	return JOG_CondRetOK;

}/* Fim função JOG Carrega Jogo */

JOG_tpCondRet JOG_LeInput(char * opcaoJogador,char tipo,char * elemsEsperados,int * qtdElems){
	//C para carregar o jogo
	//N para novo jogo
	//A para aumentas apostas
	//Resto
	char inputsPadrao[] = {'A','a','S','s','E','e','f','F'};
	int i;
	int leituraSucedida = 0;
	char text[] = {' ','%',tipo};
	char ** vetTab = (char**)malloc(24 * sizeof(char*));
	char  nome[] = {'s','a','v','e','\0'};
	int leitor;
	if(tipo == 'd'){
		printf("Deseja realizar alguma operacao especial\n");
		scanf(" %c",opcaoJogador);
		if(*opcaoJogador == 'S' || *opcaoJogador == 's'){
			printf("Qual?\n");
			scanf(" %c",opcaoJogador);
		}else{
			printf("Digite o inteiro desejado\n");
			scanf(" %d",&leitor);
			*qtdElems = leitor;
			return JOG_CondRetOK;
		}

	}
	else{
		scanf(text,opcaoJogador);
	}
	if( qtdElems == 0 ){
		if( *opcaoJogador == 'A' || *opcaoJogador == 'a'){
			if(JOG_AumentarAposta() == JOG_CondRetDesistencia){
				return JOG_CondRetDesistencia;
			}/* if */
			printf("Forneça o que foi pedido inicialmente\n");
			return JOG_LeInput(opcaoJogador,tipo,elemsEsperados,qtdElems);
		}/* if */
		if( *opcaoJogador == 'f' || *opcaoJogador == 'F' ){
			return JOG_CondRetFinalizarPartida;
		}/* if */
		if( *opcaoJogador == 'S' || *opcaoJogador == 's'|| *opcaoJogador == 'E' || *opcaoJogador == 'e'){
			TAB_ExibeTabuleiro(vetTab);
			JOG_SalvaJogo(vetTab,nome);
			return JOG_CondRetFinalizarPartida;
		}/* if */

		return JOG_CondRetOK;
	}
	for (i = 0; i < *qtdElems; i++){
		if(elemsEsperados[i] == *opcaoJogador){
			return JOG_CondRetOK; 
		}/* if */
	}/* for */
	if( *opcaoJogador == 'A' || *opcaoJogador == 'a'){
		JOG_AumentarAposta();
		printf("Forneça o que foi pedido inicialmente\n");
		return JOG_LeInput(opcaoJogador,tipo,elemsEsperados,qtdElems);
	}/* if */
	if( *opcaoJogador == 'S' || *opcaoJogador == 's'|| *opcaoJogador == 'E' || *opcaoJogador == 'e'){
		TAB_ExibeTabuleiro(vetTab);
		JOG_SalvaJogo(vetTab,nome);
		return JOG_CondRetOK;
	}/* if */
	if( *opcaoJogador == 'f' || *opcaoJogador == 'F' ){
		return JOG_CondRetFinalizarPartida;
	}/* if */

	return JOG_CondRetInputInvalido;


}


/********** Fim do módulo de implementação: Módulo Jogo **********/
int main(void) {
	char ** vetTab = (char**)malloc(sizeof(char**));
	
	char ** vetTemp = (char**)malloc(sizeof(char**));
	
	JOG_IniciaJogo();
	getchar();
	return 0;
}
#include <malloc.h>
#include <stdio.h>

#include "Tabuleiro.h"
#include "LISTA.H"
#include "Peca.H"


/***************************************************************************
*  $MCI Modulo de implementacao: Modulo Tabuleiro
*
*  Arquivo gerado:              Tabuleiro.c
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: 
*			DF - Daniel Machado Carneiro Faller
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes      
*       1.00   DF   22/04/2019	 Inicio das implementacoes
*		1.01   DF	28/04/2019	 Juntando com o módulo peca 
*
***************************************************************************/

/*****  Dados encapsulados no módulo  *****/

	#define PLAYER1_ID 'p'
	#define PLAYER2_ID 'b'

	static LIS_tppLista tabuleiro;
		/* Ponteiro para a cabeça do tabuleiro */

/***** Protótipos das funções encapuladas no módulo *****/

	static void TAB_DestroiElemCasa( void * pDado ) ;
	
	static void TAB_DestroiTabuleiro ( void ) ;
	
	static void TAB_DestroiElemTabuleiro ( void * pDado ) ;
	
	static TAB_tpCondRet TAB_AdicionarCasasIniciais ( void ) ;

	static TAB_tpCondRet TAB_PosicaoValida (char playerCor,int casa, PEC_tpPeca ** peca ,int * pecasJaFinalizadas) ;
	
	static int ComparaCasas ( LIS_tppLista lista1, LIS_tppLista lista2 ) ;
	
	static TAB_tpCondRet TAB_InserirTabuleiro ( char playerCor, int casa ) ;

	static LIS_tppLista TAB_PegaCasa ( int pos ) ;



/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TAB Cria Tabuleiro 
*  ****/
TAB_tpCondRet TAB_CriaTabuleiro( void )
{
	int i = 0;

	if(tabuleiro != NULL)
	{
		TAB_DestroiTabuleiro();//Checa se é necessario resetar tabuleiro
	} /* if */

	tabuleiro = LIS_CriarLista(TAB_DestroiElemTabuleiro);

	if(tabuleiro == NULL)
	{
		return TAB_CondRetFaltouMemoria;
	} /* if */

	while (i < 24) 
	{
		LIS_tppLista temp;
		temp = LIS_CriarLista(TAB_DestroiElemCasa);
		LIS_InserirElementoApos(tabuleiro,temp);
		i++;

	} /* while */

	return TAB_AdicionarCasasIniciais();
	
}/* Fim função: TAB Cria Tabuleiro  */

/***************************************************************************
*
*  Função: TAB Exibe Tabuleiro
*  ****/

TAB_tpCondRet TAB_ExibeTabuleiro( char ** vetTab)
	{
		LIS_tppLista temp;
		PEC_tpPeca ** ptrPeca;

		char * corTemp;
		char * cor;
		char * vetTemp;
		int i =0,b = 0, c = 0;
		LIS_tpCondRet estado;

		ptrPeca = (PEC_tpPeca**)malloc(sizeof(PEC_tpPeca*));
		
		if( ptrPeca == NULL){
			return TAB_CondRetFaltouMemoria;
		}/* if */
		if(tabuleiro == NULL)
		{
			return TAB_CondRetTABNExiste;
		} /* if */

		IrInicioLista(tabuleiro);
	
		do
		{
			//printf("Casa:%d --- ",i);
			temp = (LIS_tppLista)LIS_ObterValor(tabuleiro);
			IrInicioLista(temp);
			b = 0;
			
			vetTemp = (char*)malloc(5*sizeof(char*));
			while(b < 5) {

				cor = (char*)malloc(sizeof(char));
				*ptrPeca  = (PEC_tpPeca*)LIS_ObterValor(temp);

				if (*ptrPeca == NULL) {
					for (b; b < 5; b++) {
						vetTemp[b] = ' ';
					}

					break;
				}

				//PEC_ExibePeca(ptrPeca);

				PEC_ObterCorPeca(ptrPeca, cor);

				vetTemp[b] = *cor;
				/*if (b > 0) {
					for ( c = b; c--; c >=0) {
					vetTemp[c] = *cor;
					}
				}*/
				b++;

				estado = LIS_AvancarElementoCorrente(temp, 1);

				if ( estado == LIS_CondRetFimLista || estado == LIS_CondRetListaVazia) 
				{	
	
					for (b; b < 5; b++) {
						vetTemp[b] = ' ';
					}

					break;
				}/* if */

				
			}

			vetTab[i] = vetTemp;

			i++;
			//printf("\n");

		} while (LIS_CondRetFimLista != LIS_AvancarElementoCorrente(tabuleiro, 1));
		
		free(cor);
		free(ptrPeca);

		return TAB_CondRetOK;

	}/* Fim função: TAB Exibe Tabuleiro  */

/***************************************************************************
*
*  Função: TAB Mover Peça
*  ****/

TAB_tpCondRet TAB_MoverPeca(char playerCor,int origem,int destino, PEC_tpPeca ** peca, int * pecasJaFinalizadas)
{
	TAB_tpCondRet estado;
	TAB_tpCondRet condicaoDestino;
	LIS_tppLista checaOrigem;
	LIS_tppLista casaADestruir;
	
	if(tabuleiro == NULL) return TAB_CondRetTABNExiste;

	if(origem < 0 || origem > 23 ){
		return TAB_CondRetForaDosLimites;
	}/* if */
	
	if(playerCor != PLAYER1_ID && playerCor != PLAYER2_ID){
		return TAB_CondRetPecaInvalida;
	}/* if */ 
	
    checaOrigem = TAB_PegaCasa(origem);
	condicaoDestino = TAB_PosicaoValida(playerCor,destino,peca,pecasJaFinalizadas);
	//Parametro peca retorna a peça a ser inserida na lista de peças capturadas ou finalizadas
	
	if(checaOrigem == NULL || condicaoDestino == TAB_CondRetPosInvalida )
	{
		return TAB_CondRetPosInvalida;
	} /* if */
	
	if( LIS_ObterValor(checaOrigem) == NULL || *(char*)LIS_ObterValor(checaOrigem) != playerCor){
		return TAB_CondRetPosInvalida;
	} /* if */

 	if( condicaoDestino == TAB_CondRetPecaCapturada){
		casaADestruir = TAB_PegaCasa(destino);
		LIS_ExcluirElemento(casaADestruir);
		TAB_InserirTabuleiro(playerCor,destino);
		LIS_ExcluirElemento(checaOrigem);
		return TAB_CondRetPecaCapturada;

	}/* if */
	if( condicaoDestino == TAB_CondRetPecaFinalizada){
		casaADestruir = TAB_PegaCasa(destino);
		TAB_InserirTabuleiro(playerCor,destino);
		LIS_ExcluirElemento(checaOrigem);
		return TAB_CondRetPecaFinalizada;
	}
	
		
	LIS_ExcluirElemento(checaOrigem);
	
	estado = TAB_InserirTabuleiro(playerCor,destino);

	return estado;

}/* Fim função: TAB Mover Peça  */

/***********************************************************************
*  Função:  TAB Pega Casa 
*
*  $ED Descrição da função
*	Retorna o endereço da lista com posição, dentro do tabuleiro,
*	referente a passada como parâmetro
*
*  $EP: Parâmetros da Função
*		pos: inteiro referente a distância entre a origem da lista e o elemento a ser buscado
*
*  $EA: Assertivas de entrada
*		A lista global do tabuleiro precisa estar construida, assim como a lista interna 
*		de cada casa.
*
*  $R:	Requisitos
*		O parâmetro posição deve ter sido checado anteriormente
*****************************************************************************************/
LIS_tppLista TAB_PegaCasa(int pos)
{
	IrInicioLista(tabuleiro);
	LIS_AvancarElementoCorrente(tabuleiro,pos);

	if(LIS_ObterValor(tabuleiro) == NULL) 
	{
		return NULL;
	} /* if */

	return (LIS_tppLista)LIS_ObterValor(tabuleiro);

}/* Fim função: TAB Pega Casa  */

/*****************************************************************************************
* $AS Assertivas de Saída
*	 Lista retornada
*  
*  $FV Valor retornado
*		Casa retornada
*
*
 Fim Assertiva de Saida TAB_PegaCasa
**************************************************************************************************/
/************************************************************************
*	Função TAB Conta Pecas
*
*	$ED Descrição da função
*		Conta a quantidade de peças dentro de uma casa se a peça tiver cor igual a passada como parâmetro
*		adiciona um ao primeiro parâmetro de retorno qtdPlayer1, caso contrario adiciona ao qtdPlayer2
*	
*  $EP: Parâmetros da Função
*		qtdPlayer1: Parâmetro de retorno para a quantidade de peças na lista igual a passada como parâmetro
*		qtdPlayer2: Parâmetro de retorno para a quantidade de peças na lista diferente da passada como parâmetro
*
*	$EA: Assertivas de entrada
*		Lista existente
*		Parâmetros de retornos previamente inicializados
*
*/
TAB_tpCondRet TAB_ContaPecas(LIS_tppLista lista, char cor,int * qtdPlayer1,int * qtdPlayer2){
	
	PEC_tpPeca * peca;
	char * tempCor = (char*)malloc(sizeof(char));

	if(LIS_ObterValor(lista) == NULL){
		return TAB_CondRetCASVazio;
	}/* if */
	IrInicioLista(lista);
	do{
		peca = (PEC_tpPeca*)LIS_ObterValor(lista);
		PEC_ObterCorPeca(&peca,tempCor);
		if(*tempCor == cor){
			*qtdPlayer1 += 1;
		}/* if */
		else{
			*qtdPlayer2 += 1;
		}/* else */
	}while(LIS_AvancarElementoCorrente(lista,1) != LIS_CondRetFimLista);
	
	return TAB_CondRetOK;
}
/*
/*****************************************************************************************
* $AS Assertivas de Saída
*	 Se não retornou TAB_CondRetVazio, então se qtdPlayer1 for igual a zero então
*	 qtdPlayer2 é diferente de zero, ou vice-versa
*  
*  $FV Valor retornado
*		TAB_tpCondRetOk
*		TAB_CondRetCASVazio
*
 Fim Assertiva de Saida TAB_ContaPecas
**************************************************************************************************/

/***************************************************************************
*
*  Funções: TAB Adicionar Casa N 
*
*  $ED Descrição da função
*	Função para construir os elementos iniciais do tabuleiro de Gamão
*   Passada como parâmetro na criação da lista e chamada pelo módulo lista
*	
*  $EP: Parâmetros da Função
*		nPos:	Posição da casa a serem inseridas as peças
*		nElems:	Quantidade de peças na casa
*		Cor:	Cor das peças
*
*  $EA: Assertivas de entrada
*		Ao chamar esta função seu parâmetros devem condizer com uma casa inicial de um tabuleiro de Gamão
*		A lista global do tabuleiro precisa estar construida, assim como a lista interna de cada casa.
*		int nPOs precisa ser um número maior que zero e menor que 25
*		Cor Necessariamente 'P' ou 'B'
*****************************************************************************************/

TAB_tpCondRet AdicionaCasaN (int nPos,int nElems, char Cor)
{
	LIS_tppLista casaN;
	PEC_tpPeca ** ptrP = (PEC_tpPeca**)malloc(sizeof(PEC_tpPeca*));
	PEC_tpCondRet estado;
	int i = 0;
	int * pecasJaFinalizadas = (int*)malloc(2 * sizeof(int));

	if( TAB_PosicaoValida(Cor,nPos,ptrP,pecasJaFinalizadas) == TAB_CondRetPosInvalida){
		return TAB_CondRetPosInvalida;
	}
	if ( nPos < 0 || nPos > 23 ){
		return TAB_CondRetForaDosLimites;
	}/* if */
	if ( Cor != PLAYER1_ID && Cor != PLAYER2_ID){
		return TAB_CondRetPecaInvalida;
	}/* if */
	if(ptrP == NULL){
		return TAB_CondRetFaltouMemoria;
	}/* if */
	casaN = TAB_PegaCasa(nPos);
	
	while(i < nElems){
		estado = PEC_CriarPeca(ptrP,Cor);
		if(estado  == PEC_CondRetFaltouMemoria){
			return TAB_CondRetFaltouMemoria;
		} /* if */
		
		if(PEC_CondRetOK == estado){
			LIS_InserirElementoApos(casaN,*ptrP);
		}
		else{
			return TAB_CondRetPecaInvalida;
		}
		i++;
	}
	free(pecasJaFinalizadas);
	free(ptrP);
	return TAB_CondRetOK;
}/* Fim função: TAB Adicionar Casa N  */

/*
* $AS Assertivas de Saída
*	 Peças adicionadas a casa corretamente
*	 Estrutura da tabuleiro e da casa mantidas
*  
*  $FV Valor retornado
*		TAB_CondRetFaltouMemoria
*		TAB_CondRetOK
*		TAB_CondRetPecaInvalida
*	
*
 Fim Assertiva de Saida TAB_PegaCasa
**************************************************************************************************/

/***********************************************************************
*  Função:  TAB Compara Casas 
*
*  $ED Descrição da função
*		Compara duas casas, passando por cada elemento e verificando se a outra lista possui um igual
*		na mesma posição.
*
*  $EP: Parâmetros da Função
*		Casa1: Lista referente a primeira casa da comparação
*		Casa2: Lista referente a segunda casa da comparação
*
*  $EA: Assertivas de entrada
*		Ambas as listas devem existir
*****************************************************************************************/
int TAB_ComparaCasas(LIS_tppLista Casa1, LIS_tppLista Casa2)
{
	if(Casa1 == NULL || Casa2 == NULL) return 0;
	IrInicioLista(Casa1);
	IrInicioLista(Casa2);
	do{
		if(*(char*)LIS_ObterValor(Casa1) != *(char*)LIS_ObterValor(Casa2) ) return 0;

	}while(LIS_AvancarElementoCorrente(Casa1,1) != LIS_CondRetFimLista);
	
	if(LIS_AvancarElementoCorrente(Casa2,1) != LIS_CondRetFimLista) return 0;
	return 1;

}/* Fim função: TAB Compara Casas */

/*****************************************************************************************
* $AS Assertivas de Saída
*	 Ponteiro Corrente de ambas as listas alterado
*	 Estrutura das listas mantidas
*	 
*  
*  $FV Valor retornado
*	 Inteiro retornado sendo:
*	 0: As casas não são iguais
*	 1: Casas iguais
*
*
 Fim Assertiva de Saida TAB_ComparaCasas
**************************************************************************************************/


/***************************************************************************
*
*  Função: TAB Adicionar Casas Iniciais
*
*  $AE Assertivas de Entrada
*		Tabuleiro previamente construido
*********************************************************************************************/

TAB_tpCondRet TAB_AdicionarCasasIniciais( void )
{
	TAB_tpCondRet estado;
	estado = AdicionaCasaN(0,2,PLAYER1_ID);
	if(estado != TAB_CondRetOK) return estado;

	estado = AdicionaCasaN(5,5,PLAYER2_ID);
	if(estado != TAB_CondRetOK) return estado;

	estado = AdicionaCasaN(7,3,PLAYER2_ID);
	if(estado != TAB_CondRetOK) return estado;

	estado = AdicionaCasaN(11,5,PLAYER1_ID);
	if(estado != TAB_CondRetOK) return estado;

	estado = AdicionaCasaN(12,5,PLAYER2_ID);
	if(estado != TAB_CondRetOK) return estado;

	estado = AdicionaCasaN(16,3,PLAYER1_ID);
	if(estado != TAB_CondRetOK) return estado;

	estado = AdicionaCasaN(18,5,PLAYER1_ID);
	if(estado != TAB_CondRetOK) return estado;
	estado = AdicionaCasaN(23,2,PLAYER2_ID);
	if(estado != TAB_CondRetOK) return estado;
	
	return TAB_CondRetOK;
}/* Fim função: TAB Adicionar Casas Iniciais  */

/*
* $AS Assertivas de Saída
*	 Peças adicionadas as casas formulando um tabuleiro de Gamão
*
* Fim Assertiva de Saida 
**************************************************************************************************/

/************************************************************************************************
*	Função: TAB  Inserir Tabuleiro
*	
*	$ED: Descrição da Função
*		Inseri um valor numa casa de posição, dentro do tabuleiro, especificada nos parâmetro
*
*	$EP: Parâmetros da Função
*		playerCor : Cor da peça a ser inserido
*		casa	  : Número da casa no tabuleiro
*
*	$EA: Assertivas de entrada
*		A lista global do tabuleiro precisa estar construida, assim como a lista interna de cada casa.
*		int casa precisa ser um número maior que zero e menor que 25 para ser inserido corretamente 
*****************************************************************************************/

TAB_tpCondRet TAB_InserirTabuleiro(char playerCor, int casa) {
	LIS_tppLista temp;
	PEC_tpPeca * p;
	
	
	if(tabuleiro == NULL) return  TAB_CondRetTABNExiste; 	
	PEC_CriarPeca(&p,playerCor);
	if(p == NULL) return TAB_CondRetFaltouMemoria;

	IrInicioLista(tabuleiro);
	
	if (casa <= 23 && casa >= 0) {
		temp = TAB_PegaCasa(casa);
		LIS_InserirElementoApos(temp,p);
		return TAB_CondRetOK;
	}
	

	return TAB_CondRetForaDosLimites;
}/* Fim função: TAB Inserir Tabuleiro  */

/* ***********************************************************************
*	$AS Assertivas de Saída
*		Estrutura do tabuleiro mantida
*		Peca inserida na posição especificada
*  
*	$FV Valor retornado
*		TAB_CondRetOK
*		TAB_CondRetTABNExiste
*		TAB_CondRetForaDosLimites
*		TAB_CondRetFaltouMemória
*
 Fim Assertiva de Saida TAB_InserirTabuleiro 

 *******************************************************/

/************************************************************************************************
*	Função: TAB  PosicaoValida

*	$ED: Descrição da Função
*		 Checa a se é possível inserir um elemento numa casa, conferindo a 
*		 Cor do player passado como parâmetro e a casa.
*
*	$EP: Parâmetros da Função
*		playerCor : Cor da peça a ser inserido
*		casa	  : Número da casa no tabuleiro
*
*	$EA: Assertivas de entrada
*		A lista global do tabuleiro precisa estar construida, assim como a lista interna de cada casa.
*		O parâmetro casa precisa estar entre [0,23]
*****************************************************************************************************/


TAB_tpCondRet TAB_PosicaoValida(char playerCor,int casa, PEC_tpPeca ** peca,int * pecasJaFinalizadas){

	char playerID;
	LIS_tppLista temp;
	char * cor;
	int * pBool, * bBool;
	pBool = (int*)malloc(sizeof(int));
	bBool = (int*)malloc(sizeof(int));
	cor = (char*)malloc(sizeof(char));

	temp = TAB_PegaCasa(casa);
    IrInicioLista(temp);
	

	if(casa < 0 || casa > 23)
	{
		TAB_BuscaChecker(pBool,bBool,pecasJaFinalizadas);
		if(playerCor == 'p'){
			if(*pBool == 1){
				//peca = (PEC_tpPeca**)malloc(sizeof(PEC_tpPeca*));
				PEC_CriarPeca(peca,playerCor);
				return TAB_CondRetPecaFinalizada;
			}
		}/* if */
		if(playerCor == 'b'){
			if(*bBool == 1){
				//peca = (PEC_tpPeca**)malloc(sizeof(PEC_tpPeca*));
				PEC_CriarPeca(peca,playerCor);
				return TAB_CondRetPecaFinalizada;
			}
		}/* if */

		return TAB_CondRetPosInvalida;
	} /* if */


	if(LIS_ObterValor(temp) == NULL)
	{
		return TAB_CondRetOK;
	} /* if */
	
	playerID = *(char*)LIS_ObterValor(temp);
	*cor = playerID;
	
	

	if(playerID == playerCor)
	{
		return TAB_CondRetOK;
	} /* if */
	else
	{
		if(LIS_AvancarElementoCorrente(temp,1) == LIS_CondRetFimLista)
		{
			//peca = (PEC_tpPeca**)malloc(sizeof(PEC_tpPeca*));
			PEC_CriarPeca(peca,*cor);
			return TAB_CondRetPecaCapturada;
		} /* if */

		return TAB_CondRetPosInvalida;

	} /* else */
}

/**************************************************************************************************
*	$AS Assertivas de Saída
*	 	Estrutura do tabuleiro mantida
*	 	Caso a posição possua apenas uma peca de uma cor distinta da passada como parâmetro, 
*		esta função se encarrega de eliminar esta peca
*  
*   $FV Valor retornado
*		True:	Se existiam uma ou menos peças na posição do tabuleiro
*		False:	Se a casa estava fora dos limites, ou possuia duas ou mais pecas de uma cor distinta 
*
*	Fim Assertiva de Saida TAB_ExibeTabuleiro
 **************************************************************************************************/


/******************************************************************************************
*   Função TAB Checa Checker
*   $ED: Descrição da função
*		Checa se a casa tem apenas um elemento ou não
*	
*	$EP: Parâmetros da função a casa a ser checada
*		casa : cabeça da lista de peças a ser testada
*	
*	$EA: Assertivas de entrada 
*		Casa válida possuido de 0 a 5 elementos
*
*/
int TAB_ChecaChecker(LIS_tppLista casa){
	
	IrInicioLista(casa);
	if(LIS_AvancarElementoCorrente(casa,1) == LIS_CondRetFimLista){
		return 1;
	}/* if */
	return 0;
}

/* $AS Assertivas de Saida TAB_DestroiTabuleiro
*	Estrutura da lista mantida
*	Elemento corrente possivelmente deslocado
*
*  Fim Assertiva de Saida TAB_ChecaChecker */



/*
*	Função BuscaChecker
***/
TAB_tpCondRet TAB_BuscaChecker(int * pretasBool, int * brancasBool, int * pecasJaFinalizadas){
	int *qtdPecasPretas, *qtdPecasBrancas;
	/*Ponteiros para chama função TAB_ContaPecas */
	int pretasFinalizando, brancasFinalizando;
	
	int i = 0;
	LIS_tppLista casa;

	qtdPecasBrancas = (int*)malloc(sizeof(int));
	qtdPecasPretas = (int*)malloc(sizeof(int));
	*qtdPecasBrancas = 0;
	*qtdPecasPretas = 0;
	*pretasBool = 0;
	*brancasBool = 0;

	brancasFinalizando = *pecasJaFinalizadas;
	pretasFinalizando = *(pecasJaFinalizadas +1);
	IrInicioLista(tabuleiro);
	
	for(i = 0; i < 6; i ++){
		*qtdPecasBrancas = 0;
		casa = TAB_PegaCasa(i);
		TAB_ContaPecas(casa,'b',qtdPecasBrancas,qtdPecasPretas);
		brancasFinalizando += *qtdPecasBrancas;
		*qtdPecasBrancas = 0;
	}/* for */
	if(brancasFinalizando == 15){
		*brancasBool = 1;
	}/* if */
	if(*qtdPecasPretas == 0){
		for(i = 17; i < 24; i ++){
			casa = TAB_PegaCasa(i);
			TAB_ContaPecas(casa,'b',qtdPecasBrancas,qtdPecasPretas);
			pretasFinalizando += *qtdPecasPretas;
			*qtdPecasPretas = 0;
		}
		if(pretasFinalizando == 15){
			*pretasBool = 1;
		}/* if */

	}/* if */
	free(qtdPecasPretas);
	free(qtdPecasBrancas);
	return TAB_CondRetOK;

}/* Fim função: TAB_BuscaChecker */

/***********************************************************************
*
*  $FC Função: TAB Destroi Tabuleiro
*
*  $EA: Assertivas de entrada
*		Tem que existir um tabuleiro a ser destruida
*
*  Fim Assertivas de Entrada TAB_DestroiTabuleiro 
*
***********************************************************************/

void TAB_DestroiTabuleiro( void ) 
{
	int i;
	LIS_tppLista lista;

	PEC_tpPeca ** peca;
	peca = (PEC_tpPeca**)malloc(sizeof(PEC_tpPeca*));
	IrInicioLista(tabuleiro);
	
	for ( i = 0; i < 24; i++)
	{
		if(LIS_ObterValor(tabuleiro) != NULL)
		{
			LIS_DestruirLista((LIS_tppLista)LIS_ObterValor(tabuleiro));
		
		} /* if */

		LIS_AvancarElementoCorrente(tabuleiro, 1);
	} /* for */

	IrInicioLista(tabuleiro);
	LIS_DestruirLista(tabuleiro);

}/* Fim função: TAB Destroi Tabuleiro  */

/* $AS Assertivas de Saida TAB_DestroiTabuleiro
*	Tabuleiro destruido
*
*  Fim Assertiva de Saida TAB_DestroiTabuleiro */

/***************************************************************************************************
*
*  Função: TAB Função Destroi Elemento Casa
*
*  $ED Descrição da função
*	Função para destruir um elemento dentro da lista de casas
*   Passada como parâmetro na criação da lista e chamada pelo módulo lista
*	
*  $EP: Parâmetros da Função
*		pDado: Endereço de memória para o elemento da lista a ser excluido
*
*  $EA: Assertivas de entrada
*		A lista global do tabuleiro precisa estar construida, assim como a lista interna de cada casa.
*		int casa precisa ser um número maior que zero e menor que 25 para ser inserido corretamente 
*
*/
void TAB_DestroiElemCasa(void * pDado)
{
	LIS_tppLista temp;
	temp = (LIS_tppLista)pDado;
	free(LIS_ObterValor(temp));
	free(pDado);
}/* Fim função: TAB Destroi Elemento da casa  */

/*
* $AS Assertivas de Saída
*	 Garante-se que a estrutura será mantida pelas outras funções do módulo lista
*	 Elemento da lista destruido e desencadeado
*  
 Fim Assertiva de Saida TAB_DestroiElemCasa 

**************************************************************************************************/
/**************************************************************************************************
*
*  Função: TAB Função Destroi Elemento do Tabuleiro
*
*  $EP: Parâmetros da Função
*		pDado: Endereço de memória para o elemento da lista a ser excluido
*
*  $EA: Assertivas de entrada
*		O ponteiro passado deve se referir a uma casa que deva ser liberada
*
**************************************************************************************************/
void TAB_DestroiElemTabuleiro(void * pDado) {
	free(pDado);
}/* Fim função: TAB Destroi Elemento do Tabuleiro */
/*
* $AS Assertivas de Saída
*	 Garante-se que a estrutura será mantida pelas outras funções do módulo lista
*	 Elemento da lista destruido e desencadeado
*  
 Fim Assertiva de Saida TAB_DestroiElemTabuleiro
**************************************************************************************************/

TAB_tpCondRet TAB_ExisteMovimento( char playerCor, int * movimentos, int sentido){
	char ** vetTab;
	LIS_tppLista casa;
	int destino;
	PEC_tpPeca * peca;
	char * cor;
	int i;
	int * pecasJaFinalizadas = (int*)malloc(2 * sizeof(int));
	vetTab = (char**)malloc(24 * sizeof(char*));
	cor = (char*)malloc(sizeof(char));
	IrInicioLista(tabuleiro);
	for(i = 0; i < 24;i++){
		casa = (LIS_tppLista)LIS_ObterValor(tabuleiro);
		peca = (PEC_tpPeca*)LIS_ObterValor(casa);
		PEC_ObterCorPeca(&peca,cor);
		
		if(*cor == playerCor ){
			destino = i + *movimentos * sentido ;
			if( destino >= 0 && destino < 24){
				if(TAB_PosicaoValida(playerCor,destino,&peca,pecasJaFinalizadas) != TAB_CondRetPosInvalida ){
					return TAB_CondRetOK;
				}/* if */
			}/* if */
			destino = i + *(movimentos + 1)* sentido ;
			if(destino >= 0 && destino < 24){
				if(TAB_PosicaoValida(playerCor,destino,&peca,pecasJaFinalizadas) != TAB_CondRetPosInvalida){
					return TAB_CondRetOK;
				}/* if */
			}/* if */
		}/* if */
		LIS_AvancarElementoCorrente(tabuleiro,1);
	}/* for */

	return TAB_CondRetPosInvalida;
}

/***************************************************************************
*
*  Função: TAB Cria Tabuleiro 
*  ****/
TAB_tpCondRet TAB_CriaTabuleiroVazio( void )
{
	int i = 0;

	if(tabuleiro != NULL)
	{
		TAB_DestroiTabuleiro();//Checa se é necessario resetar tabuleiro
	} /* if */

	tabuleiro = LIS_CriarLista(TAB_DestroiElemTabuleiro);

	if(tabuleiro == NULL)
	{
		return TAB_CondRetFaltouMemoria;
	} /* if */

	while (i < 24) 
	{
		LIS_tppLista temp;
		temp = LIS_CriarLista(TAB_DestroiElemCasa);
		LIS_InserirElementoApos(tabuleiro,temp);
		i++;

	} /* while */

	return TAB_CondRetOK;
	
}/* Fim função: TAB Cria Tabuleiro  */


/********** Fim do módulo de implementação: Módulo Tabuleiro **********/
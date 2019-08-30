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
*		1.01   DF	28/04/2019	 Juntando com o m�dulo peca 
*
***************************************************************************/

/*****  Dados encapsulados no m�dulo  *****/

	#define PLAYER1_ID 'p'
	#define PLAYER2_ID 'b'

	static LIS_tppLista tabuleiro;
		/* Ponteiro para a cabe�a do tabuleiro */

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

	static void TAB_DestroiElemCasa( void * pDado ) ;
	
	static void TAB_DestroiTabuleiro ( void ) ;
	
	static void TAB_DestroiElemTabuleiro ( void * pDado ) ;
	
	static TAB_tpCondRet TAB_AdicionarCasasIniciais ( void ) ;

	static TAB_tpCondRet TAB_PosicaoValida (char playerCor,int casa, PEC_tpPeca ** peca ,int * pecasJaFinalizadas) ;
	
	static int ComparaCasas ( LIS_tppLista lista1, LIS_tppLista lista2 ) ;
	
	static TAB_tpCondRet TAB_InserirTabuleiro ( char playerCor, int casa ) ;

	static LIS_tppLista TAB_PegaCasa ( int pos ) ;



/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: TAB Cria Tabuleiro 
*  ****/
TAB_tpCondRet TAB_CriaTabuleiro( void )
{
	int i = 0;

	if(tabuleiro != NULL)
	{
		TAB_DestroiTabuleiro();//Checa se � necessario resetar tabuleiro
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
	
}/* Fim fun��o: TAB Cria Tabuleiro  */

/***************************************************************************
*
*  Fun��o: TAB Exibe Tabuleiro
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

	}/* Fim fun��o: TAB Exibe Tabuleiro  */

/***************************************************************************
*
*  Fun��o: TAB Mover Pe�a
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
	//Parametro peca retorna a pe�a a ser inserida na lista de pe�as capturadas ou finalizadas
	
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

}/* Fim fun��o: TAB Mover Pe�a  */

/***********************************************************************
*  Fun��o:  TAB Pega Casa 
*
*  $ED Descri��o da fun��o
*	Retorna o endere�o da lista com posi��o, dentro do tabuleiro,
*	referente a passada como par�metro
*
*  $EP: Par�metros da Fun��o
*		pos: inteiro referente a dist�ncia entre a origem da lista e o elemento a ser buscado
*
*  $EA: Assertivas de entrada
*		A lista global do tabuleiro precisa estar construida, assim como a lista interna 
*		de cada casa.
*
*  $R:	Requisitos
*		O par�metro posi��o deve ter sido checado anteriormente
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

}/* Fim fun��o: TAB Pega Casa  */

/*****************************************************************************************
* $AS Assertivas de Sa�da
*	 Lista retornada
*  
*  $FV Valor retornado
*		Casa retornada
*
*
 Fim Assertiva de Saida TAB_PegaCasa
**************************************************************************************************/
/************************************************************************
*	Fun��o TAB Conta Pecas
*
*	$ED Descri��o da fun��o
*		Conta a quantidade de pe�as dentro de uma casa se a pe�a tiver cor igual a passada como par�metro
*		adiciona um ao primeiro par�metro de retorno qtdPlayer1, caso contrario adiciona ao qtdPlayer2
*	
*  $EP: Par�metros da Fun��o
*		qtdPlayer1: Par�metro de retorno para a quantidade de pe�as na lista igual a passada como par�metro
*		qtdPlayer2: Par�metro de retorno para a quantidade de pe�as na lista diferente da passada como par�metro
*
*	$EA: Assertivas de entrada
*		Lista existente
*		Par�metros de retornos previamente inicializados
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
* $AS Assertivas de Sa�da
*	 Se n�o retornou TAB_CondRetVazio, ent�o se qtdPlayer1 for igual a zero ent�o
*	 qtdPlayer2 � diferente de zero, ou vice-versa
*  
*  $FV Valor retornado
*		TAB_tpCondRetOk
*		TAB_CondRetCASVazio
*
 Fim Assertiva de Saida TAB_ContaPecas
**************************************************************************************************/

/***************************************************************************
*
*  Fun��es: TAB Adicionar Casa N 
*
*  $ED Descri��o da fun��o
*	Fun��o para construir os elementos iniciais do tabuleiro de Gam�o
*   Passada como par�metro na cria��o da lista e chamada pelo m�dulo lista
*	
*  $EP: Par�metros da Fun��o
*		nPos:	Posi��o da casa a serem inseridas as pe�as
*		nElems:	Quantidade de pe�as na casa
*		Cor:	Cor das pe�as
*
*  $EA: Assertivas de entrada
*		Ao chamar esta fun��o seu par�metros devem condizer com uma casa inicial de um tabuleiro de Gam�o
*		A lista global do tabuleiro precisa estar construida, assim como a lista interna de cada casa.
*		int nPOs precisa ser um n�mero maior que zero e menor que 25
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
}/* Fim fun��o: TAB Adicionar Casa N  */

/*
* $AS Assertivas de Sa�da
*	 Pe�as adicionadas a casa corretamente
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
*  Fun��o:  TAB Compara Casas 
*
*  $ED Descri��o da fun��o
*		Compara duas casas, passando por cada elemento e verificando se a outra lista possui um igual
*		na mesma posi��o.
*
*  $EP: Par�metros da Fun��o
*		Casa1: Lista referente a primeira casa da compara��o
*		Casa2: Lista referente a segunda casa da compara��o
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

}/* Fim fun��o: TAB Compara Casas */

/*****************************************************************************************
* $AS Assertivas de Sa�da
*	 Ponteiro Corrente de ambas as listas alterado
*	 Estrutura das listas mantidas
*	 
*  
*  $FV Valor retornado
*	 Inteiro retornado sendo:
*	 0: As casas n�o s�o iguais
*	 1: Casas iguais
*
*
 Fim Assertiva de Saida TAB_ComparaCasas
**************************************************************************************************/


/***************************************************************************
*
*  Fun��o: TAB Adicionar Casas Iniciais
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
}/* Fim fun��o: TAB Adicionar Casas Iniciais  */

/*
* $AS Assertivas de Sa�da
*	 Pe�as adicionadas as casas formulando um tabuleiro de Gam�o
*
* Fim Assertiva de Saida 
**************************************************************************************************/

/************************************************************************************************
*	Fun��o: TAB  Inserir Tabuleiro
*	
*	$ED: Descri��o da Fun��o
*		Inseri um valor numa casa de posi��o, dentro do tabuleiro, especificada nos par�metro
*
*	$EP: Par�metros da Fun��o
*		playerCor : Cor da pe�a a ser inserido
*		casa	  : N�mero da casa no tabuleiro
*
*	$EA: Assertivas de entrada
*		A lista global do tabuleiro precisa estar construida, assim como a lista interna de cada casa.
*		int casa precisa ser um n�mero maior que zero e menor que 25 para ser inserido corretamente 
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
}/* Fim fun��o: TAB Inserir Tabuleiro  */

/* ***********************************************************************
*	$AS Assertivas de Sa�da
*		Estrutura do tabuleiro mantida
*		Peca inserida na posi��o especificada
*  
*	$FV Valor retornado
*		TAB_CondRetOK
*		TAB_CondRetTABNExiste
*		TAB_CondRetForaDosLimites
*		TAB_CondRetFaltouMem�ria
*
 Fim Assertiva de Saida TAB_InserirTabuleiro 

 *******************************************************/

/************************************************************************************************
*	Fun��o: TAB  PosicaoValida

*	$ED: Descri��o da Fun��o
*		 Checa a se � poss�vel inserir um elemento numa casa, conferindo a 
*		 Cor do player passado como par�metro e a casa.
*
*	$EP: Par�metros da Fun��o
*		playerCor : Cor da pe�a a ser inserido
*		casa	  : N�mero da casa no tabuleiro
*
*	$EA: Assertivas de entrada
*		A lista global do tabuleiro precisa estar construida, assim como a lista interna de cada casa.
*		O par�metro casa precisa estar entre [0,23]
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
*	$AS Assertivas de Sa�da
*	 	Estrutura do tabuleiro mantida
*	 	Caso a posi��o possua apenas uma peca de uma cor distinta da passada como par�metro, 
*		esta fun��o se encarrega de eliminar esta peca
*  
*   $FV Valor retornado
*		True:	Se existiam uma ou menos pe�as na posi��o do tabuleiro
*		False:	Se a casa estava fora dos limites, ou possuia duas ou mais pecas de uma cor distinta 
*
*	Fim Assertiva de Saida TAB_ExibeTabuleiro
 **************************************************************************************************/


/******************************************************************************************
*   Fun��o TAB Checa Checker
*   $ED: Descri��o da fun��o
*		Checa se a casa tem apenas um elemento ou n�o
*	
*	$EP: Par�metros da fun��o a casa a ser checada
*		casa : cabe�a da lista de pe�as a ser testada
*	
*	$EA: Assertivas de entrada 
*		Casa v�lida possuido de 0 a 5 elementos
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
*	Fun��o BuscaChecker
***/
TAB_tpCondRet TAB_BuscaChecker(int * pretasBool, int * brancasBool, int * pecasJaFinalizadas){
	int *qtdPecasPretas, *qtdPecasBrancas;
	/*Ponteiros para chama fun��o TAB_ContaPecas */
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

}/* Fim fun��o: TAB_BuscaChecker */

/***********************************************************************
*
*  $FC Fun��o: TAB Destroi Tabuleiro
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

}/* Fim fun��o: TAB Destroi Tabuleiro  */

/* $AS Assertivas de Saida TAB_DestroiTabuleiro
*	Tabuleiro destruido
*
*  Fim Assertiva de Saida TAB_DestroiTabuleiro */

/***************************************************************************************************
*
*  Fun��o: TAB Fun��o Destroi Elemento Casa
*
*  $ED Descri��o da fun��o
*	Fun��o para destruir um elemento dentro da lista de casas
*   Passada como par�metro na cria��o da lista e chamada pelo m�dulo lista
*	
*  $EP: Par�metros da Fun��o
*		pDado: Endere�o de mem�ria para o elemento da lista a ser excluido
*
*  $EA: Assertivas de entrada
*		A lista global do tabuleiro precisa estar construida, assim como a lista interna de cada casa.
*		int casa precisa ser um n�mero maior que zero e menor que 25 para ser inserido corretamente 
*
*/
void TAB_DestroiElemCasa(void * pDado)
{
	LIS_tppLista temp;
	temp = (LIS_tppLista)pDado;
	free(LIS_ObterValor(temp));
	free(pDado);
}/* Fim fun��o: TAB Destroi Elemento da casa  */

/*
* $AS Assertivas de Sa�da
*	 Garante-se que a estrutura ser� mantida pelas outras fun��es do m�dulo lista
*	 Elemento da lista destruido e desencadeado
*  
 Fim Assertiva de Saida TAB_DestroiElemCasa 

**************************************************************************************************/
/**************************************************************************************************
*
*  Fun��o: TAB Fun��o Destroi Elemento do Tabuleiro
*
*  $EP: Par�metros da Fun��o
*		pDado: Endere�o de mem�ria para o elemento da lista a ser excluido
*
*  $EA: Assertivas de entrada
*		O ponteiro passado deve se referir a uma casa que deva ser liberada
*
**************************************************************************************************/
void TAB_DestroiElemTabuleiro(void * pDado) {
	free(pDado);
}/* Fim fun��o: TAB Destroi Elemento do Tabuleiro */
/*
* $AS Assertivas de Sa�da
*	 Garante-se que a estrutura ser� mantida pelas outras fun��es do m�dulo lista
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
*  Fun��o: TAB Cria Tabuleiro 
*  ****/
TAB_tpCondRet TAB_CriaTabuleiroVazio( void )
{
	int i = 0;

	if(tabuleiro != NULL)
	{
		TAB_DestroiTabuleiro();//Checa se � necessario resetar tabuleiro
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
	
}/* Fim fun��o: TAB Cria Tabuleiro  */


/********** Fim do m�dulo de implementa��o: M�dulo Tabuleiro **********/
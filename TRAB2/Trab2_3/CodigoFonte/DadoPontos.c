/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo Dado Pontos
*
*  Arquivo gerado:              DadoPontos.c
*  Letras identificadoras:      DAP
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Jogo do Gam�o - Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: JP - J�ssica Pereira Cesario
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es      
*       1.00   JP   15/04/2019 In�cio do desenvolvimento
*
***************************************************************************/


#include  <stdio.h> 
#include  <malloc.h>


#define DadoPontos_OWN
#include "DadoPontos.h"
#undef DadoPontos_OWN

/***********************************************************************
*
*  $TC Tipo de dados: DAP Descritor do dados de ponto.
*
*
*  $ED Descri��o do tipo
*     Descreve uma estrutura do ponto de dados
*
***********************************************************************/

   typedef struct tgDadoPontos {

	   int ValorPartida;
	   /* Pontua�ao atual do jogo
               *
               *$EED Assertivas estruturais
               *   � 1 se o jogo esta no come�o
			   */
	   
	   char JogadorDobra;
	   /* Jogador que pode dobrar a pontua��o na partida
               *
               *$EED Assertivas estruturais
               *   � '\0' se o jogo esta no come�o e ninguem fez nenhuma dobra
			   *   � p se o jogador da cor preta  dobrou na ultima rodada
			   *   � b se o jogador da cor branca dobrou na ultima rodada
			   */

   } tpDadoPontos ;


/*****  Dados encapsulados no m�dulo  *****/

	static tpDadoPontos * pDadoPontos = NULL ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: DAP Criar Dado
*  ****/

   DAP_tpCondRet DAP_CriaDadoPontos ( void )
   {

	   if( pDadoPontos != NULL)
	   {
		   DAP_DestruirDadoPontos( ) ;
	   } /* if */

	   pDadoPontos = ( tpDadoPontos * ) malloc( sizeof( tpDadoPontos )) ;
	   if( pDadoPontos == NULL)
	   {
		   return DAP_CondRetFaltouMemoria ;
	   } /* if */

	   pDadoPontos-> ValorPartida = 1 ;
	   pDadoPontos-> JogadorDobra = '\0' ;

	   return DAP_CondRetOK ;

   } /* Fim fun��o: DAP Criar Dado pontos */

/***************************************************************************
*
*  Fun��o: DAP Destruir Dado pontos
*  ****/

   DAP_tpCondRet DAP_DestruirDadoPontos( void )
   {

      if ( pDadoPontos == NULL )
      {
		  return DAP_CondRetDadoPontosNaoExiste ;

      } /* if */

	  free( pDadoPontos ) ;
	  pDadoPontos = NULL ;

	  return DAP_CondRetOK ; 

   } /* Fim fun��o: DAP Destruir Dado Pontos */

/***************************************************************************
*
*  Fun��o: DAP Dobrar Pontua��o
*  ****/

   DAP_tpCondRet DAP_DobrarPontuacao( char jogador )
   {

      if ( pDadoPontos == NULL )
      {
		  return DAP_CondRetDadoPontosNaoExiste ;

      } /* if */

	  if ( pDadoPontos->ValorPartida == 64 ) 
	  {
		  return DAP_CondRetPontuacaoMaxima ;

	  }/* if */

	  if ( pDadoPontos->JogadorDobra == jogador ) 
	  {
		  return DAP_CondRetNaoPodeDobrar ;

	  }/* if */

	  pDadoPontos->ValorPartida *= 2 ;
	  pDadoPontos->JogadorDobra  = jogador ;

	  return DAP_CondRetOK ; 

   } /* Fim fun��o: DAP Dobrar Pontuacao */

/***************************************************************************
*
*  Fun��o: DAP Obter pontua��o da partida
*  ****/

   DAP_tpCondRet DAP_ObterValorPartida ( int *pontuacao )
   {

      if ( pDadoPontos == NULL )
      {
		  return DAP_CondRetDadoPontosNaoExiste ;

      } /* if */

	  *pontuacao = pDadoPontos->ValorPartida;

	  return DAP_CondRetOK ; 

   } /* Fim fun��o: DAP Obter pontua��o da partida */

/********** Fim do m�dulo de implementa��o: M�dulo DadoPontos **********/
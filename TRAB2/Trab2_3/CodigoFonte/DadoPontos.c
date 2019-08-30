/***************************************************************************
*  $MCI Módulo de implementação: Módulo Dado Pontos
*
*  Arquivo gerado:              DadoPontos.c
*  Letras identificadoras:      DAP
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Jogo do Gamão - Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: JP - Jéssica Pereira Cesario
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações      
*       1.00   JP   15/04/2019 Início do desenvolvimento
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
*  $ED Descrição do tipo
*     Descreve uma estrutura do ponto de dados
*
***********************************************************************/

   typedef struct tgDadoPontos {

	   int ValorPartida;
	   /* Pontuaçao atual do jogo
               *
               *$EED Assertivas estruturais
               *   É 1 se o jogo esta no começo
			   */
	   
	   char JogadorDobra;
	   /* Jogador que pode dobrar a pontuação na partida
               *
               *$EED Assertivas estruturais
               *   É '\0' se o jogo esta no começo e ninguem fez nenhuma dobra
			   *   É p se o jogador da cor preta  dobrou na ultima rodada
			   *   É b se o jogador da cor branca dobrou na ultima rodada
			   */

   } tpDadoPontos ;


/*****  Dados encapsulados no módulo  *****/

	static tpDadoPontos * pDadoPontos = NULL ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: DAP Criar Dado
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

   } /* Fim função: DAP Criar Dado pontos */

/***************************************************************************
*
*  Função: DAP Destruir Dado pontos
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

   } /* Fim função: DAP Destruir Dado Pontos */

/***************************************************************************
*
*  Função: DAP Dobrar Pontuação
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

   } /* Fim função: DAP Dobrar Pontuacao */

/***************************************************************************
*
*  Função: DAP Obter pontuação da partida
*  ****/

   DAP_tpCondRet DAP_ObterValorPartida ( int *pontuacao )
   {

      if ( pDadoPontos == NULL )
      {
		  return DAP_CondRetDadoPontosNaoExiste ;

      } /* if */

	  *pontuacao = pDadoPontos->ValorPartida;

	  return DAP_CondRetOK ; 

   } /* Fim função: DAP Obter pontuação da partida */

/********** Fim do módulo de implementação: Módulo DadoPontos **********/
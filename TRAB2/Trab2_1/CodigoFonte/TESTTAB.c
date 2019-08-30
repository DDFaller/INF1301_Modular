#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "Tabuleiro.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     CRIAR_TAB_CMD      "=criar"
#define     EXIBI_CMD          "=exibir"
#define     MOVER_CMD	       "=mover"


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TARV Efetuar opera��es de teste espec�ficas para DadoPontos
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     DadoPontos sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

	   TAB_tpCondRet CondRetObtido   = TAB_CondRetOK ;
	   TAB_tpCondRet CondRetEsperada = TAB_CondRetOK ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      int  PosOrigem     =  0   ;
	  int  PosDest       =  0 ;

      int  NumLidos = -1 ;

	  if(strcmp(ComandoTeste,CRIAR_TAB_CMD) == 0){

		  NumLidos = LER_LerParametros("i",&CondRetEsperada);

		  if(NumLidos != 1) return TST_CondRetParm;

		  CondRetObtido = TAB_CriaTabuleiro();

		  return TST_CompararInt(CondRetEsperada,CondRetObtido,"Retorno errado ao Cria tabuleiro");

	  }

	  if(strcmp(ComandoTeste, EXIBI_CMD) == 0){

		  NumLidos = LER_LerParametros("i",&CondRetEsperada);

		  if(NumLidos != 1) return TST_CondRetParm;

		  CondRetObtido = TAB_ExibeTabuleiro();

		  return TST_CompararInt(CondRetEsperada,CondRetObtido,"Retorno errado ao Exibir tabuleiro");

	  }

	  if(strcmp(ComandoTeste, MOVER_CMD) == 0){

		  NumLidos = LER_LerParametros("ciii",&ValorEsperado,&PosOrigem,&PosDest,&CondRetEsperada);

		  if(NumLidos != 4) return TST_CondRetParm;

		  CondRetObtido = TAB_MoverPeca(ValorEsperado,PosOrigem,PosDest);

		  return TST_CompararInt(CondRetEsperada,CondRetObtido,"Retorno errado ao Cria tabuleiro");

	  }

      

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TDAD Efetuar opera��es de teste espec�ficas para Dado */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/
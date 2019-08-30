/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTDAD.C
*  Letras identificadoras:      TDAD
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: JP - J�ssica Pereira Cesario
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       1.00   JP   5/05/2019 Documenta��o
*		1.00   
*
*  $ED Descri��o do m�dulo
*     Este modulo cont�m uma fun��o espec�ficaa para o teste do
*     m�dulo dado. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo dado:
*
*     ""=rolar""      - chama a fun��o DAD_RolarDados( )
*
***************************************************************************/
#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "Dado.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     ROLAR_DAD_CMD       "=rolar"

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TARV Efetuar opera��es de teste espec�ficas para �rvore
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     �rvore sendo testado.
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

      DAD_tpCondRet CondRetObtido   = DAD_CondRetOK ;
      DAD_tpCondRet CondRetEsperada = DAD_CondRetOK ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;

      int  NumLidos = -1 ;
	  int Dados[2];

      /* Testar DAD Rolar dados */

         if ( strcmp( ComandoTeste , ROLAR_DAD_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DAD_RolarDados(Dados) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao Rolar Dado." );

         } /* fim ativa: Testar DAD Rolar Dado */
     

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TDAD Efetuar opera��es de teste espec�ficas para Dado */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/
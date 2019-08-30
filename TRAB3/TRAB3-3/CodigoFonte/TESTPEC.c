
/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTPEC.C
*  Letras identificadoras:      TPEC
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Jogo de Gam�o - Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: JP - J�ssica Pereira Cesario
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       1.00   JP   28/04/2019 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este modulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo pe�a. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo pe�a:
*
*     "=criar"         - chama a fun��o PECC_CriarPecaCapturada( )
*     "=destroi"	   - chama a fun��o PECC_ResetarPecaCapturada( )
*     "=adicionar"     - chama a fun��o PECC_AdicionaPecaCapturada( ) 
*     "=contar"        - chama a fun��o PECC_ObterQuantidadeLisPC( ) e retorna 
*							por referencia o valor da cor da pe�a
*     "=remover"       - chama a fun��o PECC_RemoverPecaCapturada( )
*
***************************************************************************/
#include    <string.h>
#include    <stdio.h>
#include	<stdlib.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "PecasCapturadas.h"
#include    "Peca.H"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define      CRIAR_PC_CMD       "=criar"
#define      DESTRUIR_PC_CMD    "=destruir"
#define      REMOVE_PC_CMD 		"=remover"
#define      CONTAR_PC_CMD 	    "=contar"
#define      INSERIR_PC_CMD 	"=adicionar"


int ind = 0 ;
PEC_tpPeca *pPeca[20];

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TPECC Efetuar opera��es de teste espec�ficas para peca capturada
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     peca capturada sendo testado.
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

      PECC_tpCondRet CondRetObtido   = PECC_CondRetOK ;
      PECC_tpCondRet CondRetEsperada = PECC_CondRetOK ;
                                      /* inicializa para qualquer coisa */
      int ValorEsperado   =  0   ;
	  int  ValorEsperado1 = '?'  ;
      char ValorObtido    = '!'  ;
      char cor            = ' '  ;
      int  indice         =  0   ;
	  int  ValorPart      = NULL ;

      int  NumLidos = -1 ;

	  TST_tpCondRet Ret ;

      /* Testar PECC Criar Peca Capturada*/

         if ( strcmp( ComandoTeste , CRIAR_PC_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "i" ,
                                &CondRetEsperada ) ;
         
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PECC_CriarPecaCapturada() ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao Criar Peca capturada." );

         } /* fim ativa: Testar PECC criar Peca Capturada */
		  
	/* Testar PECC Destroi Peca Capturada */

		 else if ( strcmp( ComandoTeste , DESTRUIR_PC_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" ,
                                &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PECC_ResetarPecaCapturada() ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado Destruir Peca capturada." );

         } /* fim ativa: Testar PECC Destroi peca capturada */

	/* Testar PECC Adicionar pecas capturadas */

		 else if ( strcmp( ComandoTeste , INSERIR_PC_CMD ) == 0 )
		 {
			 NumLidos = LER_LerParametros( "i" ,
                              &CondRetEsperada ) ;
			 if ( NumLidos != 1 )
             {
                return TST_CondRetParm ;
             } /* if */

			 PEC_CriarPeca(&pPeca[ind], 'b');

             CondRetObtido = PECC_AdicionaPecaCapturada(pPeca[ind]) ;
			 ind+=1;	

             return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                     "Retorno errado Adicionar Peca capturada." );
		 } /* fim ativa: Testar PECC inserir peca capturada */

	/* Testar PECC obter quantidade de pecas capturadas */

		 else if ( strcmp( ComandoTeste , CONTAR_PC_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "cii" ,
                                &cor, &ValorEsperado, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PECC_ObterQuantidadeLisPC(cor, &ValorPart ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado para obter quantidade de peca capturada." );

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararInt( ValorEsperado , ValorPart ,
                                     "Conteudo da peca esta errado." ) ;

         } /* fim ativa: Testar PECC obter quantidade de pecas capturadaS */

		 else if ( strcmp( ComandoTeste , REMOVE_PC_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "ci" ,
                                &cor, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PECC_RemoverPecaCapturada( cor ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado Destruir Peca capturada." );

         } /* fim ativa: Testar PECC Remover peca capturada */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: PECC Efetuar opera��es de teste espec�ficas para peca capturada */


/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/
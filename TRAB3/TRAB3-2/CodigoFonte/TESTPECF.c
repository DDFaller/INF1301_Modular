
/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTPECF.C
*  Letras identificadoras:      TPECF
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
*       1.00   JP   10/06/2019 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este modulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo pe�a finalizada. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo pe�a:
*
*     "=criar"         - chama a fun��o PECF_CriarPecaFinalizada( )
*     "=destroi"	   - chama a fun��o PECF_ResetarPecaFinalizada( )
*     "=adicionar"     - chama a fun��o PECF_AdicionaFinaliada( ) 
*     "=contar"        - chama a fun��o PECF_ObterQuantidadeLisPF( ) e retorna 
*							por referencia o valor da cor da pe�a
*
***************************************************************************/
#include    <string.h>
#include    <stdio.h>
#include	<stdlib.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "PecaFinalizada.h"
#include    "Peca.H"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define      CRIAR_PF_CMD       "=criar"
#define      DESTRUIR_PF_CMD    "=destruir"
#define      CONTAR_PF_CMD 	    "=contar"
#define      INSERIR_PF_CMD 	"=adicionar"

int ind = 0 ;
PEC_tpPeca *pPeca[20];


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TPEC Efetuar opera��es de teste espec�ficas para peca
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     peca sendo testado.
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

      PECF_tpCondRet CondRetObtido   = PECF_CondRetOK ;
      PECF_tpCondRet CondRetEsperada = PECF_CondRetOK ;
                                      /* inicializa para qualquer coisa */
      int ValorEsperado =  0   ;
      char ValorObtido   = '!'  ;
      char cor           = ' '  ;
      int  indice        =  0   ;
	  int  ValorPart     = NULL ;

      int  NumLidos = -1 ;

	  TST_tpCondRet Ret ;

      /* Testar PECF Criar peca */

         if ( strcmp( ComandoTeste , CRIAR_PF_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "i" ,
                                &CondRetEsperada ) ;
         
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PECF_CriarPecaFinalizada() ;
     
				/* acrescento no indice para quando for colocar outra pe�a n�o substituir a anterior */

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao Criar Peca Finalizada." );

         } /* fim ativa: Testar PECF criar peca finalizada */
		  
	/* Testar PECF Destroi peca finalizada */

         else if ( strcmp( ComandoTeste , DESTRUIR_PF_CMD ) == 0 )
         {
          NumLidos = LER_LerParametros( "i" ,
                                &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PECF_ResetarPecaFinalizada() ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado Destruir Peca finalizada." );

         } /* fim ativa: Testar PECF Destroi peca finalizada */

      /* Testar PECF obter quantidade de pecas finalizadas */

		 else if ( strcmp( ComandoTeste , CONTAR_PF_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "cii" ,
                                &cor, &ValorEsperado, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PECF_ObterQuantidadeLisPF(cor, &ValorPart ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao obter valor da partida." );

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararInt( ValorEsperado , ValorPart ,
                                     "Conteudo da peca esta errado." ) ;

         } /* fim ativa: Testar PECF obter quantidade de pecas finalizadas */

	/* Testar PECF Adicionar peca finalizada */

         else if ( strcmp( ComandoTeste , INSERIR_PF_CMD ) == 0 ){
			 
			 NumLidos = LER_LerParametros( "i" ,
                              &CondRetEsperada ) ;
			 if ( NumLidos != 1 )
             {
                return TST_CondRetParm ;
             } /* if */

			 PEC_CriarPeca(&pPeca[ind], 'b');

             CondRetObtido = PECF_AdicionaPecaFinalizada(pPeca[ind]) ;
			 ind+=1;	

             return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                     "Retorno errado Adicionar Peca finalizada." );

          } /* fim ativa: Testar PECF Adicionar peca finalizada */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: PECF Efetuar opera��es de teste espec�ficas para peca finalizada */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/
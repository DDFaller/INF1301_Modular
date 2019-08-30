/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTDAP.C
*  Letras identificadoras:      TDAP
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: JP - Jéssica Pereira Cesario
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   JP   2/04/2019 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este modulo contém as funções específicas para o teste do
*     módulo dadoPontos. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo dadoPontos:
*
*     "=criar"      - chama a função DAP_CriaDadoPontos( )
*     "=destroi"    - chama a função DAP_DestruirDadoPontos( )
*     "=obter"      - chama a função DAP_ObterValorPartida( ) e retorna
*                     por referencia o valor da partida.
*     "=dobrar"     - chama a função DAP_DobrarPontuacao( )
*                     e dobra o valor da partida.
*
***************************************************************************/
#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "DadoPontos.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_DADO_CMD      "=criar"
#define     DESTROI_CMD         "=destruir"
#define     OBTER_VAL_PAR       "=obter"
#define     DOBRA_VAL_CMD       "=dobrar"

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TDAD Efetuar operações de teste específicas para DadoPontos
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     DadoPontos sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      DAP_tpCondRet CondRetObtido   = DAP_CondRetOK ;
      DAP_tpCondRet CondRetEsperada = DAP_CondRetOK ;
                                      /* inicializa para qualquer coisa */

      int ValorEsperado = 0  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;
	  int  ValorPart     = NULL ;

      int  NumLidos = -1 ;

	  TST_tpCondRet Ret ;
      /* Testar DAP Criar dadoPontos */

         if ( strcmp( ComandoTeste , CRIAR_DADO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DAP_CriaDadoPontos() ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao Criar Dado Pontos." );

         } /* fim ativa: Testar DAP criar dadoPontos */

	 /* Testar DAP Destroi Dado Pontos */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DAP_DestruirDadoPontos() ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado Destroi Dado Pontos." );

         } /* fim ativa: Testar DAP Destroi dadoPontos */

      /* Testar DAP obter valor partida */

         else if ( strcmp( ComandoTeste , OBTER_VAL_PAR ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &ValorEsperado, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DAP_ObterValorPartida( &ValorPart ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao obter valor da partida." );

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararInt( ValorEsperado , ValorPart ,
                                     "Conteúdo da peça está errado." ) ;

         } /* fim ativa: Testar DAP obter valor partida */

      /* Testar  DAP dobrar valor do Dado Pontos */

         else if ( strcmp( ComandoTeste , DOBRA_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ci" ,
                               &ValorDado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DAP_DobrarPontuacao( ValorDado );

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao dobrar valor do Dado Pontos." );

         } /* fim ativa: DAP dobrar valor do Dado Pontos */
     
      return TST_CondRetNaoConhec ;

   } /* Fim função: TDAP Efetuar operações de teste específicas para Dado Pontos*/

/********** Fim do módulo de implementação: Módulo de teste específico **********/

/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTPEC.C
*  Letras identificadoras:      TPEC
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Jogo de Gamão - Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: JP - Jéssica Pereira Cesario
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   JP   28/04/2019 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este modulo contém as funções específicas para o teste do
*     módulo peça. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo peça:
*
*     "=criar"         - chama a função PECC_CriarPecaCapturada( )
*     "=destroi"	   - chama a função PECC_ResetarPecaCapturada( )
*     "=adicionar"     - chama a função PECC_AdicionaPecaCapturada( ) 
*     "=contar"        - chama a função PECC_ObterQuantidadeLisPC( ) e retorna 
*							por referencia o valor da cor da peça
*     "=remover"       - chama a função PECC_RemoverPecaCapturada( )
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

/* Tabela dos nomes dos comandos de teste específicos */

#define      CRIAR_PC_CMD       "=criar"
#define      DESTRUIR_PC_CMD    "=destruir"
#define      REMOVE_PC_CMD 		"=remover"
#define      CONTAR_PC_CMD 	    "=contar"
#define      INSERIR_PC_CMD 	"=adicionar"


int ind = 0 ;
PEC_tpPeca *pPeca[20];

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TPECC Efetuar operações de teste específicas para peca capturada
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     peca capturada sendo testado.
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

   } /* Fim função: PECC Efetuar operações de teste específicas para peca capturada */


/********** Fim do módulo de implementação: Módulo de teste específico **********/
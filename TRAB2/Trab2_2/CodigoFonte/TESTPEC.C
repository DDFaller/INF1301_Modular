
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
*     "=criar"      - chama a função PEC_CriarPeca( )
*     "=destroi"    - chama a função PEC_DestruirPeca( )
*     "=obter"        - chama a função PEC_ObterCorPeca( ) e retorna 
*                      por referencia o valor da cor da peça
*      "=mudar"        - chama a função PEC_MudarEstadoPeca( )
*      "=exibir"        - chama a função PEC_ExibePeca( )
*
***************************************************************************/
#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "Peca.H"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_PECA_CMD      "=criar"
#define     DESTROI_CMD         "=destruir"
#define     OBTER_COR_CMD       "=obter"
#define     MUDAR_EST_CMD       "=mudar"
#define     EXIBIR_PEC_CMD      "=exibir"

int indPeca =  0 ;
PEC_tpPeca * pPeca[10];
	/*vetor para teste*/


/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TPEC Efetuar operações de teste específicas para peca
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     peca sendo testado.
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

      PEC_tpCondRet CondRetObtido   = PEC_CondRetOK ;
      PEC_tpCondRet CondRetEsperada = PEC_CondRetOK ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char cor           = ' '  ;
      int  indice        =  0   ;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;
      /* Testar DAP Criar dadoPontos */


      /* Testar PEC Criar peca */

         if ( strcmp( ComandoTeste , CRIAR_PECA_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "ci" ,
                               &cor, &CondRetEsperada ) ;
         
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PEC_CriarPeca( &pPeca[indPeca], cor) ;
            indPeca+=1;
				/* acrescento no indice para quando for colocar outra peça não substituir a anterior */

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao Criar Peca." );

         } /* fim ativa: Testar PEC criar peca */

       /* Testar PEC Destroi peca */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {
          NumLidos = LER_LerParametros( "ii" ,
                               &indice, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PEC_DestruirPeca( &pPeca[indice] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado Destruir Peca." );

         } /* fim ativa: Testar PEC Destroi peca */

      /* Testar PEC Obter Cor Peca */

         else if ( strcmp( ComandoTeste , OBTER_COR_CMD ) == 0 ){

            NumLidos = LER_LerParametros( "cii" ,
                               &ValorEsperado, &indice, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PEC_ObterCorPeca(&pPeca[indice], &cor ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao Obter Cor Peca." );

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararChar( ValorEsperado , cor ,
                                     "Conteudo da peca esta errado." ) ;

         } /* fim ativa: Testar PEC Obter Cor Peca */
	
	/* Testar PEC Mudar Estado Peca */

         else if ( strcmp( ComandoTeste , MUDAR_EST_CMD ) == 0 ){

            NumLidos = LER_LerParametros( "ii" ,
                               &indice, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PEC_MudarEstadoPeca( &pPeca[indice] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao Mudar Estado Peca." );

         } /* fim ativa: Testar PEC Mudar estado peça */

    /* Testar PEC Exibe Peca */

         else if ( strcmp( ComandoTeste , EXIBIR_PEC_CMD ) == 0 ){

            NumLidos = LER_LerParametros( "ii" ,
                               &indice, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PEC_ExibePeca( &pPeca[indice] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao Exibe Peca." );

         } /* fim ativa: Testar PEC Exibe Peca */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TPEC Efetuar operações de teste específicas para peca */

/********** Fim do módulo de implementação: Módulo de teste específico **********/
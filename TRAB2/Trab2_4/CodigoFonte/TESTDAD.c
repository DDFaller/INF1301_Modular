/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTDAD.C
*  Letras identificadoras:      TDAD
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
*       1.00   JP   5/05/2019 Documentação
*		1.00   
*
*  $ED Descrição do módulo
*     Este modulo contém uma função específicaa para o teste do
*     módulo dado. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo dado:
*
*     ""=rolar""      - chama a função DAD_RolarDados( )
*
***************************************************************************/
#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "Dado.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define     ROLAR_DAD_CMD       "=rolar"

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TARV Efetuar operações de teste específicas para árvore
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     árvore sendo testado.
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

   } /* Fim função: TDAD Efetuar operações de teste específicas para Dado */

/********** Fim do módulo de implementação: Módulo de teste específico **********/
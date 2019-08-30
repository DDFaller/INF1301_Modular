#if ! defined( DadoPontos_ )
#define DadoPontos_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo DadoPontos
*
*  Arquivo gerado:              DadoPontos.h
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
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     explorar uma estrutura.
*	  A Dado pontos possui um ponteiro que cont�m uma refer�ncia para o dado pontos
*     A Dado pontos possui  o jogodor que dobrou na ultima rodada e a pontua��o atual da partida.
*     A cada momento o m�dulo admite apenas um dado pontos.
*     Ao iniciar a execu��o do programa n�o exeiste o dado pontos.
*     O dado pontos � iniciado com o valor 1, segundo as regras do jogo.
*     O jogador � iniciado pelo valor 0 no come�o da partida, j� que nenhum jogador dobrou ainda.
*
***************************************************************************/

#if defined( DadoPontos_OWN )
   #define DadoPontos_EXT
#else
   #define DadoPontos_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: DAP Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         DAP_CondRetOK = 0 ,
               /* Executou correto */

         DAP_CondRetDadoPontosNaoExiste = 1 ,
               /* Dado pontos n�o existe */

         DAP_CondRetFaltouMemoria = 2 ,
               /* Faltou mem�ria ao alocar dados */

		 DAP_CondRetPontuacaoMaxima = 3 ,
			      /* Alcan�ou a condi��o m�xima da partida */

		 DAP_CondRetNaoPodeDobrar = 4
			     /* Jogador n�o pode dobrar, dobrou na �ltima partida */

   } DAP_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: DAP Criar Dado Pontos
*
*  $ED Descri��o da fun��o
*     Cria um dado pontos.
*     Caso j� exista um dado, esse ser� destru�do.
*
*  $FV Valor retornado
*     DAP_CondRetOK
*     DAP_CondRetFaltouMemoria
*
***********************************************************************/

/* $AE Assertivas de entrada DAP_CriaDadoPontos
*	  Tem que existir mem�ria para cria��o do dado pontos.    
*
*  Fim Assertivas de Entrada DAP_CriaDadoPontos */

   DAP_tpCondRet DAP_CriaDadoPontos ( void ) ;

/* $AS Assertivas de Saida DAP_CriaDadoPontos
*	  A memoria referente ao pDadoPontos tem que ser alocada. 
*	  Para o dado pontos criado ValorPartida = 1 e JogadorDobra = 0.
*	  A fun��o retorna DAP_CondRet.
*
*  Fim Assertiva de Saida DAP_CriaDadoPontos */

/***********************************************************************
*
*  $FC Fun��o: DAP Destruir dado pontos
*
*  $ED Descri��o da fun��o
*     Destr�i o dado pontos.
*     Faz nada caso o dado pontos n�o exista.
*
*  $FV Valor retornado
*     DAP_CondRetOK
*     DAP_CondRetDadoPontosNaoExiste
*
***********************************************************************/

/* $AE Assertivas de entrada DAP_DestruirDadoPontos
*     Tem que existir um dado pontos para ser destru�do. (pDadoPontos != NULL)
*
* Fim Aseertivas de Entrada DAP_DestruirDadoPontos */

   DAP_tpCondRet DAP_DestruirDadoPontos( void ) ;

/* $AS Assertivas de Saida DAP_DestruirDadoPontos
*     O dado pontos deve ser excluido.
*     A fun��o retorna DAP_CondRet.
*
* Fim Assertiva de Saida DAP_DestruirDadoPontos */

/***********************************************************************
*
*  $FC Fun��o: DAP dobra a pontua��o do dado pontos, caso o jogador que 
*				   solicitou possa fazer essa proposta.
*
*  $EP Par�metros
*     $P ValorParm - jogador que solicitou que os pontos sejam dobrados.
*
*  $FV Valor retornado
*     DAP_CondRetOK
*     DAP_CondRetPontuacaoMaxima
*     DAP_CondRetDadoPontosNaoExiste
*     DAP_CondRetNaoPodeDobrar    
*
***********************************************************************/

/* $AE Assertivas de entrada DAP_DobrarPontuacao
*     O jogador que solicitou a dobra tem que ser diferente daquele que
*     dobrou pela ultima vez. (JogadorDobra != jogador)
*
* Fim Aseertivas de Entrada DAP_DobrarPontuacao */

   DAP_tpCondRet DAP_DobrarPontuacao( char ValorParm ) ;

/* $AS Assertivas de Saida DAP_DobrarPontuacao
*     O dado pontos devera ser dobrado. (ValorPartida *= 2)
*     A fun��o retorna DAP_CondRet.
*
* Fim Assertiva de Saida DAP_DobrarPontuacao */

/***********************************************************************
*
*  $FC Fun��o: DAP obtem o valor da partida 
*
*  $EP Par�metros
*     $P ValorParm - campo que ser� retornado por referencia o atual valor
*	                 da partida.
*
*  $FV Valor retornado
*     DAP_CondRetOK
*     DAP_CondRetDadoPontosNaoExiste
*
***********************************************************************/

/* $AE Assertivas de entrada DAP_ObterValorPartida
*     Existe um dado armazenando o valor da partida. (pDadoPontos != NULL)
*
* Fim Aseertivas de Entrada DAP_ObterValorPartida */

   DAP_tpCondRet DAP_ObterValorPartida ( int *ValorParm ) ;

/* $AS Assertivas de Saida DAP_ObterValorPartida
*     O valor da partida � passado por referencia para a variavel pontuacao.
*     A fun��o retorna DAP_CondRet.
*
* Fim Assertiva de Saida DAP_ObterValorPartida */

#undef DadoPontos_EXT

/********** Fim do m�dulo de defini��o: M�dulo DadoPontos **********/

#else
#endif

#if ! defined( DadoPontos_ )
#define DadoPontos_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo DadoPontos
*
*  Arquivo gerado:              DadoPontos.h
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
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar uma estrutura.
*	  A Dado pontos possui um ponteiro que contém uma referência para o dado pontos
*     A Dado pontos possui  o jogodor que dobrou na ultima rodada e a pontuação atual da partida.
*     A cada momento o módulo admite apenas um dado pontos.
*     Ao iniciar a execução do programa não exeiste o dado pontos.
*     O dado pontos é iniciado com o valor 1, segundo as regras do jogo.
*     O jogador é iniciado pelo valor 0 no começo da partida, já que nenhum jogador dobrou ainda.
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
               /* Dado pontos não existe */

         DAP_CondRetFaltouMemoria = 2 ,
               /* Faltou memória ao alocar dados */

		 DAP_CondRetPontuacaoMaxima = 3 ,
			      /* Alcançou a condição máxima da partida */

		 DAP_CondRetNaoPodeDobrar = 4
			     /* Jogador não pode dobrar, dobrou na última partida */

   } DAP_tpCondRet ;


/***********************************************************************
*
*  $FC Função: DAP Criar Dado Pontos
*
*  $ED Descrição da função
*     Cria um dado pontos.
*     Caso já exista um dado, esse será destruído.
*
*  $FV Valor retornado
*     DAP_CondRetOK
*     DAP_CondRetFaltouMemoria
*
***********************************************************************/

/* $AE Assertivas de entrada DAP_CriaDadoPontos
*	  Tem que existir memória para criação do dado pontos.    
*
*  Fim Assertivas de Entrada DAP_CriaDadoPontos */

   DAP_tpCondRet DAP_CriaDadoPontos ( void ) ;

/* $AS Assertivas de Saida DAP_CriaDadoPontos
*	  A memoria referente ao pDadoPontos tem que ser alocada. 
*	  Para o dado pontos criado ValorPartida = 1 e JogadorDobra = 0.
*	  A função retorna DAP_CondRet.
*
*  Fim Assertiva de Saida DAP_CriaDadoPontos */

/***********************************************************************
*
*  $FC Função: DAP Destruir dado pontos
*
*  $ED Descrição da função
*     Destrói o dado pontos.
*     Faz nada caso o dado pontos não exista.
*
*  $FV Valor retornado
*     DAP_CondRetOK
*     DAP_CondRetDadoPontosNaoExiste
*
***********************************************************************/

/* $AE Assertivas de entrada DAP_DestruirDadoPontos
*     Tem que existir um dado pontos para ser destruído. (pDadoPontos != NULL)
*
* Fim Aseertivas de Entrada DAP_DestruirDadoPontos */

   DAP_tpCondRet DAP_DestruirDadoPontos( void ) ;

/* $AS Assertivas de Saida DAP_DestruirDadoPontos
*     O dado pontos deve ser excluido.
*     A função retorna DAP_CondRet.
*
* Fim Assertiva de Saida DAP_DestruirDadoPontos */

/***********************************************************************
*
*  $FC Função: DAP dobra a pontuação do dado pontos, caso o jogador que 
*				   solicitou possa fazer essa proposta.
*
*  $EP Parâmetros
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
*     A função retorna DAP_CondRet.
*
* Fim Assertiva de Saida DAP_DobrarPontuacao */

/***********************************************************************
*
*  $FC Função: DAP obtem o valor da partida 
*
*  $EP Parâmetros
*     $P ValorParm - campo que será retornado por referencia o atual valor
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
*     O valor da partida é passado por referencia para a variavel pontuacao.
*     A função retorna DAP_CondRet.
*
* Fim Assertiva de Saida DAP_ObterValorPartida */

#undef DadoPontos_EXT

/********** Fim do módulo de definição: Módulo DadoPontos **********/

#else
#endif

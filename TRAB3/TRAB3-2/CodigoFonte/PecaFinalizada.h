#if ! defined( PECF_ )
#define PECF_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Peças Finalizadas
*
*  Arquivo gerado:              PecasFinalizadas.h
*  Letras identificadoras:      PECF
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
*       1.00   JP   25/04/2019 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar uma estrutura.
*     A Peca finalizada possui uma cor p (preta) ou b (branca), uma lista com todas as peças brancas e 
*	  outra com as peças pretas e o tamanho de cada lista
*     Ao iniciar a execução do programa não existe nenhuma peca finalizada, mas ao decorrer do jogo
*     podem existir muitas peças.
*
***************************************************************************/

#if defined( PECF_OWN )
   #define PECF_EXT
#else
   #define PECF_EXT extern
#endif

typedef struct tgPecaF PECF_tpPecaF;
#include   "Peca.H"

/***********************************************************************
*
*  $TC Tipo de dados: PECF Condições de retorno
*
***********************************************************************/

   typedef enum {

        PECF_CondRetOK = 0 ,
               /* Executou correto */

        PECF_CondRetPecaFinalizadaNaoExiste = 1 ,
               /* Peça não existe */

        PECF_CondRetFaltouMemoria = 2 ,
               /* Faltou memória ao alocar dados */
		
		PECF_CondRetNaoEPecaFinalizada = 3 ,
    			     /* Não é peça, o que significa que 
    			     *  o caracter verificado não é p nem b */
    	PECF_CondRetLimiteDePecaFinalizada = 4,

    	PECF_CondRetErro = 5

   } PECF_tpCondRet ;

/***********************************************************************
*
*  $FC Função: PECF Criar Peca
*
*  $ED Descrição da função
*     Cria duas listas de pecas finalizadas.
*
*  $FV Valor retornado
*     PECF_CondRetOK
*     PECF_CondRetFaltouMemoria
*
***********************************************************************/

/* $AE Assertivas de entrada PECF_CriarPecaFinalizada
*   Tem que existir memória para criação da peça finalizada. 
*   A Cor enviada tem que ser p ou b   
*
*  Fim Assertivas de Entrada PECF_CriarPecaFinalizada */

   PECF_tpCondRet PECF_CriarPecaFinalizada ( void ) ;

/* $AS Assertivas de Saida PECF_CriarPecaFinalizada
*   A memoria referente ao pPecaF tem que ser alocada. 
*   Para a peca finalizada criada CorPeca == cor.
*   quant = 0 
*   A função retorna PECF_CondRet.
*
*  Fim Assertiva de Saida PECF_CriarPecaFinalizada */

/***********************************************************************
*
*  $FC Função: PECF Adiciona Peca
*
*  $ED Descrição da função
*     Adiciona uma peça finalizada a lista de peças finalizadas.
*     Faz nada caso a peça não exista.
*
*  $EP Parâmetros
*     $P pPeca - ponteiro para a peça a ser adicionada na lista de peças finalizadas.
*
*  $FV Valor retornado
*     PECF_CondRetOK
*	  PECF_CondRetLimiteDePecaFinalizada
*     PECF_CondRetPecaFinalizadaNaoExiste
*
***********************************************************************/

/* $AE Assertivas de entrada PECF_AdicionaPecaFinalizada
*   Tem que existir um peça a ser Adicionada (pPeca != NULL)  
*
*  Fim Assertivas de Entrada PECF_AdicionaPecaFinalizada */

   PECF_tpCondRet PECF_AdicionaPecaFinalizada( PEC_tpPeca *pPeca );

/* $AS Assertivas de Saida PECF_AdicionaPecaFinalizada
*   A peça tem que ser adicionada a lista.  
*   A função retorna PECF_CondRet.
*
*  Fim Assertiva de Saida PECF_AdicionaPecaFinalizada */

/***********************************************************************
*
*  $FC Função: PECF Resetar Peças Finalizadas
*
*  $ED Descrição da função
*     Resetar a lista de peças finalizadas
*
*  $EP Parâmetros
*     $P corPeca    - a cor do jogador para saber quantas peças finalizadas ele tem.
*	  $P ObterValor - compo que sera retornado a quantidade de peças finalizadas que tem.
*
*  $FV Valor retornado
*     PECF_CondRetOK
*     PECF_CondRetPecaFinalizadaNaoExiste
*
***********************************************************************/

/* $AE Assertivas de entrada PECF_ObterQuantidadeLisPF
*   Tem que existir uma lista de peças finalizadas
*
*  Fim Assertivas de Entrada PECF_ObterQuantidadeLisPF */

   PECF_tpCondRet PECF_ObterQuantidadeLisPF ( char corPeca, int *ObterValor ) ; 

/* $AS Assertivas de Saida PECF_ObterQuantidadeLisPF
*   A quantidade de peças tem que ser devolvida
*   A função retorna PECF_CondRet.
*
*  Fim Assertiva de Saida PECF_ObterQuantidadeLisPF */


/***********************************************************************
*
*  $FC Função: PECF Resetar Peças Finalizadas
*
*  $ED Descrição da função
*     Resetar a lista de peças finalizadas
*
*  $FV Valor retornado
*     PECF_CondRetOK
*     PECF_CondRetPecaFinalizadaNaoExiste
*
***********************************************************************/

/* $AE Assertivas de entrada PECF_ResetarPecaFinalizada
*   Tem que existir uma peça a ser resetada (pPecaF != NULL) e tem que 
*	existir um elemento na lista 
*
*  Fim Assertivas de Entrada PECF_ResetarPecaFinalizada */

   PECF_tpCondRet PECF_ResetarPecaFinalizada ( ) ; 

/* $AS Assertivas de Saida PECF_ResetarPecaFinalizada
*   A lista tem que ser resetada.
*   A função retorna PECF_CondRet.
*
*  Fim Assertiva de Saida PECF_ResetarPecaFinalizada */

#undef PECF_EXT

/********** Fim do módulo de definição: Módulo Peca Finalizada **********/

#else
#endif

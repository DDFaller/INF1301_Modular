#if ! defined( PECC_ )
#define PECC_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Peças Capturadas
*
*  Arquivo gerado:              PecasCapturadas.h
*  Letras identificadoras:      PECC
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
*     A Peca capturada possui uma cor p (preta) ou b (branca), uma lista com todas as peças brancas e 
*	    outra com as peças pretas e o tamanho de cada lista
*     Ao iniciar a execução do programa não existe nenhuma peca capturada, mas ao decorrer do jogo
*     podem existir muitas peças.
*
***************************************************************************/

#if defined( PECC_OWN )
   #define PECC_EXT
#else
   #define PECC_EXT extern
#endif

#include   "Peca.H"
typedef struct tgPecaC PECC_tpPecaC;


/***********************************************************************
*
*  $TC Tipo de dados: PECC Condições de retorno
*
***********************************************************************/

   typedef enum {

        PECC_CondRetOK = 0 ,
               /* Executou correto */

        PECC_CondRetPecaCapturadaNaoExiste = 1 ,
               /* Peça não existe */

        PECC_CondRetFaltouMemoria = 2 ,
               /* Faltou memória ao alocar dados */

    		PECC_CondRetNaoEPecaCapturada = 3 ,
    			     /* Não é peça, o que significa que 
    			     *  o caracter verificado não é p nem b */
    		PECC_CondRetLimiteDePecaCapturada = 4,

    		PECC_CondRetErro = 5

   } PECC_tpCondRet ;

/***********************************************************************
*
*  $FC Função: PECC Criar Peca
*
*  $ED Descrição da função
*     Cria uma peca capturada.
*     Se o valor da cor é diferente de p ou b não cria.
*
*  $EP Parâmetros
*     $P pPecaC - ponteiro para a criação de uma peça capturada.
*     $P valorParm - cor que será atribuida a peça que sera criado.
*
*  $FV Valor retornado
*     PECC_CondRetOK
*     PECC_CondRetFaltouMemoria
*     PECC_CondRetNaoEPecaCapturada
*     PECC_CondRetLimiteDePecaCapturada
*
***********************************************************************/

/* $AE Assertivas de entrada PECC_CriarPecaCapturada
*   Tem que existir memória para criação da peça capturada. 
*   A Cor enviada tem que ser p ou b   
*
*  Fim Assertivas de Entrada PECC_CriarPecaCapturada */

   PECC_tpCondRet PECC_CriarPecaCapturada ( void );

/* $AS Assertivas de Saida PECC_CriarPecaCapturada
*   A memoria referente ao pPecaC tem que ser alocada. 
*   Para a peca capturada criada CorPeca == cor.
*   quant = 0 
*   A função retorna PECC_CondRet.
*
*  Fim Assertiva de Saida PECC_CriarPecaCapturada */

/***********************************************************************
*
*  $FC Função: PECC Adiciona Peca
*
*  $ED Descrição da função
*     Adiciona uma peça capturada a lista de peças capturada.
*     Faz nada caso a peça não exista.
*
*  $EP Parâmetros
*     $P pPecaC - ponteiro para a peça capturada a ser adicionada.
*
*  $FV Valor retornado
*     PECC_CondRetOK
*     PECC_CondRetPecaCapturadaNaoExiste
*
***********************************************************************/

/* $AE Assertivas de entrada PECC_AdicionaPeca
*   Tem que existir um peça a ser Adicionada (pPecaC != NULL)  
*
*  Fim Assertivas de Entrada PECC_AdicionaPeca */

   PECC_tpCondRet PECC_AdicionaPecaCapturada( PEC_tpPeca *pPeca ) ;

/* $AS Assertivas de Saida PECC_AdicionaPeca
*   A peça capturada tem que ser adicionada  
*   A função retorna PECC_CondRet.
*
*  Fim Assertiva de Saida PECC_AdicionaPeca */

/***********************************************************************
*
*  $FC Função: PECC obter quantidae de peças capturadas
*
*  $ED Descrição da função
*     Obtem o quantidade de peças ja adicionandas na lista de peças capturadas
*      e retorna essa quantidade por referencia.
*
*  $EP Parâmetros
*     $P pPecaC      - ponteiro para uma peça capturada.
*     $P valorParm   - campo que será retornado por referencia a quantidade de peças
*
*  $FV Valor retornado
*     PECC_CondRetOK
*     PECC_CondRetPecaCapturadaNaoExiste
*
***********************************************************************/

/* $AE Assertivas de entrada PECC_ObterQuantidadeLisPC
*     Existe uma peça. (pPecaC != NULL)
*     A quantidade é um inteiro de 0 a 15.
*
* Fim Aseertivas de Entrada PECC_ObterQuantidadeLisPC */

   PECC_tpCondRet PECC_ObterQuantidadeLisPC ( char cor , int *ObterValor ) ;

/* $AS Assertivas de Saida PECC_ObterQuantidadeLisPC
*     A quantidader é passado por referencia para a variavel valorParm.
*     A função retorna PECF_CondRet.
*
* Fim Assertiva de Saida PECC_ObterQuantidadeLisPC */

/***********************************************************************
*
*  $FC Função: PECC Remover Peças Capturadas
*
*  $ED Descrição da função
*     Remover a peça capturada da lista de peças capturadas.
*
*  $EP Parâmetros
*     $P pPecaC - ponteiro para a peça que sera retirada.
*
*  $FV Valor retornado
*     PECC_CondRetOK
*     PECC_CondRetErro
*     PECC_CondRetPecaCapturadaNaoExiste
*
***********************************************************************/

/* $AE Assertivas de entrada PECC_RemoverPecaCapturada
*   Tem que existir uma peça a ser removida (pPecaC -> quant != 0)
*
*  Fim Assertivas de Entrada PECC_RemoverPecaCapturada */

   PECC_tpCondRet PECC_RemoverPecaCapturada ( char cor ) ;

/* $AS Assertivas de Saida PECC_RemoverPecaCapturada
*   A peça tem que ser removida.
*   A função retorna PECC_CondRet.
*
*  Fim Assertiva de Saida PECC_RemoverPecaCapturada */

/***********************************************************************
*
*  $FC Função: PECC Remover Peças Capturadas
*
*  $ED Descrição da função
*     Remover a lista de peças capturadas
*
*  $EP Parâmetros
*     $P pPecaC - ponteiro para a peça que tera a lista resetada.
*
*  $FV Valor retornado
*     PECC_CondRetOK
*     PECC_CondRetPecaCapturadaNaoExiste
*
***********************************************************************/

/* $AE Assertivas de entrada PECC_ResetarPecaCapturada
*   Tem que existir uma peça a ser resetada (pPecaC != NULL) e tem que 
*   existir um elemento na lista 
*
*  Fim Assertivas de Entrada PECC_ResetarPecaCapturada */

   PECC_tpCondRet PECC_ResetarPecaCapturada( void ) ;

/* $AS Assertivas de Saida PECC_ResetarPecaCapturada
*   A lista tem que ser resetada.
*   A função retorna PECC_CondRet.
*
*  Fim Assertiva de Saida PECC_ResetarPecaCapturada */

#undef PECC_EXT

/********** Fim do módulo de definição: Módulo Peca Capturada **********/

#else
#endif





#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Peça
*
*  Arquivo gerado:              Peca.h
*  Letras identificadoras:      PEC
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
*     A Peca possui uma cor p (preta) ou b (branca)
*     Ao iniciar a execução do programa não exeiste o nenhuma peca, mas ao decorrer do jogo
*     podem existir muitas peças.
*
***************************************************************************/

#if defined( PECA_OWN )
   #define PECA_EXT
#else
   #define PECA_EXT extern
#endif

typedef struct tgPeca PEC_tpPeca;


/***********************************************************************
*
*  $TC Tipo de dados: PEC Condições de retorno
*
***********************************************************************/

   typedef enum {

        PEC_CondRetOK = 0 ,
               /* Executou correto */

        PEC_CondRetPecaNaoExiste = 1 ,
               /* Peça não existe */

        PEC_CondRetFaltouMemoria = 2 ,
               /* Faltou memória ao alocar dados */

		PEC_CondRetNaoEPeca = 3
			     /* Não é peça, o que significa que 
			     *  o caracter verificado não é p nem b 
			     */

   } PEC_tpCondRet ;

/***********************************************************************
*
*  $FC Função: PEC Criar Peca
*
*  $ED Descrição da função
*     Cria uma peca.
*	  Se o valor da cor é diferente de p ou b não cria
*
*  $EP Parâmetros
*     $P pPeca - ponteiro para a criação de uma peça.
*     $P valorParm - cor que será atribuida a nova peça criada.
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetFaltouMemoria
*     PEC_CondRetNaoEPeca
*
***********************************************************************/

/* $AE Assertivas de entrada PEC_CriarPeca
*   Tem que existir memória para criação da peça. 
*   A Cor enviada tem que ser p ou b   
*
*  Fim Assertivas de Entrada PEC_CriarPeca */

   PEC_tpCondRet PEC_CriarPeca ( PEC_tpPeca ** pPeca, char valorParm );

/* $AS Assertivas de Saida PEC_CriarPeca
*   A memoria referente ao pPeca tem que ser alocada. 
*   Para o peca criado CorPeca == cor.
*   A função retorna PEC_CondRet.
*
*  Fim Assertiva de Saida PEC_CriarPeca */

/***********************************************************************
*
*  $FC Função: PEC Destroi Peca
*
*  $ED Descrição da função
*     Destroi uma peça.
*     Faz nada caso a peça não exista.
*
*  $EP Parâmetros
*     $P pPeca - ponteiro para a peça a ser destruida.
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPecaNaoExiste
*
***********************************************************************/

/* $AE Assertivas de entrada PEC_DestruirPeca
*   Tem que existir um peça a ser destruida (pPeca != NULL)  
*
*  Fim Assertivas de Entrada PEC_DestruirPeca */

   PEC_tpCondRet PEC_DestruirPeca ( PEC_tpPeca ** pPeca ); 

/* $AS Assertivas de Saida PEC_DestruirPeca
*   A peça tem que ser destruida 
*   A função retorna PEC_CondRet.
*
*  Fim Assertiva de Saida PEC_DestruirPeca */

/***********************************************************************
*
*  $FC Função: PEC obtem o cor da peça
*
*  $ED Descrição da função
*     Obtem a cor da peça enviada por parametro e retorna
*     essa cor por referencia.
*
*  $EP Parâmetros
*     $P pPeca       - ponteiro para a criação de uma peça.
*     $P valorParm   - campo que será retornado por referencia a cor da peça
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPecaNaoExiste
*
***********************************************************************/

/* $AE Assertivas de entrada PEC_ObterCorPeca
*     Existe uma peça. (pPeca != NULL)
*     A cor da peça é p(preta) ou b(branca).
*
* Fim Aseertivas de Entrada PEC_ObterCorPeca */

   PEC_tpCondRet PEC_ObterCorPeca ( PEC_tpPeca ** pPeca, char *valorParm );

/* $AS Assertivas de Saida PEC_ObterCorPeca
*     A cor da peça é passado por referencia para a variavel ObterCor.
*     A função retorna PEC_CondRet.
*
* Fim Assertiva de Saida PEC_ObterCorPeca */

/***********************************************************************
*
*  $FC Função: PEC Mudar Estado Peça
*
*  $ED Descrição da função
*     Muda o estado de uma peça.
*     Faz nada caso a peça não exista.
*
*  $EP Parâmetros
*     $P pPeca - ponteiro para a peça que tera o estado modificado.
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPecaNaoExiste
*
***********************************************************************/

/* $AE Assertivas de entrada PEC_MudarEstadoPeca
*   Tem que existir um peça a ser modificada (pPeca != NULL)  
*
*  Fim Assertivas de Entrada PEC_MudarEstadoPeca */

   PEC_tpCondRet PEC_MudarEstadoPeca ( PEC_tpPeca ** pPeca ); 

/* $AS Assertivas de Saida PEC_MudarEstadoPeca
*   O estado tem que ser modificado.
*   A função retorna PEC_CondRet.
*
*  Fim Assertiva de Saida PEC_MudarEstadoPeca */

/***********************************************************************
*
*  $FC Função: PEC Exibe Peca
*
*  $ED Descrição da função
*     Exibe uma peça.
*     Faz nada caso a peça não exista.
*
*  $EP Parâmetros
*     $P pPeca - ponteiro para a peça a ser exibida.
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPecaNaoExiste
*
***********************************************************************/

/* $AE Assertivas de entrada PEC_ExibePeca
*   Tem que existir um peça a ser exibida (pPeca != NULL)  
*
*  Fim Assertivas de Entrada PEC_ExibePeca */

   PEC_tpCondRet PEC_ExibePeca ( PEC_tpPeca ** pPeca );

/* $AS Assertivas de Saida PEC_ExibePeca
*   A peça tem que ser exibida 
*   A função retorna PEC_CondRet.
*
*  Fim Assertiva de Saida PEC_ExibePeca */

#undef PECA_EXT

/********** Fim do módulo de definição: Módulo Peca **********/

#else
#endif

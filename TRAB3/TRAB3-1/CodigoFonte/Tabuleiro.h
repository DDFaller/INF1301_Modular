#if ! defined( TABULEIRO_ )
#define TABULEIRO_

#include "Peca.H"
/***************************************************************************
*
*  $MCD Módulo de definição: TAB Tabuleiro com listas encadeadas
*
*  Arquivo gerado:              Tabuleiro.h
*  Letras identificadoras:      TAB
*
*  Projeto: INF 1301			Desenvolvimento de um tabuleiro de gamão
*  Autores: df
*
*  $HA Histórico de evolução:
*
*  $ED Descrição do módulo
*     Criação e manipulação de um tabuleiro, utilizando uma implementação de listas duplamente encadeadas.
*     Existirá apenas um tabuleiro, utilizando uma variável interna.
*     O tabuleiro possui uma cabeça encapsulando o seu estado.
*	  Cada casa do tabuleiro utiliza listas duplamente encadeadas para salvar as n pecas contidas.
*
*     O tabuleiro conterá em cada elemento uma casa, que é definida por uma lista.
*     Cada elemento da casa conterá os elementos nela contidos, especificando a lista ao módulo peça.
*
*
***************************************************************************/


#if defined( TABULEIRO__OWN )
   #define TABULEIRO__EXT
#else
   #define TABULEIRO__EXT extern
#endif


typedef enum{
	TAB_CondRetOK				= 0 ,
		/* Concluiu corretamente */

    TAB_CondRetTABNExiste		= 2,
		/* Tabuleiro não foi previamente criado */

	TAB_CondRetCASVazio			= 3,
		/* Casas vazia */

	TAB_CondRetPosInvalida		= 4,
		/* Posição Inválida para peça */

	TAB_CondRetForaDosLimites	= 5,
		/* Posição fora dos limites [0,24] */

	TAB_CondRetFaltouMemoria	= 6,
		/* Erro na alocação de memória */

	TAB_CondRetPecaInvalida		= 7,
		/* Peca tem cor diferente do esperado */
	
	TAB_CondRetPecaFinalizada   = 8,
	    /* Peca foi finalizada */

	TAB_CondRetPecaCapturada
		/* Peca foi captura */
} TAB_tpCondRet;

/***********************************************************************
*
*  $FC Função: TAB & Adiciona Casa N
*
*  $ED Descrição da função
*     Insere o número de peças especificadas no tabuleiro
*
*  $PF:Parâmetros da função
*	   nPos: Casa onde as peças serão inseridas
*	   nElems: Número de peças
*	   ID:   Cor do player
*
* ¨$AE Assertivas de entrada
*	  Tabuleiro existe
*	  Posicao para as peças válida
*
************************************************************************/ 

TAB_tpCondRet AdicionaCasaN ( int nPos, int nElems, char ID ) ;

/************************************************************************
* ¨$AS Assertivas de Saída
*	  Pecas adicionadas ao tabuleiro
*  $FV Valor retornado
*		TAB_CondRetOK
*		TAB_CondRetFaltouMemória
*		TAB_CondRetPecaInvalida;
*
* Fim Assertiva de Saida TAB_AdicionaCasaN */

/***********************************************************************
/***********************************************************************
*
*  $FC Função: TAB & Cria Tabuleiro
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada, com 24 elementos, e 
*	  salva na variável interna tabuleiro.
*     Dentro de cada elemento do tabuleiro existirá outra lista duplamente 
*	  encadeada, inicializadas nesta função.
*     Cada elemento desta sublista salvará a peça.
*     Não existe identificador de tipo associados às listas.
*
* ¨$AE Assertivas de entrada
*	  Caso haja um tabuleiro previamente criado, esta função sobreescreve este
*
************************************************************************/ 

  TAB_tpCondRet TAB_CriaTabuleiro();

/************************************************************************
* ¨$AS Assertivas de Saída
*	  Gera o tabuleiro com as 24 casas através da lista duplamente encadeada.  
*  $FV Valor retornado
*		TAB_CondRetOK
*		TAB_CondRetFaltouMemória
*
* Fim Assertiva de Saida TAB_CriaTabuleiro */

/***********************************************************************
*
*  $FC Função: TAB & ExibeTabuleiro
*
*  $ED Descrição da função
*		Salva o tabuleiro dentro de um vetor de vetores
*
*  $FP Parâmetros da função
*		Ponteiro de ponteiro onde será retornado o tabuleiro  
*
*  $AE Assertivas de Entrada
*		Tabuleiro contendo 24 casas e as casas iniciais do Gamão ja preenchidas.
*
************************************************************************/ 

TAB_tpCondRet TAB_ExibeTabuleiro(char ** vetTab);

/************************************************************************
* ¨$AS Assertivas de Saída
*	  Estrutura do tabuleiro mantida
*	  Tabuleiro retornado
*  
*  $FV Valor retornado
*		TAB_CondRetOK
*
 Fim Assertiva de Saida TAB_ExibeTabuleiro */

/***********************************************************************
*
*  $FC Função: TAB & Mover Peça
*
*  $ED Descrição da função
*     Move uma peça ja existente no tabuleiro passando a cor da peça, 
*	  a posição de origem e a posição de destino 
*
*
*  $AE Assertivas de entrada
*	  Cor da peça precisa ser 'p' ou 'b'
*	  Posição de origem precisa conter uma peça da cor previamente citada
*	  Posição de destino precisa ser válida, ou seja, conter uma ou menos 
*	  peças de uma cor distinta
*
************************************************************************/

TAB_tpCondRet TAB_MoverPeca(char playerID,int origem,int destino, PEC_tpPeca ** peca, int * pecasJaFinalizadas);

/************************************************************************
* ¨$AS Assertivas de Saída
*	  Mantém a estrutura do tabuleiro correta, porém deslocando a peça 
*	  para o novo destino
*  
*  $FV Valor retornado
*		TAB_CondRetOK
*		TAB_CondRetTABNExiste
*		TAB_CondRetPosInvalida
*		TAB_CondRetForaDosLimites;
*
* Fim Assertiva de Saida TAB_MoverPeça 
 ***********************************************************************/
/***********************************************************************
*
*  $FC Função: TAB & Busca Checker
*
*  $ED Descrição da função
*     Avalia se é possivel fazer o movimento para finalizar as peças
*	  
*
*  $AE Assertivas de entrada
*	  Cor da peça precisa ser 'p' ou 'b'
*	  Posição de origem precisa conter uma peça da cor previamente citada
*	  Posição de destino precisa ser válida, ou seja, conter uma ou menos 
*	  peças de uma cor distinta
*
************************************************************************/

TAB_tpCondRet TAB_BuscaChecker(int * pretasBool, int * brancasBool, int * pecasJaFinalizadas);

/************************************************************************
* ¨$AS Assertivas de Saída
*	  Mantém a estrutura do tabuleiro correta, porém deslocando a peça 
*	  para o novo destino
*  
*  $FV Valor retornado
*		TAB_CondRetOK
*
* Fim Assertiva de Saida TAB_BuscaChecker
 ***********************************************************************/
/***********************************************************************
*
*  $FC Função: TAB & Existe Movimento
*
*  $ED Descrição da função
*		Avalia se é possivel mover uma peça no tabuleiro de determinado player
*
*  $AE Assertivas de entrada
*	   Tabuleiro precisa existir
*	   Cor do player válida
*		
************************************************************************/
TAB_tpCondRet TAB_ExisteMovimento( char playerCor, int * origem, int sentido);
/************************************************************************
* ¨$AS Assertivas de Saída
*	  Estrutura do tabuleiro mantida
*  
*  $FV Valor retornado
*		TAB_CondRetOK
*		TAB_CondRetPosInvalida
*
* Fim Assertiva de Saida TAB_ExisteMovimento
 ***********************************************************************/
/***********************************************************************
*
*  $FC Função: TAB & Cria Tabuleiro Vazio
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada, com 24 elementos, e 
*	  salva na variável interna tabuleiro.
*     Dentro de cada elemento do tabuleiro existirá outra lista duplamente 
*	  encadeada, inicializadas nesta função.
*     Cada elemento desta sublista salvará a peça.
*     Não existe identificador de tipo associados às listas.
*	  As listas internas das casas não são inicializadas
* ¨$AE Assertivas de entrada
*	  Caso haja um tabuleiro previamente criado, esta função sobreescreve este
*
************************************************************************/ 
TAB_tpCondRet TAB_CriaTabuleiroVazio( void );
/************************************************************************
* ¨$AS Assertivas de Saída
*	  Estrutura do tabuleiro criada e salva
*  
*  $FV Valor retornado
*		TAB_CondRetOK
*
* Fim Assertiva de Saida TAB_CriaTabuleiroVazio
 ***********************************************************************/



#undef TABULEIRO__EXT

/********** Fim do módulo de definição: TAB tabuleiro com listas encadeadas  **********/

#else
#endif

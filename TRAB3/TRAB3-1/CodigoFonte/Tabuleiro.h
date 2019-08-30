#if ! defined( TABULEIRO_ )
#define TABULEIRO_

#include "Peca.H"
/***************************************************************************
*
*  $MCD M�dulo de defini��o: TAB Tabuleiro com listas encadeadas
*
*  Arquivo gerado:              Tabuleiro.h
*  Letras identificadoras:      TAB
*
*  Projeto: INF 1301			Desenvolvimento de um tabuleiro de gam�o
*  Autores: df
*
*  $HA Hist�rico de evolu��o:
*
*  $ED Descri��o do m�dulo
*     Cria��o e manipula��o de um tabuleiro, utilizando uma implementa��o de listas duplamente encadeadas.
*     Existir� apenas um tabuleiro, utilizando uma vari�vel interna.
*     O tabuleiro possui uma cabe�a encapsulando o seu estado.
*	  Cada casa do tabuleiro utiliza listas duplamente encadeadas para salvar as n pecas contidas.
*
*     O tabuleiro conter� em cada elemento uma casa, que � definida por uma lista.
*     Cada elemento da casa conter� os elementos nela contidos, especificando a lista ao m�dulo pe�a.
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
		/* Tabuleiro n�o foi previamente criado */

	TAB_CondRetCASVazio			= 3,
		/* Casas vazia */

	TAB_CondRetPosInvalida		= 4,
		/* Posi��o Inv�lida para pe�a */

	TAB_CondRetForaDosLimites	= 5,
		/* Posi��o fora dos limites [0,24] */

	TAB_CondRetFaltouMemoria	= 6,
		/* Erro na aloca��o de mem�ria */

	TAB_CondRetPecaInvalida		= 7,
		/* Peca tem cor diferente do esperado */
	
	TAB_CondRetPecaFinalizada   = 8,
	    /* Peca foi finalizada */

	TAB_CondRetPecaCapturada
		/* Peca foi captura */
} TAB_tpCondRet;

/***********************************************************************
*
*  $FC Fun��o: TAB & Adiciona Casa N
*
*  $ED Descri��o da fun��o
*     Insere o n�mero de pe�as especificadas no tabuleiro
*
*  $PF:Par�metros da fun��o
*	   nPos: Casa onde as pe�as ser�o inseridas
*	   nElems: N�mero de pe�as
*	   ID:   Cor do player
*
* �$AE Assertivas de entrada
*	  Tabuleiro existe
*	  Posicao para as pe�as v�lida
*
************************************************************************/ 

TAB_tpCondRet AdicionaCasaN ( int nPos, int nElems, char ID ) ;

/************************************************************************
* �$AS Assertivas de Sa�da
*	  Pecas adicionadas ao tabuleiro
*  $FV Valor retornado
*		TAB_CondRetOK
*		TAB_CondRetFaltouMem�ria
*		TAB_CondRetPecaInvalida;
*
* Fim Assertiva de Saida TAB_AdicionaCasaN */

/***********************************************************************
/***********************************************************************
*
*  $FC Fun��o: TAB & Cria Tabuleiro
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada, com 24 elementos, e 
*	  salva na vari�vel interna tabuleiro.
*     Dentro de cada elemento do tabuleiro existir� outra lista duplamente 
*	  encadeada, inicializadas nesta fun��o.
*     Cada elemento desta sublista salvar� a pe�a.
*     N�o existe identificador de tipo associados �s listas.
*
* �$AE Assertivas de entrada
*	  Caso haja um tabuleiro previamente criado, esta fun��o sobreescreve este
*
************************************************************************/ 

  TAB_tpCondRet TAB_CriaTabuleiro();

/************************************************************************
* �$AS Assertivas de Sa�da
*	  Gera o tabuleiro com as 24 casas atrav�s da lista duplamente encadeada.  
*  $FV Valor retornado
*		TAB_CondRetOK
*		TAB_CondRetFaltouMem�ria
*
* Fim Assertiva de Saida TAB_CriaTabuleiro */

/***********************************************************************
*
*  $FC Fun��o: TAB & ExibeTabuleiro
*
*  $ED Descri��o da fun��o
*		Salva o tabuleiro dentro de um vetor de vetores
*
*  $FP Par�metros da fun��o
*		Ponteiro de ponteiro onde ser� retornado o tabuleiro  
*
*  $AE Assertivas de Entrada
*		Tabuleiro contendo 24 casas e as casas iniciais do Gam�o ja preenchidas.
*
************************************************************************/ 

TAB_tpCondRet TAB_ExibeTabuleiro(char ** vetTab);

/************************************************************************
* �$AS Assertivas de Sa�da
*	  Estrutura do tabuleiro mantida
*	  Tabuleiro retornado
*  
*  $FV Valor retornado
*		TAB_CondRetOK
*
 Fim Assertiva de Saida TAB_ExibeTabuleiro */

/***********************************************************************
*
*  $FC Fun��o: TAB & Mover Pe�a
*
*  $ED Descri��o da fun��o
*     Move uma pe�a ja existente no tabuleiro passando a cor da pe�a, 
*	  a posi��o de origem e a posi��o de destino 
*
*
*  $AE Assertivas de entrada
*	  Cor da pe�a precisa ser 'p' ou 'b'
*	  Posi��o de origem precisa conter uma pe�a da cor previamente citada
*	  Posi��o de destino precisa ser v�lida, ou seja, conter uma ou menos 
*	  pe�as de uma cor distinta
*
************************************************************************/

TAB_tpCondRet TAB_MoverPeca(char playerID,int origem,int destino, PEC_tpPeca ** peca, int * pecasJaFinalizadas);

/************************************************************************
* �$AS Assertivas de Sa�da
*	  Mant�m a estrutura do tabuleiro correta, por�m deslocando a pe�a 
*	  para o novo destino
*  
*  $FV Valor retornado
*		TAB_CondRetOK
*		TAB_CondRetTABNExiste
*		TAB_CondRetPosInvalida
*		TAB_CondRetForaDosLimites;
*
* Fim Assertiva de Saida TAB_MoverPe�a 
 ***********************************************************************/
/***********************************************************************
*
*  $FC Fun��o: TAB & Busca Checker
*
*  $ED Descri��o da fun��o
*     Avalia se � possivel fazer o movimento para finalizar as pe�as
*	  
*
*  $AE Assertivas de entrada
*	  Cor da pe�a precisa ser 'p' ou 'b'
*	  Posi��o de origem precisa conter uma pe�a da cor previamente citada
*	  Posi��o de destino precisa ser v�lida, ou seja, conter uma ou menos 
*	  pe�as de uma cor distinta
*
************************************************************************/

TAB_tpCondRet TAB_BuscaChecker(int * pretasBool, int * brancasBool, int * pecasJaFinalizadas);

/************************************************************************
* �$AS Assertivas de Sa�da
*	  Mant�m a estrutura do tabuleiro correta, por�m deslocando a pe�a 
*	  para o novo destino
*  
*  $FV Valor retornado
*		TAB_CondRetOK
*
* Fim Assertiva de Saida TAB_BuscaChecker
 ***********************************************************************/
/***********************************************************************
*
*  $FC Fun��o: TAB & Existe Movimento
*
*  $ED Descri��o da fun��o
*		Avalia se � possivel mover uma pe�a no tabuleiro de determinado player
*
*  $AE Assertivas de entrada
*	   Tabuleiro precisa existir
*	   Cor do player v�lida
*		
************************************************************************/
TAB_tpCondRet TAB_ExisteMovimento( char playerCor, int * origem, int sentido);
/************************************************************************
* �$AS Assertivas de Sa�da
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
*  $FC Fun��o: TAB & Cria Tabuleiro Vazio
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada, com 24 elementos, e 
*	  salva na vari�vel interna tabuleiro.
*     Dentro de cada elemento do tabuleiro existir� outra lista duplamente 
*	  encadeada, inicializadas nesta fun��o.
*     Cada elemento desta sublista salvar� a pe�a.
*     N�o existe identificador de tipo associados �s listas.
*	  As listas internas das casas n�o s�o inicializadas
* �$AE Assertivas de entrada
*	  Caso haja um tabuleiro previamente criado, esta fun��o sobreescreve este
*
************************************************************************/ 
TAB_tpCondRet TAB_CriaTabuleiroVazio( void );
/************************************************************************
* �$AS Assertivas de Sa�da
*	  Estrutura do tabuleiro criada e salva
*  
*  $FV Valor retornado
*		TAB_CondRetOK
*
* Fim Assertiva de Saida TAB_CriaTabuleiroVazio
 ***********************************************************************/



#undef TABULEIRO__EXT

/********** Fim do m�dulo de defini��o: TAB tabuleiro com listas encadeadas  **********/

#else
#endif

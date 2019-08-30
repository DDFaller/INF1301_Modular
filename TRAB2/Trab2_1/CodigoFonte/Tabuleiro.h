#if ! defined( Tabuleiro_ )
#define Tabuleiro_

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

#if defined( Tabuleiro_OWN )
   #define Tabuleiro_EXT
#else
   #define Tabuleiro_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do tabuleiro
*
***********************************************************************/

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

		TAB_CondRetPecaInvalida		= 7
			/* Peca tem cor diferente do esperado */

	} TAB_tpCondRet;

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
*		Exibe o tabuleiro percorrendo do primeiro elemento at� o �ltimo e 
*		printando a lista de pe�as dentro de cada casa
*
*  $AE Assertivas de Entrada
*		Tabuleiro contendo 24 casas e as casas iniciais do Gam�o ja preenchidas.
*
************************************************************************/ 

	TAB_tpCondRet TAB_ExibeTabuleiro();

/************************************************************************
* �$AS Assertivas de Sa�da
*	  N�o altera em nada a estrutura do tabuleiro, por�m a posii��o do Elemento
*	  corrente vai para a ultima casa do tabuleiro
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

	TAB_tpCondRet TAB_MoverPeca( char playerID, int origem, int destino ) ;

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

#undef Tabuleiro_EXT

/********** Fim do m�dulo de defini��o: TAB tabuleiro com listas encadeadas  **********/

#else
#endif

#if ! defined( Tabuleiro_ )
#define Tabuleiro_

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

#if defined( Tabuleiro_OWN )
   #define Tabuleiro_EXT
#else
   #define Tabuleiro_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do tabuleiro
*
***********************************************************************/

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

		TAB_CondRetPecaInvalida		= 7
			/* Peca tem cor diferente do esperado */

	} TAB_tpCondRet;

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
*		Exibe o tabuleiro percorrendo do primeiro elemento até o último e 
*		printando a lista de peças dentro de cada casa
*
*  $AE Assertivas de Entrada
*		Tabuleiro contendo 24 casas e as casas iniciais do Gamão ja preenchidas.
*
************************************************************************/ 

	TAB_tpCondRet TAB_ExibeTabuleiro();

/************************************************************************
* ¨$AS Assertivas de Saída
*	  Não altera em nada a estrutura do tabuleiro, porém a posiição do Elemento
*	  corrente vai para a ultima casa do tabuleiro
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

	TAB_tpCondRet TAB_MoverPeca( char playerID, int origem, int destino ) ;

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

#undef Tabuleiro_EXT

/********** Fim do módulo de definição: TAB tabuleiro com listas encadeadas  **********/

#else
#endif

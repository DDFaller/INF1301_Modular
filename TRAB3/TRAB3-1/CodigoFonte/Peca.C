
#include "Peca.H"
#include <stdio.h>
#include <malloc.h>

/***************************************************************************
*  $MCI Módulo de implementação: Módulo Peça
*
*  Arquivo gerado:              Peca.c
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
***************************************************************************/



/***********************************************************************
*
*  $TC Tipo de dados: PEC Descritor da peça.
*
*  $ED Descrição do tipo
*     Descreve uma estrutura de peça.
*
***********************************************************************/

	typedef struct tgPeca
	{
		char CorPeca;
			/* Cor da peca no jogo, pode ser preta ou branca
		    *
		    *$EED Assertivas estruturais
			*   É p se é da cor preta
			*   É b se é da cor branca  */
		int  estado;
			/* Estado que a peca se encontra, pode ser 0 ou 1
		    *
		    *$EED Assertivas estruturais
			*   É 1 se a peça esta no tabuleiro
			*   É 0 se a peça foi capturada  */

	} tpPeca;


/*****  Codigo das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: PEC Destruir Peca
*  ****/

	PEC_tpCondRet PEC_DestruirPeca ( tpPeca ** pPeca )
	{
		if ( (*pPeca) != NULL )
      	{	
			
			free( *pPeca ) ;
			*pPeca=NULL;

			return PEC_CondRetOK ; 
			
     	} /* if */

		return PEC_CondRetPecaNaoExiste ;
	
	} /* Fim função: PEC Destruir Peca */

/***************************************************************************
*
*  Função: PEC Criar Peca
*  ****/

   PEC_tpCondRet PEC_CriarPeca ( tpPeca ** pPeca, char cor )
   {
	   
   		//if( (*pPeca) != NULL)
   		//{
   		//	PEC_DestruirPeca (pPeca);
   		//} /* if */

		if ( cor != 'b' && cor != 'p')
      	{
			return PEC_CondRetNaoEPeca ;
     	} /* if */

   		*pPeca = ( tpPeca* ) malloc ( sizeof( tpPeca ));

	    if (* pPeca == NULL )
	    {
			return PEC_CondRetFaltouMemoria;
	    } /* if */
		
	    (*pPeca) -> CorPeca = cor;
	    (*pPeca) -> estado  = 1;

	    return PEC_CondRetOK;
   } /* Fim função: PEC Criar Peca */

/***************************************************************************
*
*  Função: PEC Obter Cor Peca
*  ****/

	PEC_tpCondRet PEC_ObterCorPeca ( tpPeca ** pPeca, char *ObterCor )
	{
		
		if ( (*pPeca) == NULL )
      	{
			return PEC_CondRetPecaNaoExiste ;
     	} /* if */

		*ObterCor = ( *pPeca ) -> CorPeca ;
		
		return PEC_CondRetOK ; 

	
	} /* Fim função: PEC Obter Cor Peca */

/***************************************************************************
*
*  Função: PEC Exibe Peca
*  ****/
	PEC_tpCondRet PEC_ExibePeca( tpPeca ** pPeca )
	{
		if ( (*pPeca) == NULL )
      	{
			return PEC_CondRetPecaNaoExiste ;
     	} /* if */
		
		printf("\nCor : %c, Estado : %d ->\n",( *pPeca ) -> CorPeca,( *pPeca ) -> estado);

		return PEC_CondRetOK;
	}/* Fim função: PEC Exibe Peca */

/***************************************************************************
*
*  Função: PEC Mudar estado Peca
*  ****/

	PEC_tpCondRet PEC_MudarEstadoPeca ( tpPeca ** pPeca )
	{
		
		if ( (*pPeca) == NULL )
      	{
			return PEC_CondRetPecaNaoExiste ;
     	} /* if */

		if ( (*pPeca) -> estado == 1 )
      	{
			 (*pPeca) -> estado = 0 ;
			 
     	} /* if */

      	return PEC_CondRetOK;
	}/* Fim função: PEC Mudar estado Peca */


/********** Fim do módulo de implementação: Módulo Peca **********/


/***************************************************************************
*  $MCI Módulo de implementação: PECC Peças Capturadas
*
*  Arquivo gerado:              PECC.c
*  Letras identificadoras:      PECC
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: JP - Jessica Pereira Cesario
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	   1.0		JP		06/06	 Começo do Desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <malloc.h>
#include   "LISTA.H"
#include   "Peca.H"

#define PECC_OWN
#include "PecasCapturadas.h"
#undef PECC_OWN


/***********************************************************************
*
*  $TC Tipo de dados: PECC Descritor da estrutura de Peças Capturadas
*
*  $ED Descrição do tipo
*     Descreve uma estrutura de peça Capturadas
*
***********************************************************************/

	typedef struct tgPecaC 
	{

		LIS_tppLista LisPecaCapturadaB ;
		/* Lista de Peças Capturadas brancas*/

		LIS_tppLista LisPecaCapturadaP ;
		/* Lista de Peças Capturadas pretas*/

		int quantB ;
		/* Número de elementos na lista de peças brancas */

		int quantP ;
		/* Número de elementos na lista de peças pretas */

	} tpPecaC ;

/*****  Dados encapsulados no módulo  *****/

	static tpPecaC *pPecaC = NULL;

/***** Protótipos das funções encapuladas no módulo *****/
	
	static void PECC_ExcluirValor (void * pdado);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PECC Criar Peca Capturada
*  ****/

	PECC_tpCondRet PECC_CriarPecaCapturada ( void )
	{
		pPecaC = ( tpPecaC* ) malloc (sizeof( tpPecaC ));

		if( pPecaC == NULL )
		{
			return PECC_CondRetFaltouMemoria ;
		}/* if */


		pPecaC -> quantP = 0 ;
		pPecaC -> quantB = 0 ;
		pPecaC -> LisPecaCapturadaB = LIS_CriarLista(PECC_ExcluirValor);
		pPecaC -> LisPecaCapturadaP = LIS_CriarLista(PECC_ExcluirValor);

		if (pPecaC  -> LisPecaCapturadaP == NULL || pPecaC  -> LisPecaCapturadaB == NULL)
		{
		   return PECC_CondRetFaltouMemoria;
		}/* if */

		return PECC_CondRetOK;

	}/* Fim função: PECC Criar Peca Capturada */

/***************************************************************************
*
*  Função: PECC Adiciona Peca Capturada
*  ****/
	PECC_tpCondRet PECC_AdicionaPecaCapturada( PEC_tpPeca *pPeca )
	{
		char cor ;
		PEC_ObterCorPeca(&pPeca,&cor);
		
		if ((pPecaC == NULL) || (pPeca == NULL))
		{
			return PECC_CondRetPecaCapturadaNaoExiste;
		}/* if */

		if (cor == 'b')
		{
			if(pPecaC->quantB == 15)
			{
				return PECC_CondRetLimiteDePecaCapturada;
			}/* if */

			LIS_InserirElementoApos(pPecaC->LisPecaCapturadaB, pPeca);
			pPecaC ->quantB += 1;
		}/* if */

		else
		{
			if(pPecaC->quantP == 15)
			{
				return PECC_CondRetLimiteDePecaCapturada;
			}/* if */

			LIS_InserirElementoApos(pPecaC->LisPecaCapturadaP, pPeca);
			pPecaC ->quantP += 1;
		}/* else */

		return PECC_CondRetOK;
	
}/* Fim função: PECC Criar Peca Capturada */


/***************************************************************************
*
*  Função: PECC Obter Quantidade Peca Capturada
*  ****/

	PECC_tpCondRet PECC_ObterQuantidadeLisPC ( char cor , int *ObterValor )
	{

		if ( pPecaC == NULL )
      	{
			return PECC_CondRetPecaCapturadaNaoExiste ;
     	} /* if */

		if (cor == 'b')
		{
			*ObterValor = pPecaC -> quantB ;
		} /* if */

		else 
		{
			*ObterValor = pPecaC -> quantP ;
		}/* else */

		return PECC_CondRetOK ;

	}/* Fim função: PECC Obter Quantidade Peca Capturada */

/***************************************************************************
*
*  Função: PECC Remover Peca Capturada
*  ****/

	PECC_tpCondRet PECC_RemoverPecaCapturada ( char cor )
	{
		if (cor == 'b')
		{
			if( pPecaC -> quantB == 0)
			{
				return PECC_CondRetPecaCapturadaNaoExiste ;
			} /* if */

			pPecaC -> quantB--;
			if(LIS_ExcluirElemento(pPecaC->LisPecaCapturadaB) != LIS_CondRetOK)
			{
				printf("Erro ao excluir peca da barra \n");
				return PECC_CondRetErro;
			}/* if */

		}/* if */

		if (cor == 'p')
		{
			if( pPecaC -> quantP == 0)
			{
				return PECC_CondRetPecaCapturadaNaoExiste ;
			} /* if */

			pPecaC -> quantP--;
			if(LIS_ExcluirElemento(pPecaC->LisPecaCapturadaP) != LIS_CondRetOK)
			{
				printf("Erro ao excluir peca da barra \n");
				return PECC_CondRetErro;
			}/* if */

		}/* if */
		
		return PECC_CondRetOK;
	}

/***************************************************************************
*
*  Função: PECC Resetar lista Peca Capturada
*  ****/

	PECC_tpCondRet PECC_ResetarPecaCapturada( void )
	{
		if ( pPecaC == NULL )
      	{
			return PECC_CondRetPecaCapturadaNaoExiste ;
     	} /* if */

		LIS_DestruirLista(pPecaC->LisPecaCapturadaB);
		LIS_DestruirLista(pPecaC->LisPecaCapturadaP);
		free(pPecaC);
		pPecaC = NULL;
		
		return PECC_CondRetOK ; 

	}/* Fim função: PECC Resetar Peca Capturada */

/***********************************************************************
*
*  $FC Função: PECF Excluir valor
*
*  $ED Descrição da função
*     Excluir o valor que é enviado.
*
*  $EP Parâmetros
*     $P pdado    - valor a ser excluido
*
***********************************************************************/

    void PECC_ExcluirValor (void * pdado)
 {
	 free(pdado);
 }

/********** Fim do módulo de implementação: Módulo Peca Capturada**********/


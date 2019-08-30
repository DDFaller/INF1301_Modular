/***************************************************************************
*  $MCI Módulo de implementação: PECF Peças Finalizadas
*
*  Arquivo gerado:              PECF.c
*  Letras identificadoras:      PECF
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: JP - Jessica Pereira Cesario
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
	   1.0		JP		31/05	 Começo do Desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <malloc.h>
#include   "LISTA.H"
#include   "Peca.H"

#define PECF_OWN
#include "PecaFinalizada.h"
#undef PECF_OWN


/***********************************************************************
*
*  $TC Tipo de dados: PECF Descritor da estrutura de peças finalizadas
*
*  $ED Descrição do tipo
*     Descreve uma estrutura de peça finalizada.
*
***********************************************************************/

	typedef struct tgPecaF 
	{

		LIS_tppLista LisPecaFinalizadaB ;
		/* Lista de Peças Finalizadas brancas*/

		LIS_tppLista LisPecaFinalizadaP ;
		/* Lista de Peças Finalizadas pretas*/

		int quantB ;
		/* Número de elementos na lista de peças brancas */

		int quantP ;
		/* Número de elementos na lista de peças pretas */

	} tpPecaF ;

/*****  Dados encapsulados no módulo  *****/

	static tpPecaF *pPecaF = NULL;

/***** Protótipos das funções encapuladas no módulo *****/

 void PECF_ExcluirValor (void * pdado);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PECF Criar Peca Finalizada
*  ****/

	PECF_tpCondRet PECF_CriarPecaFinalizada ( void )
	{
		pPecaF = ( tpPecaF* ) malloc (sizeof( tpPecaF ));

		if( pPecaF == NULL )
		{
			return PECF_CondRetFaltouMemoria ;
		}/* if */


		pPecaF -> quantP = 0 ;
		pPecaF -> quantB = 0 ;
		pPecaF -> LisPecaFinalizadaB = LIS_CriarLista(PECF_ExcluirValor);
		pPecaF -> LisPecaFinalizadaP = LIS_CriarLista(PECF_ExcluirValor);

		if (pPecaF  -> LisPecaFinalizadaP == NULL || pPecaF  -> LisPecaFinalizadaB == NULL)
		   return PECF_CondRetFaltouMemoria;

		return PECF_CondRetOK;

	}/* Fim função: PECF Criar Peca Finalizada */

/***************************************************************************
*
*  Função: PECF Adicionar Peca Finalizada
*  ****/
	PECF_tpCondRet PECF_AdicionaPecaFinalizada( PEC_tpPeca *pPeca )
	{
		char cor ;
		PEC_ObterCorPeca(&pPeca,&cor);
		
		if ((pPecaF == NULL) || (pPeca == NULL))
		{
			return PECF_CondRetPecaFinalizadaNaoExiste;
		}/* if */

		if (cor == 'b')
		{
			if(pPecaF->quantB == 15)
			{
				return PECF_CondRetLimiteDePecaFinalizada;
			}/* if */

			LIS_InserirElementoApos(pPecaF->LisPecaFinalizadaB, pPeca);
			pPecaF ->quantB += 1;
		}/* if */

		else
		{
			if(pPecaF->quantP == 15)
			{
				return PECF_CondRetLimiteDePecaFinalizada;
			}/* if */

			LIS_InserirElementoApos(pPecaF->LisPecaFinalizadaP, pPeca);
			pPecaF ->quantP += 1;
		}/* else */

		return PECF_CondRetOK;
	
	}/* Fim função: PECF Adicionar Peca Finalizada */

/***************************************************************************
*
*  Função: PECF Obter Quantidade Peca Finalizada
*  ****/

	PECF_tpCondRet PECF_ObterQuantidadeLisPF ( char cor, int *ObterValor )
	{
		if ( pPecaF == NULL )
      	{
			return PECF_CondRetPecaFinalizadaNaoExiste ;
     	} /* if */

		if (cor == 'b')
		{
			*ObterValor = pPecaF -> quantB ;
		} /* if */

		else 
		{
			*ObterValor = pPecaF -> quantP ;
		}/* else */

		return PECF_CondRetOK ; 


	}/* Fim função: PECF Obter Quantidade Peca Finalizada */

/***************************************************************************
*
*  Função: PECF Resetar lista Peca Finalizada
*  ****/

	PECF_tpCondRet PECF_ResetarPecaFinalizada( void )
	{
		if ( pPecaF == NULL )
      	{
			return PECF_CondRetPecaFinalizadaNaoExiste ;
     	} /* if */

		LIS_DestruirLista(pPecaF->LisPecaFinalizadaB);
		LIS_DestruirLista(pPecaF->LisPecaFinalizadaP);
		free(pPecaF);
		pPecaF = NULL;
		
		return PECF_CondRetOK ; 

	}/* Fim função: PECF Resetar Peca Finalizada */

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

    void PECF_ExcluirValor (void * pdado)
 {
	 free(pdado);
 }

/********** Fim do módulo de implementação: Módulo Peca Finalizada**********/



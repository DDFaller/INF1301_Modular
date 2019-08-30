/***************************************************************************
*  $MCI M�dulo de implementa��o: PECF Pe�as Finalizadas
*
*  Arquivo gerado:              PECF.c
*  Letras identificadoras:      PECF
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: JP - Jessica Pereira Cesario
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
	   1.0		JP		31/05	 Come�o do Desenvolvimento
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
*  $TC Tipo de dados: PECF Descritor da estrutura de pe�as finalizadas
*
*  $ED Descri��o do tipo
*     Descreve uma estrutura de pe�a finalizada.
*
***********************************************************************/

	typedef struct tgPecaF 
	{

		LIS_tppLista LisPecaFinalizadaB ;
		/* Lista de Pe�as Finalizadas brancas*/

		LIS_tppLista LisPecaFinalizadaP ;
		/* Lista de Pe�as Finalizadas pretas*/

		int quantB ;
		/* N�mero de elementos na lista de pe�as brancas */

		int quantP ;
		/* N�mero de elementos na lista de pe�as pretas */

	} tpPecaF ;

/*****  Dados encapsulados no m�dulo  *****/

	static tpPecaF *pPecaF = NULL;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

 void PECF_ExcluirValor (void * pdado);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: PECF Criar Peca Finalizada
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

	}/* Fim fun��o: PECF Criar Peca Finalizada */

/***************************************************************************
*
*  Fun��o: PECF Adicionar Peca Finalizada
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
	
	}/* Fim fun��o: PECF Adicionar Peca Finalizada */

/***************************************************************************
*
*  Fun��o: PECF Obter Quantidade Peca Finalizada
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


	}/* Fim fun��o: PECF Obter Quantidade Peca Finalizada */

/***************************************************************************
*
*  Fun��o: PECF Resetar lista Peca Finalizada
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

	}/* Fim fun��o: PECF Resetar Peca Finalizada */

/***********************************************************************
*
*  $FC Fun��o: PECF Excluir valor
*
*  $ED Descri��o da fun��o
*     Excluir o valor que � enviado.
*
*  $EP Par�metros
*     $P pdado    - valor a ser excluido
*
***********************************************************************/

    void PECF_ExcluirValor (void * pdado)
 {
	 free(pdado);
 }

/********** Fim do m�dulo de implementa��o: M�dulo Peca Finalizada**********/



/***************************************************************************
*  $MCI Módulo de implementação: Módulo Dado
*
*  Arquivo gerado:              Dados.c
*  Letras identificadoras:      DAD
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Jogo de Gamão - Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mbs Miguel Basso Sanseverino
			JP - Jessica Pereira Cesario
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações      
*       1.00   mbs   10/04/2019 Início do desenvolvimento
*		1.00   JP    05/05/2019 Documentação
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   <stdlib.h>
#include   <time.h>

#define DADOS_OWN
#include "Dado.h"
#undef DADOS_OWN

/*****  Codigo das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: DAD Rolar Dados
*  ****/
DAD_tpCondRet DAD_RolarDados(int * Dados) {
	
	time_t t;
	srand(time(&t)); //Escolhe a Seed do Random

	Dados[0] = ((rand() % 6) + 1);
	Dados[1] = ((rand() % 6) + 1);
	
	return DAD_CondRetOK;
	
}/* Fim função: DAD Rolar Dados */


/********** Fim do módulo de implementação: Módulo Dado **********/


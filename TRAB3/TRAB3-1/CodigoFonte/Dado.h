/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Dados
*
*  Arquivo gerado:              Dados.h
*  Letras identificadoras:      DAD
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Gamao
*  Gestor:  DI/PUC-Rio
*  Autores: mbs - Miguel Basso Sanseverino
*			JP - Jessica Pereira Cesario
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		2.00   JP    5/05/2019 Documentação
*		2.00   mbs   20/04/2019 Finalização do Módulo
*       1.00   mbs   15/04/2019 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para rolar dois
*     dado de 6 lados e armazenar os resultados.
*
***************************************************************************/
/***********************************************************************
*
*  $TC Tipo de dados: ARV Condicoes de retorno
*
***********************************************************************/

   typedef enum {

         DAD_CondRetOK = 0 ,
               /* Executou correto */

	} DAD_tpCondRet ;


/***********************************************************************

/***********************************************************************
*
*  $FC Função: DAD Rolar Dado
*
*  $ED Descrição da função
*     Rola dois dado de 6 lados e armazena os resultados.
*
*  $EP Parâmetros
*     $P ValorParm - vetor de duas posiçoes que seram retornados o valor dos dados
*					 por referencia.
*
*  $FV Valor retornado
*     DAD_CondRetOK
*
***********************************************************************/

/* $AE Assertivas de entrada DAD_RolarDados
*   Tem que existir um espaço de memoria para o dado poder ser rolado.  
*
*  Fim Assertivas de Entrada DAD_RolarDados */

	DAD_tpCondRet DAD_RolarDados(int * ValorParm);

/* $AS Assertivas de Saida DAD_RolarDados
*   Tem que existir 2 valores de 1 á 6 armazenos no Dados.
*   A função retorna DAD_CondRet.
*
*  Fim Assertiva de Saida DAD_RolarDados */


/********** Fim do módulo de definição: Módulo Dado **********/
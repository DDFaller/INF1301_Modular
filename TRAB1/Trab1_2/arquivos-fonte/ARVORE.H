#if ! defined( ARVORE_ )
#define ARVORE_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo �rvore
*
*  Arquivo gerado:              ARVORE.H
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*			JP  - J�ssica Pereira
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*		4.00   JP	 02/04/2019 Atualiz��o da interface de algumas fun��es e
*                               de as condi��es de retorno.	
*       3.00   avs   28/02/2003 Uniformiza��o da interface das fun��es e
*                               de todas as condi��es de retorno.
*       2.00   avs   03/08/2002 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00   avs   15/08/2001 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     explorar �rvores bin�rias.
*     A �rvore possui uma cabe�a que cont�m uma refer�ncia para a ra�z da
*     �rvore e outra para um n� corrente da �rvore.
*     A cada momento o m�dulo admite no m�ximo uma �nica �rvore.
*     Ao iniciar a execu��o do programa n�o existe �rvore.
*     A �rvore poder� estar vazia. Neste caso a raiz e o n� corrente
*     ser�o nulos, embora a cabe�a esteja definida.
*     O n� corrente ser� nulo se e somente se a �rvore estiver vazia.
*
***************************************************************************/

#if defined( ARVORE_OWN )
   #define ARVORE_EXT
#else
   #define ARVORE_EXT extern
#endif



/***********************************************************************
*
*  $TC Tipo de dados: ARV Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         ARV_CondRetOK = 0 ,
               /* Executou correto */

         ARV_CondRetNaoCriouRaiz = 1 ,
               /* N�o criou n� raiz */

         ARV_CondRetErroEstrutura = 2 ,
               /* Estrutura da �rvore est� errada */

         ARV_CondRetNaoEhFolha = 3 ,
               /* N�o � folha relativa � dire��o de inser��o desejada */

         ARV_CondRetArvoreNaoExiste = 4 ,
               /* �rvore n�o existe */

         ARV_CondRetArvoreVazia = 5 ,
               /* �rvore est� vazia */

         ARV_CondRetNohEhRaiz = 6 ,
               /* N� corrente � raiz */

         ARV_CondRetNaoPossuiFilho = 7 ,
               /* N� corrente n�o possui filho na dire��o desejada */

         ARV_CondRetFaltouMemoria = 8
               /* Faltou mem�ria ao alocar dados */

   } ARV_tpCondRet ;
/***********************************************************************
*
*  $FC Fun��o: ARV Criar �rvore
*
*  $ED Descri��o da fun��o
*     Cria uma nova �rvore vazia.
*     Caso j� exista uma �rvore, esta ser� destru�da.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*
***********************************************************************/

   ARV_tpCondRet ARV_CriarArvore( void ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Destruir �rvore
*
*  $ED Descri��o da fun��o
*     Destr�i o corpo e a cabe�a da �rvore, anulando a �rvore corrente.
*     Faz nada caso a �rvore corrente n�o exista.
*
***********************************************************************/

   void ARV_DestruirArvore( void ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Adicionar filho � esquerda
*
*  $EP Par�metros
*     $P ValorParm - valor a ser inserido no novo n�.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetErroEstrutura
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoEhFolha     - caso n�o seja folha para a esquerda
*
***********************************************************************/

   ARV_tpCondRet ARV_InserirEsquerda( char ValorParm , char ChaveParm) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Adicionar filho � direita
*
*  $EP Par�metros
*     $P ValorParm - valor a ser inserido no novo n�
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetErroEstrutura
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoEhFolha     - caso n�o seja folha para a direita
*
***********************************************************************/

   ARV_tpCondRet ARV_InserirDireita( char ValorParm , char ChaveParm ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Ir para n� pai
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNoEhRaiz
*
***********************************************************************/

   ARV_tpCondRet ARV_IrPai( void ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Ir para n� � esquerda
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNaoPossuiFilho   - n� corrente n�o possui filho � esquerda
*
***********************************************************************/

   ARV_tpCondRet ARV_IrNoEsquerda( void ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Ir para n� � direita
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNaoPossuiFilho   - n� corrente n�o possui filho � direita
*
***********************************************************************/

   ARV_tpCondRet ARV_IrNoDireita( void ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Obter valor corrente
*
*  $EP Par�metros
*     $P ValorParm - � o par�metro que receber� o valor contido no n�.
*                    Este par�metro � passado por refer�ncia.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*
***********************************************************************/

   ARV_tpCondRet ARV_ObterValorCorr( char * ValorParm ) ;

/***********************************************************************
*
*  $FC Fun��o: ARV Costura as folhas da arvore 
*
*  $ED Descri��o da fun��o
*     Costura todas as folhas da �rvore, em ordem alfabetica,
*	  a partir da chave que cada no possui.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*
***********************************************************************/

   ARV_tpCondRet ARV_CosturarArvore(void);

/***********************************************************************
*
*  $FC Fun��o: ARV Exibe folhas
*
*  $ED Descri��o da fun��o
*     Exibe todas as folhas de uma �rvore.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*
***********************************************************************/

   ARV_tpCondRet ARV_ExibeFolhas(void);

/***********************************************************************
*
*  $FC Fun��o: ARV  Adiciona elemento na lista
*
*  $ED Descri��o da fun��o
*     Cria uma lista que � associado a todos os n�s-folhas.
*	  Insere o dado recebido como par�metro nos primeiros n�s das mesmas.
*
*  $EP Par�metros
*	  ValorParm  - valor referente a folha que eu quero inserir o elemento.
*     Valor		 - inteiro a ser inserido na lista.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreVazia
*     ARV_CondRetArvoreNaoExiste
*	  ARV_CondRetNaoEhFolha
*
***********************************************************************/

	ARV_tpCondRet ARV_AdicionarElementoLista(char valorParm, int valor);


#undef ARVORE_EXT

/********** Fim do m�dulo de defini��o: M�dulo �rvore **********/

#else
#endif

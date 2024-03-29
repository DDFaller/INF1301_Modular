/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo �rvore
*
*  Arquivo gerado:              ARVORE.C
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*			JP  - J�ssica Pereira
*			DF  - Daniel Faller
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*		4.00   DF	 02/04/2019 Atualiz��o da interface de algumas fun��es e
*                               de as condi��es de retorno.	
*		4.00   JP	 02/04/2019 Atualiz��o da interface de algumas fun��es e
*                               de as condi��es de retorno.	
*       3.00   avs   28/02/2003 Uniformiza��o da interface das fun��es e
*                               de todas as condi��es de retorno.
*       2.00   avs   03/08/2002 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00   avs   15/08/2001 In�cio do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#include "LISTA.H"

#define ARVORE_OWN
#include "ARVORE.H"
#undef ARVORE_OWN


/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do n� da �rvore
*
*
*  $ED Descri��o do tipo
*     Descreve a organiza��o do n�
*
***********************************************************************/

   typedef struct tgNoArvore {

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   � NULL sse o n� � raiz
               *   Se n�o for raiz, um de pNoEsq ou pNoDir de pNoPai do n�
               *   corrente apontam para o n� corrente 
			   */
         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para filho � esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do n� X != NULL ent�o pNoPai de pNoEsq aponta para o n� X 
			   */
         struct tgNoArvore * pNoDir ;
               /* Ponteiro para filho � direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do n� X != NULL ent�o pNoPai de pNoDir aponta para o n� X 
			   */
         char Valor ;
               /* Valor do n� */
			  /*  Ponteiro para pr�xima folha
			  */
		 struct tgNoArvore * pNoProxfolha ;
			   /* Ponteiro para a proxima folha da �rvore
			  */
		 char Chave ;
			   /* Campo alfan�merio a ser utilizado na ordenamento
			  */
		 LIS_tppLista  pElemLista;
			   /*  Campo que corresponde a lista que os nos folhas possuem
			   *
			   *$EED Assertivas Estruturais
			   *	se a n� n�o for folha este campo � null
			   */
			   
   } tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabe�a de uma �rvore
*
*
*  $ED Descri��o do tipo
*     A cabe�a da �rvore � o ponto de acesso para uma determinada �rvore.
*     Por interm�dio da refer�ncia para o n� corrente e do ponteiro
*     pai pode-se navegar a �rvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a �rvore em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgArvore {

         tpNoArvore * pNoRaiz ;
               /* Ponteiro para a raiz da �rvore */

         tpNoArvore * pNoCorr ;
               /* Ponteiro para o n� corrente da �rvore */

   } tpArvore ;


/*****  Dados encapsulados no m�dulo  *****/

      static tpArvore * pArvore = NULL ;
            /* Ponteiro para a cabe�a da �rvore */
	  
	  static tpNoArvore * pFolhas = NULL ;
		    /* Ponteiro para a cabe�a das folhas */


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static tpNoArvore * CriarNo( char ValorParm , char ChaveParm ) ;

   static ARV_tpCondRet CriarNoRaiz( char ValorParm  , char ChaveParm ) ;

   static void DestroiArvore( tpNoArvore * pNo ) ;

   void ordem_simetrica( tpNoArvore * pNoRaiz );

   void destroilis( void *p );

   int ContaFolhas( void );

   tpNoArvore ** PreencheVetor( int ValorParm );

   void BubbleSort ( void );

   void ExibeFolhas ( tpNoArvore * pNoFolha );

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

	/***************************************************************************
*
*  Fun��o: ARV Criar �rvore
*  ****/

   ARV_tpCondRet ARV_CriarArvore( void )
   {

      if ( pArvore != NULL )
      {
         ARV_DestruirArvore( ) ;
      } /* if */

      pArvore = ( tpArvore * ) malloc( sizeof( tpArvore )) ;
      if ( pArvore == NULL )
      {
         return ARV_CondRetFaltouMemoria ;
      } /* if */

      pArvore->pNoRaiz = NULL ;
      pArvore->pNoCorr = NULL ;

      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Criar �rvore */

   /***************************************************************************
*
*  Fun��o: ARV Destruir �rvore
*  ****/

   void ARV_DestruirArvore( void )
   {

      if ( pArvore != NULL )
      {
         if ( pArvore->pNoRaiz != NULL )
         {
            DestroiArvore( pArvore->pNoRaiz ) ;
         } /* if */
         free( pArvore ) ;
         pArvore = NULL ;
      } /* if */

   } /* Fim fun��o: ARV Destruir �rvore */

   /***************************************************************************
*
*  Fun��o: ARV Adicionar filho � esquerda
*  ****/

   ARV_tpCondRet ARV_InserirEsquerda( char ValorParm , char ChaveParm )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      /* Tratar vazio, esquerda */

         CondRet = CriarNoRaiz( ValorParm , ChaveParm) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar n� � esquerda de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( ValorParm ,ChaveParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar n�o folha � esquerda */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim fun��o: ARV Adicionar filho � esquerda */

   /***************************************************************************
*
*  Fun��o: ARV Adicionar filho � direita
*  ****/

  ARV_tpCondRet ARV_InserirDireita( char ValorParm , char ChaveParm )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      /* Tratar vazio, direita */

         CondRet = CriarNoRaiz( ValorParm , ChaveParm) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar n� � direita de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( ValorParm , ChaveParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr;
            pCorr->pNoDir    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar n�o folha � direita */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim fun��o: ARV Adicionar filho � direita */

   /***************************************************************************
*
*  Fun��o: ARV Ir para n� pai
*  ****/

   ARV_tpCondRet ARV_IrPai( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */
      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoPai != NULL )
      {
         pArvore->pNoCorr = pArvore->pNoCorr->pNoPai ;
         return ARV_CondRetOK ;
      } else {
         return ARV_CondRetNohEhRaiz ;
      } /* if */

   } /* Fim fun��o: ARV Ir para n� pai */

   /***************************************************************************
*
*  Fun��o: ARV Ir para n� � esquerda
*  ****/

   ARV_tpCondRet ARV_IrNoEsquerda( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoEsq == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoEsq ;
      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Ir para n� � esquerda */

   /***************************************************************************
*
*  Fun��o: ARV Ir para n� � direita
*  ****/

   ARV_tpCondRet ARV_IrNoDireita( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoDir == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoDir ;
      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Ir para n� � direita */

   /***************************************************************************
*
*  Fun��o: ARV Obter valor corrente
*  ****/

   ARV_tpCondRet ARV_ObterValorCorr( char * ValorParm )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */
      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */
      * ValorParm = pArvore->pNoCorr->Valor ;

      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Obter valor corrente */

   /***************************************************************************
*
*  Fun��o: ARV Exibe folhas
*  ****/
   
   ARV_tpCondRet ARV_ExibeFolhas( void ){

	   if(pArvore == NULL){
		   return ARV_CondRetArvoreNaoExiste;
	   }/* if */
	   
	   if ( pArvore->pNoRaiz == NULL )
       {
		   return ARV_CondRetArvoreVazia ;
       } /* if */

	   printf("\n");

	   if ( pFolhas != NULL )
	   {
		   ExibeFolhas(pFolhas);
	   } /* if */

      return ARV_CondRetOK;
   } /* Fim fun��o: ARV Exibe folhas */

   /***************************************************************************
*
*  Fun��o: ARV Costurar �rvore
*  ****/

   ARV_tpCondRet ARV_CosturarArvore( void )
   {	

	   if(pArvore == NULL){
		   return ARV_CondRetArvoreNaoExiste;
	   }/* if */
	   
	   if ( pArvore->pNoRaiz == NULL )
       {
		   return ARV_CondRetArvoreVazia ;
       } /* if */

	   ordem_simetrica(pArvore->pNoRaiz) ; /* costura as folhas */
	    
	   BubbleSort(); /* ordena a costura */

	   return ARV_CondRetOK;
   }/* Fim fun��o: ARV Costura �rvore */

   /***************************************************************************
*
*  Fun��o: ARV Adicionar elemento na lista
*  ****/

   ARV_tpCondRet ARV_AdicionarElementoLista(char valorParm,  int valor){
	   
	   int * p,i=0;
	   tpNoArvore *aux = pFolhas;
	   
	   if(pArvore == NULL)
	   {
		   return ARV_CondRetArvoreNaoExiste;
	   }/* if */
	   
	   if ( pArvore->pNoRaiz == NULL )
       {
		   return ARV_CondRetArvoreVazia ;
       } /* if */

	   p = (int*)malloc(sizeof(int));

	   if(p == NULL)
	   {
		   return ARV_CondRetFaltouMemoria;
	   } /* if */

	   *p = valor;
	   
	   while(aux!=NULL){
		   if(aux->Valor==valorParm){
			   LIS_InserirElementoAntes(aux->pElemLista,p);
			   i = 1;
		   }
		   aux=aux->pNoProxfolha;
	   } /* while */
	   if(i==0)
		   return ARV_CondRetNaoEhFolha;
	   return ARV_CondRetOK;

   }/* Fim fun��o: ARV Adicionar elemento na lista */

   /*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: ARV Criar n� da �rvore
*
*  $FV Valor retornado
*     Ponteiro para o n� criado.
*     Ser� NULL caso a mem�ria tenha se esgotado.
*     Os ponteiros do n� criado estar�o nulos e o valor � igual ao do
*     par�metro.
*
***********************************************************************/

   tpNoArvore * CriarNo( char ValorParm , char ChaveParm)
   {

      tpNoArvore * pNo ;
	  LIS_tppLista lista = LIS_CriarLista(destroilis);

      pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
	  pNo->pNoProxfolha = NULL;
	  pNo->pElemLista = NULL;
	  pNo->Valor  = ValorParm ;
	  pNo->Chave  = ChaveParm ;

      return pNo ;

   } /* Fim fun��o: ARV Criar n� da �rvore */

   /***********************************************************************
*
*  $FC Fun��o: ARV Criar n� raiz da �rvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

   ARV_tpCondRet CriarNoRaiz( char ValorParm, char ChaveParm)
   {

      ARV_tpCondRet CondRet ;
      tpNoArvore * pNo ;

      if ( pArvore == NULL )
      {
         CondRet = ARV_CriarArvore( ) ;

         if ( CondRet != ARV_CondRetOK )
         {
            return CondRet ;
         } /* if */
      } /* if */

      if ( pArvore->pNoRaiz == NULL )
      {
         pNo = CriarNo( ValorParm , ChaveParm) ;
         if ( pNo == NULL )
         {
            return ARV_CondRetFaltouMemoria ;
         } /* if */
         pArvore->pNoRaiz = pNo ;
         pArvore->pNoCorr = pNo ;

         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNaoCriouRaiz ;

   } /* Fim fun��o: ARV Criar n� raiz da �rvore */

   /***********************************************************************
*
*  $FC Fun��o: ARV Destruir a estrutura da �rvore
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/

   void DestroiArvore( tpNoArvore * pNo )
   {

      if ( pNo->pNoEsq != NULL )
      {
         DestroiArvore( pNo->pNoEsq ) ;
      } /* if */

      if ( pNo->pNoDir != NULL )
      {
         DestroiArvore( pNo->pNoDir ) ;
      } /* if */

      free( pNo ) ;

   } /* Fim fun��o: ARV Destruir a estrutura da �rvore */

   /***********************************************************************
*
*  $FC Fun��o: Ordem Simetrica
*
*  $ED Descri��o da fun��o
*     Faz uma costura nas folhas em ordem simetrica.
*	  Essa costura � associada a uma variavel encapsulada no m�dulo que possui a cabe�a da mesma
*
*  $EP Par�metros
*     pNoRaiz  - um ponteiro para a �rvore.
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*     
***********************************************************************/

	void ordem_simetrica( tpNoArvore * pNoRaiz )
	{	
		if(pNoRaiz != NULL){

			ordem_simetrica(pNoRaiz->pNoEsq);

			if(pNoRaiz->pNoDir==NULL && pNoRaiz->pNoEsq==NULL){
				
				pNoRaiz->pElemLista = LIS_CriarLista(destroilis);

				if(pFolhas==NULL)

					pFolhas=pNoRaiz;
				else{
					pNoRaiz->pNoProxfolha=pFolhas;
					
					pFolhas=pNoRaiz;
				}
			}
			ordem_simetrica(pNoRaiz->pNoDir);
		}

		return;

	} /* Fim fun��o: ordem simetrica */

   /***********************************************************************
*
*  $FC Fun��o: Conta folhas
*
*  $ED Descri��o da fun��o
*    Conta a quantidade de Folhas na �rvore
*
*  $FV Valor retornado
*     inteiro com a quantidade de folhas
*
***********************************************************************/

    int ContaFolhas( void )
	{
	   tpNoArvore * temp;
	   int i = 0;
	   temp = pFolhas;
	   while(temp->pNoProxfolha != NULL){
		   i++;
		   temp = temp->pNoProxfolha;
	   }
	   return i + 1;
   } /* Fim fun��o: Conta folhas */

	/***********************************************************************
*
*  $FC Fun��o:   Preenche vetor
*
*  $ED Descri��o da fun��o
*     Preenche vetor com as folhas da �rvore
*
*  $EP Par�metros
*     ValorParm  - um inteiro que � a quantidade de folhas na �rvore.
*
*  $FV Valor retornado
*     Um ponteiro de ponteiro para �rvore
*     
***********************************************************************/

   tpNoArvore ** PreencheVetor( int ValorParm )
   {
	   int j;
	   tpNoArvore * temp = NULL;
	   tpNoArvore ** vFolhas = (tpNoArvore**)malloc( ValorParm  * sizeof( tpNoArvore*));
	   temp = pFolhas;
	   for(j = 0; j < ValorParm;j++){
		   vFolhas[j] = temp;
		   temp = temp->pNoProxfolha;
	   } /* for */
	   return vFolhas;
   } /* Fim fun��o: Preenche vetor */

   /***********************************************************************
*
*  $FC Fun��o: Bubble Sort
*
*  $ED Descri��o da fun��o
*     Ordena um vetor de ponteiros a partir das chaves das folhas da �rvore
*
***********************************************************************/
  
  void BubbleSort ( void )
   {
	   tpNoArvore * temp=NULL;
	   tpNoArvore ** vFolhas;
	   int swapped,index = 0, i = ContaFolhas(), ant = i - 1, k;  

	   vFolhas = PreencheVetor(i);

	   do
       { 
		   swapped = 0; 
		   while (index != ant) 
           { 
			   if (vFolhas[index]->Chave >= vFolhas[index + 1]->Chave)
               {  
                       temp = vFolhas[index];
					   vFolhas[index] = vFolhas[index + 1];
					   vFolhas[index + 1] = temp;
                   swapped = 1; 
               }/* if */ 
               index++;
		   } /* while */
           ant--; 
		   index = 0;
       }while (swapped); /* Reconstroe a variavel folhas de acordo com a ordem de elementos no vetor */
	   
	   for(k = 0; k < i - 1;k++){
		   vFolhas[k]->pNoProxfolha = vFolhas[k+1];
	   }/* for */

	   vFolhas[k]->pNoProxfolha = NULL;
	   pFolhas = vFolhas[0];

	   
	   free(vFolhas); /* Destroi vetor */
	   return;
   } /* Fim fun��o: BubbleSort */

  /***********************************************************************
*
*  $FC Fun��o: Exibe Folhas
*
*  $ED Descri��o da fun��o
*     Preenche vetor com as folhas da �rvore
*
*  $EP Par�metros
*     pNoFolha  - Um ponteiro de ponteiro para �rvore.
*
***********************************************************************/

  void ExibeFolhas ( tpNoArvore * pNoFolha )
   {

	   tpNoArvore *aux = pNoFolha;
	   while(aux!=NULL){
		   printf("Valor: %c Chave: %d  ->  ",aux->Valor,aux->Chave);
		   aux=aux->pNoProxfolha;
	   } /* while */
	   
   }/* Fim fun��o: Exibe folhas */

  
  /***********************************************************************
*
*  $FC Fun��o: destroi lista
*
*  $ED Descri��o da fun��o
*    Destroi o parametro enviado como par�metro.
*
*  $EP Par�metros
*     ValorParm  - Um valor a ser destruido
*     
***********************************************************************/

   void destroilis( void * ValorParm )
   {
		 free( ValorParm );
	
   }/* fim destroi lista */ 
   
/********** Fim do m�dulo de implementa��o: M�dulo �rvore **********/

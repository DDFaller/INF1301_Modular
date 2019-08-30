/***************************************************************************
*  $MCI Módulo de implementação: Módulo árvore
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
*			JP  - Jéssica Pereira
*			DF  - Daniel Faller
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		4.00   DF	 02/04/2019 Atualizção da interface de algumas funções e
*                               de as condições de retorno.	
*		4.00   JP	 02/04/2019 Atualizção da interface de algumas funções e
*                               de as condições de retorno.	
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
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
*  $TC Tipo de dados: ARV Descritor do nó da árvore
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct tgNoArvore {

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente 
			   */
         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para filho à esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do nó X != NULL então pNoPai de pNoEsq aponta para o nó X 
			   */
         struct tgNoArvore * pNoDir ;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X 
			   */
         char Valor ;
               /* Valor do nó */
			  /*  Ponteiro para próxima folha
			  */
		 struct tgNoArvore * pNoProxfolha ;
			   /* Ponteiro para a proxima folha da árvore
			  */
		 char Chave ;
			   /* Campo alfanúmerio a ser utilizado na ordenamento
			  */
		 LIS_tppLista  pElemLista;
			   /*  Campo que corresponde a lista que os nos folhas possuem
			   *
			   *$EED Assertivas Estruturais
			   *	se a nó não for folha este campo é null
			   */
			   
   } tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça de uma árvore
*
*
*  $ED Descrição do tipo
*     A cabe‡a da árvore é o ponto de acesso para uma determinada árvore.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a árvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a árvore em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgArvore {

         tpNoArvore * pNoRaiz ;
               /* Ponteiro para a raiz da árvore */

         tpNoArvore * pNoCorr ;
               /* Ponteiro para o nó corrente da árvore */

   } tpArvore ;


/*****  Dados encapsulados no módulo  *****/

      static tpArvore * pArvore = NULL ;
            /* Ponteiro para a cabeça da árvore */
	  
	  static tpNoArvore * pFolhas = NULL ;
		    /* Ponteiro para a cabeça das folhas */


/***** Protótipos das funções encapuladas no módulo *****/

   static tpNoArvore * CriarNo( char ValorParm , char ChaveParm ) ;

   static ARV_tpCondRet CriarNoRaiz( char ValorParm  , char ChaveParm ) ;

   static void DestroiArvore( tpNoArvore * pNo ) ;

   void ordem_simetrica( tpNoArvore * pNoRaiz );

   void destroilis( void *p );

   int ContaFolhas( void );

   tpNoArvore ** PreencheVetor( int ValorParm );

   void BubbleSort ( void );

   void ExibeFolhas ( tpNoArvore * pNoFolha );

/*****  Código das funções exportadas pelo módulo  *****/

	/***************************************************************************
*
*  Função: ARV Criar árvore
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

   } /* Fim função: ARV Criar árvore */

   /***************************************************************************
*
*  Função: ARV Destruir árvore
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

   } /* Fim função: ARV Destruir árvore */

   /***************************************************************************
*
*  Função: ARV Adicionar filho à esquerda
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

      /* Criar nó à esquerda de folha */

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

      /* Tratar não folha à esquerda */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à esquerda */

   /***************************************************************************
*
*  Função: ARV Adicionar filho à direita
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

      /* Criar nó à direita de folha */

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

      /* Tratar não folha à direita */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à direita */

   /***************************************************************************
*
*  Função: ARV Ir para nó pai
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

   } /* Fim função: ARV Ir para nó pai */

   /***************************************************************************
*
*  Função: ARV Ir para nó à esquerda
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

   } /* Fim função: ARV Ir para nó à esquerda */

   /***************************************************************************
*
*  Função: ARV Ir para nó à direita
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

   } /* Fim função: ARV Ir para nó à direita */

   /***************************************************************************
*
*  Função: ARV Obter valor corrente
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

   } /* Fim função: ARV Obter valor corrente */

   /***************************************************************************
*
*  Função: ARV Exibe folhas
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
   } /* Fim função: ARV Exibe folhas */

   /***************************************************************************
*
*  Função: ARV Costurar árvore
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
   }/* Fim função: ARV Costura árvore */

   /***************************************************************************
*
*  Função: ARV Adicionar elemento na lista
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

   }/* Fim função: ARV Adicionar elemento na lista */

   /*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: ARV Criar nó da árvore
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do nó criado estarão nulos e o valor é igual ao do
*     parâmetro.
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

   } /* Fim função: ARV Criar nó da árvore */

   /***********************************************************************
*
*  $FC Função: ARV Criar nó raiz da árvore
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

   } /* Fim função: ARV Criar nó raiz da árvore */

   /***********************************************************************
*
*  $FC Função: ARV Destruir a estrutura da árvore
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

   } /* Fim função: ARV Destruir a estrutura da árvore */

   /***********************************************************************
*
*  $FC Função: Ordem Simetrica
*
*  $ED Descrição da função
*     Faz uma costura nas folhas em ordem simetrica.
*	  Essa costura é associada a uma variavel encapsulada no módulo que possui a cabeça da mesma
*
*  $EP Parâmetros
*     pNoRaiz  - um ponteiro para a árvore.
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

	} /* Fim função: ordem simetrica */

   /***********************************************************************
*
*  $FC Função: Conta folhas
*
*  $ED Descrição da função
*    Conta a quantidade de Folhas na árvore
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
   } /* Fim função: Conta folhas */

	/***********************************************************************
*
*  $FC Função:   Preenche vetor
*
*  $ED Descrição da função
*     Preenche vetor com as folhas da árvore
*
*  $EP Parâmetros
*     ValorParm  - um inteiro que é a quantidade de folhas na árvore.
*
*  $FV Valor retornado
*     Um ponteiro de ponteiro para árvore
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
   } /* Fim função: Preenche vetor */

   /***********************************************************************
*
*  $FC Função: Bubble Sort
*
*  $ED Descrição da função
*     Ordena um vetor de ponteiros a partir das chaves das folhas da árvore
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
   } /* Fim função: BubbleSort */

  /***********************************************************************
*
*  $FC Função: Exibe Folhas
*
*  $ED Descrição da função
*     Preenche vetor com as folhas da árvore
*
*  $EP Parâmetros
*     pNoFolha  - Um ponteiro de ponteiro para árvore.
*
***********************************************************************/

  void ExibeFolhas ( tpNoArvore * pNoFolha )
   {

	   tpNoArvore *aux = pNoFolha;
	   while(aux!=NULL){
		   printf("Valor: %c Chave: %d  ->  ",aux->Valor,aux->Chave);
		   aux=aux->pNoProxfolha;
	   } /* while */
	   
   }/* Fim função: Exibe folhas */

  
  /***********************************************************************
*
*  $FC Função: destroi lista
*
*  $ED Descrição da função
*    Destroi o parametro enviado como parâmetro.
*
*  $EP Parâmetros
*     ValorParm  - Um valor a ser destruido
*     
***********************************************************************/

   void destroilis( void * ValorParm )
   {
		 free( ValorParm );
	
   }/* fim destroi lista */ 
   
/********** Fim do módulo de implementação: Módulo árvore **********/

/*
 * container.c
 *
 *  Created on: 2 mars 2020
 *      Author: eleve
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "container.h"

typedef struct tt_node {
	struct tt_node* pPrev;
	struct tt_node* pNext;
	void*			pElem;
}t_node;

t_node* NodeNew(t_node*pPrev, t_node*pNext, void*pElem) {

	 t_node*pNewNode;

	pNewNode = (t_node*) malloc ( sizeof(t_node) );

	assert(pNewNode != NULL);

	pNewNode->pNext = pNext;
	pNewNode->pPrev = pPrev;
	pNewNode->pElem = pElem;

	if(pNext != NULL)
		pNext->pPrev = pNewNode;

	if(pPrev != NULL)
		pPrev->pNext = pNewNode;


	return pNewNode;
}

t_node* NodeDel(t_node*pNode, t_ptfVV pDelElemFunc, void*pParam) {

	assert(pNode != NULL);

	if(pDelElemFunc != NULL){ pDelElemFunc(pNode->pElem, pParam); pNode->pElem = NULL;}
	else 					{ free(pNode->pElem); }

	if(pNode->pPrev != NULL)
		pNode->pPrev->pNext = pNode->pNext;
	if(pNode->pNext != NULL)
		pNode->pNext->pPrev = pNode->pPrev;

	free(pNode);

	return NULL;
}

t_node* NodeDelReturnNext(t_node*pNode, t_ptfVV pDelElemFunc, void*pParam) {

	assert(pNode != NULL);
	t_node* NodeNext = pNode->pNext;
	
	if (pDelElemFunc != NULL) { pDelElemFunc(pNode->pElem, pParam); pNode->pElem = NULL; }
	else {free(pNode->pElem);}

	if (pNode->pPrev != NULL)
		pNode->pPrev->pNext = pNode->pNext;
	if (pNode->pNext != NULL)
		pNode->pNext->pPrev = pNode->pPrev;

	free(pNode);

	return NodeNext;
}

t_node* NodeDelReturnPrev(t_node*pNode, t_ptfVV pDelElemFunc, void*pParam) {

	assert(pNode != NULL);
	t_node* NodePrev = pNode->pPrev;

	if (pDelElemFunc != NULL) { pDelElemFunc(pNode->pElem, pParam); }
	else { free(pNode->pElem); }

	if (pNode->pPrev != NULL)
		pNode->pPrev->pNext = pNode->pNext;
	if (pNode->pNext != NULL)
		pNode->pNext->pPrev = pNode->pPrev;

	free(pNode);

	return NodePrev;
}

struct s_container {
	int			nCard;
	t_node*		pHead;
	t_node*		pTail;
	t_ptfVV		pDelElemFunc;
};

struct s_container* ContainerNew(t_ptfVV pDelElemFunc) {
	
	struct s_container* pNewContainer;

	pNewContainer = (struct s_container*) malloc( sizeof(struct s_container) );

	if(pNewContainer != NULL) {
		pNewContainer->nCard = 0;
		pNewContainer->pHead = NULL;
		pNewContainer->pTail = NULL;
		pNewContainer->pDelElemFunc = pDelElemFunc;
	}

	return pNewContainer;
}

struct s_container* ContainerDel(t_pContainer pContainer, void*pParam) {

	assert(pContainer != NULL);

	while(pContainer->pHead != NULL){
		pContainer->pTail = pContainer->pHead;
		pContainer->pHead = pContainer->pHead->pNext;
		NodeDel(pContainer->pTail, pContainer->pDelElemFunc, pParam);
		pContainer->nCard--;
	}

	assert(pContainer->nCard == (int)NULL);

	free(pContainer);

	return NULL;
}


void* ContainerPushback(t_pContainer pContainer, void*pElem){

	assert(pContainer != NULL);

	t_node* nodePushBack;
	nodePushBack = NodeNew(pContainer->pTail, NULL, pElem);

	assert(nodePushBack != NULL);

	if(nodePushBack != NULL){
		if(pContainer->nCard == 0)
			pContainer->pHead = nodePushBack;

		pContainer->pTail = nodePushBack;
	}

	pContainer->nCard++;
	return nodePushBack->pElem;
}

void* ContainerPushfront(t_pContainer pContainer, void*pElem){
	t_node* nodePushFront;
	nodePushFront = NodeNew(NULL, pContainer->pHead, pElem);

	assert(nodePushFront != NULL);

	if(nodePushFront != NULL){

		if(pContainer->nCard == 0)
			pContainer->pTail = nodePushFront;

		pContainer->pHead = nodePushFront;
	}

	pContainer->nCard++;
	return nodePushFront->pElem;

}

void* ContainerPushat(t_pContainer pContainer, void*pElem, int nAt){

	t_node* nodePushAt, *pScan;
	pScan = pContainer->pHead;
	
	if ((nAt > 0) && (nAt < (pContainer->nCard))) {

		while (--nAt) { pScan = pScan->pNext; }
		nodePushAt = NodeNew(pScan, pScan->pNext, pElem);
		pContainer->nCard++;
	}
	if (!nAt) {
		ContainerPushfront(pContainer, pElem);
		nodePushAt = pContainer->pHead;
	}
	if (nAt >= (pContainer->nCard)) {
		ContainerPushback(pContainer, pElem);
		nodePushAt = pContainer->pTail;
	}

	

		return nodePushAt->pElem;
	
}


void* ContainerGetback(t_pContainer pContainer){
	if(pContainer->pTail->pElem)
		return pContainer->pTail->pElem;
	else
		return NULL;
}

void* ContainerGetfront(t_pContainer pContainer){
	if(pContainer->pHead->pElem)
			return pContainer->pHead->pElem;
		else
			return NULL;
}

void* ContainerGetat(t_pContainer pContainer, int nAt){
	if(nAt <= pContainer->nCard){
		t_node* pScan = pContainer->pHead;
		while (--nAt != 0) { pScan = pScan->pNext; }
		if(pScan->pElem)
			return pScan->pElem;
		else
			return NULL;
	}
	else { return NULL;}
}

void* ContainerPopback(t_pContainer pContainer){
	if(pContainer->pTail->pElem) {

		t_node* pTailC = pContainer->pTail->pPrev;
		void* pElem = pContainer->pTail->pElem;
		NodeDel(pContainer->pTail, pContainer->pDelElemFunc, pParam);
		pContainer->pTail = pTailC;
		pContainer->nCard--;
		return pElem;

	} else { return NULL; }
}
void* ContainerPopfront(t_pContainer pContainer){
	if(pContainer->pHead->pElem) {

		t_node* pHeadC = pContainer->pHead->pNext;

		void* pElem = pContainer->pHead->pElem;
		NodeDel(pContainer->pHead, pContainer->pDelElemFunc, pParam);
		pContainer->pHead = pHeadC;
		pContainer->nCard--;
		return pElem;

	} else { return NULL; }
}
void* ContainerPopat(t_pContainer pContainer, int nAt){
	if(nAt <= pContainer->nCard){
			t_node* pScan = pContainer->pHead;
			while (--nAt >= 0) { pScan = pScan->pNext; }
			if(pScan->pElem) {

				void* pElem = pScan->pElem;
				NodeDel(pScan, pContainer->pDelElemFunc);
				pContainer->nCard--;
				return pElem;

			} else { return NULL; }
		}
		else { return NULL; }
}

void* ContainerParse(t_pContainer pContainer, t_ptfVV pfParseFunc, void*pParam){

	t_node* pScan;
	pScan = pContainer->pHead;
	while( (pScan != NULL) && (pfParseFunc(pScan->pElem, pParam) == NULL) ) pScan = pScan->pNext;
	return NULL;
}

void* ContainerSort(t_pContainer pContainer, t_ptfVVV pSortFunc, void*pParam) {
	t_node* pScan;
	pScan = pContainer->pHead;
	
	while (pScan != NULL){
		pSortFunc(pScan, pScan->pNext, pParam);
		pScan = pScan->pNext;
	}

	return NULL;

}

void* ContainerParseDelIf(t_pContainer pContainer, t_ptfVV pfParseFunc, void*pParam) {

	t_node* pScan;
	pScan = pContainer->pHead;
	while (pScan != NULL) {
	
		if (pfParseFunc(pScan->pElem, pParam) != NULL) {
			pScan = NodeDelReturnNext(pScan, pContainer->pDelElemFunc, pParam);
			if (pScan) {
				if (pScan->pNext == NULL) { pContainer->pTail = pScan; }
				if (pScan->pPrev == NULL) { pContainer->pHead = pScan; }
			} else {
				pContainer->nCard--;
				if (pContainer->nCard == 0)
				{
					pContainer->pHead = NULL;
					pContainer->pTail = NULL;
				}
				continue;
			}
			pContainer->nCard--;
		}
		else { pScan = pScan->pNext; }
	}
	return NULL;
}

int ContainerCard(t_pContainer pContainer) {
	return pContainer->nCard;
}
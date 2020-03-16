/*
 * container.h
 *
 *  Created on: 2 mars 2020
 *      Author: eleve
 */

typedef struct s_container*	t_pContainer;

typedef void*(*t_ptfV)(void*);

typedef void*(*t_ptfVV)(void*, void*);

typedef void*(*t_ptfVVV)(void*, void*, void*);

struct s_container* ContainerNew(t_ptfVV pDelElemFunc);
struct s_container* ContainerDel(t_pContainer pContainer, void*pParam);

void* ContainerPushback(t_pContainer pContainer, void*pElem);
void* ContainerPushfront(t_pContainer pContainer, void*pElem);
void* ContainerPushat(t_pContainer pContainer, void*pElem, int nAt);

void* ContainerGetback(t_pContainer pContainer);
void* ContainerGetfront(t_pContainer pContainer);
void* ContainerGetat(t_pContainer pContainer, int nAt);

void* ContainerPopback(t_pContainer pContainer);
void* ContainerPopfront(t_pContainer pContainer);
void* ContainerPopat(t_pContainer pContainer, int nAt);

void* ContainerParse(t_pContainer pContainer, t_ptfVV pfParseFunc, void*pParam);
void* ContainerSort(t_pContainer pContainer, t_ptfVVV pSortFunc, void*pParam);

void* ContainerParseDelIf(t_pContainer pContainer, t_ptfVV pfParseFunc, void*pParam);
int ContainerCard(t_pContainer pContainer);
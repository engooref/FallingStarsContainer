/*
 * container.h
 *
 *  Created on: 2 mars 2020
 *      Author: eleve
 */

typedef void*(*t_ptfV)(void*);

typedef void*(*t_ptfVV)(void*, void*);

typedef void*(*t_ptfVVV)(void*, void*, void*);

struct s_container* ContainerNew(t_ptfV pDelElemFunc);

struct s_container* ContainerDel(struct s_container*pContainer);

void* ContainerPushback(struct s_container*pContainer, void*pElem);
void* ContainerPushfront(struct s_container*pContainer, void*pElem);
void* ContainerPushat(struct s_container*pContainer, void*pElem, int nAt);

void* ContainerGetback(struct s_container*pContainer);
void* ContainerGetfront(struct s_container*pContainer);
void* ContainerGetat(struct s_container*pContainer, int nAt);

void* ContainerPopback(struct s_container*pContainer);
void* ContainerPopfront(struct s_container*pContainer);
void* ContainerPopat(struct s_container*pContainer, int nAt);

void* ContainerParse(struct s_container*pContainer, t_ptfVV pfParseFunc, void*pParam);
void* ContainerSort(struct s_container*pContainer, t_ptfVVV pSortFunc, void*pParam);



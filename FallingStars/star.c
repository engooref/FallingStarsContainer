/***************************************************************************
* File: star.c
*
*  Created on: xx/xx/xxxx
*      Author: xxxxxxxxxx
***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#include <SDL2\SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "star.h"

struct s_star {
	//To complete...

};

//Star module Private Prototypes declaration----------------------------------------//
void _StarDraw(struct s_star*pStar, SDL_Renderer*pRenderer);
void _StarHide(struct s_star*pStar, SDL_Renderer*pRenderer, SDL_Color colorBkgnd);



//Star module Public Functions implementation---------------------------------------//
struct s_star* StarNew(int iLocX, int iLocY) {

	struct s_star * pNewStar = NULL;


	return pNewStar;
}

struct s_star* StarDel(struct s_star*pStar, SDL_Renderer*pRenderer, SDL_Color colorBkgnd) {

	return NULL;
}

int StarMove(struct s_star*pStar, SDL_Renderer*pRenderer, SDL_Color colorBkgnd, SDL_Point whMax,int iPaddingW, int iPaddingH) {

	return 0;
}


void StarOffsetLocation(struct s_star*pStar, SDL_Point offset, SDL_Renderer*pRenderer, SDL_Color colorBkgnd) {

}




//Star module Private Functions implementation---------------------------------------//
void _StarDraw(struct s_star*pStar, SDL_Renderer*pRenderer) {

}

void _StarHide(struct s_star*pStar, SDL_Renderer*pRenderer, SDL_Color colorBkgnd) {

}

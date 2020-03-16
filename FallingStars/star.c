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
	SDL_Color 	color;
	SDL_Point	location;
	SDL_Point 	speed;
};

//Star module Private Prototypes declaration----------------------------------------//
void _StarDraw(struct s_star*pStar, SDL_Renderer*pRenderer);
void _StarHide(struct s_star*pStar, SDL_Renderer*pRenderer, SDL_Color colorBkgnd);



//Star module Public Functions implementation---------------------------------------//
struct s_star* StarNew(int iLocX, int iLocY) {

	struct s_star * pNewStar = NULL;
	pNewStar = (struct s_star*)malloc(sizeof(struct s_star));
	pNewStar->location.x = iLocX;
	pNewStar->location.y = iLocY;
	pNewStar->color.r = rand()%(STAR_RGB_MAX - STAR_RGB_MIN + 1) + STAR_RGB_MIN;
	pNewStar->color.g = rand()%(STAR_RGB_MAX - STAR_RGB_MIN + 1) + STAR_RGB_MIN;
	pNewStar->color.b = rand()%(STAR_RGB_MAX - STAR_RGB_MIN + 1) + STAR_RGB_MIN;
	pNewStar->color.a = 255;
	do {
		pNewStar->speed.x = rand()%(2 * STAR_SPEED_MAX + 1) - STAR_SPEED_MAX;
		pNewStar->speed.y = rand()%(2 * STAR_SPEED_MAX + 1) - STAR_SPEED_MAX;
	} while ((pNewStar->speed.x == 0) || (pNewStar->speed.y == 0));

	return pNewStar;
}

struct s_star* StarDel(struct s_star*pStar, SDL_Renderer*pRenderer, SDL_Color colorBkgnd) {

	_StarHide(pStar, pRenderer, colorBkgnd);
	//SDL_RenderPresent(pRenderer);
	free(pStar);
	return NULL;
}

int StarMove(struct s_star*pStar, SDL_Renderer*pRenderer, SDL_Color colorBkgnd, SDL_Point whMax,int iPaddingW, int iPaddingH) {

	_StarHide(pStar, pRenderer, colorBkgnd);
	pStar->location.x += pStar->speed.x;
	pStar->location.y += pStar->speed.y;
//	if ((pStar->location.x < 0) || (pStar->location.x > whMax.x) ||
//		(pStar->location.y < 0) || (pStar->location.y > whMax.y)) {
	if ((pStar->location.x < 0 - iPaddingW) || (pStar->location.x > whMax.x + iPaddingW) ||
			(pStar->location.y < 0 - iPaddingH) || (pStar->location.y > whMax.y + iPaddingH)) {
		return -1; 	// Si l'étoile sort de la zone d'affichage (n'est pas redessinée)
	}
	_StarDraw(pStar, pRenderer);
	return 0;	// Sinon l'étoile est redessinée
}


void StarOffsetLocation(struct s_star*pStar, SDL_Point offset, SDL_Renderer*pRenderer, SDL_Color colorBkgnd) {
	_StarHide(pStar, pRenderer, colorBkgnd);
	pStar->location.x += 2 * offset.x;
	pStar->location.y += 2 * offset.y;
	_StarDraw(pStar, pRenderer);
	return;
}




//Star module Private Functions implementation---------------------------------------//
// Affichage de l'étoile passée en paramètre
void _StarDraw(struct s_star*pStar, SDL_Renderer*pRenderer) {
	SDL_SetRenderDrawColor(pRenderer, pStar->color.r, pStar->color.g, pStar->color.b, pStar->color.a);
	SDL_RenderFillRect(pRenderer, &pStar->location);
//	SDL_RenderDrawPoint(pRenderer, pStar->location.x, pStar->location.y );
	return;
}

// Effacement de l'étoile passée en paramètre
void _StarHide(struct s_star*pStar, SDL_Renderer*pRenderer, SDL_Color colorBkgnd) {
	SDL_SetRenderDrawColor(pRenderer, colorBkgnd.r, colorBkgnd.g, colorBkgnd.b, colorBkgnd.a);
	SDL_RenderFillRect(pRenderer, &pStar->location);
//	SDL_RenderDrawPoint(pRenderer, pStar->location.x, pStar->location.y );
	return;
}

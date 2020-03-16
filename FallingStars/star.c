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

struct s_star{
	SDL_Color 	color;
	SDL_Point	location;
	SDL_Point 	speed;
};

//Star module Private Prototypes declaration----------------------------------------//
void _StarDraw(struct s_star*pStar, t_starParams*pStarParams);
void _StarHide(struct s_star*pStar, t_starParams*pStarParams);



//Star module Public Functions implementation---------------------------------------//
struct s_star* StarNew(int iLocX, int iLocY) {

	struct s_star * pNewStar = NULL;

	pNewStar = (struct s_star*)malloc(sizeof(struct s_star));
	pNewStar->location.x = iLocX;
	pNewStar->location.y = iLocY;
	pNewStar->color.r = rand() % (STAR_RGB_MAX - STAR_RGB_MIN + 1) + STAR_RGB_MIN;
	pNewStar->color.g = rand() % (STAR_RGB_MAX - STAR_RGB_MIN + 1) + STAR_RGB_MIN;
	pNewStar->color.b = rand() % (STAR_RGB_MAX - STAR_RGB_MIN + 1) + STAR_RGB_MIN;
	pNewStar->color.a = 255;

	do {
		pNewStar->speed.x = rand() % (2 * STAR_SPEED_MAX + 1) - STAR_SPEED_MAX;
		pNewStar->speed.y = rand() % (2 * STAR_SPEED_MAX + 1) - STAR_SPEED_MAX;
	} while ((pNewStar->speed.x == 0) || (pNewStar->speed.y == 0));


	return pNewStar;
}

struct s_star* StarDel(struct s_star*pStar, t_starParams*pStarParams) {

	_StarHide(pStar, pStarParams);
	//SDL_RenderPresent(pRenderer);
	free(pStar);

	return NULL;
}

int StarMove(struct s_star*pStar, t_starParams*pStarParams) {

	_StarHide(pStar, pStarParams);
	pStar->location.x += pStar->speed.x;
	pStar->location.y += pStar->speed.y;

	if ((pStar->location.x < 0 - pStarParams->iPaddingW) || (pStar->location.x > pStarParams->pWhMax->x + pStarParams->iPaddingW) ||
		(pStar->location.y < 0 - pStarParams->iPaddingH) || (pStar->location.y > pStarParams->pWhMax->y + pStarParams->iPaddingH)) {
		return -1; 	// Si l'étoile sort de la zone d'affichage (n'est pas redessinée)
	}
	_StarDraw(pStar, pStarParams);
	return 0;	// Sinon l'étoile est redessinée

}


int StarOffsetLocation(struct s_star*pStar, t_starParams*pStarParams){
	_StarHide(pStar, pStarParams);
	pStar->location.x += 2 * pStarParams->pOffset->x;
	pStar->location.y += 2 * pStarParams->pOffset->y;
	_StarDraw(pStar, pStarParams);
	return 0;

}




//Star module Private Functions implementation---------------------------------------//
void _StarDraw(struct s_star*pStar, t_starParams*pStarParams) {
	SDL_SetRenderDrawColor(pStarParams->pRenderer, pStar->color.r, pStar->color.g, pStar->color.b, pStar->color.a);
	SDL_RenderDrawPoint(pStarParams->pRenderer, pStar->location.x, pStar->location.y);
	return;
}

void _StarHide(struct s_star*pStar, t_starParams*pStarParams) {
	SDL_SetRenderDrawColor(pStarParams->pRenderer, 
						   pStarParams->pColorBkgnd->r, 
						   pStarParams->pColorBkgnd->g, 
						   pStarParams->pColorBkgnd->b, 
						   pStarParams->pColorBkgnd->a);

	SDL_RenderDrawPoint(pStarParams->pRenderer, pStar->location.x, pStar->location.y );
	return;
}

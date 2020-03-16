/***************************************************************************
* File: star.h
*
*  Created on: xx/xx/xxxx
*      Author: xxxxxxxxxx
***************************************************************************/

#define STAR_NB_MAX			(1500)
#define STAR_SPEED_MAX		(8)
#define STAR_RGB_MIN		(100)
#define STAR_RGB_MAX		(255)


struct s_star* StarNew(int iLocX, int iLocY);
struct s_star* StarDel(struct s_star*pStar, SDL_Renderer*pRenderer, SDL_Color colorBkgnd);
int StarMove(struct s_star*pStar, SDL_Renderer*pRenderer, SDL_Color colorBkgnd, SDL_Point whMax, int iPaddingW, int iPaddingH);
void StarOffsetLocation(struct s_star*pStar, SDL_Point offset, SDL_Renderer*pRenderer, SDL_Color colorBkgnd);

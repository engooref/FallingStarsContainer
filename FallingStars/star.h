/***************************************************************************
* File: star.h
*
*  Created on: xx/xx/xxxx
*      Author: xxxxxxxxxx
***************************************************************************/

#define STAR_NB_MAX			(3000)
#define STAR_SPEED_MAX		(8)
#define STAR_RGB_MIN		(100)
#define STAR_RGB_MAX		(255)
#define STAR_GEN_NB_MIN		(10)
#define STAR_GEN_NB_MAX		(100)

typedef struct {
	SDL_Renderer	*	pRenderer;
	SDL_Color		*	pColorBkgnd;
	SDL_Point		*	pWhMax;
	SDL_Point		*	pOffset;
	int					iPaddingW;
	int					iPaddingH;
}t_starParams;

struct s_star* StarNew(int iLocX, int iLocY);
struct s_star* StarDel(struct s_star*pStar, t_starParams*pStarParams);
int StarMove(struct s_star*pStar,			t_starParams*pStarParams);
int StarOffsetLocation(struct s_star*pStar, t_starParams*pStarParams);

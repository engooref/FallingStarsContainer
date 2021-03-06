/***************************************************************************
* File: app.h
*
*  Created on: xx/xx/xxxx
*      Author: xxxxxxxxxx
***************************************************************************/

#include"app.h"
#include"star.h"
#include "Container\container.h"

//Private function prototypes--------------------------------------------//
Uint32 _AppAnimateCallBack(Uint32 interval, void*pParam);


enum APP_STATUS {
	ST_ALL_CLEARED					= 0x00000000,
	ST_ALL_SETTED					= 0xFFFFFFFF,
	ST_MOUSE_GEN_TRACKING			= 0x00000001,
	ST_CHANGE_ORIGIN_ASKED			= 0x00000002,
};

#define TglMouseGenTracking()		mBitsTgl(app.nStatus, 	ST_MOUSE_GEN_TRACKING)
#define IsMouseOrgTracking()		mIsBitsSet(app.nStatus, ST_MOUSE_GEN_TRACKING)

#define SetChangeOriginAsked()		mBitsSet(app.nStatus, 	ST_CHANGE_ORIGIN_ASKED)
#define ClrChangeOriginAsked()		mBitsClr(app.nStatus, 	ST_CHANGE_ORIGIN_ASKED)
#define IsChangeOriginAsked()		mIsBitsSet(app.nStatus, ST_CHANGE_ORIGIN_ASKED)


static struct {
	Uint32				nStatus;
	Uint32	 			nWindowID;
	SDL_Window	 	* 	pWindow;
	SDL_Renderer 	* 	pRenderer;
	SDL_Point			windowSize;
	SDL_Color			colorBkgnd;
	SDL_TimerID			nTimerID;

	t_pContainer		pStars;
	t_starParams		starsParams;
	int					timeOut;
	char			*	pWindowTitleStr;

	SDL_Point			genOrg,
						genOrgOld,
						genOrgOffset;

}app;

int AppNew(char*strWinTitle) {

	app.nStatus = ST_ALL_CLEARED;
	
	app.nWindowID = -1;
	app.pRenderer = NULL;
	app.pWindow = NULL;

	app.colorBkgnd.r = 0;
	app.colorBkgnd.r = 0;
	app.colorBkgnd.r = 0;
	app.colorBkgnd.a = 255;
	app.pWindowTitleStr = WINDOW_TITLE_STR;
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		fprintf(stderr, "SDL video init failed: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	app.pWindow = SDL_CreateWindow(
		strWinTitle,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
		);

	if (app.pWindow == NULL) {
		fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	app.nWindowID = SDL_GetWindowID(app.pWindow);
	SDL_GetWindowSize(app.pWindow, &app.windowSize.x, &app.windowSize.y);

	app.pRenderer = SDL_CreateRenderer(app.pWindow, -1, SDL_RENDERER_ACCELERATED);
	if (app.pRenderer == NULL) {
		fprintf(stderr, "Failed to create accelerated renderer.\n");
		app.pRenderer = SDL_CreateRenderer(app.pWindow, -1, SDL_RENDERER_SOFTWARE);
		if (app.pRenderer == NULL) {
			fprintf(stderr, "Failed to create software renderer.\n");
			return EXIT_FAILURE;
		}
		fprintf(stderr, "Software renderer created instead!\n");
	}

	SDL_SetRenderDrawColor(app.pRenderer, app.colorBkgnd.r, app.colorBkgnd.g, app.colorBkgnd.b, app.colorBkgnd.a);
	SDL_RenderClear(app.pRenderer);

	SDL_RenderPresent(app.pRenderer);

	srand((unsigned int)time(NULL));


	
	//---------------------------------------------------------------------------//
	app.timeOut = GEN_SEQUENCE_TIMEOUT_MIN;
	app.genOrgOld.x = app.genOrg.x = app.windowSize.x / 2;
	app.genOrgOld.y = app.genOrg.y = app.windowSize.y / 2;
	
	//Initialisation de la structure starParams----------------------------------//
	app.starsParams.pRenderer = app.pRenderer;
	app.starsParams.pColorBkgnd = &app.colorBkgnd;
	app.starsParams.pOffset = &app.genOrgOffset;
	app.starsParams.pWhMax = &app.windowSize;
	app.starsParams.iPaddingW = SCREEN_OUT_PADDING_W;
	app.starsParams.iPaddingH = SCREEN_OUT_PADDING_H;

	//Cr�ation du conteneur------------------------------------------------------//
	app.pStars = ContainerNew((t_ptfVV)StarDel);

	app.nTimerID = SDL_AddTimer(ANIMATION_TICK, _AppAnimateCallBack, NULL);

	return 0;
}

int AppDel(void) {
	
	//Destroy remaining stars section--------------------------------------------//
	app.pStars = ContainerDel(app.pStars, &app.starsParams);
	//---------------------------------------------------------------------------//

	SDL_RemoveTimer(app.nTimerID);
	
	if (app.pWindow) {
		SDL_DestroyWindow(app.pWindow);
		app.pWindow = NULL;
	}
	if (app.pRenderer) {
		SDL_DestroyRenderer(app.pRenderer);
		app.pRenderer = NULL;
	}
	
	app.nWindowID = -1;
	SDL_Quit();

	return 0;
}

int AppRun(void) {
	int quit;
	SDL_Event event;

	quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_MOUSEMOTION:
				if (IsMouseOrgTracking()) {
					app.genOrg.x = event.motion.x;
					app.genOrg.y = event.motion.y;
					app.genOrgOffset.x = app.genOrg.x - app.genOrgOld.x;
					app.genOrgOffset.y = app.genOrg.y - app.genOrgOld.y;
					SetChangeOriginAsked();
					app.genOrgOld.x = app.genOrg.x;
					app.genOrgOld.y = app.genOrg.y;
				}
				break;
			case SDL_WINDOWEVENT:
				if (event.window.windowID != app.nWindowID) break;
				switch (event.window.event) {
				case SDL_WINDOWEVENT_CLOSE:
					event.type = SDL_QUIT;
					SDL_PushEvent(&event);
					break;
				default:
					break;
				}
				break;
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit = 1;
					break;
				case SDLK_SPACE:
					TglMouseGenTracking();
					if(IsMouseOrgTracking()){
						SDL_GetMouseState(&app.genOrg.x, &app.genOrg.y);
					}
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}
	return 0;
}


Uint32 _AppAnimateCallBack(Uint32 interval, void*pParam) {

	char buf[128];
	//Falling stars moving section------------------------------------------------------------------------------//
	
	ContainerParseDelIf(app.pStars, (t_ptfVV)StarMove, &app.starsParams);

	sprintf(buf, "%s [%03d]", app.pWindowTitleStr, ContainerCard(app.pStars));
	SDL_SetWindowTitle(app.pWindow, buf);

	//Generation rate timeout section----------------------------------------------------------------------------//
	if (app.timeOut) {
		if (--app.timeOut == 0) {

			app.timeOut = rand() % (GEN_SEQUENCE_TIMEOUT_MAX - GEN_SEQUENCE_TIMEOUT_MIN + 1) + GEN_SEQUENCE_TIMEOUT_MIN;

			int nbStarsToGenerate = rand() % (STAR_GEN_NB_MAX - STAR_GEN_NB_MIN + 1) + STAR_GEN_NB_MIN;

			while ((nbStarsToGenerate--) && (ContainerCard(app.pStars) <= STAR_NB_MAX) ) { ContainerPushback(app.pStars, StarNew(app.genOrg.x, app.genOrg.y)); }
		}
	}

	//Stars mouse cursor move tracking section------------------------------------------------------------------//
	if (IsChangeOriginAsked()) {
		//Take into account the falling stars generation origin change--------------------------------------//
		ContainerParse(app.pStars, (t_ptfVV)StarOffsetLocation, &app.starsParams);


		//Acknowledgment of the origin change------------------------//
		ClrChangeOriginAsked();
	}


	SDL_RenderPresent(app.pRenderer);

	return interval;
}

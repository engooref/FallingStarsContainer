/***************************************************************************
* File: app.h
*
*  Created on: xx/xx/xxxx
*      Author: xxxxxxxxxx
***************************************************************************/

#define _CRT_SECURE_NO_WARNINGS


#ifdef WIN32
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG
#endif // WIN32

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifdef WIN32
#include <SDL2\SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#ifdef WIN32
#pragma comment(lib,"SDL2/x86/SDL2.lib")
#pragma comment(lib,"SDL2/x86/SDL2main.lib")
#endif // WIN32

#define WINDOW_TITLE_STR			"Falling Stars"

#define SCREEN_WIDTH				((int)(640*(16.0/9.0)))
#define SCREEN_HEIGHT				((int)(480*(16.0/9.0)))
#define SCREEN_OUT_PADDING_W		((int)(SCREEN_WIDTH/1))
#define SCREEN_OUT_PADDING_H		((int)(SCREEN_HEIGHT/1))
#define ANIMATION_TICK				(20)
#define GEN_SEQUENCE_TIMEOUT_MIN	(5)
#define GEN_SEQUENCE_TIMEOUT_MAX	(30)


#define mBitsSet(f,m)			((f)|=(m))
#define mBitsClr(f,m)			((f)&=(~(m)))
#define mBitsTgl(f,m)			((f)^=(m))
#define mBitsMsk(f,m)			((f)& (m))
#define mIsBitsSet(f,m)			(((f)&(m))==(m))
#define mIsBitsClr(f,m)			(((~(f))&(m))==(m))


int AppNew(char*strWinTitle);
int AppDel(void);
int AppRun(void);

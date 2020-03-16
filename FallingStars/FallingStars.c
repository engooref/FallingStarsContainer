/*
 ============================================================================
 Name        : FallingStars.c
 Author      : **************
 Version     :
 Copyright   : Your copyright notice
 Description : C Ansi-style
 ============================================================================
 */

#include"app.h"

int main(int argc, char**argv) {

#ifdef WIN32
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG
#endif // WIN32

	printf("==========ENTER %s===========\n", WINDOW_TITLE_STR);

	if (AppNew(WINDOW_TITLE_STR) == EXIT_FAILURE) {
		fprintf(stderr, "Failed to initialize App! Program aborted!\n");
		printf("==========EXIT StarExpans WITH FAILURE===========\n");
		return EXIT_FAILURE;
	}
	AppRun();
	AppDel();
	printf("==========EXIT  %s===========\n", WINDOW_TITLE_STR);
	return EXIT_SUCCESS;
}

#include <stdio.h>
#include "game.h"

int main(int argc, char *argv[])
{
	CB_WindowOptions_t windowOptions = {
		.title = "Super Slime Bros",

		.windowFlags = SDL_WINDOW_OPENGL,
		.rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE,

		.FPS = 60.f,

		.width = 800, .height = 600,
	};

	CB_Window_t *window = CB_CreateWindow(windowOptions);	
	if (window == NULL)
		exit(EXIT_FAILURE);

	CB_Game_t *game = CB_CreateGame(window);
	if (game == NULL) {
		CB_DestroyWindow(window);
		exit(EXIT_FAILURE);
	}

	CB_RunState(game->state);

	CB_DestroyGame(game);
	CB_DestroyWindow(window);

	return 0;
}

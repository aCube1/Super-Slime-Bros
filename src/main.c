#include <stdio.h>
#include "System/game.h"

int main(int argc, char *argv[])
{
	CB_WindowOptions_t windowOptions = {
		.title = "Super Slime Bros",

		.windowFlags = SDL_WINDOW_OPENGL,
		.rendererFlags = SDL_RENDERER_ACCELERATED,

		.FPS = 60.f,

		.width = 800, .height = 600,
	};

	CB_Window_t *window = CB_CreateWindow(windowOptions);	
	if (window == NULL)
		exit(EXIT_FAILURE);

	CB_GameOptions_t gameOptions = {
		.window = window,
	};

	CB_Game_t *game = CB_CreateGameState(gameOptions);
	if (game == NULL) {
		CB_DestroyWindow(window);
		exit(EXIT_FAILURE);
	}

	CB_GameRun(game);

	CB_DestroyGameState(game);
	CB_DestroyWindow(window);

	return 0;
}

#include <stdio.h>
#include "System/game.h"

void create(void);
void destroy(void);

void eventHandler(CB_Window_t *window);
void update(CB_Window_t *window);
void render(CB_Window_t *window);

int main(int argc, char *argv[])
{
	CB_WindowOptions_t windowOptions = {
		.title = "Super Slime Bros",

		.windowFlags = SDL_WINDOW_OPENGL,
		.rendererFlags = SDL_RENDERER_ACCELERATED,

		.FPS = 60.f,

		.width = 800, .height = 600,
	};

	CB_GameOptions_t gameOptions = {
		.create = create,
		.destroy = destroy,

		.eventHandler = eventHandler,
		.update = update,
		.render = render,	
	};

	CB_Window_t *window = CB_CreateWindow(windowOptions);	
	CB_Game_t *game = CB_CreateGameState(gameOptions);

	CB_GameRun(game, window);

	CB_DestroyGameState(game);
	CB_DestroyWindow(window);

	return 0;
}

void create(void) {}
void destroy(void) {}

void eventHandler(CB_Window_t *window) {}
void update(CB_Window_t *window) {}
void render(CB_Window_t *window) {}

#include "Core/log.h"
#include "Core/window.h"

CB_Window_t *CB_CreateWindow(CB_WindowOptions_t options)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		CB_LogSDLError("Cannot Initialize SDL2");

		return NULL;
	}

	CB_Window_t *window = malloc(sizeof(CB_Window_t));

	if (window == NULL) {
		CB_LogError("Cannot Create Window Bases");

		CB_DestroyWindow(window);
		return NULL;
	}
	CB_LogInfo("Window Bases Created");
	
	int winX, winY, winWidth, winHeight, winFlags, renderFlags;

	winX = options.x ? options.x : SDL_WINDOWPOS_CENTERED; /* Window X Position */
	winY = options.y ? options.y : SDL_WINDOWPOS_CENTERED; /* Window Y Position */
	winWidth = options.width ? options.width : 800; /* Window Width */
        winHeight = options.height ? options.height : 600; /* Window Height */	
	winFlags = options.windowFlags ? options.windowFlags : 0; /* Window Flags */

	window->handler = SDL_CreateWindow(options.title, winX, winY, winWidth, winHeight, winFlags);
	if (window == NULL) {
		CB_LogError("Cannot Create Window Handler");

		CB_DestroyWindow(window);
		return NULL;
	}
	CB_LogInfo("Window Handler Created");

	renderFlags = options.rendererFlags ? options.rendererFlags : 0; /* Renderer Flags */

	window->renderer = SDL_CreateRenderer(window->handler, -1, renderFlags);
	if (window->renderer == NULL) {
		CB_LogError("Cannot Create Window Renderer");

		CB_DestroyWindow(window);
		return NULL;
	}
	CB_LogInfo("Window Renderer Created");

	for (int i = 0; i < 322; i++) 
		window->keys[i] = false;

	window->maxFPS = options.FPS ? options.FPS : 30.f;
	window->isOpen = true;

	CB_LogInfo("Window Created And Openned");
	return window;
}

void CB_DestroyWindow(CB_Window_t *window)
{
	if (window != NULL) {
		if (window->handler != NULL) {
			SDL_DestroyWindow(window->handler);
			CB_LogInfo("Window Handler Destroyed");
		}

		if (window->renderer != NULL) {
			SDL_DestroyRenderer(window->renderer);
			CB_LogInfo("Window Renderer Destroyed");
		}

		free(window);
		CB_LogInfo("Window Destroyed");
	}

	SDL_Quit();
	CB_LogInfo("SDL2 Quitted");
}

void CB_CheckKeyboard(CB_Window_t *window, SDL_KeyboardEvent *keyboardEvent)
{
	switch (keyboardEvent->type) {
		case SDL_KEYDOWN:
			break;
			window->keys[keyboardEvent->keysym.sym] = true;
		case SDL_KEYUP:
			window->keys[keyboardEvent->keysym.sym] = false;
			break;
		default:
			break;
	}
}

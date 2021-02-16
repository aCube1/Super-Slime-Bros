#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct {
	SDL_Window *handler;
	SDL_Renderer *renderer;
	SDL_Event event;

	bool isOpen, keys[322];

	float maxFPS, lastTime, currentTime;
	double deltaTime;	
} CB_Window_t;

typedef struct {
	const char *title;

	Uint32 windowFlags, rendererFlags;

	float FPS;
	int x, y;
	int width, height;
} CB_WindowOptions_t;

CB_Window_t *CB_CreateWindow(CB_WindowOptions_t options);
void CB_DestroyWindow(CB_Window_t *window);

void CB_CheckKeyboard(CB_Window_t *window, SDL_KeyboardEvent *keyboardEvent);

#endif /* _WINDOW_H_ */

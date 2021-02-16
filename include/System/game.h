#ifndef _GAME_H_
#define _GAME_H_

#include "Core/window.h"

typedef struct {
	CB_Window_t *window;
	
	void (*create)(CB_Window_t *window);
	void (*destroy)(void);

	void (*eventHandler)(CB_Window_t *window);
	void (*update)(CB_Window_t *window);
	void (*render)(CB_Window_t *window);
} CB_Game_t;

typedef struct {
	CB_Window_t *window;

	void (*create)(CB_Window_t *window);
	void (*destroy)(void);

	void (*eventHandler)(CB_Window_t *window);
	void (*update)(CB_Window_t *window);
	void (*render)(CB_Window_t *window);
} CB_GameOptions_t;

CB_Game_t *CB_CreateGameState(CB_GameOptions_t options);
void CB_DestroyGameState(CB_Game_t *game);

void CB_GameEventHandler(CB_Game_t *game);
void CB_GameUpdate(CB_Game_t *game);
void CB_GameRender(CB_Game_t *game);

void CB_GameRun(CB_Game_t *game);

#endif /* _GAME_H_ */

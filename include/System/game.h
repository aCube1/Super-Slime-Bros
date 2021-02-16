#ifndef _GAME_H_
#define _GAME_H_

#include "Core/window.h"

typedef struct {
	void (*create)(void);
	void (*destroy)(void);

	void (*eventHandler)(CB_Window_t *window);
	void (*update)(CB_Window_t *window);
	void (*render)(CB_Window_t *window);
} CB_Game_t;

typedef struct {
	void (*create)(void);
	void (*destroy)(void);

	void (*eventHandler)(CB_Window_t *window);
	void (*update)(CB_Window_t *window);
	void (*render)(CB_Window_t *window);
} CB_GameOptions_t;

CB_Game_t *CB_CreateGameState(CB_GameOptions_t options);
void CB_DestroyGameState(CB_Game_t *game);

void CB_GameEventHandler(CB_Game_t *game, CB_Window_t *window);
void CB_GameUpdate(CB_Game_t *game, CB_Window_t *window);
void CB_GameRender(CB_Game_t *game, CB_Window_t *window);

void CB_GameRun(CB_Game_t *game, CB_Window_t *window);

#endif /* _GAME_H_ */

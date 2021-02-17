#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL2/SDL_events.h>
#include "Graphics/sprite.h"

typedef struct {
	CB_Sprite_t *sprite;	
	SDL_Rect rect;

	int Hspeed, Vspeed;
	short vx, vy; /* Vector X/Y */
} CB_Player_t;

typedef struct {
	SDL_Renderer *renderer;
	int x, y, width, height, Hspeed, Vspeed;

	const char *filePath;
} CB_PlayerOptions_t;

CB_Player_t *CB_CreatePlayer(CB_PlayerOptions_t options);
void CB_DestroyPlayer(CB_Player_t *player);

void CB_PlayerEventHandler(CB_Player_t *player, SDL_Event *event);
void CB_PlayerUpdate(CB_Player_t *player, float deltaTime);
void CB_PlayerRender(CB_Player_t *player, SDL_Renderer *renderer);

#endif /* _PLAYER_H_ */

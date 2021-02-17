#ifndef _GAME_H_
#define _GAME_H_

#include "System/state.h"
#include "System/player.h"

typedef struct {
	CB_State_t *state;
	CB_Player_t *player;
} CB_Game_t;

CB_Game_t *CB_CreateGame(CB_Window_t *window);
void CB_DestroyGame(CB_Game_t *game);

#endif /* _SLIME_H_ */

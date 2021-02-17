#include "System/input.h"
#include "Core/log.h"
#include "System/player.h"

CB_Player_t *CB_CreatePlayer(CB_PlayerOptions_t options)
{
	CB_Player_t *player = malloc(sizeof(CB_Player_t));

	if (player == NULL) {
		CB_LogError("Cannot Create Player Bases");

		CB_DestroyPlayer(player);
		return NULL;
	}
	CB_LogInfo("Player Bases Created");

	CB_SpriteOptions_t spriteOptions = {
		.renderer = options.renderer,
		.filePath = options.filePath,	
	};	

	player->sprite = CB_CreateSprite(spriteOptions); 
	if (player->sprite == NULL) {
		CB_LogError("Cannot Create Player Sprite");

		CB_DestroyPlayer(player);
		return NULL;
	}
	CB_LogInfo("Player Sprite Created");

	player->rect = (SDL_Rect) {
		.x = options.x ? options.x : 0,
		.y = options.y ? options.y : 0,
		.w = options.width ? options.width : 64,
		.h = options.height ? options.height : 64,
	};

	player->Hspeed = options.Hspeed ? options.Hspeed : 200;
	player->Vspeed = options.Vspeed ? options.Vspeed : 200;

	return player;
}

void CB_DestroyPlayer(CB_Player_t *player)
{
	if (player != NULL) {
		if (player->sprite != NULL) {
			CB_DestroySprite(player->sprite);
			CB_LogInfo("Player Sprite Destroyed");
		}

		free(player);
		CB_LogInfo("Player Bases Destroyed");
	}
}

void CB_PlayerEventHandler(CB_Player_t *player, SDL_Event *event)
{
	if (CB_KeyboardIsDown(SDLK_a)) {
		player->vx = -1;
	} else if (CB_KeyboardIsDown(SDLK_d)) {
		player->vx = 1;
	}

}

void CB_PlayerUpdate(CB_Player_t *player, float deltaTime)
{			
	player->rect.x += (player->vx * player->Hspeed) * deltaTime;
	player->rect.y += (player->vy * player->Vspeed) * deltaTime;

	player->vx = 0;
	player->vy = 0;
}

void CB_PlayerRender(CB_Player_t *player, SDL_Renderer *renderer)
{
	CB_DrawSprite(renderer, player->sprite, &player->rect);
}

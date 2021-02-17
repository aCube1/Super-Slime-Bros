#include "Core/log.h"
#include "game.h"

void CB_Create(CB_Window_t *window);
void CB_Destroy(void);

void CB_EventHandler(CB_Window_t *window);
void CB_Update(CB_Window_t *window);
void CB_Render(CB_Window_t *window);

CB_Game_t *CB_CreateGame(CB_Window_t *window)
{
	CB_Game_t *game = malloc(sizeof(CB_Game_t));

	if (game == NULL) {
		CB_LogError("Cannot Create Game Base");

		CB_DestroyGame(game);
		return NULL;
	}
	CB_LogInfo("Game Base Created");

	CB_StateOptions_t stateOptions = {
		.window = window,

		.create = CB_Create,
		.destroy = CB_Destroy,

		.eventHandler = CB_EventHandler,
		.update = CB_Update,
		.render = CB_Render,
	};

	game->state = CB_CreateState(stateOptions);
	if (game->state == NULL) {
		CB_LogError("Cannot Create Game State To Game Base");

		CB_DestroyGame(game);
		return NULL;
	}
	CB_LogInfo("Game State To Game Base Created");

	return game;
}

void CB_DestroyGame(CB_Game_t *game)
{
	if (game != NULL) {
		if (game->state != NULL)
			CB_DestroyState(game->state);
		
		free(game);
		CB_LogInfo("Game Base Destroyed");
	}
}

void CB_Create(CB_Window_t *window) 
{

}

void CB_Destroy(void)
{

}

void CB_EventHandler(CB_Window_t *window)
{

}

void CB_Update(CB_Window_t *window)
{

}

void CB_Render(CB_Window_t *window)
{

}

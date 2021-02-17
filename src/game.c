#include "Core/log.h"
#include "game.h"

static CB_Player_t *player;

bool CB_Create(CB_Window_t *window);
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

bool CB_Create(CB_Window_t *window)
{
	CB_PlayerOptions_t playerOptions = {
		.renderer = window->renderer,
		.x = 300,
		.y = 400,
		.width = 64,
		.height = 64,

		.filePath = "../res/slime.png"
	};	

	player = CB_CreatePlayer(playerOptions);
	if (player == NULL) {
		CB_LogError("Cannot Create Player For Game");

		return false;
	}

	return true;
}

void CB_Destroy(void)
{
	if (player != NULL) {
		CB_DestroyPlayer(player);
	}
}

void CB_EventHandler(CB_Window_t *window)
{
	CB_PlayerEventHandler(player, &window->event);
}

void CB_Update(CB_Window_t *window)
{
	CB_PlayerUpdate(player, window->deltaTime);
}

void CB_Render(CB_Window_t *window)
{
	CB_PlayerRender(player, window->renderer);
}

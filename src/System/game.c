#include "Core/log.h"
#include "System/game.h"
#include "Graphics/sprite.h"

CB_Sprite_t *sprite = NULL;
SDL_Rect dstRect = {
	.x = 64,
	.y = 64,
	.w = 64,
	.h = 64,
};

CB_Game_t *CB_CreateGameState(CB_GameOptions_t options)
{
	CB_Game_t *game = malloc(sizeof(CB_Game_t));

	if (game == NULL) {
		CB_LogError("Cannot Create Game State");

		CB_DestroyGameState(game);
		return NULL;
	}

	if (options.window == NULL) {
		CB_LogError("Game Window Is Required To Load GameState");

		CB_DestroyGameState(game);
		return NULL;
	}

	game->window = options.window;

	game->create = options.create ? options.create : NULL;
	if (game->create != NULL)
		game->create(game->window);

	game->destroy = options.destroy ? options.destroy : NULL;

	game->eventHandler = options.eventHandler ? options.eventHandler : NULL;
	game->update = options.update ? options.update : NULL;
	game->render = options.render ? options.render : NULL;

	return game;
}

void CB_DestroyGameState(CB_Game_t *game)
{
	if (game != NULL) {
		if (game->destroy != NULL)
			game->destroy();

		free(game);
		CB_LogInfo("Game State Destroyed");
	}
}

void CB_GameEventHandler(CB_Game_t *game)
{
	while (SDL_PollEvent(&game->window->event)) {
		switch (game->window->event.type) {
			case SDL_QUIT:
				game->window->isOpen = false;
				break;
			default:
				if (game->eventHandler != NULL)
					game->eventHandler(game->window);
				
				CB_CheckKeyboard(game->window, &game->window->event.key);
				break;
		}
	}
}

void CB_GameUpdate(CB_Game_t *game)
{
	if (game->update != NULL)
		game->update(game->window);
}

void CB_GameRender(CB_Game_t *game)
{
	SDL_RenderClear(game->window->renderer);
	/* Draw Content */
	if (game->render != NULL)
		game->render(game->window);

	SDL_RenderPresent(game->window->renderer);
}

void CB_GameRun(CB_Game_t *game)
{
	while (game->window->isOpen) {
		game->window->deltaTime = (SDL_GetTicks() - game->window->lastTime) / 1000.f;
		game->window->lastTime = SDL_GetTicks();

		CB_GameEventHandler(game);
		CB_GameUpdate(game);
		CB_GameRender(game);

		game->window->currentTime = SDL_GetTicks() - game->window->lastTime;
		if (1000.f / game->window->maxFPS > game->window->currentTime) {
			SDL_Delay((1000.f / game->window->maxFPS) - game->window->currentTime);
		}
	}
}

#include "Core/log.h"
#include "System/game.h"

CB_Game_t *CB_CreateGameState(CB_GameOptions_t options)
{
	CB_Game_t *game = malloc(sizeof(CB_Game_t));

	if (game == NULL) {
		CB_LogError("Cannot Create Game State");

		CB_DestroyGameState(game);
		return NULL;
	}

	game->create = options.create ? options.create : NULL;
	if (game->create != NULL)
		game->create();

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

void CB_GameEventHandler(CB_Game_t *game, CB_Window_t *window)
{
	while (SDL_PollEvent(&window->event)) {
		switch (window->event.type) {
			case SDL_QUIT:
				window->isOpen = false;
				break;
			default:
				if (game->eventHandler != NULL)
					game->eventHandler(window);
				
				CB_CheckKeyboard(window, &window->event.key);
				break;
		}
	}
}

void CB_GameUpdate(CB_Game_t *game, CB_Window_t *window)
{
	if (game->update != NULL)
		game->update(window);
}

void CB_GameRender(CB_Game_t *game, CB_Window_t *window)
{
	SDL_RenderClear(window->renderer);
	/* Draw Content */
	if (game->render != NULL)
		game->render(window);
	SDL_RenderPresent(window->renderer);
}

void CB_GameRun(CB_Game_t *game, CB_Window_t *window)
{
	while (window->isOpen) {
		window->deltaTime = (SDL_GetTicks() - window->lastTime) / 1000.f;
		window->lastTime = SDL_GetTicks();

		CB_GameEventHandler(game, window);
		CB_GameUpdate(game, window);
		CB_GameRender(game, window);

		window->currentTime = SDL_GetTicks() - window->lastTime;
		if (1000.f / window->maxFPS > window->currentTime) {
			SDL_Delay((1000.f / window->maxFPS) - window->currentTime);
		}
	}
}

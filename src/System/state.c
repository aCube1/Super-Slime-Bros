#include "System/input.h"
#include "Core/log.h"
#include "System/state.h"

static void CB_StateEventHandler(CB_State_t *state);
static void CB_StateUpdate(CB_State_t *state);
static void CB_StateRender(CB_State_t *state);

CB_State_t *CB_CreateState(CB_StateOptions_t options)
{
	CB_State_t *state = malloc(sizeof(CB_State_t));

	if (state == NULL) {
		CB_LogError("Cannot Create State");

		CB_DestroyState(state);
		return NULL;
	}

	if (options.window == NULL) {
		CB_LogError("Game Window Is Required To Load State");

		CB_DestroyState(state);
		return NULL;
	}

	state->window = options.window;

	state->create = options.create ? options.create : NULL;
	if (state->create != NULL)
		if (!state->create(state->window)) {
			CB_LogError("Create CallBack Returned \"false\", The State Cannot Be Created");

			CB_DestroyState(state);
			return NULL;
		}

	state->destroy = options.destroy ? options.destroy : NULL;

	state->eventHandler = options.eventHandler ? options.eventHandler : NULL;
	state->update = options.update ? options.update : NULL;
	state->render = options.render ? options.render : NULL;

	return state;
}

void CB_DestroyState(CB_State_t *state)
{
	if (state != NULL) {
		if (state->destroy != NULL)
			state->destroy();

		free(state);
		CB_LogInfo("State Destroyed");
	}
}

void CB_RunState(CB_State_t *state)
{
	while (state->window->isOpen) {
		state->window->deltaTime = (SDL_GetTicks() - state->window->lastTime) / 1000.f;
		state->window->lastTime = SDL_GetTicks();

		CB_StateEventHandler(state);
		CB_StateUpdate(state);
		CB_StateRender(state);

		state->window->currentTime = SDL_GetTicks() - state->window->lastTime;
		if (1000.f / state->window->maxFPS > state->window->currentTime) {
			SDL_Delay((1000.f / state->window->maxFPS) - state->window->currentTime);
		}
	}
}

static void CB_StateEventHandler(CB_State_t *state)
{
	while (SDL_PollEvent(&state->window->event)) {
		switch (state->window->event.type) {
			case SDL_QUIT:
				state->window->isOpen = false;
				break;
			default:
				CB_CheckKeyboard(&state->window->event.key);
				if (state->eventHandler != NULL)
					state->eventHandler(state->window);
				
				break;
		}
	}
}

static void CB_StateUpdate(CB_State_t *state)
{
	if (state->update != NULL)
		state->update(state->window);
}

static void CB_StateRender(CB_State_t *state)
{
	SDL_RenderClear(state->window->renderer);
	/* Draw Content */
	if (state->render != NULL)
		state->render(state->window);

	SDL_RenderPresent(state->window->renderer);
}

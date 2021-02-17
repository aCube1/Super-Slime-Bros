#ifndef _STATE_H_
#define _STATE_H_

#include "Core/window.h"

typedef struct {
	CB_Window_t *window;
	
	void (*create)(CB_Window_t *window);
	void (*destroy)(void);

	void (*eventHandler)(CB_Window_t *window);
	void (*update)(CB_Window_t *window);
	void (*render)(CB_Window_t *window);
} CB_State_t;

typedef struct {
	CB_Window_t *window;

	void (*create)(CB_Window_t *window);
	void (*destroy)(void);

	void (*eventHandler)(CB_Window_t *window);
	void (*update)(CB_Window_t *window);
	void (*render)(CB_Window_t *window);
} CB_StateOptions_t;

CB_State_t *CB_CreateState(CB_StateOptions_t options);
void CB_DestroyState(CB_State_t *state);
void CB_RunState(CB_State_t *state);

#endif /* _STATE_H_ */

#include "System/input.h"

static bool keyboard[322];

void CB_CheckKeyboard(SDL_KeyboardEvent *keyboardEvent)
{

#ifndef _KEYBOARD_
#define _KEYBOARD_
	for (int i = 0; i < 322; i++) 
		keyboard[i] = false;
#endif /* _KEYBOARD_ */

	switch (keyboardEvent->type) {
		case SDL_KEYDOWN:
			keyboard[keyboardEvent->keysym.sym] = true;
			break;
		case SDL_KEYUP:
			keyboard[keyboardEvent->keysym.sym] = false;
			break;
		default:
			break;
	}
}

bool CB_KeyboardIsDown(int key)
{
	return keyboard[key];
}

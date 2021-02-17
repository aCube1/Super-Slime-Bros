#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdbool.h>
#include "SDL2/SDL_events.h"

void CB_CheckKeyboard(SDL_KeyboardEvent *keyboardEvent);

bool CB_KeyboardIsDown(int key);

#endif /* _INPUT_H_ */

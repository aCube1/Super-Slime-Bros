#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL2/SDL_render.h>

typedef struct {
	SDL_Texture *texture;
	SDL_Rect srcRect;

	unsigned char *data;
	int width, height, nrChannels, pitch;
	Uint32 pixelFormat;
} CB_Sprite_t;

typedef struct {
	SDL_Renderer *renderer;
	SDL_Rect *srcRect;

	const char *filePath;
} CB_SpriteOptions_t;

CB_Sprite_t *CB_CreateSprite(CB_SpriteOptions_t options);
void CB_DestroySprite(CB_Sprite_t *sprite);

void CB_DrawSprite(SDL_Renderer *renderer, CB_Sprite_t *sprite, SDL_Rect *dstRect);

#endif /* _SPRITE_H_ */

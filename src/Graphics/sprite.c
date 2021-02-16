#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "Core/log.h"
#include "Graphics/sprite.h"

CB_Sprite_t *CB_CreateSprite(CB_SpriteOptions_t options)
{
	CB_Sprite_t *sprite = malloc(sizeof(CB_Sprite_t));

	if (sprite == NULL) {
		CB_LogError("Cannot Create Sprite Base");

		CB_DestroySprite(sprite);
		return NULL;
	}
	CB_LogInfo("Sprite Base Created");

	sprite->data = stbi_load(options.filePath, &sprite->width, &sprite->height, &sprite->nrChannels, 0);
	if (sprite->data == NULL) {
		CB_LogError("Cannot Load Sprite Data");
		CB_LogError(stbi_failure_reason());

		CB_DestroySprite(sprite);
		return NULL;
	}
	CB_LogInfo("Sprite Data Loaded");

	if (sprite->nrChannels == STBI_rgb) {
		sprite->pitch = sprite->width * (sizeof(uint8_t) * 3);
		sprite->pixelFormat = SDL_PIXELFORMAT_RGB24;
	} else if (sprite->nrChannels == STBI_rgb_alpha) {
		sprite->pitch = sprite->width * (sizeof(uint8_t) * 4);
		sprite->pixelFormat = SDL_PIXELFORMAT_RGBA32;
	} else {
		sprite->pitch = 0;
		sprite->pixelFormat = SDL_PIXELFORMAT_UNKNOWN;
	}

	sprite->texture = SDL_CreateTexture(options.renderer, sprite->pixelFormat, SDL_TEXTUREACCESS_STREAMING, sprite->width, sprite->height);
	if (sprite->texture == NULL) {
		CB_LogError("Cannot Load Sprite Texture");

		CB_DestroySprite(sprite);
		return NULL;
	}
	CB_LogInfo("Sprite Texture Loaded");

	if (SDL_UpdateTexture(sprite->texture, NULL, sprite->data, sprite->pitch) < 0) {
		CB_LogError("Cannot Load Data To Sprite Texture");

		CB_DestroySprite(sprite);
		return NULL;
	}
	CB_LogInfo("Data Loaded To Sprite Texture");

	sprite->srcRect = (options.srcRect != NULL) ? *options.srcRect : (SDL_Rect) {
		.x = 0,
		.y = 0,
		.w = sprite->width,
		.h = sprite->height,
	};

	return sprite;
}

void CB_DestroySprite(CB_Sprite_t *sprite)
{
	if (sprite != NULL) {
		if (sprite->data != NULL) {
			stbi_image_free(sprite->data);
			CB_LogInfo("Sprite Data Destroyed");
		}

		if (sprite->texture != NULL) {
			SDL_DestroyTexture(sprite->texture);
			CB_LogInfo("Sprite Texture Destroyed");
		}

		free(sprite);
		CB_LogInfo("Sprite Destroyed");
	}
}

void CB_DrawSprite(SDL_Renderer *renderer, CB_Sprite_t *sprite, SDL_Rect *dstRect)
{
	SDL_RenderCopy(renderer, sprite->texture, &sprite->srcRect, dstRect);
}

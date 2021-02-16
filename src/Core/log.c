#include <SDL2/SDL_error.h>
#include "Core/log.h"

void CB_Log(const char *msg, int logPrefix)
{
	switch (logPrefix) {
		case CB_LOG_ERROR:
			fprintf(stderr, "[ERROR] CUBE - %s\n", msg);
			break;
		case CB_LOG_WARN:
			fprintf(stdout, "[WARN] CUBE - %s\n", msg);
			break;
		case CB_LOG_DEBUG:
			fprintf(stdout, "[DEBUG] CUBE - %s\n", msg);
			break;
		case CB_LOG_INFO:
			fprintf(stdout, "[INFO] CUBE - %s\n", msg);
			break;
		case CB_LOG_SDLERROR:
			fprintf(stderr, "[SDL ERROR] CUBE - %s\n\t:%s\n", msg, SDL_GetError());
			break;
	};
}

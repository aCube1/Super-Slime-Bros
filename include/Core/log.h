#ifndef _LOG_H_
#define _LOG_H_

#define CB_LogError(msg) CB_Log(msg, CB_LOG_ERROR)
#define CB_LogWarn(msg) CB_Log(msg, CB_LOG_WARN)
#define CB_LogDebug(msg) CB_Log(msg, CB_LOG_Debug)
#define CB_LogInfo(msg) CB_Log(msg, CB_LOG_INFO)

#define CB_LogSDLError(msg) CB_Log(msg, CB_LOG_SDLERROR)

enum {
	CB_LOG_ERROR,
	CB_LOG_WARN,
	CB_LOG_DEBUG,
	CB_LOG_INFO,

	CB_LOG_SDLERROR,
};

void CB_Log(const char *msg, int logPrefix);

#endif /* _LOG_H_ */

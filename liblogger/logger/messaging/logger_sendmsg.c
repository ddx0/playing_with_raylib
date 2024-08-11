#include "logger.priv.h"
#include <string.h>
#include <stddef.h>

void _replaceMsgNum(Logger *self) {
    char *pStart = strstr(self->msg.msgBuf, "[Q");
    pStart++;
    char *const pEnd = strstr(self->msg.msgBuf, "Q]");
    const ptrdiff_t diff = pEnd - pStart; // size is 0-counted
    const unsigned workingBufferSize = diff + 1;
    
    ASSERT(workingBufferSize == 20, "working buffer not size 20");

    char msgNumAsStr[20 + 1];
    snprintf(msgNumAsStr, 21, "%20llu", self->msg.msgNum);

    ASSERT(msgNumAsStr[20] == '\0', "did not null terminate");

    memcpy(pStart, msgNumAsStr, workingBufferSize);
}

// info: send message to logger
// return: 0 on message sent, -1 on message fail
int logger_sendmsg(Logger *logger, const char *msg) {
    if (!_logger_create_message(logger, msg)) {
        logger->msg.msgNum++;
        // find + replace msgNum
        _replaceMsgNum(logger);
        // write buffer
        fprintf(logger->logger, "%s\n", logger->msg.msgBuf);
        fflush(logger->logger);
        return 0;
    }

    PRINT_ERR_MSG("could not send message");
    return -1;
}

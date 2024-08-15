#include "logger.priv.h"
#include <string.h>
#include <stddef.h>

// after the call to _logger_create_message, if successful, our message will not have a msgNum so we replace that here
static inline void _replaceMsgNum(Logger *self, uint64_t msgNum) {
    char *const pStart = strstr(self->msg.msgBuf, "[Q") + 1;
    char *const pEnd = strstr(self->msg.msgBuf, "Q]");

    // sanity check
    const ptrdiff_t diff = pEnd - pStart; // size is 0-counted since we don't have NULL term
    const unsigned workingBufferSize = diff + 1;
    ASSERT(workingBufferSize == 20, "working buffer not size 20");
    char msgNumAsStr[20 + 1] = {0};
    snprintf(msgNumAsStr, 21, "%20llu", msgNum);
    ASSERT(msgNumAsStr[20] == '\0', "did not null terminate");
    memcpy(pStart, msgNumAsStr, workingBufferSize);
}

// info: send message to logger, replace msgNum
// return: 0 on message sent, -1 on message fail
int logger_sendmsg_num(Logger *logger, const char *msg, uint64_t msgNum) {
    if (!_logger_create_message(logger, msg)) {
        // find + replace msgNum
        _replaceMsgNum(logger, msgNum);
        // write buffer
        fprintf(logger->logger, "%s\n", logger->msg.msgBuf);
        fflush(logger->logger);
        return 0;
    }

    PRINT_ERR_MSG("could not send message");
    return -1;
}

// info: send message to logger, use internal msgNum counter
//       internal msgNum counter incremented after successful message sent
// return: 0 on message sent, -1 on message fail
int logger_sendmsg(Logger *logger, const char *msg) {
    if (!(logger_sendmsg_num(logger, msg, logger->msg.msgNum++) == 0)) {
        logger->msg.msgNum--;
        return -1;
    }
}

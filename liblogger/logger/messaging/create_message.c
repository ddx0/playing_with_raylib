#include "logger.priv.h"
#include <string.h>

#define ERR_MSG_CREATE(msg) PRINT_ERR_MSG("cannot create message: " msg)
#define CLEANUP_MSG_BUF \
free((void *)msgBuf); \
msgBuf = NULL

// try to create message for logger, save in internal buffer
// return: 0 if msg is input to buffer successfully, -1 on error
int _logger_create_message(Logger *self, const char *msg) {
    ASSERT(self, "can't create message if logger is null");
    // make sure msg fits
    const char *msgBuf = _util_safe_cstr(msg, MAX_MSG_SIZE, MAX_MSG_SIZE);

    if (!msgBuf) {
        ERR_MSG_CREATE("input msg failed to parse");
        return -1;
    }

    // don't need to check if ready since this will check for us
    if (!_logger_generate_timestamp(self)) {
        // can ignore retval, everything should fit
        strlcat(self->msg.msgBuf, msgBuf, MSG_BUF_SIZE);
        CLEANUP_MSG_BUF;
        return 0;
    } else {
        ERR_MSG_CREATE("couldn't create message");
        CLEANUP_MSG_BUF;
        return -1;
    }
}

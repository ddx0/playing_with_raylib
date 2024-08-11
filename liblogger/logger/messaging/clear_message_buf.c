#include "logger.priv.h"
#include <string.h>

void _logger_clear_msg_buf(Logger *self) {
    ASSERT(self, "can't clear msg buffer on null logger");

    memset(self->msg.msgBuf, 0, MSG_BUF_SIZE);
}

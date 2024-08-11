#include "logger.priv.h"
#include <stdbool.h>
#include <string.h>

// initialize all values for new logger
void _logger_init(Logger *self) {
    ASSERT(self, "cannot initialize null logger");

    self->logger = NULL;

    self->flags.isReadyToSend = false;
    self->flags.hasOpen_fd = false;

    self->msg.msgNum = 0;

    _logger_clear_msg_buf(self);
    _logger_reset_ts_format_str(self);
}

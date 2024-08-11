#include "logger.priv.h"
#include <stdbool.h>

// info: check if logger has open fd
// return: valid ? true : false
bool _logger_has_open_fd(Logger *self) {
    if (!(self->logger)) {
        return (self->flags.hasOpen_fd = false);
    } else {
        return (self->flags.hasOpen_fd = true);
    }
}

// info: ready to send status, ready if fd + timestamp format is set
// return: ready ? true : false
bool _logger_is_ready(Logger *self) {
    if (_logger_has_open_fd(self) && self->timestamp.isSet) {
        return (self->flags.isReadyToSend = true);
    } else {
        return (self->flags.isReadyToSend = false);
    }
}

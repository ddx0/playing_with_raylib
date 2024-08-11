#include "logger.priv.h"
#include <stdbool.h>
#include <string.h>

// info: zero-out the internal timestamp format buffer
// return:
void _logger_reset_ts_format_str(Logger *self) {
    memset(self->timestamp.formatStr, 0, TIMESTAMP_BUF_SIZE);
    self->timestamp.isSet = false;
}

#include "logger.priv.h"
#include <stdbool.h>
#include <string.h>

#define CLEANUP_TS_FORMAT_STR \
free((void *)valid_ts_format_str); \
valid_ts_format_str = NULL

// info: set timestamp format data string
// return: 0 if set successfully, -1 on error
int _logger_set_ts_format_str(Logger *self, const char *ts_format) {
    const char *valid_ts_format_str = _util_safe_cstr(ts_format, TIMESTAMP_BUF_SIZE, TIMESTAMP_BUF_SIZE);

    // validate cstr buffer
    if (valid_ts_format_str) {
        _logger_reset_ts_format_str(self);
        strlcpy(self->timestamp.formatStr, valid_ts_format_str, TIMESTAMP_BUF_SIZE);
        self->timestamp.isSet = true;
        CLEANUP_TS_FORMAT_STR;
        return 0;
    } else if (valid_ts_format_str == NULL) {
        PRINT_ERR_MSG("couldn't parse ts_format");
    } else {
        PRINT_ERR_MSG("unknown error");
    }

    self->timestamp.isSet = false;
    return -1;
}

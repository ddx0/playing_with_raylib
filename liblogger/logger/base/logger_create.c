#include "logger.priv.h"

#define CLEANUP_LOGGER \
free((void *)new_logger); \
new_logger = NULL

// logger constructor - sets default timestamp format str
Logger *logger_create() {
    Logger *new_logger = (Logger *)malloc(sizeof(Logger));

    if (!new_logger) {
        PRINT_ERR_MSG("could not allocate memory for logger");
        return NULL;
    }

    _logger_init(new_logger);

    if (!_logger_set_ts_format_str(new_logger, TIMESTAMP_FORMAT_STR_DEFAULT)) {
        if (!logger_set_logger(new_logger, "default")) {
            logger_sendmsg(new_logger, "logger created successfully...");
            return new_logger;
        }
    }

    CLEANUP_LOGGER;
    return NULL;
}

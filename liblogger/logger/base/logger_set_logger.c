#include "logger.priv.h"
#include <stdbool.h>
#include <string.h>

// info: set logger file pointer
// return: //
int logger_set_logger(Logger *self, const char *path) {
    FILE *fp = NULL;
    const char *logger_path = NULL;

    if (!(logger_path = _util_safe_cstr(path, strlen(path) + 1, LOGGER_PATH_BUF_SIZE))) {
        PRINT_ERR_MSG("couldn't set logger_path");
        goto set_flags;
    }
    if (strcmp(logger_path, "default") == 0) {
        fp = stdout;
    } else {
        if (!(fp = fopen(logger_path, "w"))) {
            PRINT_ERR_MSG("couldn't open logger_path");
        }
    }

    free((void *)logger_path);
    logger_path = NULL;

    self->logger = fp;

set_flags:
    return (_logger_has_open_fd(self)) ? 0 : -1;
}

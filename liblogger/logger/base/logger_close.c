#include "logger.priv.h"
#include <stdbool.h>

// info: close logger file pointer - free open fd if needed, reset associated flags
// return: 0 on success, -1 on error closing fd
int _logger_close_logger(Logger *self) {
    // no cleanup required
    if (self->logger == stdout) {
        return 0;
    }
    if (!_logger_has_open_fd(self)) {
        PRINT_ERR_MSG("logger has no open fd");
        return -1;
    }

    // cleanup only if necessary
    if (self->flags.hasOpen_fd) {
        if (!fclose(self->logger)) {
            return 0;
        }
        PRINT_ERR_MSG("couldn't close logger file fd");
        return -1;
    }
    
    PRINT_ERR_MSG("unknown error condition");
    return -1;
}

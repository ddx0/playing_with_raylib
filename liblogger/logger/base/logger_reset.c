#include "logger.priv.h"

// info: logger reset - reinit but safely close any open fd
// return: 0 on reset, -1 on error
int logger_reset(Logger *self) {
    if (!self) {
        PRINT_ERR_MSG("can't reset null logger");
        return -1;
    }

    if (!_logger_close_logger(self)) {
        _logger_init(self);
        return 0;

    }
    
    PRINT_ERR_MSG("couldn't close open fd");
    return -1;
}

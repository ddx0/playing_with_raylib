#include "logger.priv.h"

// logger destructor
// returns 0 if destroyed, -1 on err
int logger_destroy(Logger **logger) {
    ASSERT(*logger, "cannot destroy null logger");

    if (!logger_reset(*logger)) {
        free(*logger);
        *logger = NULL;
        return 0;
    }

    PRINT_ERR_MSG("can't destroy logger");
    return -1;
}

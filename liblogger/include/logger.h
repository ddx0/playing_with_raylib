// logger.h
#ifndef LOGGER_H
#define LOGGER_H

// #include <stdio.h>
// #include <stdbool.h>
#include <stdlib.h>
// #include <string.h>
// #include <stdint.h>
// #include <time.h>
// #include <assert.h>
// #include <unistd.h>
// #include <sys/stat.h>

typedef struct Logger_t Logger;

extern Logger *logger_create();
extern int logger_reset(Logger *);
extern int logger_set_logger(Logger *, const char *);
extern int logger_destroy(Logger **logger);
extern int logger_sendmsg(Logger *logger, const char *msg);

#endif

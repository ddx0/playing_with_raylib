// logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <stdlib.h>

typedef struct Logger_t Logger;

extern Logger *logger_create();
extern int logger_reset(Logger *self);
extern int logger_set_logger(Logger *self, const char *path);
extern int logger_destroy(Logger **logger);
extern int logger_sendmsg_num(Logger *logger, const char *msg, uint64_t msgNum);
extern int logger_sendmsg(Logger *logger, const char *msg);

#endif

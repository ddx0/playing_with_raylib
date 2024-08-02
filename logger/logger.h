// logger.h
#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Logger Logger;

extern Logger *logger_create(const char *path);
extern Logger *logger_create_default();
extern int logger_destroy(Logger **logger);
extern void logger_sendmsg(Logger *logger, const char *msg);

#endif

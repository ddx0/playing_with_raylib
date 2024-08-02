#include "logger.h"

#define DEV_DEBUG 1
#define PRINT_ERR_MSG(msg) fprintf(stderr, "ERROR: %s: " msg "\n", __FUNCTION__); fflush(stderr);
#define PRINT_DEV_MSG(msg) fprintf(stdout, "DEV: %s: " msg "\n", __FUNCTION__); fflush(stdout);

struct Logger {
    FILE *logger;
    bool isValid;
    uint64_t msgNum;
};

// internal prototypes
void logger_set(Logger *logger, FILE *log_fp);
void logger_unset(Logger *logger);

// logger constructor
// on success, opens file handle to be freed by destructor
Logger *logger_create(const char *path) {
    Logger *new_logger = NULL;
    FILE *fp = NULL;

    if (path == NULL) {
        PRINT_ERR_MSG("path null")
        return NULL;
    }
    if ((new_logger = (Logger *)malloc(sizeof(Logger))) == NULL) {
        PRINT_ERR_MSG("could not allocate memory")
        return NULL;
    }

    // check for default
    if (strcmp(path, "default") == 0) {
        logger_set(new_logger, stdout);
    } else {
        if ((fp = fopen(path, "w")) == NULL) {
            PRINT_ERR_MSG("couldn't create/open file for logger")
            return NULL;
        }
        logger_set(new_logger, fp);
    }

    #ifdef DEV_DEBUG
    PRINT_DEV_MSG("logger created successfully")
    #endif

    return new_logger;
}

// defaults to stdout
Logger *logger_create_default() {
    return logger_create("default");
}

// logger destructor
// returns 0 on success, -1 on error
int logger_destroy(Logger **logger) {
    // printf("PRE_EXECUTE: %p\n", (void *) logger);
    if (*logger == NULL) {
        PRINT_ERR_MSG("cannot destroy logger")
        return -1;
    }
    if ((*logger)->logger != stdout) {
        if (fclose((*logger)->logger) != 0) {
            PRINT_ERR_MSG("cannot close open fd on logger")
            return -1;
        }

        #ifdef DEV_DEBUG
        PRINT_DEV_MSG("fd successfully closed")
        #endif
    }
    logger_unset(*logger);
    free(*logger);
    *logger = NULL;
    // printf("POST_EXECUTE: %p\n", (void *) logger);

    #ifdef DEV_DEBUG
    PRINT_DEV_MSG("logger destroyed successfully")
    #endif

    return 0;
}

void logger_set(Logger *logger, FILE *log_fp) {
    if (logger == NULL) {
        PRINT_ERR_MSG("*logger null")
        return;
    }
    if (log_fp == NULL) {
        PRINT_ERR_MSG("*out_log null")
        return;
    }

    logger->logger = log_fp;
    logger->isValid = true;
    logger->msgNum = 0;

    #ifdef DEV_DEBUG
    PRINT_DEV_MSG("logger set successfully")
    #endif
    return;
}

void logger_unset(Logger *logger) {
    if (logger == NULL) {
        PRINT_ERR_MSG("*logger null")
        return;
    }

    logger->logger = NULL;
    logger->isValid = false;
    logger->msgNum = 0;

    #ifdef DEV_DEBUG
    PRINT_DEV_MSG("logger unset successfully")
    #endif
    return;
}

void logger_sendmsg(Logger *logger, const char *msg) {
    if (logger == NULL) {
        PRINT_ERR_MSG("*logger null")
        return;
    }
    if (msg == NULL) {
        PRINT_ERR_MSG("*msg null")
        return;
    }
    if (!(logger->isValid)) {
        PRINT_ERR_MSG("logger not valid")
        return;
    }

    // pull time info
    time_t current_time = time(NULL);
    if (current_time == (time_t)(-1)) {
        PRINT_ERR_MSG("could not pull current time")
        return;
    }
    // make a timestamp
    char timestamp[256] = {0};
    if (strftime(timestamp, 256, "[%F] - [%T]", gmtime(&current_time)) <= 0) {
        PRINT_ERR_MSG("problem saving timestamp")
    }

    if((fprintf(logger->logger, "%s | [%20llu]: %s\n", timestamp, ++(logger->msgNum), msg)) < 0) {
        PRINT_ERR_MSG("problems writing to logger")
        return;
    }

    fflush(logger->logger);
    #ifdef DEV_DEBUG
    PRINT_DEV_MSG("logger msg sent successfully")
    #endif
    return;
}

// logger.priv.h
//   - header for logger private objects

#ifndef LOGGER_PRIV_H
#define LOGGER_PRIV_H

#include "logger.h"
#include <stdio.h>

// CONSTANTS
#define TIMESTAMP_BUF_SIZE 128                            // buffer size for timestamp (after translation with suffix, library-wide)
#define TIMESTAMP_FORMAT_STR_DEFAULT "[%F] - [%T]"        // strftime format string for log prefix
#define MSG_BUF_SIZE 4096                                 // size of msg buf (ts + msg)
#define MAX_MSG_SIZE (MSG_BUF_SIZE - TIMESTAMP_BUF_SIZE)  // max size for msg
#define LOGGER_PATH_BUF_SIZE 2048                         // path to set logger can only be up to of len(this - 1) chars

// DATA STRUCTURES
typedef struct Logger_Flags_t {
    bool isReadyToSend;
    bool hasOpen_fd;
} Logger_Flags;

typedef struct Logger_Msg_t {
    uint64_t msgNum;
    char msgBuf[MSG_BUF_SIZE];
} Logger_Msg;

typedef struct Logger_Timestamp_t {
    bool isSet;
    char formatStr[TIMESTAMP_BUF_SIZE];
} Logger_Timestamp;

struct Logger_t {
    FILE *logger;
    Logger_Flags flags;
    Logger_Msg msg;
    Logger_Timestamp timestamp;
};

// PROTOTYPES
// safe cstr handlers
const char *_util_safe_cstr(const char *, const size_t, const size_t);
int _logger_generate_timestamp(Logger *);
// reset
void _logger_init(Logger *);
// ready = open fd + has timestamp (is ready to sendmsg)
bool _logger_has_open_fd(Logger *);
bool _logger_is_ready(Logger *);
// logger file pointer
int _logger_close_logger(Logger *);
// logger msg
void _logger_clear_msg_buf(Logger *);
int _logger_create_message(Logger *, const char *);
// logger timestamp format string
int _logger_set_ts_format_str(Logger *, const char *);
void _logger_reset_ts_format_str(Logger *);

// FUNCTION MACROS
#define PRINT_ERR_MSG(msg) fprintf(stderr, "ERROR: %s: " msg "\n", __FUNCTION__); fflush(stderr)
#define PRINT_DEV_MSG(msg) fprintf(stdout, "DEV: %s: " msg "\n", __FUNCTION__); fflush(stdout)
#define ASSERT(cond, msg) do { \
    if (!(cond)) { \
        fprintf(stderr, __FILE__ ": %d: assertion %s failed: %s\n", __LINE__, #cond, msg); \
        exit(-1); \
    } \
} while (0)
#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

#endif

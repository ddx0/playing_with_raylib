#include "logger.priv.h"
#include <time.h>
#include <string.h>

#define TS_SUFFIX " | [%20llu]: "
#define CLEANUP_TIMESTAMP \
free((void *)timestamp); \
timestamp = NULL
#define CLEANUP_SUFFIX \
free((void *)suffix); \
suffix = NULL

// info: generate timestamp, place into internal msg buffer
// return: on success (0), msg buffer is cleared and generated timestamp is copied into msg buffer
//         on failure (-1), return with zero side effects
int _logger_generate_timestamp(Logger *self) {
    const time_t current_time = time(NULL);
    char *timestamp = NULL;

    if (!_logger_is_ready(self)) {
        PRINT_ERR_MSG("cannot generate timestamp if logger not ready");
        return -1;
    }
    if (current_time == (time_t)(-1)) {
        PRINT_ERR_MSG("could not pull current time");
        return -1;
    }
    if (!(timestamp = (char *)malloc(sizeof(char) * TIMESTAMP_BUF_SIZE))) {
        PRINT_ERR_MSG("could not allocate timestamp buffer");
        return -1;
    } else {
        memset(timestamp, 0, TIMESTAMP_BUF_SIZE);
    }

    // make initial timestamp
    const size_t timestamp_len = strftime(timestamp, TIMESTAMP_BUF_SIZE, self->timestamp.formatStr, gmtime(&current_time));

    if (!timestamp_len) {
        PRINT_ERR_MSG("could not build timestamp from format str");
        goto cleanup;
    }

    // calculate len of suffix (expanded)
    const int expanded_suffix_len = snprintf(NULL, 0, TS_SUFFIX, self->msg.msgNum);

    if (expanded_suffix_len < 0) {
        PRINT_ERR_MSG("problem expanding suffix");
        goto cleanup;
    }

    // make sure we have enough room for the timestamp + suffix
    const bool has_enough_room_for_suffix = ((timestamp_len + expanded_suffix_len) < TIMESTAMP_BUF_SIZE);

    if (has_enough_room_for_suffix) {
        // generate suffix
        char *suffix = (char *)malloc(sizeof(char) * (expanded_suffix_len + 1));
        if (!suffix) {
            PRINT_ERR_MSG("couldn't allocate memory for suffix");
            goto cleanup;
        }
        snprintf(suffix, expanded_suffix_len + 1, TS_SUFFIX, self->msg.msgNum);

        // replace msgNum with placeholder to be replaced by logger_sendmsg
        //   - note: this is kinda hacky, refactoring needed
        char *pStart = strchr(suffix, '[');
        while (*++pStart != ']') {
            *pStart = 'Q';
        }
        pStart = NULL;

        // append suffix
        strlcat(timestamp, suffix, TIMESTAMP_BUF_SIZE);
        CLEANUP_SUFFIX;

        // copy to internal msg buffer
        _logger_clear_msg_buf(self);
        strlcpy(self->msg.msgBuf, timestamp, MSG_BUF_SIZE);
        CLEANUP_TIMESTAMP;
        return 0;
    } else {
        PRINT_ERR_MSG("no room for suffix in buffer");
    }

cleanup:
    PRINT_ERR_MSG("could not generate timestamp");
    CLEANUP_TIMESTAMP;
    return -1;
}

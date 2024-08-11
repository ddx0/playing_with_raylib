#include "logger.priv.h"
#include <string.h>
#include <stddef.h>

// returns byte position of first null-terminator in src buffer, or 0 if none found before dstsize or end of buffer
#define BYTES_UNTIL_NULL_TERM_static_fn(src, srcsize, dstsize) ({ \
    ASSERT(src, "src is null"); \
    ASSERT(_Generic((srcsize), size_t: 1, default: 0), "srcsize not size_t"); \
    ASSERT(_Generic((dstsize), size_t: 1, default: 0), "dstsize not size_t"); \
    size_t result = 0; \
    do { \
        static inline size_t _num_bytes_until_null(const char *_src, const size_t _srcsize, const size_t _dstsize) { \
            size_t pos = 0; \
            while ((pos < _srcsize) && (pos < _dstsize)) { \
                if (_src[pos++] == '\0') { \
                    return pos; \
                } \
            } \
            return 0; \
        } \
        result = _num_bytes_until_null(src, srcsize, dstsize); \
    } while (0); \
    result; \
})
#define BYTES_UNTIL_NULL_TERM_no_fn(src, srcsize, dstsize) ({ \
    ASSERT(src, "src is null"); \
    ASSERT(_Generic((srcsize), size_t: 1, default: 0), "srcsize not size_t"); \
    ASSERT(_Generic((dstsize), size_t: 1, default: 0), "dstsize not size_t"); \
    size_t pos = 0; \
    size_t null_pos = 0; \
    while ((pos < srcsize) && (pos < dstsize)) { \
        if (src[pos++] == '\0') { \
            null_pos = pos; \
            break; \
        } \
    } \
    (null_pos > 0) ? null_pos : 0; \
})

// info: return safe c-str copy, only copies if src is valid c-str and won't truncate by dstsize
// return: string if valid copy, NULL if not
// side effects: allocates new c-str if successful
const char *_util_safe_cstr(const char *src, const size_t srcsize, const size_t dstsize) {
    char *str = NULL;
    size_t bytes_to_nul = 0;

    bytes_to_nul = BYTES_UNTIL_NULL_TERM_no_fn(src, srcsize, dstsize);

    // verify src is null-terminated by dstsize, so strlcpy doesn't fail
    if (!bytes_to_nul) {
        PRINT_ERR_MSG("src not valid: src was not null-terminated by src/dst size");
        return NULL;
    }

    if ((str = (char *)malloc(sizeof(char) * dstsize)) == NULL) {
        PRINT_ERR_MSG("could not allocate memory for buffer");
        return NULL;
    } else {
        memset(str, 0, dstsize);
    }

    // we can ignore retval since we verified valid string and don't allow truncation
    strlcpy(str, src, dstsize);

    return str;
}

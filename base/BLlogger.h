#ifndef BLLOGGER_H_
#define BLLOGGER_H_
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BLlogger_sink_null,
    BLlogger_sink_stdout,
    BLlogger_sink_stderr,
    BLlogger_sink_undefined
} BLlogger_sink_t;

typedef enum {
    BLlogger_level_error,
    BLlogger_level_info,
    BLlogger_level_debug
} BLlogger_level_t;

void BLlogger_setsink(BLlogger_sink_t sink);

void BLlogger_setlevel(BLlogger_level_t level);

FILE* BLlogger_get();

BLlogger_level_t BLloggere_getlevel();

int BLlogger_active(BLlogger_level_t level);

#define BLLOGGER_LOG(level,...) if (BLlogger_active(level)) { \
    fprintf(BLlogger_get(), __VA_ARGS__); }
#define BLLOGGER_ERROR(...) BLLOGGER_LOG(BLlogger_level_error, __VA_ARGS__)
#define BLLOGGER_INFO(...) BLLOGGER_LOG(BLlogger_level_info, __VA_ARGS__)
#define BLLOGGER_DEBUG(...) BLLOGGER_LOG(BLlogger_level_debug, __VA_ARGS__)
#ifdef __cplusplus
}
#endif
#endif /* BLLOGGER_H_ */
#ifndef BLLOGGER_H_
#define BLLOGGER_H_
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BLlogger_sink_stdout,
    BLlogger_sink_stderr,
    BLlogger_sink_newfile,
    BLlogger_sink_existingfile,
    BLlogger_sink_undefined
} BLlogger_sink_t;

typedef enum {
    BLlogger_level_error,
    BLlogger_level_warning,
    BLlogger_level_info,
    BLlogger_level_debug,
    BLlogger_level_trace
} BLlogger_level_t;

#define BLLOGLEVELLABELS { \
    "ERR", \
    "WRN", \
    "INF", \
    "DBG", \
    "TRC" \
}

/*!
\brief set log sink
\param sink [in] sink type
\param file_option [in] it specifies a filename when sink == BLlogger_sink_newfile or == BLlogger_sink_existingfile.
    In the case that file_option == NULL && sink == BLlogger_sink_existingfile, /dev/null is attached to pflogger.
*/
int BLlogger_setsink(BLlogger_sink_t sink, const char* file_option);

void BLlogger_setlevel(BLlogger_level_t level);

FILE* BLlogger_get();

BLlogger_level_t BLloggere_getlevel();

int BLlogger_active(BLlogger_level_t level);

void BLlogger_printloginfo(BLlogger_level_t level);

/*!
\brief close the sink file if it is a normal file.
*/
void BLlogger_close();

#define BLLOG(level,...) if (BLlogger_active(level)) { BLlogger_printloginfo(level); fprintf(BLlogger_get(), __VA_ARGS__); }
#define BLLOG_ERR(...) BLLOG(BLlogger_level_error, __VA_ARGS__)
#define BLLOG_WRN(...) BLLOG(BLlogger_level_warning, __VA_ARGS__)
#define BLLOG_INF(...) BLLOG(BLlogger_level_info, __VA_ARGS__)
// BLLOG_DBG and BLLOG_TRC is enabled only when _DEBUG is defined.
#ifdef _DEBUG
#define BLLOG_DBG(...) BLLOG(BLlogger_level_debug, __VA_ARGS__)
#define BLLOG_TRC(...) BLLOG(BLlogger_level_trace, __VA_ARGS__)
#else
#define BLLOG_DBG(...)
#define BLLOG_TRC(...)
#endif
#ifdef __cplusplus
}
#endif
#endif /* BLLOGGER_H_ */
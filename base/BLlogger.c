#include "base/BLlogger.h"
#include "base/BLfile.h"
#include "base/BLbase.h"

static FILE* pflogger = NULL;
static BLlogger_level_t current_level = BLlogger_level_info;
static BLlogger_sink_t current_sink = BLlogger_sink_undefined;

int BLlogger_setsink(BLlogger_sink_t sink, const char* file_option)
{
    int err = EXIT_SUCCESS;
    FILE* newsink = NULL;
    do {
        switch (sink)
        {
        case BLlogger_sink_stdout:
        {
            current_sink = sink;
            pflogger = stdout;
            break;
        }
        case BLlogger_sink_stderr:
        {
            current_sink = sink;
            pflogger = stderr;
            break;
        }
        case BLlogger_sink_newfile:
        {
            BLlogger_close();
            err = BLfile_open(&newsink, file_option, "w");
            if (EXIT_SUCCESS == err)
            {
                pflogger = newsink;
                current_sink = sink;
            }
            break;
        }
        case BLlogger_sink_existingfile:
        {
            BLlogger_close();
            err = BLfile_open(&newsink, ((NULL == file_option) ? "/dev/null" : file_option), "a");
            if (EXIT_SUCCESS == err)
            {
                pflogger = newsink;
                current_sink = sink;
            }
            break;
        }
        default:
            break;
        }
    } while (0);
    return err;
}

void BLlogger_setlevel(BLlogger_level_t level)
{
    current_level = level;
}

FILE* BLlogger_get()
{
    assert(pflogger);
    return pflogger;
}

BLlogger_level_t BLloggere_getlevel()
{
    return current_level;
}

int BLlogger_active(BLlogger_level_t level)
{
    return (int)((int)level <= (int)current_level);
}

void BLlogger_printloginfo(BLlogger_level_t level)
{
    const char* labels[] = BLLOGLEVELLABELS;
    struct tm tm;
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    localtime_r(&ts.tv_sec, &tm);
    fprintf(pflogger, "%04d-%02d-%02d %02d:%02d:%02d.%06d,%s,",
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, ts.tv_nsec/1000,
        labels[level]);
}

void BLlogger_close()
{
    if ((current_sink == BLlogger_sink_existingfile) || (current_sink == BLlogger_sink_newfile))
    {
        fclose(pflogger);
    }
    current_sink = BLlogger_sink_stderr;
    pflogger = stderr;
}
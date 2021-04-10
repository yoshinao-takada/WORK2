#include "base/BLlogger.h"

static FILE* pflogger = NULL;
static BLlogger_sink_t current_sink = BLlogger_sink_undefined;
static BLlogger_level_t current_level = BLlogger_level_error;

void BLlogger_setsink(BLlogger_sink_t sink)
{
    if (current_sink == BLlogger_sink_null)
    {
        fclose(pflogger);
    }
    current_sink = sink;
    if (current_sink == BLlogger_sink_null)
    {
        pflogger = fopen("/dev/null", "w");
    }
    else if (current_sink == BLlogger_sink_stderr)
    {
        pflogger = stderr;
    }
    else if (current_sink == BLlogger_sink_stdout)
    {
        pflogger = stdout;
    }
    else
    {
        pflogger = NULL;
    }
}

void BLlogger_setlevel(BLlogger_level_t level)
{
    current_level = level;
}

FILE* BLlogger_get()
{
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
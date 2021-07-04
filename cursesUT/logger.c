#include "base/BLlogger.h"
#include "base/BLbase.h"
#define TEST_RESULT_DIR "../../WorkData/curses/"
#define LOGSINK_FILE    TEST_RESULT_DIR "logsink.txt"

int logger();

int sink_stdout()
{
    int err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = BLlogger_setsink(BLlogger_sink_stdout, NULL)))
        {
            UT_SHOWBREAK(stderr, __FILE__, __LINE__, err);
        }
        BLlogger_setlevel(BLlogger_level_trace);
        BLLOG_ERR("%s,%d,BLLOG_ERR\n", __FUNCTION__, __LINE__);
        BLLOG_WRN("%s,%d,BLLOG_WRN\n", __FUNCTION__, __LINE__);
        BLLOG_INF("%s,%d,BLLOG_INF\n", __FUNCTION__, __LINE__);
        BLLOG_DBG("%s,%d,BLLOG_DBG\n", __FUNCTION__, __LINE__);
        BLLOG_TRC("%s,%d,BLLOG_TRC\n", __FUNCTION__, __LINE__);
        BLlogger_close();
    } while (0);
    return err;
}

int sink_null()
{
    int err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = BLlogger_setsink(BLlogger_sink_existingfile, NULL)))
        {
            UT_SHOWBREAK(stderr, __FILE__, __LINE__, err);
        }
        BLlogger_setlevel(BLlogger_level_trace);
        BLLOG_ERR("%s,%d,BLLOG_ERR\n", __FUNCTION__, __LINE__);
        BLLOG_WRN("%s,%d,BLLOG_WRN\n", __FUNCTION__, __LINE__);
        BLLOG_INF("%s,%d,BLLOG_INF\n", __FUNCTION__, __LINE__);
        BLLOG_DBG("%s,%d,BLLOG_DBG\n", __FUNCTION__, __LINE__);
        BLLOG_TRC("%s,%d,BLLOG_TRC\n", __FUNCTION__, __LINE__);
        BLlogger_close();
    } while (0);
    return err;
}


int sink_newfile()
{
    int err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = BLlogger_setsink(BLlogger_sink_newfile, LOGSINK_FILE)))
        {
            UT_SHOWBREAK(stderr, __FILE__, __LINE__, err);
        }
        BLlogger_setlevel(BLlogger_level_trace);
        BLLOG_ERR("%s,%d,level=trace,BLLOG_ERR\n", __FUNCTION__, __LINE__);
        BLLOG_WRN("%s,%d,level=trace,BLLOG_WRN\n", __FUNCTION__, __LINE__);
        BLLOG_INF("%s,%d,level=trace,BLLOG_INF\n", __FUNCTION__, __LINE__);
        BLLOG_DBG("%s,%d,level=trace,BLLOG_DBG\n", __FUNCTION__, __LINE__);
        BLLOG_TRC("%s,%d,level=trace,BLLOG_TRC\n", __FUNCTION__, __LINE__);
        BLlogger_setlevel(BLlogger_level_debug);
        BLLOG_ERR("%s,%d,level=debug,BLLOG_ERR\n", __FUNCTION__, __LINE__);
        BLLOG_WRN("%s,%d,level=debug,BLLOG_WRN\n", __FUNCTION__, __LINE__);
        BLLOG_INF("%s,%d,level=debug,BLLOG_INF\n", __FUNCTION__, __LINE__);
        BLLOG_DBG("%s,%d,level=debug,BLLOG_DBG\n", __FUNCTION__, __LINE__);
        BLLOG_TRC("%s,%d,level=debug,BLLOG_TRC\n", __FUNCTION__, __LINE__);
        BLlogger_setlevel(BLlogger_level_info);
        BLLOG_ERR("%s,%d,level=info,BLLOG_ERR\n", __FUNCTION__, __LINE__);
        BLLOG_WRN("%s,%d,level=info,BLLOG_WRN\n", __FUNCTION__, __LINE__);
        BLLOG_INF("%s,%d,level=info,BLLOG_INF\n", __FUNCTION__, __LINE__);
        BLLOG_DBG("%s,%d,level=info,BLLOG_DBG\n", __FUNCTION__, __LINE__);
        BLLOG_TRC("%s,%d,level=info,BLLOG_TRC\n", __FUNCTION__, __LINE__);
        BLlogger_setlevel(BLlogger_level_warning);
        BLLOG_ERR("%s,%d,level=warning,BLLOG_ERR\n", __FUNCTION__, __LINE__);
        BLLOG_WRN("%s,%d,level=warning,BLLOG_WRN\n", __FUNCTION__, __LINE__);
        BLLOG_INF("%s,%d,level=warning,BLLOG_INF\n", __FUNCTION__, __LINE__);
        BLLOG_DBG("%s,%d,level=warning,BLLOG_DBG\n", __FUNCTION__, __LINE__);
        BLLOG_TRC("%s,%d,level=warning,BLLOG_TRC\n", __FUNCTION__, __LINE__);
        BLlogger_setlevel(BLlogger_level_error);
        BLLOG_ERR("%s,%d,level=error,BLLOG_ERR\n", __FUNCTION__, __LINE__);
        BLLOG_WRN("%s,%d,level=error,BLLOG_WRN\n", __FUNCTION__, __LINE__);
        BLLOG_INF("%s,%d,level=error,BLLOG_INF\n", __FUNCTION__, __LINE__);
        BLLOG_DBG("%s,%d,level=error,BLLOG_DBG\n", __FUNCTION__, __LINE__);
        BLLOG_TRC("%s,%d,level=error,BLLOG_TRC\n", __FUNCTION__, __LINE__);
        BLlogger_close();
    } while (0);
    return err;
}

int sink_existingfile()
{
    int err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = BLlogger_setsink(BLlogger_sink_existingfile, LOGSINK_FILE)))
        {
            UT_SHOWBREAK(stderr, __FILE__, __LINE__, err);
        }
        BLlogger_setlevel(BLlogger_level_trace);
        BLLOG_ERR("%s,%d,level=trace,BLLOG_ERR\n", __FUNCTION__, __LINE__);
        BLLOG_WRN("%s,%d,level=trace,BLLOG_WRN\n", __FUNCTION__, __LINE__);
        BLLOG_INF("%s,%d,level=trace,BLLOG_INF\n", __FUNCTION__, __LINE__);
        BLLOG_DBG("%s,%d,level=trace,BLLOG_DBG\n", __FUNCTION__, __LINE__);
        BLLOG_TRC("%s,%d,level=trace,BLLOG_TRC\n", __FUNCTION__, __LINE__);
        BLlogger_setlevel(BLlogger_level_debug);
        BLLOG_ERR("%s,%d,level=debug,BLLOG_ERR\n", __FUNCTION__, __LINE__);
        BLLOG_WRN("%s,%d,level=debug,BLLOG_WRN\n", __FUNCTION__, __LINE__);
        BLLOG_INF("%s,%d,level=debug,BLLOG_INF\n", __FUNCTION__, __LINE__);
        BLLOG_DBG("%s,%d,level=debug,BLLOG_DBG\n", __FUNCTION__, __LINE__);
        BLLOG_TRC("%s,%d,level=debug,BLLOG_TRC\n", __FUNCTION__, __LINE__);
        BLlogger_setlevel(BLlogger_level_info);
        BLLOG_ERR("%s,%d,level=info,BLLOG_ERR\n", __FUNCTION__, __LINE__);
        BLLOG_WRN("%s,%d,level=info,BLLOG_WRN\n", __FUNCTION__, __LINE__);
        BLLOG_INF("%s,%d,level=info,BLLOG_INF\n", __FUNCTION__, __LINE__);
        BLLOG_DBG("%s,%d,level=info,BLLOG_DBG\n", __FUNCTION__, __LINE__);
        BLLOG_TRC("%s,%d,level=info,BLLOG_TRC\n", __FUNCTION__, __LINE__);
        BLlogger_setlevel(BLlogger_level_warning);
        BLLOG_ERR("%s,%d,level=warning,BLLOG_ERR\n", __FUNCTION__, __LINE__);
        BLLOG_WRN("%s,%d,level=warning,BLLOG_WRN\n", __FUNCTION__, __LINE__);
        BLLOG_INF("%s,%d,level=warning,BLLOG_INF\n", __FUNCTION__, __LINE__);
        BLLOG_DBG("%s,%d,level=warning,BLLOG_DBG\n", __FUNCTION__, __LINE__);
        BLLOG_TRC("%s,%d,level=warning,BLLOG_TRC\n", __FUNCTION__, __LINE__);
        BLlogger_setlevel(BLlogger_level_error);
        BLLOG_ERR("%s,%d,level=error,BLLOG_ERR\n", __FUNCTION__, __LINE__);
        BLLOG_WRN("%s,%d,level=error,BLLOG_WRN\n", __FUNCTION__, __LINE__);
        BLLOG_INF("%s,%d,level=error,BLLOG_INF\n", __FUNCTION__, __LINE__);
        BLLOG_DBG("%s,%d,level=error,BLLOG_DBG\n", __FUNCTION__, __LINE__);
        BLLOG_TRC("%s,%d,level=error,BLLOG_TRC\n", __FUNCTION__, __LINE__);
        BLlogger_close();
    } while (0);
    return err;
}

int logger()
{
    int err = EXIT_SUCCESS;
    int err_each = EXIT_SUCCESS;
    do {
        err |= (err_each = sink_stdout());
        if (err_each)
        {
            UT_SHOW(stderr, __FUNCTION__, __LINE__, err_each);
        }
        err |= (err_each = sink_null());
        if (err_each)
        {
            UT_SHOW(stderr, __FUNCTION__, __LINE__, err_each);
        }
        err |= (err_each = sink_newfile());
        if (err_each)
        {
            UT_SHOW(stderr, __FUNCTION__, __LINE__, err_each);
        }
        err |= (err_each = sink_existingfile());
        if (err_each)
        {
            UT_SHOW(stderr, __FUNCTION__, __LINE__, err_each);
        }
    } while (0);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}
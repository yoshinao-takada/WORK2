#ifndef BLTRACE_H_
#define BLTRACE_H_
#include <stdio.h>

static FILE* logsink = NULL;

#ifdef _DEBUG
#define DBG(...) if (logsink) { fprintf(logsink, __VA_ARGS__); fflush(logsink); }

#define DBGAT(func,line) DBG("%s,%d\n", func, line)

#else
#define DBG(...)

#define DBGAT(func,line) DBG("%s,%d\n", func, line)

#endif

#endif /* BLTRACE_H_ */

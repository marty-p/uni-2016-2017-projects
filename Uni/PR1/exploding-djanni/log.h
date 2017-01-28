#ifndef __EDJ_LOG_H__
#define __EDJ_LOG_H__

/* include list */
#include "common.h"
#include "date.h"

/* prototype list */
extern FILE ** log_instance(void);
extern void log_init(const char * log_file_name);
extern void log_write(const char * format, ...);
extern void log_deinit(void);

#endif


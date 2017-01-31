#ifndef __EDJ_LOG_H__
#define __EDJ_LOG_H__

/* macro list */
// #define LOG_IN_APPEND_MODE

/* include list */
#include "common.h"

/* prototype list */
extern FILE ** log_instance(void);
extern void log_init(const char * log_file_name);
extern void log_write(const char * format, ...);
extern void log_deinit(void);

#endif


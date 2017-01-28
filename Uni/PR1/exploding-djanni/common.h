#ifndef __EDJ_COMMON_H__
#define __EDJ_COMMON_H__

/* macro list */
#ifndef _DEBUG
#define _DEBUG
#endif

/* include list */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _MSC_VER
#define false   0
#define true    1
#define _Bool int
#else
#include <stdbool.h>
#endif

/* prototype list */
extern void clear_input_line();
extern void clear_file_input_line(FILE * fp);
extern void clear_console();
extern int get_random_number(int min, int max);

#endif


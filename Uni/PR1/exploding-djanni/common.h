#ifndef __EDJ_COMMON_H__
#define __EDJ_COMMON_H__

/* macro list */
#ifndef _DEBUG // already defined in visual studio
#define _DEBUG
#endif
#define CURRENT_DATE_LEN 19

/* include list */
#include <stdio.h> // almost all i/o and file
#include <stdlib.h> // random number generation and exit failure
#include <string.h> // player's name strlen
#include <time.h> // date format

#ifdef _MSC_VER // visual studio 2010 test compilation
#define false	0
#define true	1
#define _Bool int
#else
#include <stdbool.h> // _Bool
#endif

#include <stdarg.h> // for variadic functions

/* prototype list */
extern void clear_input_line(void);
extern void clear_file_input_line(FILE * fp);
extern void clear_console(void);
extern int get_random_number(int min, int max);
extern void get_current_date_format(char * datebuf, int datebuf_len);

#endif


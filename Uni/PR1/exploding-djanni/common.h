#ifndef __EDJ_COMMON_H__
#define __EDJ_COMMON_H__

/* macro list */
#if defined(_MSC_VER) && defined(_DEBUG) // already defined in visual studio (target debug)
#undef _DEBUG
#endif

#ifndef _DEBUG
// #define _DEBUG // debug flag
#endif

// #define SHOW_AI_DEBUG_INFO // print extra ai info (cards and count each turn)
#define AI_USE_NORMAL_CARDS_IN_PANIC // ai will use normal cards when in panic
// #define AI_USE_SHUFFLE_IF_NO_HOPE // ai will use the shuffle even if the exploding cards in the deck are 100%

#define CLEAR_CONSOLE_EACH_TURN // clear the console each turn
#ifdef CLEAR_CONSOLE_EACH_TURN
#define CLEAR_CONSOLE_TIME_WAIT 3 // n seconds to wait before cleaning
#define DO_NOT_USE_TIME_WAIT // use enter key press instead of waiting
#define CLEAR_CONSOLE_WHEN_NOPING // clear the console when the can nope function is called
#endif

#define CURRENT_DATE_LEN 19 // +1; current data format length

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
extern void clear_all_delayed(void);
extern void clear_all(void);
extern void wait_for_n_seconds(int seconds);
extern int get_random_number(int min, int max);
extern void get_current_date_format(char * datebuf, int datebuf_len);

#endif


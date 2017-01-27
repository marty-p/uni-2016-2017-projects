#include "common.h"

void clear_input()
{
	char dummy_char;
	// clear the buffer from improper values (EOF in case we redirect the stdin from file)
	while ((dummy_char = getchar()) != '\n' && dummy_char != EOF)
		continue;
}

void clear_console() // clear the console
{
#if defined(_WIN32)
	system("cls");
#elif defined(linux)
	system("clear");
#endif
}


#include "common.h"

void clear_input_line()
{
	char dummy_char;
	// clear the buffer from improper values (EOF in case we redirect the stdin from file)
	while ((dummy_char = getchar()) != '\n' && dummy_char != EOF)
		continue;
}

void clear_file_input_line(FILE * fp)
{
	fscanf(fp, "%*[^\n]\n"); // clear the remaining bytes of the line
}

void clear_console() // clear the console
{
#if defined(_WIN32) || defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
	system("cls");
#elif defined(linux) || defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	system("clear");
#endif
}


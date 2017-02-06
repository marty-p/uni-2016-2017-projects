#include "common.h"

void clear_input_line(void)
{
	int dummy_char;
	// clear the buffer from improper values (EOF in case we redirect the stdin from file)
	while ((dummy_char = getchar()) != '\n' && dummy_char != EOF)
		continue;
}

void clear_file_input_line(FILE * fp)
{
	fscanf(fp, "%*[^\n]\n"); // clear the remaining bytes of the line
}

void clear_console(void) // clear the console
{
#if defined(_WIN32) || defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__) // windows (visualstudio/mingw)
	system("cls");
#elif defined(linux) || defined(__linux__) || defined(__unix__) || defined(__APPLE__) //linux/unix/osx
	system("clear");
#endif
}

void clear_all_delayed(void) // clear the console after n seconds
{
#ifdef CLEAR_CONSOLE_EACH_TURN
#ifdef DO_NOT_USE_TIME_WAIT
	printf("Press enter key to clear the console!\n");
	getchar(); // simulate enter key press
#else
	printf("Waiting for %d seconds before cleaning the console!\n", CLEAR_CONSOLE_TIME_WAIT); // wait three seconds
	wait_for_n_seconds(CLEAR_CONSOLE_TIME_WAIT);
#endif
	clear_console();
#endif
}

void clear_all(void) // clear the console and ask for enter key press
{
#ifdef CLEAR_CONSOLE_EACH_TURN
	printf("Press enter key to continue...\n");
	clear_input_line(); // simulate enter key press
	clear_console();
#endif
}

void wait_for_n_seconds(int seconds)
{
	time_t end_time = time(NULL) + seconds; // the only "standard" way to keep the cpu busy for n seconds
	while (time(0) < end_time)
		continue;
}

int get_random_number(int min, int max)
{
	return min + rand() % (max-min+1); // generates a random number between min and max
}

void get_current_date_format(char * datebuf, int datebuf_len)
{
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime); // get current machine time
	timeinfo = localtime(&rawtime); // get local tm struct

	strftime(datebuf, datebuf_len, "%Y/%m/%d %H:%M:%S", timeinfo); // format year/month/day hour:minute:second
}


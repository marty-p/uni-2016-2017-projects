#include "log.h"

FILE ** log_instance() // creating a "getter" func instead of global variable
{
	static FILE * log_file = NULL; // static to get an always available ptr to file
	return &log_file;
}

void log_init(const char * log_file_name)
{
	// check invalid file name
	if (log_file_name == NULL)
	{
		printf("You passed a null ptr as filename to the log_init func\n");
		return;
	}

	// get log file instance
	FILE ** plog_file = log_instance();
	if (*plog_file == NULL) // if null, we'll initialize it
	{
		*plog_file = fopen(log_file_name, "a"); // open the log file on append mode
		if (*plog_file == NULL) // if it fails, it will print the error
		{
			printf("You couldn't open the relative log file: %s\n", log_file_name);
			return;
		}
	}
}

void log_write(const char * msg)
{
	// get log file instance
	FILE ** plog_file = log_instance();
	if (*plog_file == NULL) // if null, we'll skip it
		return;

	char datebuf[CURRENT_DATE_LEN+1] = {0};
	get_current_date_format(datebuf, sizeof(datebuf));

	// write the msg to file appending also the current date
	fprintf(*plog_file, "%s :: %s\n", datebuf, msg);
#ifdef _DEBUG
	printf("%s :: %s\n", datebuf, msg);
#endif
}

void log_deinit()
{
	// get log file instance
	FILE ** plog_file = log_instance();
	if (*plog_file == NULL)
	{
		printf("You are trying to close a null ptr file in the log_deinit func\n");
		return;
	}
	fclose(*plog_file);
	*plog_file = NULL;
}


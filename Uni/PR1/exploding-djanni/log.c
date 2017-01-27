#include "log.h"

FILE ** log_instance() // creating a "getter" func instead of global variable
{
	static FILE * log_file = NULL; // static to get an always available ptr to file
	return &log_file;
}

void log_init(const char * log_file_name)
{
	// get the log file instance
	FILE ** plog_file = log_instance();

	// check invalid file name
	if (log_file_name == NULL)
	{
		printf("You passed a null ptr as filename to the log_init func\n");
		return;
	}

	// if null, we'll initialize it
	if (*plog_file == NULL)
	{
		*plog_file = fopen(log_file_name, "a"); // open the log file in append mode
		if (*plog_file == NULL) // if it fails, it will print the error
		{
			printf("You couldn't open the relative log file: %s\n", log_file_name);
			return;
		}
	}
}

void log_write(const char * msg)
{
	char datebuf[CURRENT_DATE_LEN+1] = ""; // buffer to store the current date
	FILE ** plog_file = log_instance(); // get the log file instance

	// if null, we'll skip it
	if (*plog_file == NULL)
		return;

	// get the current date
	get_current_date_format(datebuf, sizeof(datebuf));

	// write the msg to file appending also the current date
	fprintf(*plog_file, "%s :: %s\n", datebuf, msg);
#ifdef _DEBUG
	printf("%s :: %s\n", datebuf, msg);
#endif
}

void log_deinit()
{
	// get the log file instance
	FILE ** plog_file = log_instance();

	// if null, we'll warn
	if (*plog_file == NULL)
	{
		printf("You are trying to close a null ptr file in the log_deinit func\n");
		return;
	}

	// close the file and reset the ptr to file
	fclose(*plog_file);
	*plog_file = NULL;
}


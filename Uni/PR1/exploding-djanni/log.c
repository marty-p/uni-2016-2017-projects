#include "log.h"

FILE ** log_instance(void) // creating a getter/singleton-like func instead of global variable
{
	static FILE * log_file = NULL; // static to get an always available ptr to file
	return &log_file; // returning its ptr so we can change it elsewhere
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
#ifdef LOG_IN_APPEND_MODE
		*plog_file = fopen(log_file_name, "a"); // open the log file in append mode
#else
		*plog_file = fopen(log_file_name, "w"); // open the log file in write mode
#endif
		if (*plog_file == NULL) // if it fails, it will print the error
		{
			printf("You couldn't open the relative log file: %s\n", log_file_name);
			return;
		}
	}
}

void log_write(const char * format, ...)
{
	char datebuf[CURRENT_DATE_LEN+1] = ""; // buffer to store the current date
	FILE ** plog_file = log_instance(); // get the log file instance
	va_list args; // variadic argument list

	// if null, we'll skip it
	if (*plog_file == NULL)
		return;

	// get the current date
	get_current_date_format(datebuf, sizeof(datebuf));

	// write the current date in file
	fprintf(*plog_file, "%s :: ", datebuf);
	// write the formatted message in file
	va_start(args, format); // start va processing
	vfprintf(*plog_file, format, args); // format and write to file
	va_end(args); // end va processing
	fprintf(*plog_file, "\n"); // append newline

	fflush(*plog_file); // flush everything in case of runtime issues

#ifdef _DEBUG
	// print the current date
	printf("%s :: ", datebuf);
	// print the formatted message
	va_start(args, format); // start va processing
	vprintf(format, args); // format and write to file
	va_end(args); // end va processing
	printf("\n"); // append newline
#endif
}

void log_deinit(void)
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


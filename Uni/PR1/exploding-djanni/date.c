#include "date.h"

void get_current_date_format(char * datebuf, int datebuf_len)
{
	time_t current_time = time(0); // get current machine time
	struct tm cts = *localtime(&current_time); // get local tm struct
	snprintf(datebuf, datebuf_len, "%04d/%02d/%02d %02d:%02d:%02d", cts.tm_year+1900, cts.tm_mon+1, cts.tm_mday, cts.tm_hour, cts.tm_min, cts.tm_sec); // print format the date
	// note: cts.tm_year starts from 1900, so we must sum the result to that value
	// note2: cts.tm_mon starts from 0, so we must increase it by one
}


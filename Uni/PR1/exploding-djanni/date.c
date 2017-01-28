#include "date.h"

void get_current_date_format(char * datebuf, int datebuf_len)
{
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime); // get current machine time
	timeinfo = localtime(&rawtime); // get local tm struct

	strftime(datebuf, datebuf_len, "%Y/%m/%d %H:%M:%S", timeinfo); // format year/month/day hour:minute:second
}


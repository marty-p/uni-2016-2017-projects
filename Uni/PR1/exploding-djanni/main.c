#include "main.h"

int main(void)
{

	log_init("log.txt");

	core_run();

	log_deinit();

#ifdef _DEBUG
	printf("Press any key to continue...\n");
	getchar(); // simulate key press
#endif
	return 0;
}


#include "main.h"

int main(void)
{
	log_init("log.txt"); // initialize the logging file

	core_run(); // run the game

	log_deinit(); // deinitialize the logging file

#ifdef _DEBUG
	printf("Press any key to continue...\n");
	getchar(); // simulate key press
#endif
	return 0;
}


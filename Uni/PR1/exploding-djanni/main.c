#include "main.h"

int main(void)
{
	srand(time(NULL));

	log_init("log.txt"); // initialize the logging file

	core_run(); // run the game

	log_deinit(); // deinitialize the logging file

#ifdef _DEBUG
	printf("Press enter key to continue...\n");
	getchar(); // simulate enter key press
#endif
	return 0;
}


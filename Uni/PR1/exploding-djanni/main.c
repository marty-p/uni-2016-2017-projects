#include "main.h"

int main(void)
{
	srand(time(NULL)); // generate the initial random seed from the current time machine

	log_init("log.txt"); // initialize the logging file

	core_run(); // run the game

	log_deinit(); // deinitialize the logging file

#ifdef _DEBUG
	printf("Press enter key to continue...\n");
	getchar(); // simulate enter key press
#endif
	return 0; // exit from the program (status 0=ok)
}


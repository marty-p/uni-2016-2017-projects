#include "main.h"

int main(void)
{
	log_init("log.txt");

	log_write("starting the game...");
	core_run();

	log_deinit();
	return 0;
}


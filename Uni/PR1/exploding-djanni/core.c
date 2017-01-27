#include "core.h"

void core_run()
{
	char menu_choice;
	_Bool wrong_choice;

	do
	{
		wrong_choice = false;

		printf("What do you want to do? (1/2/q)\n");
		printf("\t1. Start a new game\n");
		printf("\t2. Load a saved game\n");
		printf("\tq. Exit\n");

		// ask which choice to make
		scanf("%c", &menu_choice);
		clear_input();

		// process the choice
		switch (menu_choice)
		{
			case '1':
				log_write("starting a new game...");
				break;
			case '2':
				log_write("loading a saved game...");
				break;
			case 'q':
				log_write("exit confirmed...");
				return;
				break;
			default: // if it's not in the list, we'll repeat it
				wrong_choice = true;
				break;
		}
	} while (wrong_choice==true);
}


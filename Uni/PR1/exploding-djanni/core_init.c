#include "core_init.h"

_Bool core_init(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus)
{
	char menu_choice;
	_Bool wrong_choice;

	// display the initial menu
	do
	{
		wrong_choice = false;

		printf("What do you want to do? (1/2/q)\n");
		printf("\t1. Start a new game\n");
		printf("\t2. Load a saved game\n");
		printf("\tq. Exit\n");

		// ask which choice to make
		scanf("%c", &menu_choice);
		clear_input_line(); // clear the input line from junk

		// process the choice
		switch (menu_choice)
		{
			case '1':
				log_write("starting a new game...");
				// it will return false if quitted or failed reading the txt files:
				if (core_init_new_game(pPlayers, players_count, pDeck, pStatus) == false)
					return false;
				break;
			case '2':
				log_write("loading a saved game...");
				// it will return false if quitted or failed reading the sav files:
				if (core_init_load_game(pPlayers, players_count, pDeck, pStatus) == false)
					return false;
				break;
			case 'q':
				log_write("exit confirmed...");
				return false;
				break; // redundant line (not executed due to the return statement)
			default: // if it's not in the list, we'll repeat it
				wrong_choice = true;
				break;
		}
	}
	while (wrong_choice==true);

	return true;
}

_Bool core_init_new_game(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus)
{
	core_init_default_players(pPlayers, players_count); // initialize the players
	core_init_default_status(pStatus, pPlayers, players_count); // initialize the game status

	return core_load_default_deck(pPlayers, players_count, pDeck, core_init_choose_mode()); // it will return false in case of failure
}

_Bool core_init_load_game(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus)
{
	char savefile_path[FILEPATH_LEN+1] = ""; // save file's path
	FILE * save_fp = NULL; // ptr of the save file
	int i, j; // counter for iteration
	Card tmp_card; // dummy variable used when freading

	// skip null ptr
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL)
		return false;

	printf("Write the path of the savefile you want to load: (empty: %s)\n", SAVEFILE_FILENAME);
	scanf("%259[^\n]s", savefile_path);
	clear_input_line(); // clear the input line from junk

	// if empty, set up the default filename
	if (strlen(savefile_path)==0)
		strncpy(savefile_path, SAVEFILE_FILENAME, FILEPATH_LEN);

	// open the save file in read and binary mode
	save_fp = fopen(savefile_path, "rb");
	if (save_fp==NULL) // exit in case of failure
	{
		log_write("the save file %s couldn't be open", savefile_path);
		return false;
	}

	// fetching all the data from the binary file
	// first block of data
	for (i=0; i<players_count; i++)
	{
		fread(pPlayers[i].name, sizeof(pPlayers[i].name), 1, save_fp);
		fread(&pPlayers[i].is_alive, sizeof(pPlayers[i].is_alive), 1, save_fp);
		if (pPlayers[i].is_alive==true)
		{
			fread(&pPlayers[i].card_count, sizeof(pPlayers[i].card_count), 1, save_fp);
			fread(&pPlayers[i].type, sizeof(pPlayers[i].type), 1, save_fp);
			for (j=0; j<pPlayers[i].card_count; j++)
			{
				fread(tmp_card.title, sizeof(tmp_card.title), 1, save_fp);
				fread(&tmp_card.type, sizeof(tmp_card.type), 1, save_fp);
				pPlayers[i].card_list = card_node_insert_head(pPlayers[i].card_list, tmp_card);
			}
		}
	}

	// second block of data
	fread(&pDeck->count, sizeof(pDeck->count), 1, save_fp);
	for (i=0; i<pDeck->count; i++)
	{
		fread(tmp_card.title, sizeof(tmp_card.title), 1, save_fp);
		fread(&tmp_card.type, sizeof(tmp_card.type), 1, save_fp);
		pDeck->card_list = card_node_insert_head(pDeck->card_list, tmp_card);
	}

	// third block of data
	fread(&pStatus->player_turn, sizeof(pStatus->player_turn), 1, save_fp);
	fread(&pStatus->is_attacked, sizeof(pStatus->is_attacked), 1, save_fp);
	if (fread(&pStatus->total_turns, sizeof(pStatus->total_turns), 1, save_fp)==0) // extra
		pStatus->total_turns = 0;

	return true;
}

_Bool core_init_save_game(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus)
{
	char savefile_path[FILEPATH_LEN+1] = ""; // save file's path
	FILE * save_fp = NULL; // ptr of the save file
	int i, j; // counter for iteration
	CardNode * pTmpCardNode = NULL; // dummy variable for iteration

	// skip null ptr
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL)
		return false;

	printf("Write the path of the savefile you want to save: (empty: %s)\n", SAVEFILE_FILENAME);
	scanf("%259[^\n]s", savefile_path);
	clear_input_line(); // clear the input line from junk

	// if empty, set up the default filename
	if (strlen(savefile_path)==0)
		strncpy(savefile_path, SAVEFILE_FILENAME, FILEPATH_LEN);

	// open the save file in write and binary mode
	save_fp = fopen(savefile_path, "wb");
	if (save_fp==NULL) // exit in case of failure
	{
		log_write("the save file %s couldn't be open", savefile_path);
		return false;
	}

	// flushing all the data into the binary file
	// first block of data
	for (i=0; i<players_count; i++)
	{
		fwrite(pPlayers[i].name, sizeof(pPlayers[i].name), 1, save_fp);
		fwrite(&pPlayers[i].is_alive, sizeof(pPlayers[i].is_alive), 1, save_fp);
		if (pPlayers[i].is_alive==true)
		{
			fwrite(&pPlayers[i].card_count, sizeof(pPlayers[i].card_count), 1, save_fp);
			fwrite(&pPlayers[i].type, sizeof(pPlayers[i].type), 1, save_fp);
			pTmpCardNode = pPlayers[i].card_list;
			for (j=0; j<pPlayers[i].card_count && pTmpCardNode!=NULL; j++)
			{
				fwrite(pTmpCardNode->card.title, sizeof(pTmpCardNode->card.title), 1, save_fp);
				fwrite(&pTmpCardNode->card.type, sizeof(pTmpCardNode->card.type), 1, save_fp);
				pTmpCardNode = pTmpCardNode->next;
			}
			// redundant check in case we encountered runtime errors
			if (j!=pPlayers[i].card_count)
			{
				log_write("an error occurred when saving the player #%d's deck [j: %d, count: %d, node count: %d]", i, j, pPlayers[i].card_count, card_node_count(pPlayers[i].card_list));
				return false;
			}
		}
	}

	// second block of data
	fwrite(&pDeck->count, sizeof(pDeck->count), 1, save_fp);
	pTmpCardNode = pDeck->card_list;
	for (i=0; i<pDeck->count && pTmpCardNode!=NULL; i++)
	{
		fwrite(pTmpCardNode->card.title, sizeof(pTmpCardNode->card.title), 1, save_fp);
		fwrite(&pTmpCardNode->card.type, sizeof(pTmpCardNode->card.type), 1, save_fp);
		pTmpCardNode = pTmpCardNode->next;
	}
	// redundant check in case we encountered runtime errors
	if (i!=pDeck->count)
	{
		log_write("an error occurred when saving the deck [i: %d, count: %d, node count: %d]", i, pDeck->count, card_node_count(pDeck->card_list));
		return false;
	}

	// third block of data
	fwrite(&pStatus->player_turn, sizeof(pStatus->player_turn), 1, save_fp);
	fwrite(&pStatus->is_attacked, sizeof(pStatus->is_attacked), 1, save_fp);
	fwrite(&pStatus->total_turns, sizeof(pStatus->total_turns), 1, save_fp); // extra

	return true;
}

DifficultyMode core_init_choose_mode(void)
{
	DifficultyMode mode_choice;
	// display the menu
	do
	{
		printf("In which mode do you want to start the game? (%d/%d/%d)\n", EASY, MEDIUM, HARD);
		printf("\t%d. Easy\n", EASY);
		printf("\t%d. Medium\n", MEDIUM);
		printf("\t%d. Hard\n", HARD);

		// ask which choice to make
		scanf("%u", &mode_choice);
		clear_input_line(); // clear the input line from junk
	}
	while (mode_choice >= DIFFICULTY_MODE_NUM); // note: it's unsigned (repeat if invalid)

	log_write("[%u]%s difficulty mode chosen...", mode_choice, get_difficulty_mode_name(mode_choice));
	return mode_choice;
}

_Bool core_init_default_status(GameStatus * pStatus, Player pPlayers[], int players_count)
{
	int i; // player's iter counter
	int is_somebody_alive = false; // if there's someone still alive, it will return true
	int random_turn; // dummy variable to pickup a valid turn
	if (pStatus!=NULL && pPlayers!=NULL)
	{
		// reset the status information
		pStatus->is_attacked = false;
		pStatus->player_turn = 0;
		pStatus->total_turns = 0;
		// check if there's someone still alive
		for (i=0; i<players_count && is_somebody_alive==false; i++)
			if (pPlayers[i].is_alive==true)
				is_somebody_alive = true;
		// skip if they are all dead
		if (is_somebody_alive)
		{
			// decide a random turn from the still alive players
			do
			{
				random_turn = get_random_number(0, players_count);
			}
			while (pPlayers[random_turn].is_alive==false); // repeat if the chosen player is dead

			pStatus->player_turn = random_turn; // assign the turn
		}
	}
	return is_somebody_alive;
}

void core_init_default_players(Player pPlayers[], int players_count)
{
	int i; // player's iter counter
	char dummychar; // dummy variable for scanf

	log_write("initializing the players...");
	if (pPlayers!=NULL) // skip null ptr
	{
		for (i=0; i<players_count; i++)
		{
			printf("Setting up the #%d player:\n", i+1);

			// grab the name
			do
			{
				printf("Choose the player's name:\n");
				scanf("%23s", pPlayers[i].name);
				clear_input_line(); // clear the input line from junk
			}
			while (strlen(pPlayers[i].name)==0); // repeat if empty

#ifdef _DEBUG
			// choose whether being alive or not (debug mode only)
			printf("Choose whether the player must be alive or not: (any:yes, n:no)\n");
			scanf("%c", &dummychar);
			clear_input_line(); // clear the input line from junk
			pPlayers[i].is_alive = (dummychar!='n');
#endif

			// choose the type
			do
			{
				printf("Choose the player's type: (AI:%d/REAL:%d)\n", AI, REAL);
				scanf("%u", &pPlayers[i].type);
				clear_input_line(); // clear the input line from junk
			}
			while (pPlayers[i].type >= PLAYER_TYPE_NUM); // note: it's unsigned (repeat if invalid)

			// null initialize the rest
			card_node_free(pPlayers[i].card_list);
			pPlayers[i].card_list = NULL;
			pPlayers[i].card_count = 0;

		}
		players_log_data(pPlayers, players_count); // log the players' info
	}
}

_Bool core_load_default_deck(Player pPlayers[], int players_count, CardDeck * pGivenDeck, DifficultyMode mode_choice)
{
	// list of the relative decks' filenames
	static const char * deckFileList[DIFFICULTY_MODE_NUM] = {"decks/explodingDjanniEasy.txt", "decks/explodingDjanniMedium.txt", "decks/explodingDjanniHard.txt"};
	FILE * fpDeck = NULL; // file pointer to deck
	CardCount cc = { { {0, NULL}, {0, NULL}, {0, NULL}, } }; // resulting structure of the textual deck files
	int i, j; // temp variable used when itering
	Card tmp_card; // temp variable used when itering

	// check to prevent out-of-range issues (note: mode_choice is unsigned)
	if (mode_choice >= DIFFICULTY_MODE_NUM)
		return false;

	// open the deck file in read mode
	fpDeck = fopen(deckFileList[mode_choice], "r");
	if (fpDeck == NULL) // exit in case of failure
	{
		log_write("the deck file %s couldn't be open", deckFileList[mode_choice]);
		return false;
	}

	// process the first line of the file (counter header)
	if (fscanf(fpDeck, "%d %d %d", &cc.cards[N_EXPLODING_DJANNI].count, &cc.cards[N_MEOOOW].count, &cc.cards[N_OTHER_CARDS].count)!=3)
	{
		log_write("the deck file header couldn't be processed");
		return false;
	}

	log_write("total available cards: exploding djanni %d, meooow %d, others %d", cc.cards[N_EXPLODING_DJANNI].count, cc.cards[N_MEOOOW].count, cc.cards[N_OTHER_CARDS].count);

	log_write("start processing the deck file...");
	// iter every deck (exploding djanni, meooow, others)
	for (i=0; i<CARD_COUNT_NUM; i++)
	{
		// iter each deck's cards
		for (j=0; !feof(fpDeck) && j < cc.cards[i].count; j++)
		{
			// scan type and title and exit in case of failure
			if (fscanf(fpDeck, "%u %127[^\n]s", &tmp_card.type, tmp_card.title)!=2)
			{
				log_write("an error occurred when reading the deck file [i: %d, j: %d]", i, j);
				return false;
			}
			clear_file_input_line(fpDeck); // clear the remaining bytes of the line
			cc.cards[i].card_list = card_node_insert_tail(cc.cards[i].card_list, tmp_card); // adding the card in the relative deck
#ifdef _DEBUG
			log_write("added in deck list [%u]%s: %s", tmp_card.type, get_card_type_name(tmp_card.type), tmp_card.title);
#endif
		}
		// redundant check in case we encountered EOF or other runtime errors
		if (j != cc.cards[i].count || cc.cards[i].count != card_node_count(cc.cards[i].card_list))
		{
			log_write("an error occurred when finished to read the deck file [j: %d, count: %d, node count: %d]", j, cc.cards[i].count, card_node_count(cc.cards[i].card_list));
			return false;
		}
	}

	log_write("total processed cards: exploding djanni %d, meooow %d, others %d",
		card_node_count(cc.cards[N_EXPLODING_DJANNI].card_list), card_node_count(cc.cards[N_MEOOOW].card_list), card_node_count(cc.cards[N_OTHER_CARDS].card_list));

#ifdef _DEBUG
	printf("main deck before deck merging and player's assignment: (%d==%d)\n", pGivenDeck->count, card_node_count(pGivenDeck->card_list));
	card_node_print(pGivenDeck->card_list);
#endif

	core_shuffle_deck(&cc.cards[N_OTHER_CARDS]); // shuffle the other cards
	core_assign_default_deck(pPlayers, players_count, &cc.cards[N_OTHER_CARDS], STARTING_OTHER_CARDS_NUM); // assign the 4 cards for each players
	core_assign_default_deck(pPlayers, players_count, &cc.cards[N_MEOOOW], STARTING_MEOOOW_NUM); // assign a meooow for each player

#ifdef _DEBUG
	printf("main deck before the second deck merging: (%d==%d)\n", pGivenDeck->count, card_node_count(pGivenDeck->card_list));
	card_node_print(pGivenDeck->card_list);
#endif

	core_merge_default_deck(pGivenDeck, &cc.cards[N_EXPLODING_DJANNI]); // merge the exploding djanni deck to the main one
	core_merge_default_deck(pGivenDeck, &cc.cards[N_MEOOOW]); // merge the meooow deck to the main one
	core_merge_default_deck(pGivenDeck, &cc.cards[N_OTHER_CARDS]); // merge the meooow deck to the main one

#ifdef _DEBUG
	printf("main deck before shuffling it: (%d==%d)\n", pGivenDeck->count, card_node_count(pGivenDeck->card_list));
	card_node_print(pGivenDeck->card_list);
#endif

	core_shuffle_deck(pGivenDeck); // merge the main deck for the last time

#ifdef _DEBUG
	printf("main deck after being shuffled: (%d==%d)\n", pGivenDeck->count, card_node_count(pGivenDeck->card_list));
	card_node_print(pGivenDeck->card_list);
	printf("exploding djanni deck after merging: (%d==%d)\n", cc.cards[N_EXPLODING_DJANNI].count, card_node_count(cc.cards[N_EXPLODING_DJANNI].card_list));
	card_node_print(cc.cards[N_EXPLODING_DJANNI].card_list);
	printf("meooow deck after merging: (%d==%d)\n", cc.cards[N_MEOOOW].count, card_node_count(cc.cards[N_MEOOOW].card_list));
	card_node_print(cc.cards[N_MEOOOW].card_list);
	printf("other cards deck after merging: (%d==%d)\n", cc.cards[N_OTHER_CARDS].count, card_node_count(cc.cards[N_OTHER_CARDS].card_list));
	card_node_print(cc.cards[N_OTHER_CARDS].card_list);
#endif

	log_write("the cards have been assigned to each player...");
	players_log_data(pPlayers, players_count); // log all the players

	return true;
}

void core_assign_default_deck(Player pPlayers[], int players_count, CardDeck * pGivenDeck, int given_cards)
{
	int i, j; // counters for iteration
	if (pPlayers!=NULL && pGivenDeck!=NULL) // skip null ptr
	{
		for (i=0; i<players_count; i++) // iter all the players
		{
			for (j=0; j<given_cards && pGivenDeck->card_list!=NULL; j++) // give j cards for i players
			{
				pPlayers[i].card_list = card_node_insert_head(pPlayers[i].card_list, pGivenDeck->card_list->card); // add the first given_deck's card into player's card_list
				pGivenDeck->card_list = card_node_remove_head(pGivenDeck->card_list); // remove the first given_deck's card
				pPlayers[i].card_count++; // keep O(1) card_count updated
				pGivenDeck->count--; // keep O(1) count updated
			}
		}
	}
}

void core_merge_default_deck(CardDeck * pMainDeck, CardDeck * pGivenDeck)
{
	if (pGivenDeck!=NULL) // skip null ptr
	{
		while (pGivenDeck->card_list!=NULL) // give all the cards of the given_deck to the main_deck
		{
			pMainDeck->card_list = card_node_insert_head(pMainDeck->card_list, pGivenDeck->card_list->card); // add the first given_deck's card into main_deck's card_list
			pGivenDeck->card_list = card_node_remove_head(pGivenDeck->card_list); // remove the first given_deck's card
			pMainDeck->count++; // keep O(1) count updated
			pGivenDeck->count--; // keep O(1) count updated
		}
	}
}


int print_welcome(void) {
	printf("*** Welcome to the Connect Four game!!! ***\n");
	printf("Weould you like to make the first move [y/n]: ");
	char input_move[1];
	scanf("%c", input_move);
	while (getchar() != '\n');
	if (input_move == "n" || input_move == "N")
		return 2;
	return 1;
}
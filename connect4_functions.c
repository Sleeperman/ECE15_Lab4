#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define BOARD_SIZE_HORIZ 7
#define BOARD_SIZE_VERT 6


int print_welcome(void) {
	printf("*** Welcome to the Connect Four game!!! ***\n");
	printf("Weould you like to make the first move [y/n]: ");
	char input_move;
	scanf("%c", &input_move);
	while (getchar() != '\n');
	if (input_move == 'n' || input_move == 'N')
		return 2;
	return 1;
}

void display_board(int board[][BOARD_SIZE_VERT]){
    int col, row;
    //board[3][3] = 1;
    //board[5][2] = 2;
    for (row = 0; row < BOARD_SIZE_VERT; row++){
        for (col = 0; col < BOARD_SIZE_HORIZ; col++){
            printf("+---");
        }
        printf("+\n");
        for (col = 0; col < BOARD_SIZE_HORIZ; col++){
            char player_move = ' ';
            if (board[col][row] == 1)
                player_move = 'X';
            else if (board[col][row] == 2)
                player_move = 'O';
            printf("| %c ", player_move);
        }
        printf("|\n");
    }
    printf("+---+---+---+---+---+---+---+\n");
    printf("  1   2   3   4   5   6   7  \n");
}

void update_board(int board[][BOARD_SIZE_VERT], int m, int player_num){
    // m is 1 - 7
    int vertical_position = 0;
    
    for (int j = BOARD_SIZE_VERT - 1; j >= 0 ; j--){//gets the vertical position of the empty cell
        if (board[m - 1][j] == 0){
            vertical_position = j;
            break;
        }
    }
        board[m-1][vertical_position] = player_num;
    
}


bool is_column_full(int board[][BOARD_SIZE_VERT], int m){
    bool full = false;
    if (board[m-1][0] != 0)
        full = true;
    return full;
}

int random_move(int board[][BOARD_SIZE_VERT], int computer_num){
    int computer_move;
    srand(time(0));
again:
    computer_move = rand() % (BOARD_SIZE_HORIZ + 1);
    bool valid = is_column_full(board, computer_move);
    if (valid)
        goto again;
   // board[computer_move - 1][1] = computer_num;
    update_board(board, computer_move, computer_num);
    //return the col computer moved in
    return computer_move;
}




int player_move(int board[][BOARD_SIZE_VERT], int player_num){
    //int valid = 1;
    int vertical_position = 0;
    int player_move;
    while (1){
        printf("Please enter your move: ");
        scanf("%d", &player_move);
        if (is_column_full(board, player_move)){
            printf("Not a valid move. Enter a column number!\n");
            continue;
        }
            
        if (player_move <= BOARD_SIZE_HORIZ && player_move > 0 && is_column_full(board, player_move == 0))
            break;
        while (getchar() != '\n');
        printf("Not a valid move. Enter a column number!\n");
    }
    
    for (int j = 0; j < BOARD_SIZE_VERT; j++){//gets the vertical position of the empty cell
        if (board[player_move - 1][j] == 0){
            vertical_position = j;
            break;
        }
    }
    update_board(board, player_move, player_num);
    return player_move;
}


bool check_win_or_tie(int board[][BOARD_SIZE_VERT], int last_move){
    int non_empty_space = 0;
    for (int i = 0; i < BOARD_SIZE_HORIZ; i++){
        for (int j = 0; j < BOARD_SIZE_VERT; j++){
            if (board[j][i] != 0){
                non_empty_space++;
            }
            if (board[j][i] != 0 && board[j][i] == board[j + 1][i] && board[j + 1][i] == board[j + 2][i] && board[j + 2][i] == board[j + 3][i]){//check horizontal for win
                if (board[j][i] == 1){
                    printf("Player X won!\n");
                    return true;
                }
                if (board[j][i] == 2){
                    printf("Player O won!\n");
                    return true;
                }
            }
            else if (board[j][i] != 0 && board[j][i] == board[j][i + 1] && board[j][i + 1] == board[j][i + 2] && board[j][i + 2] == board[j][i + 3]){//check vertical
                if (board[j][i] == 1){
                    printf("Player X wins!\n");
                    return true;
                }
                if (board[j][i] == 2){
                    printf("Player O wins!\n");
                    return true;
                }
            }
            else if (board[j][i] != 0 && board[j][i] == board[j + 1][i + 1] && board[j + 1][i + 1] == board[j + 2][i + 2] && board[j + 2][i + 2] == board[j + 3][i + 3]){
                if (board[j][i] == 1){
                    printf("Player X wins!\n");
                    return true;
                }
                if (board[j][i] == 2){
                    printf("Player O wins!\n");
                    return true;
                } //check diagnoal 1
            }
        }
    }
    for (int i = 0; i < 4; i++){
        for (int j = BOARD_SIZE_VERT; j >= 3; j--){
            if (board[j][i] == board[j - 1][i + 1] && board[j - 1][i + 1] == board[j - 2][i + 2] && board[j - 2][i + 2] == board[j - 3][i + 3]){
                if (board[j][i] == 1){
                    printf("Player X wins!\n");
                    return true;
                }
                if (board[j][i] == 2){
                    printf("Player O wins!\n");
                    return true;
                }
            }
        }
    }
    if (non_empty_space == BOARD_SIZE_VERT * BOARD_SIZE_HORIZ){
        printf("Tie game!");
        return true;
    }
    return false;
}


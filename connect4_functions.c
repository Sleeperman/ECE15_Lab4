#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define BOARD_SIZE_HORIZ 7
#define BOARD_SIZE_VERT 6

#include "connect4_functions.h"

int print_welcome(void) {
	printf("*** Welcome to the Connect Four game!!! ***\n");
	printf("Would you like to make the first move [y/n]: \n");
	char input_move;
	scanf("%c", &input_move);
	while (getchar() != '\n');
	if (input_move == 'n' || input_move == 'N')
		return 2;
	return 1;
}

void display_board(int board[][BOARD_SIZE_VERT]){
    printf("\n");
    int col, row;
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
    printf("  1   2   3   4   5   6   7  \n\n");
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
    int player_move;
    while (1) {
        printf("Please enter your move: ");
        scanf("%d", &player_move);
        while (getchar() != '\n');
        if (player_move > BOARD_SIZE_HORIZ || player_move < 0){
            printf("Not a valid move. Enter a column number!\n");
            continue;
              }

        if (player_move <= BOARD_SIZE_HORIZ && player_move > 0 && is_column_full(board, player_move) == 0)// if valid move
            break;

        if (player_move > 0 && player_move <= BOARD_SIZE_HORIZ && is_column_full(board, player_move)){//if value is between 1 and 7
     
            printf("This column is full. Try again!\n");
            player_move = 0;
            continue;
        }
            
        printf("Not a valid move. Enter a column number!\n");
    }
    
    update_board(board, player_move, player_num);
    return player_move;
}

int check_winner(int board[][BOARD_SIZE_VERT], int last_move){
    int row = BOARD_SIZE_VERT - 1; 
    int empty = 0;
    for (int i = 0; i < BOARD_SIZE_HORIZ; i++) {
        for (int j = 0; j < BOARD_SIZE_VERT; j++) {
            if (board[j][i] == 0) {
                empty++;
            }
        }
    }
    while (1) {
        if (board[last_move - 1][row] == 0 && board[last_move - 1][row - 1] != 0)
            break;
        else if (is_column_full(board, last_move) && empty != 0)
            return board[last_move - 1][0];
        else if (empty == 0)
            return 0;
       
        row--;
    }
    return board[last_move - 1][row -1];
}

bool check_win_or_tie(int board[][BOARD_SIZE_VERT], int last_move){
    int non_empty_space = 0;
    //printf("%d x %d", sizeof(board) / sizeof(board[0]), sizeof(board[0]));
    for (int i = 0; i < BOARD_SIZE_HORIZ; i++){
        for (int j = 0; j < BOARD_SIZE_VERT; j++){
            
            if (board[j][i] != 0){
                non_empty_space++;
            }
            if (board[j][i] != 0 && board[j][i] == board[j + 1][i] && board[j + 1][i] == board[j + 2][i] && board[j + 2][i] == board[j + 3][i]){//check horizontal for win
                if (board[j][i] == 1){
                    printf("*****************************\n");
                    printf("* Player X won!!! Game over *\n");
                    printf("*****************************\n");
                    return true;
                }
                if (board[j][i] == 2){
                    printf("*****************************\n");
                    printf("* Player O won!!! Game over *\n");
                    printf("*****************************\n");
                    return true;
                }
            }
            else if (i != 5 && board[j][i] != 0 && board[j][i] == board[j][i + 1] && board[j][i + 1] == board[j][i + 2] && board[j][i + 2] == board[j][i + 3]){//check vertical
                if (board[j][i] == 1){
                    //printf("j:%d i:%d %d %d %d %d\n", j, i, board[j][i], board[j][i + 1], board[j][i + 2], board[j][i + 3]);
                    printf("*****************************\n");
                    printf("* Player X won!!! Game over *\n");
                    printf("*****************************\n");
                    return true;
                }
                if (board[j][i] == 2){
                    //printf("j:%d i:%d %d %d %d %d\n", j, i,board[j][i], board[j][i + 1], board[j][i + 2], board[j][i + 3]);
                    printf("*****************************\n");
                    printf("* Player O won!!! Game over *\n");
                    printf("*****************************\n");
                    return true;
                }
            }
            else if (board[j][i] != 0 && board[j][i] == board[j + 1][i + 1] && board[j + 1][i + 1] == board[j + 2][i + 2] && board[j + 2][i + 2] == board[j + 3][i + 3]){
                if (board[j][i] == 1){
                    printf("*****************************\n");
                    printf("* Player X won!!! Game over *\n");
                    printf("*****************************\n");
                    return true;
                }
                if (board[j][i] == 2){
                    printf("*****************************\n");
                    printf("* Player O won!!! Game over *\n");
                    printf("*****************************\n");
                    return true;
                } //check diagnoal 1
            }
        }
    }
    for (int i = 0; i < 4; i++){
        for (int j = BOARD_SIZE_VERT; j >= 3; j--){
            if (board[j][i] == board[j - 1][i + 1] && board[j - 1][i + 1] == board[j - 2][i + 2] && board[j - 2][i + 2] == board[j - 3][i + 3]){
                if (board[j][i] == 1){
                    printf("*****************************\n");
                    printf("* Player X won!!! Game over *\n");
                    printf("*****************************\n");
                    return true;
                }
                if (board[j][i] == 2){
                    printf("*****************************\n");
                    printf("* Player O won!!! Game over *\n");
                    printf("*****************************\n");
                    return true;
                }
            }
        }
    }
    if (non_empty_space == BOARD_SIZE_VERT * BOARD_SIZE_HORIZ){
        printf("*****************************\n");
        printf("* Game is a tie!! No winner *\n");
        printf("*****************************\n");
        return true;
    }
    return false;
}


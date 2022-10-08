#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
bool cpuGame;

void printBoard() {
    puts("+-----------+");
    printf("| %c | %c | %c |\n", board[0], board[1], board[2]);
    puts("+-----------+");
    printf("| %c | %c | %c |\n", board[3], board[4], board[5]);
    puts("+-----------+");
    printf("| %c | %c | %c |\n", board[6], board[7], board[8]);
    puts("+-----------+");
}

void resetBoard() {
    for (int i = 0; i < 9; i++) {
        board[i] = ' ';
    }
}

bool won(char piece) {
    int winSum = 3 * piece;
    //horizontal lines
    for (int row = 0; row < 9; row += 3) {
        if (board[row] + board[row + 1] + board[row + 2] == winSum) {
            return true;
        }
    }
    //vertical lines
    for (int col = 0; col < 3; col++) {
        if (board[col] + board[col + 3] + board[col + 6] == winSum) {
            return true;
        }
    }
    //diagonal lines
    return board[0] + board[4] + board[8] == winSum || board[2] + board[4] + board[6] == winSum;
}

bool tie() {
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            return false;
        }
    }
    return true;
}

bool validPosition(int boardIndex) {
    return boardIndex >= 0 && boardIndex <= 8 && board[boardIndex] == ' ';
}

int coordsToBoardIndex(int x, int y) {
    return (x - 1) + 3 * (y - 1);
}

void turn(int player, char piece) {
    int boardIndex;
    if (player == 2 && cpuGame) {
        puts("CPU, place your piece!");
        do {
            boardIndex = rand() % 9;
        } while (!validPosition(boardIndex));
    } else {
        printf("Player %d, enter coords to place your piece: ", player);
        int x, y;
        scanf("%d %d", &x, &y);
        boardIndex = coordsToBoardIndex(x, y);
        while (!validPosition(boardIndex)) {
            puts("Invalid position, try again: ");
            scanf("%d %d", &x, &y);
            boardIndex = coordsToBoardIndex(x, y);
        }
    }
    board[boardIndex] = piece;
}

void main() {
    srand(time(NULL));
    puts("Let's begin a game of Tic-Tac-Toe!\nWho are you playing against?\n1 = Human\n2 = CPU");
    int option;
    scanf("%d", &option);
    while (option != 1 && option != 2) {
        printf("Invalid input, try again: ");
        scanf("%d", &option);
    }
    cpuGame = option == 2;
    puts("Start!");
    printBoard();
    while (true) {
        turn(1, 'X');
        printBoard();
        if (won('X')) {
            puts("Player 1 wins!");
            break;
        } else if (tie()) { //can only occur here because player 1 has last move
            puts("Game is a tie!");
            break;
        }
        turn(2, 'O');
        printBoard();
        if (won('O')) {
            printf("%s wins!\n", cpuGame ? "CPU" : "Player 2");
            break;    
        }
    }
    char response;
    do {
        printf("Would you like to play again (y/n)? ");
        scanf(" %c", &response);        
    } while (response != 'y' && response != 'n');
    if (response == 'y') {
        resetBoard();
        main();
    }
}



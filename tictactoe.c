#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
bool cpuGame = false;

bool won(char c) {
    int winSum = 3 * c;
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
    if (board[0] + board[4] + board[8] == winSum) {
        return true;
    } else if (board[2] + board[4] + board[6] == winSum) {
        return true;
    }

    return false;
}

bool tie() {
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            return false;
        }
    }
    return true;
}

bool validPosition(int posIndex) {
    return posIndex >= 0 && posIndex <= 8 && board[posIndex] == ' ';
}

int coordsToPosition(int x, int y) {
    return (x - 1) + 3 * (y - 1);
}

void playerOneTurn() {
    puts("Player 1, enter coords to place your piece: ");
    int x;
    int y;
    int posIndex;
    scanf("%d %d", &x, &y);
    posIndex = coordsToPosition(x, y);
    while (!validPosition(posIndex)) {
        puts("Invalid position, try again: ");
        scanf("%d %d", &x, &y);
        posIndex = coordsToPosition(x, y);
    }
    board[posIndex] = 'X';
}

void playerTwoTurn() {
    int posIndex;
    if (cpuGame) {
        do {
            posIndex = rand() % 9;
        } while (!validPosition(posIndex));
        puts("CPU, place your piece!");
    } else {
        puts("Player 2, enter coords to place your piece: ");
        int x;
        int y;
        scanf("%d %d", &x, &y);
        posIndex = coordsToPosition(x, y);
        while (!validPosition(posIndex)) {
            puts("Invalid position, try again: ");
            scanf("%d %d", &x, &y);
            posIndex = coordsToPosition(x, y);
        }
    }
    board[posIndex] = 'O';
}

void printBoard() {
    puts("+-----------+");
    printf("| %c | %c | %c |\n", board[0], board[1], board[2]);
    puts("+-----------+");
    printf("| %c | %c | %c |\n", board[3], board[4], board[5]);
    puts("+-----------+");
    printf("| %c | %c | %c |\n", board[6], board[7], board[8]);
    puts("+-----------+");
}

int main() {
    srand(time(NULL));
    puts("Welcome! Who are you playing against?\n1 = Human\n2 = CPU");
    int option;
    scanf("%d", &option);
    if (option == 2) {
        cpuGame = 1;
    }
    puts("Start!");
    printBoard();
    while (true) {
        playerOneTurn();
        printBoard();
        if (won('X')) {
            puts("Player 1 wins!");
            break;
        }
        if (tie()) { //can only occur here because player 1 has last move
            puts("Game is a tie!");
            break;
        }
        playerTwoTurn();
        printBoard();
        if (won('O')) {
            if (cpuGame) {
                puts("CPU wins!");
            } else {
                puts("Player 2 wins!");
            }
            break;    
        }
    }
    return 0;
}



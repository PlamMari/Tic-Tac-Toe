// Tic-Tac-Toe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
using namespace std;

#define SIDE 3
// Side of the board

// Player 1 will move with 'O' and Player 2 with 'X'
#define PLAYER_1 'O'
#define PLAYER_2 'X'

// Show the current board
void showBoard(char board[][SIDE]) {
    printf("\n\n");

    printf("\t\t\t  %c  |  %c  |  %c  \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t-----------------\n");
    printf("\t\t\t  %c  |  %c  |  %c  \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t-----------------\n");
    printf("\t\t\t  %c  |  %c  |  %c  \n\n", board[2][0], board[2][1],
        board[2][2]);
}

// Show the instructions
void showInstructions() {
    printf("\t\t\t  Tic-Tac-Toe\n\n");
    printf("Choose the number of the box, that you want to play.\n\n");

    printf("\t\t\t  1  |  2  |  3  \n");
    printf("\t\t\t------------------\n");
    printf("\t\t\t  4  |  5  |  6  \n");
    printf("\t\t\t------------------\n");
    printf("\t\t\t  7  |  8  |  9  \n\n");

    printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");
}

void initialise(char board[][SIDE]) {
    // Initially the board is empty
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            board[i][j] = ' ';
        }
    }
}

// Declare the winner of the game
void declareWinner(int whoseTurn) { printf("%c has won!\n", whoseTurn); }

// Check if any of the row is crossed
bool rowCrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
            return (true);
    }
    return (false);
}

// Check if any of the column is crossed
bool columnCrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        if (board[0][i] != ' ' && board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
            return (true);
    }
    return (false);
}

// Check if any of the diagonal is crossed
bool diagonalCrossed(char board[][SIDE]) {
    if (board[0][0] != ' ' && board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
        return (true);

    if (board[0][2] != ' ' && board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
        return (true);

    return (false);
}
// Check that returns true if the game is over
//  else it returns a false
inline bool hasWinner(char board[][SIDE]) {
    return (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board));
}

inline bool hasNoMoreMoves(int moveIndex) { return moveIndex >= SIDE * SIDE; }

inline bool isMoveValid(char board[][SIDE], int x, int y) {
    return (x >= 0 && x < SIDE) && (y >= 0 && y < SIDE) && board[x][y] == ' ';
}
// A function to play Tic-Tac-Toe
void playTicTacToe(int whoseTurn) {
    // A 3*3 Tic-Tac-Toe board for playing
    char board[SIDE][SIDE];

    initialise(board);

    // Show the instructions before playing
    showInstructions();

    int moveIndex = 0, x, y;
    int position = -1;

    // Keep playing till the game is over or it is a draw

    while (!hasWinner(board) && !hasNoMoreMoves(moveIndex)) {
        // Manual input for Player whoseTurn
        bool isPositionValid = false;
        printf("It's %c's turn.\n", whoseTurn);
        do {
            printf("Please choose a box.\n");
            cin >> position;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            x = (position - 1) / SIDE;
            y = (position - 1) % SIDE;
            // Check if the move is valid and show message, if not valid
            isPositionValid = isMoveValid(board, x, y);
            if (!isPositionValid) {
                printf("Please enter a valid position. The position you have entered "
                    "is either not in the range from 1 to 9 or is already taken\n");
            }
        } while (!isPositionValid);
        board[x][y] = whoseTurn;
        printf("%c has chosen box %d.\n", whoseTurn, position);
        showBoard(board);
        whoseTurn = (whoseTurn == PLAYER_1) ? PLAYER_2 : PLAYER_1;
        moveIndex++;

        // Fill last remaining position
        if (moveIndex == SIDE * SIDE - 1) {
            for (int x_ = 0; x_ < SIDE; x_++)
                for (int y_ = 0; y_ < SIDE; y_++)
                    if (board[x_][y_] == ' ') {
                        board[x_][y_] = whoseTurn;
                        whoseTurn = (whoseTurn == PLAYER_1) ? PLAYER_2 : PLAYER_1;
                        moveIndex++;
                    }
        }
    }

    if (hasWinner(board)) {
        // Toggling the user to declare the actual winner
        if (whoseTurn == PLAYER_1) {
            whoseTurn = PLAYER_2;
        }
        else if (whoseTurn == PLAYER_2) {
            whoseTurn = PLAYER_1;
        }
        declareWinner(whoseTurn);
    }
    else {
        printf("It's a draw.\n");
    }
}

int main() {
    // Game starts with player 1
    playTicTacToe(PLAYER_1);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

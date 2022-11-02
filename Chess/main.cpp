#include "board.h"
#include "pieces.h"
#include <stdio.h>

void Board::newGame() {

    //Reset game state
    whoseTurn = Color::WHITE;
    clearBoard();

    Color nearSideColor = (getWhitePiecesDir() > 0) ? Color::WHITE : Color::BLACK;
    Color farSideColor = (getWhitePiecesDir() > 0) ? Color::BLACK : Color::WHITE;

    //Place figures on near side
    addPiece("e1", new King(nearSideColor));
    addPiece("d1", new Queen(nearSideColor));
    addPiece("c1", new Bishop(nearSideColor));//L
    addPiece("f1", new Bishop(nearSideColor));//R
    addPiece("b1", new Knight(nearSideColor));//L
    addPiece("g1", new Knight(nearSideColor));//R
    addPiece("a1", new Rook(nearSideColor));//L
    addPiece("h1", new Rook(nearSideColor));//R

    //pawns
    for (int j = 0; j < BOARD_SIDE; ++j) { addPiece(Position(1, j), new Pawn(nearSideColor)); }

    //Place figures on far side
    addPiece("e8", new King(farSideColor));
    addPiece("d8", new Queen(farSideColor));
    addPiece("c8", new Bishop(farSideColor));//L
    addPiece("f8", new Bishop(farSideColor));//R
    addPiece("b8", new Knight(farSideColor));//L
    addPiece("g8", new Knight(farSideColor));//R
    addPiece("a8", new Rook(farSideColor));//L
    addPiece("h8", new Rook(farSideColor));//R

    //pawns
    for (int j = 0; j < BOARD_SIDE; ++j) { addPiece(Position(BOARD_SIDE - 2, j), new Pawn(farSideColor)); }
}


// Driver Code
int main() {

    Board board = Board();

    board.newGame();   

    //Input example
    
    while (true) {
        bool isMoveValid = false;
        Position from;
        Position to;
        char inpfrom[3], inpto[3];
        while (!isMoveValid) {
            board.printBoard();
            board.printMessages();
            printf("Enter your move: ");
            scanf("%s %s", (char*)&inpfrom, (char*)&inpto);
            printf("\n");
            
            Position from = inpfrom;
            Position to = inpto;
            isMoveValid = board.movePiece(from, to);
            
        }
        board.endTurn();
        if (board.getWhoseTurn() == NONE) {
            break;
        }
    }   
    if (board.whoWins == Color::WHITE) {
        printf("Check mate. White wins!");
    }
    if (board.whoWins == Color::BLACK) {
        printf("Check mate. White wins!");
    }
    if (board.whoWins == Color::NONE) {
        printf("It's a draw!");
    }
    


    return 0;
}

/*
    board.addPiece("f7", new Pawn(Color::BLACK));
    board.addPiece("f6", new Pawn(Color::BLACK));
    board.endTurn();
    board.movePiece("f7", "f5");
*/


/*
//Testing pawns
board.movePiece("e2", "e4");
board.movePiece("e4", "e5");
//board.changeTurn();
board.movePiece("e5", "f6");
//board.removePiece("e2");
//board.clearBoard();

board.addPiece("f7", new Pawn(Color::BLACK));
board.addPiece("f6", new Pawn(Color::BLACK));
board.changeTurn();
board.movePiece("f7", "f5");*/


//Testing bishop
/*board.movePiece("c1", "f4");
board.movePiece("f4", "g5");*/

#include "./board.h"
#include "./pieces.h"

#include <iostream>
#include <stdio.h>

using namespace std;

//#define SAFE_DELETE(x) if(x!= nullptr) { delete x; x= nullptr; }

bool Board::movePiece(Position from, Position to) {

    if (from == to || !from.isValid() || !to.isValid()) {
        say("Invalid positions specified.");
        return false;
    }

    //get figure from board at "from" pos    
    Piece* pieceAtFrom = getPiece(from);
    Piece* pieceAtTo = getPiece(to);

    if (pieceAtFrom == nullptr) {
        say("There is no figure to move. Enter a valid move.");
        return false;
    }

    if (whoseTurn != pieceAtFrom->getPieceColor()) {
        //&& (toPosition==nullptr || fromPosition->getPieceColor() != toPosition->getPieceColor())) {
        //fromPosition->move();
        say("You can only move a figure of your color.");
        return false;
    }

    if(check && pieceAtFrom->getPieceChar() != 'K')
    {
        say("You can move only the King, when you are checked.");
        return false;
    }

    //fail, if you want to move ontop of one of your other figures.
    if (pieceAtTo != nullptr && pieceAtFrom->getPieceColor() == pieceAtTo->getPieceColor()) {
        say("You cannot take a figure of your own color.");
        return false;
    }

    //Handle special moves cases
    bool hasPerformedSpecialMove= false;
    if(pieceAtFrom->getPieceChar() == 'K') {
        King* kingAtFrom= (King*)pieceAtFrom;
        Position rookPosFrom, rookPosTo;
        if(kingAtFrom->castle(from, to, *this, rookPosFrom, rookPosTo)) {
            setPiece(rookPosTo, getPiece(rookPosFrom));
            setPiece(rookPosFrom, nullptr);
            hasPerformedSpecialMove= true;
        }
    }

    //If the piece at "from" position is happy with the move, then do the actual address swapping on the board
    if (pieceAtFrom->move(from, to, *this) || hasPerformedSpecialMove) {
        removePiece(to);//Remove the figure at the "to" position, if any figure is present
        setPiece(to, pieceAtFrom);
        setPiece(from, nullptr);//Nullify the from position, because the figure has moved to the "to" position

        return true;
    }
    say("Invalid move.");
    return false;
}

bool Board::isPositionAttacked(Position pos, Color by) {
    for(int r= 0; r< BOARD_SIDE; r++) {
        for(int c= 0; c< BOARD_SIDE; c++) {
            Position curr(r, c);
            Piece* pieceAtCurrPos= getPiece(curr);
            if(pieceAtCurrPos != nullptr && pieceAtCurrPos->getPieceColor() == by) {
                if(pieceAtCurrPos->move(curr, pos, *this))
                {
                    return true;
                }
            }
        }
    }
    return false;
}


bool Board::isPathFree(Position from, Position to) {

    //Both the "from" and "to" positions must be valid for this check to work.
    if(!from.isValid() || !to.isValid()) { return false; }

    int rowDiff = to.r - from.r;
    int colDiff = to.c - from.c;
    
    int dc = sign(colDiff);
    int dr = sign(rowDiff);
    if (dc == 0 && dr == 0) {
        return false;
    }

    Position curr = from;
    while (curr != to) {
        curr.r = curr.r + dr;
        curr.c = curr.c + dc;
        if (curr == to) { return true; }//"to" is the next position on the path, so path is free right up to "to"
        if (!curr.isValid()) { return false; }//End loop if current position goes out of bounds.
        if (getPiece(curr) != nullptr) { return false; }//Another figure is present on the path, between "from" and "to".
    }
}

bool Board::isPathAttacked(Position from, Position to, Color attackerColor) {

    //Both the "from" and "to" positions must be valid for this check to work.
    if(!from.isValid() || !to.isValid()) { return false; }

    int rowDiff = to.r - from.r;
    int colDiff = to.c - from.c;
    
    int dc = sign(colDiff);
    int dr = sign(rowDiff);
    if (dc == 0 && dr == 0) {
        return false;
    }

    Position curr = from;
    while (curr != to) {
        curr.r = curr.r + dr;
        curr.c = curr.c + dc;
        if (curr == to) { return false; }//"to" is the next position on the path, so path is free right up to "to"
        if (!curr.isValid()) { return false; }//End loop if current position goes out of bounds.
        if(isPositionAttacked(curr, attackerColor)) { return true; }
    }
}

void Board::endTurn() {
    if(whoseTurn == Color::NONE) { return; }
    whoseTurn = (whoseTurn == Color::BLACK) ? Color::WHITE: Color::BLACK;
    check= false;
    if(whoseTurn == Color::BLACK) {
        check= isPositionAttacked(blackKingPos, Color::WHITE);
        Piece* blackKing= getPiece(blackKingPos);
        if(blackKing == nullptr) {
            whoseTurn= Color::NONE;
            return;
        }
        if (check) {
            ((King*)blackKing)->hasBeenChecked = true;
        }
        bool canMove = King::canMove(blackKingPos, Color::BLACK, *this);
        if (!canMove && check) {
            whoseTurn = Color::NONE;
            whoWins = Color::WHITE;
            return;
        }
        if (!canMove && !check && blackCount == 1) {
            whoseTurn = Color::NONE;
            whoWins = Color::NONE;
            return;
        }
    }
    else {
        check= isPositionAttacked(whiteKingPos, Color::BLACK);        
        Piece* whiteKing= getPiece(whiteKingPos);
        if(whiteKing == nullptr) {
            whoseTurn= Color::NONE;            
            return;
        }
        if (check) {            
            ((King*)whiteKing)->hasBeenChecked = true;
        }
        
        bool canMove = King::canMove(whiteKingPos, Color::WHITE, *this);
        if (!canMove && check) {
            whoseTurn = Color::NONE;
            whoWins = Color::BLACK;
            return;
        }
        if (!canMove && !check && whiteCount == 1) {
            whoseTurn = Color::NONE;
            whoWins = Color::NONE;
            return;
        }
    }
}

Color Board::getWhoseTurn() {
    return whoseTurn;
}

Color Board::getCellColor(const Position & pos) {
    //print checkered pattern of the board
    Color currentCellColor = Color::NONE;
    int i = pos.r; int j = pos.c;

    if (!pos.isValid()) {
        return Color::NONE;
    }
    if (i % 2 == 0)//even row
    {
        currentCellColor = ((j + 1) % 2 == 0) ? Color::WHITE : Color::BLACK;
    }
    else//odd row
    {
        currentCellColor = ((j + 0) % 2 == 0) ? Color::WHITE : Color::BLACK;
    }
    return currentCellColor;
}

bool Board::setPiece(Position at, Piece* toSet)
{
    if(!at.isValid()) { return false; }
    //Record the position of the kings
    if(toSet != nullptr && toSet->getPieceChar() == 'K')
    {
        if(toSet->getPieceColor() == Color::WHITE) {
            whiteKingPos= at;
        } else {
            blackKingPos= at;
        }
    }
    board[at.r][at.c] = toSet;
    return true;
}

Piece* Board::getPiece(const Position& pos) {
    if (!pos.isValid()) {
        return nullptr;
    }
    return board[pos.r][pos.c];
}

bool Board::addPiece(Position at, Piece* newPiece) {
    if (newPiece == nullptr) return false;
    if (at.isValid()) {    
        
        if (newPiece->getPieceColor() == WHITE) {
            whiteCount++;
        }
        if (newPiece->getPieceColor() == BLACK) {
            blackCount++;
        }
        return setPiece(at, newPiece);
    }
    return false;
}

bool Board::removePiece(Position at) {
    if (!at.isValid()) {
        return false;
    }

    Piece*& pieceAt = board[at.r][at.c];//Get a reference to the memory of the board at row at.r and col at.c ("at" position), where the address of a piece (Piece*) is stored
    if (pieceAt != nullptr) {        
        if (pieceAt->getPieceColor() == WHITE) {
            whiteCount--;
        }
        if (pieceAt->getPieceColor() == BLACK) {
            blackCount--;
        }
        delete pieceAt;
        pieceAt = nullptr;
    }
    return true;
}



void Board::initBoard() {
    //Init the play board
    for (int i = 0; i < BOARD_SIDE; ++i) {
        for (int j = 0; j < BOARD_SIDE; ++j) {
            board[i][j] = nullptr;
        }
    }
}

void Board::clearBoard() {
    for (int i = 0; i < BOARD_SIDE; ++i) {
        for (int j = 0; j < BOARD_SIDE; ++j) {
            removePiece(Position(i, j));
        }
    }
}


//Printing
/*
    Alternative to next code : #include "./board_printing_impl.h" 
    - The purpose of the board_printing_impl.h file is to contain the part 
    of the implementation of board, only consernned with printing. By using this pattern
    a long source file of a complicated class can be split up into multiple "sections" (small parts).
*/

void Board::say(char* message) {    
    strcpy(messagesBuffer, message);
}

void Board::printMessages() {    
    printf(messagesBuffer);
    printf("\n");
    messagesBuffer[0] = '\0';
}

void printCell(char cellchar, Color cellColor, Color pieceColor = Color::NONE);

void Board::printBoard() {

    //Piece* (&arr_board)[SIDE][SIDE]
    //Print the board with numbers and letters on the side
#ifdef ENABLE_SCREEN_CLEAR
    system("CLS");
#endif
    for (int i = 10 - 1; i >= 0; --i) {
        for (int j = 0; j < 10; ++j) {
            bool A = i == 0 || i == 9;
            bool B = j == 0 || j == 9;
            if (A || B) {
                if (i == j || i + j == 9) { cout << '\ '; }
                else {
                    printCell((char)(A ? ASCII_LETTER_UPPER - 1 + j : i + ASCII_DIGIT_LOW), Color::NONE);
                }
            }
            else {
                Position cellPosition(i - 1, j - 1);
                Color currentCellColor = getCellColor(cellPosition);
                // declare pointer to data member
                //char Piece::* ptr = &Piece::pieceChar;
                Piece* currentCellPiece = board[i - 1][j - 1];
                char currentCellChar = (currentCellPiece != nullptr) ? currentCellPiece->getPieceChar() : '\ ';
                Color pieceColor = (currentCellPiece != nullptr) ? currentCellPiece->getPieceColor() : Color::NONE;
                //arr_board[i - 1][j - 1] = '\ ';
                printCell(currentCellChar, currentCellColor, pieceColor);
            }
        }
        cout << endl;
    }
    printf("It's %s's turn.\n", whoseTurn == WHITE ? "white" : "black");
    if (check) {
        printf("Check!");
    }
}

#ifdef ENABLE_PRETTY_BOARD_PRINTING

#include <io.h>
#include <windows.h>

// Print color of the board and pieces using console colors
void printCell(char cellchar, Color cellColor, Color pieceColor) {

    //Default console color is set to 15
    const static char DEF_CONSOLE_COLOR = 15;

    static HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    int backForegrCode = DEF_CONSOLE_COLOR;//default background-foreground color
    if (cellColor == Color::BLACK) {
        backForegrCode = (pieceColor == Color::WHITE) ? 135 : 128;
    }
    else if (cellColor == Color::WHITE) {
        backForegrCode = (pieceColor == Color::WHITE) ? 103 : 96;
    }
    SetConsoleTextAttribute(console_color, backForegrCode);
    printf("%c", cellchar);
    SetConsoleTextAttribute(console_color, DEF_CONSOLE_COLOR);
}
#else

// Print color of the board and pieces using console colors
void printCell(char cellchar, Color cellColor, Color pieceColor) {

    if(pieceColor == Color::NONE && cellColor != Color::NONE){
        printf("%c", cellColor == Color::WHITE? (char)176: (char)178);
    }
    else{
        cellchar= (pieceColor == Color::BLACK)? toLower(cellchar): cellchar;
        printf("%c", cellchar);
    }
}

#endif
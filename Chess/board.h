#ifndef BOARD_H_
#define BOARD_H_

#include "./common.h"

class Piece;

class Board {
public:
    Board() {
        initBoard();
    }
    ~Board() {
        clearBoard();
    }
    void initBoard();
    void newGame();
    void clearBoard();

    void say(char* message);
    void printMessages();
    void printBoard();

    inline int getWhitePiecesDir() { return dirWhite; }
    Color getWhoseTurn();

    Color getCellColor(const Position& pos);
    Piece* getPiece(const Position& pos);

    bool addPiece(Position at, Piece* newPiece);
    bool removePiece(Position at);
    bool movePiece(Position from, Position to);

    bool isPositionAttacked(Position pos, Color by);

    bool isPathFree(Position from, Position to);
    bool isPathAttacked(Position from, Position to, Color attackerColor);

    void endTurn();

    Color whoWins = Color::NONE;
    int blackCount = 0;
    int whiteCount = 0;

private:

    bool setPiece(Position at, Piece* toSet);
    //piece factory
    /*template<typename T> T* placeFigure(Piece* (&arr_board)[SIDE][SIDE], Position& pos)
    {
        void* allocAddress = &board[pos.r][pos.c];
        T* retAddress = new(allocAddress) T();
        return retAddress;
        /*
            void* allocAddress = &board[2][2];
            King* King_l= new(allocAddress) King();
            King_l->pieceColor = Color::WHITE;
        *
    }*/

    /*void doWithPiece(Piece& piece) {
        piece.name;
    }*/

    Piece* board[BOARD_SIDE][BOARD_SIDE];
    int dirWhite = 1;
    Color whoseTurn = Color::WHITE;
    bool check= false;
    Position whiteKingPos, blackKingPos;

    char messagesBuffer[MESS_BUFF_LEN]= { '\0' };
};

#endif
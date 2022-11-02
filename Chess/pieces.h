#ifndef PIECES_H_
#define PIECES_H_

#include "./common.h"

class Piece {
    friend class Board;
protected:
    virtual bool move(Position& from, Position& to, Board& board);
public:
    Color getPieceColor() {
        return pieceColor;
    }
    char getPieceChar() {
        return pieceChar;
    }
    bool isMoveLegal(char* _posFrom, char* _posTo, Piece* (&arr_board)[BOARD_SIDE][BOARD_SIDE]) {
        Position posTo;
        Piece* Destination = arr_board[posTo.r][posTo.c];
        if ((arr_board[posTo.r][posTo.c] == nullptr) || (pieceColor != Destination->getPieceColor())) {
            //return AreCellsLegal(_posFrom, _posTo, arr_board);
        }
        return false;
    }
protected:
    Piece(Color _Color = Color::NONE) :pieceColor(_Color), pieceChar('\0') {}
    Color pieceColor;
    char pieceChar;
    //virtual bool AreCellsLegal(char* _posFrom, char* _posTo, Piece* (&arr_board)[BOARD_SIDE][BOARD_SIDE]) {} = 0;
};

class King :public Piece {
    friend class Board;
public:
    King(Color color) : Piece(color), hasMoved(false), hasBeenChecked(false) {
        pieceChar = 'K';
    };

protected:
    virtual bool move(Position& from, Position& to, Board& board);
    bool castle(Position& from, Position& to, Board& board, Position& outRookFrom, Position& outRookTo);

    bool hasMoved;
    bool hasBeenChecked;
    static bool canMove(Position kingPos, Color kingColor, Board& board);
};

class Queen :public Piece {
public:
    int startPosition(Color pieceColor) {};
    Queen(Color color) :Piece(color) {
        pieceChar = 'Q';
    };
protected:
    virtual bool move(Position& from, Position& to, Board& board);
};

class Knight :public Piece {
public:
    int startPosition(Color pieceColor) {};
    Knight(Color color) :Piece(color) {
        pieceChar = 'N';
    };
protected:
    virtual bool move(Position& from, Position& to, Board& board);
};

class Rook :public Piece {
public:
    int startPosition(Color pieceColor) {};
    Rook(Color color) :Piece(color) {
        pieceChar = 'R';
    };
protected:
    virtual bool move(Position& from, Position& to, Board& board);
};

class Bishop :public Piece {
public:
    int startPosition(Color pieceColor) {};
    Bishop(Color color) :Piece(color) {
        pieceChar = 'B';
    };
protected:
    virtual bool move(Position& from, Position& to, Board& board);
};

class Pawn :public Piece {
public:
    int startPosition(Color pieceColor) {};
    Pawn(Color color) :Piece(color) {
        pieceChar = 'P';
    };
protected:
    virtual bool move(Position& from, Position& to, Board& board);
};

#endif
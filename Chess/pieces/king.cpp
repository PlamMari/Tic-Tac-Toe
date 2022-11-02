#include "../pieces.h"
#include "../board.h"
#include <stdio.h>

//normal ingame move
bool King::move(Position& from, Position& to, Board& board) {

	//fail, If not compliant with Piece move check
	if (!Piece::move(from, to, board)) {
		return false;
	}

	//if my color is white and the board white dir is up
	int rowDiff = to.r - from.r;
  int colDiff= to.c - from.c;
  int rowDiffSign= sign(rowDiff);
  int colDiffSign= sign(colDiff);

  //It is not valid for the King to move more than one square.
	if (rowDiff*rowDiffSign >1 || colDiff*colDiffSign >1) {
		return false;
	}

  return true;
}

//special castle move
bool King::castle(Position& from, Position& to, Board& board, Position& outRookFrom, Position& outRookTo) {

  //try and perform castle moves
  outRookFrom= Position();
  outRookTo= Position();
  if(hasMoved || hasBeenChecked) { return false; }

  Color opponentColor= (pieceColor == Color::WHITE) ? Color::BLACK: Color::WHITE;
  int myColorDir = (pieceColor == Color::WHITE) ? board.getWhitePiecesDir() : -board.getWhitePiecesDir();

  Position posKingFrom= (myColorDir == 1)? "e1": "e8";
  Position posKingTo_KingSideCastle= (myColorDir == 1)? "g1": "g8";
  Position posKingTo_QueenSideCastle= (myColorDir == 1)? "c1": "c8";

  Position posRookFrom_KingSideCastle= (myColorDir == 1)? "h1": "h8";
  Position posRookTo_KingSideCastle= (myColorDir == 1)? "f1": "f8";
  Position posRookFrom_QueenSideCastle= (myColorDir == 1)? "a1": "a8";
  Position posRookTo_QueenSideCastle= (myColorDir == 1)? "d1": "d8";

  //Try king side castle
  if(from == posKingFrom && to == posKingTo_KingSideCastle)
  {
    Piece* kingSideRook = board.getPiece(posRookFrom_KingSideCastle);
    //Fail if there is no rook at the position where there is supposed to be a rook
    if(kingSideRook == nullptr || kingSideRook->getPieceChar() != 'R') { return false; }
    if(
        board.isPathFree(posKingFrom, posRookFrom_KingSideCastle)
      && !board.isPathAttacked(posKingFrom, posRookFrom_KingSideCastle, opponentColor)
    )
    {
      outRookFrom= posRookFrom_KingSideCastle;
      outRookTo= posRookTo_KingSideCastle;
      return true;
    }
  }

  //Try queen side castle
  if(from == posKingFrom && to == posKingTo_QueenSideCastle)
  {
    Piece* queenSideRook = board.getPiece(posRookFrom_QueenSideCastle);
    //Fail if there is no rook at the position where there is supposed to be a rook
    if(queenSideRook == nullptr || queenSideRook->getPieceChar() != 'R') { return false; }
    if(
        board.isPathFree(posKingFrom, posRookFrom_QueenSideCastle)
      && !board.isPathAttacked(posKingFrom, posRookFrom_QueenSideCastle, opponentColor)
    )
    {
      outRookFrom= posRookFrom_QueenSideCastle;
      outRookTo= posRookTo_QueenSideCastle;
      return true;
    }
  }

  return false;
}

bool King::canMove(Position kingPos, Color kingColor, Board& board) {
    bool noMovePossible = true;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == j == 0) continue;
            Position current(kingPos.r + i, kingPos.c + j);
            if (!board.isPositionAttacked(current, kingColor==BLACK?WHITE:BLACK)) {
                noMovePossible = false;
                return false;
            }
        }
    }
    return true;
}
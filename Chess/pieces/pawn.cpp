#include "../pieces.h"
#include "../board.h"
#include <stdio.h>

bool Piece::move(Position& from, Position& to, Board& board) {
	//fail, if the from pos points to a piece which is different than this (the current) piece.	
	return board.getPiece(from) == this;
}

bool Pawn::move(Position& from, Position& to, Board& board) {
	
	//fail, If not compliant with Piece move check
	if (!Piece::move(from, to, board)) {
		return false;
	}
	//row checks

	//if my color is white and the board white dir is up
	int rowDiff = to.r - from.r;
	int myColorDir = (pieceColor == Color::WHITE) ? board.getWhitePiecesDir() : -board.getWhitePiecesDir();//holds my direction, depensing on my color
	int myStartingRow = myColorDir > 0 ? 1 : 7 - 1;//holds the starting row for my color and direction
	if (rowDiff == 0) {
		return false;
	}
	int rowDiffSign = sign(rowDiff);
	int rowDiffAbs = rowDiff * rowDiffSign;
	if (rowDiffSign != myColorDir)
	{
		return false;
	}
	//If I want to move two squares forward and I am not in the starting position, then fail
	if (rowDiffAbs == 2 && from.r != myStartingRow) {
		return false;
	}

	//column checks
	//At this point, we know that the row transition is correct. Now we check for the column
	
	Piece* pieceAtToPos = board.getPiece(to);
	int colDiff = to.c - from.c;
	//1) Move is valid, if we move forward and there is no piece at the to pos.
	if (colDiff == 0 && rowDiffAbs <=2 && pieceAtToPos == nullptr)
	{
		if (!board.isPathFree(from, to)) {
			return false;
		}
		return true;
	}
	//2) Move is valid, if we move on diag, and there is a piece of the oposite color
	if (rowDiffAbs == 1 && (colDiff == 1 || colDiff == -1))
	{
		if (pieceAtToPos != nullptr && pieceAtToPos->getPieceColor() != pieceColor) {
			return true;
		}
	}
	return false;
}
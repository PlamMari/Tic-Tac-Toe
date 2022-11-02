#include "../pieces.h"
#include "../board.h"
#include <stdio.h>

bool Knight::move(Position& from, Position& to, Board& board) {

	//fail, If not compliant with Piece move check
	if (!Piece::move(from, to, board)) {
		return false;
	}
	int rowDiff = to.r - from.r;
	int colDiff = to.c - from.c;
	if (rowDiff * sign(rowDiff) == 2 && colDiff * sign(colDiff) == 1) {
		return true;
	}
	if (rowDiff * sign(rowDiff) == 1 && colDiff * sign(colDiff) == 2) {
		return true;
	}
	return false;
}
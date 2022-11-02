#include "../pieces.h"
#include "../board.h"
#include <stdio.h>

bool Bishop::move(Position& from, Position& to, Board& board) {

	//fail, If not compliant with Piece move check
	if (!Piece::move(from, to, board)) {
		return false;
	}
	/*if (board.getCellColor(from) != board.getCellColor(to)) {		
		return false;
	}*/
	int rowDiff = to.r - from.r;
	int colDiff = to.c - from.c;
	if (rowDiff*sign(rowDiff) != colDiff*sign(colDiff)) {
		return false;
	}
	if (!board.isPathFree(from, to)) {
		return false;
	}
	return true;
}


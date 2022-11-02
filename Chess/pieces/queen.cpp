#include "../pieces.h"
#include "../board.h"
#include <stdio.h>

bool Queen::move(Position& from, Position& to, Board& board) {
	if (!Piece::move(from, to, board)) {
		return false;
	}
	if (!board.isPathFree(from, to)) {
		return false;
	}
	if (from.c == to.c || from.r == to.r) {
		return true;
	}
	/*if (board.getCellColor(from) != board.getCellColor(to)) {
		return false;
	}*/
	int rowDiff = to.r - from.r;
	int colDiff = to.c - from.c;
	if (rowDiff * sign(rowDiff) != colDiff * sign(colDiff)) {
		return false;
	}
	return true;
}
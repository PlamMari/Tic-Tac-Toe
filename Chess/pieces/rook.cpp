#include "../pieces.h"
#include "../board.h"
#include <stdio.h>

bool Rook::move(Position& from, Position& to, Board& board) {
	if (!Piece::move(from, to, board)) {
		return false;
	}
	if (!board.isPathFree(from, to)) {
		return false;
	}
	if (from.c == to.c || from.r == to.r) {
		return true;
	}
	return false;
}
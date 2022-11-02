#include "common.h"

Position::Position(int pr, int pc) : r(pr), c(pc) {
    if (!isValid())
    {
        r = -1;
        c = -1;
    }
}
Position::Position(const char* posStr) : r(-1), c(-1) {
    if (!strToPos(posStr, *this)) {
        r = -1;
        c = -1;
    }
}

bool Position::strToPos(const char* posStr, Position& outPos) {
    char l, d;
    // early exit, if input string is not long enough
    if (posStr[0] == '\0' || posStr[1] == '\0') {
        return false;
    }
    l = posStr[0]; // gets a char in the type 'A'/'a', ..., 'H'/'h'
    d = posStr[1]; // gets a char in the type '0', ..., '9'

    // if l in range (symbols for big letters)
    // d -> translate int code to 0-9 range

    int dAsInt = (int)d;
    // exit, if d is not in range (symbols for digits)
    if (!(dAsInt >= ASCII_DIGIT_LOW + 1 && dAsInt <= ASCII_DIGIT_HIGH - 1)) {
        return false;
    }
    // calculate row
    outPos.r = dAsInt - ASCII_DIGIT_LOW - 1;

    int lAsInt = (int)l;
    // exit, if l is not in range (symbols for letters)
    if (!(lAsInt >= ASCII_LETTER_UPPER && lAsInt <= ASCII_LETTER_UPPER + 7) &&
        !(lAsInt >= ASCII_LETTER_LOWER && lAsInt <= ASCII_LETTER_LOWER + 7)) {
        return false;
    }
    // translate a->A
    if (lAsInt >= ASCII_LETTER_LOWER && lAsInt <= ASCII_LETTER_LOWER + 7) {
        lAsInt = lAsInt - (ASCII_LETTER_LOWER - ASCII_LETTER_UPPER);
    }
    // translate A-> 0-9
    if (lAsInt >= ASCII_LETTER_UPPER && lAsInt <= ASCII_LETTER_UPPER + 7) {
        outPos.c = lAsInt - ASCII_LETTER_UPPER;
    }
    return true; // if successfully read
}
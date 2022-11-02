#ifndef COMMON_H_
#define COMMON_H_

//settings

//!!! Color printing is only possible under a windows compilation
#define ENABLE_PRETTY_BOARD_PRINTING
//!!! Screen clear is only possible under a windows compilation
#define ENABLE_SCREEN_CLEAR

#define MESS_BUFF_LEN 2048

// ASCII value for 0
#define ASCII_DIGIT_LOW 48
// ASCII value for 9
#define ASCII_DIGIT_HIGH 57
//ASCII value for A in upper case
#define ASCII_LETTER_UPPER 65
//ASCII value for a in lower case
#define ASCII_LETTER_LOWER 97

//Helper functions

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

inline char toLower(char a) {
    if((int)a >= ASCII_LETTER_UPPER && (int)a< ASCII_LETTER_LOWER){
        return (int)a + (ASCII_LETTER_LOWER-ASCII_LETTER_UPPER);
    }
    return a;
}

//Size of the chess board
#define BOARD_SIDE 8

// Enumerate color of the chess pieces
enum Color { NONE, BLACK, WHITE };

class Position {
public:
    static bool strToPos(const char* posStr, Position& outPos);

    Position(int pr = -1, int pc = -1);
    Position(const char* posStr);

    inline bool isValid() const{
        return (r >= 0 && r < 8 && c >= 0 && c < 8);
    }

    inline bool operator == (const Position& oth) {
        return oth.r == r && oth.c == c;
    }

    inline bool operator != (const Position& oth) {
        return !(* this == oth);
    }
    int r, c;
};

#endif
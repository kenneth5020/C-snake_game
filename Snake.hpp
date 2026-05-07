#ifndef __SNAKE__
#define __SNAKE__
#include <ncurses.h>
#include "Pointer.hpp"
#include <deque>

enum Direction
{
    up, down, left, right
};

class SnakePiece : public Pointer
{
public:
    SnakePiece();
    SnakePiece(int y, int x);
    void SnakeHead(int y, int x);
};

class Snake 
{
std::deque<SnakePiece> prevPieces;
Direction curDirection;
public:
    Snake();
    void addPiece(SnakePiece piece);
    void removePiece();
    void pieceClear();
    int getSnakeSize();
    std::deque<SnakePiece> getPiece(); // 뱀을 인덱스로 접근
    SnakePiece tail();
    SnakePiece head();
    Direction getDirection();
    void setDirection(int i);
    void setDirection(Direction d);
    SnakePiece nextHead();
};

#endif
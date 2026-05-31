/*
 * @file Snake.hpp
 * @brief 뱀의 몸통(SnakePiece)과 이를 조작하는 Snake 클래스를 정의합니다.
 * 덱(deque)을 사용하여 뱀의 머리와 꼬리를 관리합니다.
 */

#ifndef __SNAKE__
#define __SNAKE__
#include <ncurses.h>
#include "Pointer.hpp"
#include <deque>

enum Direction {
    up, down, left, right
};

class SnakePiece : public Pointer {
public:
    SnakePiece();
    SnakePiece(const int y, const int x);
};

class Snake {
private:
    std::deque<SnakePiece> prevPieces;
    Direction curDirection;
public:
    Snake();
    void addPiece(SnakePiece piece);
    void removePiece();
    void pieceClear();
    int getSnakeSize() const;
    std::deque<SnakePiece> getPiece() const;
    SnakePiece tail() const;
    SnakePiece head() const;
    Direction getDirection() const;
    void setDirection(const int i);
    void setDirection(const Direction d);
    SnakePiece nextHead() const;
};

#endif

/*
 * @brief 뱀의 다음 머리 좌표를 계산합니다.
 * 현재 방향(curDirection)에 따라 머리 좌표에서 1칸 앞의 좌표를 반환하며, 
 * 실제 뱀의 상태를 변경하지는 않습니다.
 */

#include "Snake.hpp"

SnakePiece::SnakePiece() : Pointer(0, 0, '#') {}
SnakePiece::SnakePiece(const int y, const int x) : Pointer(y, x, '#') {}
Snake::Snake() : curDirection(up) {}
void Snake::addPiece(SnakePiece piece) {
    piece.setIcon('#');
    prevPieces.push_back(piece);
}
void Snake::removePiece() {
    if (!prevPieces.empty()) {
        prevPieces.pop_front();
    }
}
void Snake::pieceClear() {
    prevPieces.clear();
}
std::deque<SnakePiece> Snake::getPiece() const {
    if (prevPieces.size() <= 1) return std::deque<SnakePiece>();
    return std::deque<SnakePiece>(prevPieces.begin(), prevPieces.end() - 1);
}
int Snake::getSnakeSize() const {
    if (prevPieces.empty()) return 0;
    return static_cast<int>(prevPieces.size() - 1);
}
SnakePiece Snake::tail() const {
    return prevPieces.front();
}
SnakePiece Snake::head() const {
    return prevPieces.back();
}
Direction Snake::getDirection() const {
    return curDirection;
}
void Snake::setDirection(const Direction d) {
    curDirection = d;
}
void Snake::setDirection(const int i) {
    curDirection = static_cast<Direction>(i);
}
SnakePiece Snake::nextHead() const {
    int row = head().getY();
    int col = head().getX();
    switch(curDirection) {
        case up:    row--; break;
        case down:  row++; break;
        case left:  col--; break;
        case right: col++; break;
    }
    return SnakePiece(row, col);
}

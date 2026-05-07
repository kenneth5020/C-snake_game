#ifndef __GAMETIME__
#define __GAMETIME__

#include <ctime>
#include <ncurses.h>
#include "Board.hpp"

class GameTime
{
WINDOW * time_win;
Board board;
int height, width;
int tWinY, tWinX;
public:
    GameTime(int height, int width);
    void displayTime(time_t start_time);
};

#endif
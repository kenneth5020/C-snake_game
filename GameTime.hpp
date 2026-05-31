#ifndef GAMETIME_HPP
#define GAMETIME_HPP

#include <ctime>
#include <ncurses.h>

class GameTime
{
private:
    static constexpr int TIME_WIN_HEIGHT = 5;
    static constexpr int TIME_WIN_WIDTH = 42;

    WINDOW* time_win;
    int height;
    int width;
    int tWinY;
    int tWinX;

public:
    GameTime(const int height, const int width);
    ~GameTime();

    GameTime(const GameTime& other) = delete;
    GameTime& operator=(const GameTime& other) = delete;

    void displayTime(const time_t startTime) const;
};

#endif

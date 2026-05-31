#include "GameTime.hpp"

GameTime::GameTime(const int height, const int width)
    : time_win(nullptr), height(height), width(width), tWinY(0), tWinX(0)
{
    int xMax;
    int yMax;

    getmaxyx(stdscr, yMax, xMax);

    time_win = newwin(TIME_WIN_HEIGHT, TIME_WIN_WIDTH,
                      (yMax / 2) - (height / 2) - TIME_WIN_HEIGHT,
                      (xMax / 2) - (width / 2));

    getmaxyx(time_win, tWinY, tWinX);
    box(time_win, 0, 0);
}

GameTime::~GameTime()
{
    if (time_win != nullptr)
    {
        delwin(time_win);
        time_win = nullptr;
    }
}

void GameTime::displayTime(const time_t startTime) const
{
    const time_t currentTime = time(nullptr);
    const int totalSeconds = static_cast<int>(difftime(currentTime, startTime));

    const int hours = totalSeconds / 3600;
    const int minutes = (totalSeconds % 3600) / 60;
    const int seconds = totalSeconds % 60;

    mvwprintw(time_win, tWinY / 2, (tWinX - 12) / 2 - 10,
              "Time of Game : %02d : %02d : %02d",
              hours, minutes, seconds);

    wrefresh(time_win);
}

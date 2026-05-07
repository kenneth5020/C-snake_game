#include "GameTime.hpp"


GameTime::GameTime(int height, int width)
{
        int xMax, yMax;
        getmaxyx(stdscr, yMax, xMax);
        this->height = height;
        this->width = width;

        time_win = newwin(5, 42, (yMax/2)-(height/2)-5, (xMax/2)-(width/2));
        getmaxyx(time_win, tWinY, tWinX);
        box(time_win, 0, 0);
}
void GameTime::displayTime(time_t startTime)
{
        time_t current_time = time(nullptr);
        int second = static_cast<int>(difftime(current_time, startTime));

        // Format the time string
        int hours = second / 3600;
        int minutes = (second % 3600) / 60;
        int seconds = second % 60;
        mvwprintw(time_win, tWinY / 2, (tWinX - 12) / 2 - 10, "Time of Game : %02d : %02d : %02d", hours, minutes, seconds);
        wrefresh(time_win);
}

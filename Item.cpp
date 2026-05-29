#include "Item.hpp"
#include <ctime>

void initItemColors() //아이템 색상 초기화
{
    if (has_colors())
    {
        start_color();

        init_pair(ITEM_COLOR_GROW, COLOR_GREEN, COLOR_BLACK);
        init_pair(ITEM_COLOR_POISON, COLOR_RED, COLOR_BLACK);
        init_pair(ITEM_COLOR_SPEED, COLOR_YELLOW, COLOR_BLACK);
    }
}

ItemGrow::ItemGrow(int y, int x)
    : Pointer(y, x, '+' | COLOR_PAIR(ITEM_COLOR_GROW)), saveTime(time(nullptr))
{
}

ItemPoison::ItemPoison(int y, int x)
    : Pointer(y, x, '-' | COLOR_PAIR(ITEM_COLOR_POISON)), saveTime(time(nullptr))
{
}

ItemSpeed::ItemSpeed(int y, int x)
    : Pointer(y, x, '*' | COLOR_PAIR(ITEM_COLOR_SPEED)), saveTime(time(nullptr))
{
}

Empty::Empty(int y, int x)
    : Pointer(y, x, ' ')
{
}

Gate::Gate(int y, int x)
    : Pointer(y, x, 'G')
{
}

SuddenWall::SuddenWall(int y, int x)
    : Pointer(y, x, 'W'), saveTime(time(nullptr))
{
}

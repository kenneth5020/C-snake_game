#include "Item.hpp"

ItemGrow::ItemGrow(int y, int x)
    {
        this->y = y;
        this->x = x;
        this->icon = '@';
        saveTime = time(nullptr);
    }

ItemPoison::ItemPoison(int y, int x)
{
    this->y = y;
    this->x = x;
    this->icon = 'P';
    saveTime = time(nullptr);
}
ItemSpeed::ItemSpeed(int y, int x)
{
    this->y = y;
    this->x = x;
    this->icon = '!';
    saveTime = time(nullptr);
}

Gate::Gate(int y, int x) // 게이트는 O로 표기
{
    this->y = y;
    this->x = x;
    this->icon = 'O';
}

Empty::Empty(int y, int x)
    {
        this->y = y;
        this->x = x;
        this->icon = ' ';
    }
SuddenWall::SuddenWall(int y, int x)
{
    this->y = y;
    this->x = x;
    this->icon = 'x';
    saveTime = time(nullptr);
}
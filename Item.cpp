#include "Item.hpp"



ItemGrow::ItemGrow(int y, int x)
    : Pointer(y, x, '+'), saveTime(time(nullptr))
{
}

ItemPoison::ItemPoison(int y, int x)
    : Pointer(y, x, '-'), saveTime(time(nullptr))
{
}

ItemSpeed::ItemSpeed(int y, int x)
    : Pointer(y, x, '!'), saveTime(time(nullptr))
{
}

Gate::Gate(int y, int x) // 게이트는 영문자 O로 표기
    : Pointer(y, x, 'O')
{
}

Empty::Empty(int y, int x)
    : Pointer(y, x, ' ')
{
}

SuddenWall::SuddenWall(int y, int x)
    : Pointer(y, x, 'x'), saveTime(time(nullptr))
{
}

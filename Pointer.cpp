#include "Pointer.hpp"

Pointer::Pointer(int y, int x, chtype ch)
    : x(x), y(y), icon(ch)
{
}

int Pointer::getX() const
{
    return x;
}

int Pointer::getY() const
{
    return y;
}

chtype Pointer::getIcon() const
{
    return icon;
}

void Pointer::setX(int x)
{
    this->x = x;
}

void Pointer::setY(int y)
{
    this->y = y;
}

void Pointer::setIcon(chtype ch)
{
    icon = ch;
}

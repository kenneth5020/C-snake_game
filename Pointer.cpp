#include <ncurses.h>
#include "Pointer.hpp"

Pointer::Pointer()
    {
        y = 0;
        x = 0;
        icon = ' ';
    }
Pointer::Pointer(int y, int x, chtype ch)
    {
        this->y = y;
        this->x = x;
        this->icon = ch;
    }
int Pointer::getX()
    {
        return x;
    }
int Pointer::getY()
    {
        return y;
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
chtype Pointer::getIcon()
    {
        return icon;
    }

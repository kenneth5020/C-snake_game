#include <ncurses.h>
#ifndef __POINTER__
#define __POINTER__
class Pointer
{
public:
    Pointer();
    Pointer(int y, int x, chtype ch);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    chtype getIcon();
    void setIcon(chtype ch);
protected:
    int y, x;
    chtype icon;
};

#endif
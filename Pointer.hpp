#ifndef __POINTER__
#define __POINTER__

#include <ncurses.h>

class Pointer
{
public:
    Pointer(int y = 0, int x = 0, chtype ch = ' ');

    int getX() const;
    int getY() const;
    chtype getIcon() const;

    void setX(int x);
    void setY(int y);
    void setIcon(chtype ch);

protected:
    int x,y;
    chtype icon;
};

#endif

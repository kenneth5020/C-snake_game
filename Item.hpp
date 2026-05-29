#ifndef __ITEM__
#define __ITEM__

#include <ncurses.h>
#include <ctime>
#include "Pointer.hpp"

const short ITEM_COLOR_GROW = 1;//초록색
const short ITEM_COLOR_POISON = 2;//빨간색
const short ITEM_COLOR_SPEED = 3;//노란색

void initItemColors();//아이템 색상 초기화
// 맵에 생성/소멸되는 특수한 객체 관리
// 증가 아이템
class ItemGrow : public Pointer
{
public:
    ItemGrow(int y, int x);
    time_t saveTime; 
};

// 감소 아이템
class ItemPoison : public Pointer
{
public:
    ItemPoison(int y, int x);
    time_t saveTime;
};

// 속도 아이템
class ItemSpeed : public Pointer
{
public:
    ItemSpeed(int y, int x);
    time_t saveTime;
};

// 빈 공간 관리
class Empty : public Pointer
{
public:
    Empty(int y, int x);
};

// 게이트 관리
class Gate : public Pointer
{
public:
    Gate(int y, int x);
};
//일정시간 동안 생성되는 벽 관리
class SuddenWall : public Pointer
{
public:
    SuddenWall(int y, int x);
    time_t saveTime;
};

#endif

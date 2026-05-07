#include <ncurses.h>
#include "Pointer.hpp"
#include <ctime>
#ifndef __ITEM__
#define __ITEM__


// 맵에 생성 소멸 되는 특수한 객체 관리 
// 증가 아이템
class ItemGrow : public Pointer
{
    
public:
    ItemGrow(int y, int x);
    time_t saveTime; // 시간을 저장할 변수
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
class SuddenWall : public Pointer
{
public:
    SuddenWall(int y, int x);
    time_t saveTime;
};
#endif
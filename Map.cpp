#include <ncurses.h>
#include "Map.hpp"

// using namespace std;

Map::Map()
{
}
int (*Map::getMap(int st))[42] {
    return map[st];
}

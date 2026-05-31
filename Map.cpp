#include "Map.hpp"

Map::Map()
    : curStage(0)
{
}

const int (*Map::getMap(const int st) const)[MAP_WIDTH]
{
    if (st < 0 || st >= STAGE_COUNT)
    {
        return map[0];
    }

    return map[st];
}

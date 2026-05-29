#ifndef __SNAKEGAME__
#define __SNAKEGAME__

#include <ncurses.h>
#include <ctime>
#include <stdlib.h>
#include <utility>
#include <string>

#include "Board.hpp"
#include "Pointer.hpp"
#include "Item.hpp"
#include "Map.hpp"
#include "Snake.hpp"


class SnakeGame
{
private:

    Board board;
    ItemGrow *itemGrow;
    ItemSpeed *itemSpeed;
    ItemPoison *itemPoison;
    Gate *gateA;
    Gate *gateB;
    SuddenWall *suddenWall;
    Snake snake;
    bool gameOver;
    int growNumber = 0;     // missionBoard part
    int poisonNumber = 0;
    int gateNumber = 0;
    int maxSnake = 0;
    int stage = 0;
    int score = 0;
    int randomNumA = rand() % 4 + 2;
    int randomNumB = rand() % 2 + 1;
    int randomNumC = rand() % 2 + 1;
    int randomNumD = rand() % 2 + 1;
    std::pair<int, int> p;
    bool gateInUse = false;
    bool isOppositeDirection(Direction nextDirection);
    bool setGateExit(SnakePiece& next, Gate* exitGate);
    void createGates();
    void removeGates();
public:
    SnakeGame(int height, int width);
    ~SnakeGame();
    void initialize();
    void stageClear();
    bool missionClear();
    void missionCheck();
    void input();
    void updateState();
    void redraw();
    int getStage();
    bool isOver();
    void moveGateAtoB(SnakePiece& next);
    void moveGateBtoA(SnakePiece& next);
    WINDOW* getBoardWin();
    void gameRefresh();
    void updateGameTime(time_t startTime);
};

#endif

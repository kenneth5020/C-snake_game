#ifndef __BOARD__
#define __BOARD__

#include <ncurses.h>
#include <cstdlib>
#include "Pointer.hpp"
#include "Map.hpp"

class Board
{
public:
    Board();
    Board(const int height, const int width);
    ~Board();

    Board(const Board& other) = delete;
    Board& operator=(const Board& other) = delete;

    void initialize();
    void drawMap();
    void add(const Pointer& pointer);
    void clear();
    void refresh();
    int getInput();

    void addMap(const int y, const int x, const char ch);

    void updateScoreGrow(const int score);
    void updateMissionGrow(const int score);
    void updateScorePoison(const int poison);
    void updateScoreCurSnake(const int snake);
    void updateMissionCurSnake(const int snake);
    void updateScoreMaxSnake(const int snake);
    void updateScoreGate(const int gate);
    void updateScoreTime(const int seconds);
    void updateMissionPoison(const int poison);
    void updateMissionGate(const int gate);

    void getEmptyCoordinates(int& y, int& x) const;
    void getWallCoordinates(int& y, int& x) const;

    void setStage(const int stageNumber);
    int getStage() const;

    void drawState();
    void updateMissionCurSnakeCheck();
    void updateMissionGrowCheck();
    void updateMissionPoisonCheck();
    void updateMissionGateCheck();

    WINDOW* getBoardWin() const;
    WINDOW* getScoreWin() const;
    WINDOW* getMissionWin() const;

private:
    static constexpr int BOARD_HEIGHT = 22;
    static constexpr int BOARD_WIDTH = 42;
    static constexpr int SCORE_HEIGHT = 13;
    static constexpr int SCORE_WIDTH = 39;
    static constexpr int MISSION_HEIGHT = 11;
    static constexpr int MISSION_WIDTH = 39;

    WINDOW* board_win;
    WINDOW* score_win;
    WINDOW* mission_win;

    Map mapData;
    int stage;
    int height;
    int width;
};

#endif

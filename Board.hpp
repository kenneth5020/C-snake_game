#ifndef __BOARD__
#define __BOARD__
#include <ncurses.h>
#include "Pointer.hpp"
#include "Map.hpp"
#include <vector>
#include <cstdlib>
#include <string>

class Board
{
public:
    Board(); // 디폴트
    Board(int height, int width); // 생성자
    void initialize();
    void drawMap();
    void add(Pointer pointer);
    void clear();
    void refresh();
    int getInput();
    void addMap(int y, int x, char ch);
    void updateScoreGrow(int score);
    void updateMissionGrow(int score);
    void updateScorePoison(int poison);
    void updateScoreCurSnake(int snake);
    void updateMissionCurSnake(int snake);
    void updateScoreMaxSnake(int snake);
    void updateScoreGate(int gate);
    void updateScoreTime(int seconds);
    void updateMissionPoison(int poison);
    void updateMissionGate(int gate);
    void getEmptyCoordinates(int& y, int& x);
    void getWallCoordinates(int& y, int& x);
    void setStage(int a);
    int getStage();
    void drawState();
    void updateMissionCurSnakeCheck();
    void updateMissionGrowCheck();
    void updateMissionPoisonCheck();
    void updateMissionGateCheck();
    WINDOW* getBoardWin();
    WINDOW* getScoreWin();
    WINDOW* getMissionWin();
private:
    WINDOW* board_win;
    WINDOW* score_win;
    WINDOW* mission_win;
        
    Map mapData;
    int (*map)[42];
    int stage = 0; // 스테이지 불러오는 변수
    int height, width;
};

#endif

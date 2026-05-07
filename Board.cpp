#include "Board.hpp"

Board::Board() {}
Board::Board(int height, int width)
    {
        int xMax, yMax;
        this->height = 22;
        this->width = 42;
        getmaxyx(stdscr, yMax, xMax); // 좌표 중앙
        // 맵 배열을 22 42로 구현
        board_win = newwin(22, 42, (yMax/2)-(height/2), (xMax/2)-(width/2));
        score_win = newwin(13, 39, (yMax/2)-(height/2), (xMax/2)-(width/2)+42);
        mission_win = newwin(11, 39, (yMax/2)-(height/2) + 13, (xMax/2)-(width/2)+42);
        
        drawState();
        keypad(board_win, true); // 키입력 사용
        wtimeout(board_win, 200); // 딜레이
        refresh();
    }
void Board::initialize()
    {
        clear();
        refresh();
    }
void Board::drawMap() // 맵 구현부
{
    int (*map)[42] = mapData.getMap(stage);
    for(int i = 0; i < 22; i++) 
    {
        for(int j = 0; j < 42; j++) {
            int a = map[i][j];
            char ch;
            switch(a) {
                case 0:
                    ch = ' '; 
                    break;
                case 1:
                    ch = 'X';
                    break;
                case 2:
                    ch = '$'; // 통과 불가 벽
                    break;
            }

            addMap(i, j, ch); // 보드에 문자 추가
        }
    }
}
void Board::drawState()
{
    box(score_win, 0, 0);
    box(mission_win, 0, 0);
    int q, w;
    getmaxyx(score_win, q, w);
    mvwprintw(score_win, 1, 1, "-------------Score Board-------------");
    mvwprintw(score_win, 3, (w - 8) / 2 - 10, "B : ");
    mvwprintw(score_win, 5, (w - 8) / 2 - 10, "+ : ");
    mvwprintw(score_win, 7, (w - 8) / 2 - 10, "- : ");
    mvwprintw(score_win, 9, (w - 8) / 2 - 10, "G : ");
    mvwprintw(score_win, 11, (w - 8) / 2 - 10, "T : ");
    mvwprintw(score_win, 3, 19, "/");
    
    getmaxyx(mission_win, q, w);
    mvwprintw(mission_win, q / 2 - 4, 1, "------------Mission Board------------");
    mvwprintw(mission_win, q / 2 - 2, (w - 10) / 2 - 10, "B : ");
    mvwprintw(mission_win, q / 2, (w - 10) / 2 - 10, "+ : ");
    mvwprintw(mission_win, q / 2 + 2, (w - 10) / 2 - 10, "- : ");
    mvwprintw(mission_win, q / 2 + 4, (w - 10) / 2 - 10, "G : ");
}
void Board::add(Pointer pointer)
{
    mvwaddch(board_win, pointer.getY(), pointer.getX(), pointer.getIcon());
}
 void Board::clear()
    {
        wclear(board_win);
        wclear(score_win);
        wclear(mission_win);
        drawMap();
        drawState();
    }
void Board::refresh()
    {
        wrefresh(board_win);
        wrefresh(score_win);
        wrefresh(mission_win);
    }
int Board::getInput()
    {
        return wgetch(board_win);
    }
void Board::getEmptyCoordinates(int& y, int& x) // 빈곳을 찾음
{
    do{
    y = rand() % height;
    x = rand() % width;
} while (mvwinch(board_win, y, x) != ' ');    
}
void Board::getWallCoordinates(int& y, int& x) // 벽을 찾음 벽은 X로 구현
{
    do{
    y = rand() % height;
    x = rand() % width;
} while (mvwinch(board_win, y, x) != 'X');    
}
void Board::addMap(int y, int x, char ch)
{
    mvwaddch(board_win, y, x, ch);
}
void Board::updateScoreCurSnake(int snake)
{
    mvwprintw(score_win, 3, 17, "%d", snake); // y 좌표 일치
    wrefresh(score_win);
}
void Board::updateScoreMaxSnake(int snake)
{
    mvwprintw(score_win, 3, 21, "%d", snake); // y 좌표 일치
    wrefresh(score_win);
}
void Board::updateScoreGrow(int score)
{
    mvwprintw(score_win, 5, 17, "%d", score); // y 좌표 일치
    wrefresh(score_win);
}
void Board::updateScorePoison(int poison)
{
    mvwprintw(score_win, 7, 17, "%d", poison); // y 좌표 일치
    wrefresh(score_win);
}
void Board::updateScoreGate(int gate)
{
    mvwprintw(score_win, 9, 17, "%d", gate); // y 좌표 일치
    wrefresh(score_win);
}
void Board::updateScoreTime(int seconds)
{
    mvwprintw(score_win, 11, 17, "%d sec", seconds);
    wrefresh(score_win);
}
void Board::updateMissionCurSnake(int snake)
{
    mvwprintw(mission_win, 3, 17, "%d", snake); // y 좌표 일치
    wrefresh(mission_win);
}
void Board::updateMissionGrow(int score)
{
    mvwprintw(mission_win, 5, 17, "%d", score); // y 좌표 일치
    wrefresh(mission_win);
}
void Board::updateMissionPoison(int poison)
{
    mvwprintw(mission_win, 7, 17, "%d", poison); // y 좌표 일치
    wrefresh(mission_win);
}
void Board::updateMissionGate(int gate)
{
    mvwprintw(mission_win, 9, 17, "%d", gate); // y 좌표 일치
    wrefresh(mission_win);
}

void Board::updateMissionCurSnakeCheck()
{
    mvwprintw(mission_win, 3, 21, "V"); // y 좌표 일치
    wrefresh(mission_win);
}
void Board::updateMissionGrowCheck()
{
    mvwprintw(mission_win, 5, 21, "V"); // y 좌표 일치
    wrefresh(mission_win);
}
void Board::updateMissionPoisonCheck()
{
    mvwprintw(mission_win, 7, 21, "V"); // y 좌표 일치
    wrefresh(mission_win);
}
void Board::updateMissionGateCheck()
{
    mvwprintw(mission_win, 9, 21, "V"); // y 좌표 일치
    wrefresh(mission_win);
}

void Board::setStage(int a)
{
    stage = a;
}
int Board::getStage()
{
    return stage;
}
WINDOW* Board::getBoardWin() {
    return board_win;
}
WINDOW* Board::getScoreWin() {
    return score_win;
}
WINDOW* Board::getMissionWin() {
    return mission_win;
}

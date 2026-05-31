#include "Board.hpp"

Board::Board()
    : board_win(nullptr), score_win(nullptr), mission_win(nullptr), stage(0), height(BOARD_HEIGHT), width(BOARD_WIDTH)
{
}

Board::Board(const int height, const int width)
    : board_win(nullptr), score_win(nullptr), mission_win(nullptr), stage(0), height(BOARD_HEIGHT), width(BOARD_WIDTH)
{
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);

    board_win = newwin(BOARD_HEIGHT, BOARD_WIDTH, (yMax / 2) - (height / 2), (xMax / 2) - (width / 2));
    score_win = newwin(SCORE_HEIGHT, SCORE_WIDTH, (yMax / 2) - (height / 2), (xMax / 2) - (width / 2) + BOARD_WIDTH);
    mission_win = newwin(MISSION_HEIGHT, MISSION_WIDTH, (yMax / 2) - (height / 2) + SCORE_HEIGHT, (xMax / 2) - (width / 2) + BOARD_WIDTH);

    drawState();
    keypad(board_win, true);
    wtimeout(board_win, 200);
    refresh();
}

Board::~Board()
{
    if (board_win != nullptr)
    {
        delwin(board_win);
        board_win = nullptr;
    }
    if (score_win != nullptr)
    {
        delwin(score_win);
        score_win = nullptr;
    }
    if (mission_win != nullptr)
    {
        delwin(mission_win);
        mission_win = nullptr;
    }
}

void Board::initialize()
{
    clear();
    refresh();
}

void Board::drawMap()
{
    const int (*currentMap)[BOARD_WIDTH] = mapData.getMap(stage);

    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            const int mapValue = currentMap[i][j];
            char ch = ' ';

            switch (mapValue)
            {
                case 0:
                    ch = ' ';
                    break;
                case 1:
                    ch = 'X';
                    break;
                case 2:
                    ch = '$';
                    break;
                default:
                    ch = ' ';
                    break;
            }

            addMap(i, j, ch);
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

void Board::add(const Pointer& pointer)
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

void Board::getEmptyCoordinates(int& y, int& x) const
{
    do
    {
        y = rand() % height;
        x = rand() % width;
    } while (mvwinch(board_win, y, x) != ' ');
}

void Board::getWallCoordinates(int& y, int& x) const
{
    do
    {
        y = rand() % height;
        x = rand() % width;
    } while (mvwinch(board_win, y, x) != 'X');
}

void Board::addMap(const int y, const int x, const char ch)
{
    mvwaddch(board_win, y, x, ch);
}

void Board::updateScoreCurSnake(const int snake)
{
    mvwprintw(score_win, 3, 17, "%d", snake);
    wrefresh(score_win);
}

void Board::updateScoreMaxSnake(const int snake)
{
    mvwprintw(score_win, 3, 21, "%d", snake);
    wrefresh(score_win);
}

void Board::updateScoreGrow(const int score)
{
    mvwprintw(score_win, 5, 17, "%d", score);
    wrefresh(score_win);
}

void Board::updateScorePoison(const int poison)
{
    mvwprintw(score_win, 7, 17, "%d", poison);
    wrefresh(score_win);
}

void Board::updateScoreGate(const int gate)
{
    mvwprintw(score_win, 9, 17, "%d", gate);
    wrefresh(score_win);
}

void Board::updateScoreTime(const int seconds)
{
    mvwprintw(score_win, 11, 17, "%d sec", seconds);
    wrefresh(score_win);
}

void Board::updateMissionCurSnake(const int snake)
{
    mvwprintw(mission_win, 3, 17, "%d", snake);
    wrefresh(mission_win);
}

void Board::updateMissionGrow(const int score)
{
    mvwprintw(mission_win, 5, 17, "%d", score);
    wrefresh(mission_win);
}

void Board::updateMissionPoison(const int poison)
{
    mvwprintw(mission_win, 7, 17, "%d", poison);
    wrefresh(mission_win);
}

void Board::updateMissionGate(const int gate)
{
    mvwprintw(mission_win, 9, 17, "%d", gate);
    wrefresh(mission_win);
}

void Board::updateMissionCurSnakeCheck()
{
    mvwprintw(mission_win, 3, 21, "V");
    wrefresh(mission_win);
}

void Board::updateMissionGrowCheck()
{
    mvwprintw(mission_win, 5, 21, "V");
    wrefresh(mission_win);
}

void Board::updateMissionPoisonCheck()
{
    mvwprintw(mission_win, 7, 21, "V");
    wrefresh(mission_win);
}

void Board::updateMissionGateCheck()
{
    mvwprintw(mission_win, 9, 21, "V");
    wrefresh(mission_win);
}

void Board::setStage(const int stageNumber)
{
    stage = stageNumber;
}

int Board::getStage() const
{
    return stage;
}

WINDOW* Board::getBoardWin() const
{
    return board_win;
}

WINDOW* Board::getScoreWin() const
{
    return score_win;
}

WINDOW* Board::getMissionWin() const
{
    return mission_win;
}

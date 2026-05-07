#include <iostream>
#include <ncurses.h>
#include "Board.hpp"
#include "SnakeGame.hpp"
#include "Pointer.hpp"
#include "GameTime.hpp"

#define BOARD_ROWS 17
#define BOARD_COLS 17 * 2.5


using namespace std;

int main(){
    initscr();
    refresh();

    noecho();
    curs_set(0); // 커서 미표시
    // 2중 while로 clear 함수가 호출되면 내부 while문 종료 후 새 객체 생성?
    SnakeGame game(BOARD_ROWS, BOARD_COLS);
    GameTime gametime(BOARD_ROWS, BOARD_COLS);
    time_t startTime = time(nullptr);

    while(!(game.isOver()) && game.getStage() < 4)
    {
        game.input(); // 값 입력

        game.updateState(); // 게임 진행부
        game.redraw(); // 갱신
        game.updateGameTime(startTime);
        gametime.displayTime(startTime);
    }
    int height, width;
    getmaxyx(game.getBoardWin(), height, width);
    if (game.getStage() == 4) mvwprintw(game.getBoardWin(), height / 2 - 1, (width - 8) / 2, "Game Clear!");
    game.gameRefresh();
    getch(); // key 가 입력되기 전까지 대기할 수 있도록 해줌
    endwin();
    
    return 0;
}

// 시간 뜨게

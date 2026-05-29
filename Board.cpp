void drawBoard() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (mapData[y][x] == 0) {
                mvprintw(y, x, " ");
            }
            else if (mapData[y][x] == 1) {
                mvprintw(y, x, "#");
            }
            else if (mapData[y][x] == 2) {
                mvprintw(y, x, "X");
            }
            else if (mapData[y][x] == 3) {
                mvprintw(y, x, "@");
            }
            else if (mapData[y][x] == 4) {
                mvprintw(y, x, "o");
            }
            else if (mapData[y][x] == 5) {
                mvprintw(y, x, "+");
            }
            else if (mapData[y][x] == 6) {
                mvprintw(y, x, "-");
            }
            else if (mapData[y][x] == 7) {
                mvprintw(y, x, "G");
            }
        }
    }
}

void drawScoreBoard() {
    mvprintw(1, WIDTH + 4, "Stage %d", stage);

    mvprintw(3, WIDTH + 4, "Score Board");
    mvprintw(4, WIDTH + 4, "B: %d / %d", (int)snake.size(), maxLength);
    mvprintw(5, WIDTH + 4, "+: %d", growthCount);
    mvprintw(6, WIDTH + 4, "-: %d", poisonCount);
    mvprintw(7, WIDTH + 4, "G: %d", gateCount);
    mvprintw(8, WIDTH + 4, "Time: %d", gameTime);
}

void drawMissionBoard() {
    int idx = stage - 1;

    mvprintw(11, WIDTH + 4, "Mission");
    mvprintw(12, WIDTH + 4, "B: %d [%c]",
             missionB[idx],
             maxLength >= missionB[idx] ? 'v' : ' ');

    mvprintw(13, WIDTH + 4, "+: %d [%c]",
             missionGrowth[idx],
             growthCount >= missionGrowth[idx] ? 'v' : ' ');

    mvprintw(14, WIDTH + 4, "-: %d [%c]",
             missionPoison[idx],
             poisonCount >= missionPoison[idx] ? 'v' : ' ');

    mvprintw(15, WIDTH + 4, "G: %d [%c]",
             missionGate[idx],
             gateCount >= missionGate[idx] ? 'v' : ' ');
}

void drawMap() {
    clear();

    drawBoard();
    drawScoreBoard();
    drawMissionBoard();

    mvprintw(23, 0, "Arrow keys: move | q: quit");
    refresh();
}
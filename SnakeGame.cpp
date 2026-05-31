#include "SnakeGame.hpp"

SnakeGame::SnakeGame(int height, int width) : board(height, width), itemGrow(nullptr), gameOver(false)
{
    initialize(); // 보드 객체를 만들어준다.
}

SnakeGame::~SnakeGame()
{
    delete itemSpeed;
    delete itemGrow;
    delete itemPoison;
    delete gateA;
    delete gateB;
    delete suddenWall;
}

void SnakeGame::initialize()
{
    srand(time(NULL));
    gateA = nullptr;
    gateB = nullptr;
    itemPoison = nullptr;
    itemGrow = nullptr;
    itemSpeed = nullptr;
    suddenWall = nullptr;
    gateInUse = false;
    gameOver = false;
    p = std::make_pair(-1, -1);
    
    board.initialize();
    board.updateScoreGrow(0);
    board.updateScorePoison(0);
    board.updateScoreGate(0);
    
    board.updateMissionCurSnake(randomNumA);
    board.updateMissionGrow(randomNumB);
    board.updateMissionPoison(randomNumC);
    board.updateMissionGate(randomNumD);

    board.drawMap();
    board.drawState();
    snake.setDirection(up);

    SnakePiece next(10, 40); // 나중에 시작할 좌표를 줘야함
    board.add(next);
    snake.addPiece(next);

    next = snake.nextHead();
    board.add(next);
    snake.addPiece(next);

    //snake.setDirection(right);

    next = snake.nextHead();
    next.setIcon('*');
    board.add(next);
    snake.addPiece(next);
    board.updateScoreCurSnake(snake.getSnakeSize());
    maxSnake = snake.getSnakeSize();
    board.updateScoreMaxSnake(snake.getSnakeSize());
}
// 꾹 누르게 되면 값은 변화하지 않는게 맞는데 단 input의 빠르게 많이 반복하여
// update를 빠르고 많이 불러오게 되는 문제로 인해 뱀이 계속해서 움직임
void SnakeGame::input()
{
    int input = board.getInput();
    
    if (input != ERR)
    {   
    switch (input)
    { 
    case KEY_UP: // 반대방향 눌리지 않아야함, 같은 방향을 누를 수 없어야함
        if (snake.getDirection() == down) gameOver = true;
        else if (snake.getDirection() != up) snake.setDirection(up);
        break;
    case KEY_DOWN:
        if (snake.getDirection() == up) gameOver = true;
        else if (snake.getDirection() != down) snake.setDirection(down);
        break;
    case KEY_LEFT:
        if (snake.getDirection() == right) gameOver = true;
        else if (snake.getDirection() != left) snake.setDirection(left);
        break;
    case KEY_RIGHT:
        if (snake.getDirection() == left) gameOver = true;
        else if (snake.getDirection() != right) snake.setDirection(right);
        break;
    }
    }
}

bool SnakeGame::isOppositeDirection(Direction nextDirection)
{
    Direction current = snake.getDirection();
    return (current == up && nextDirection == down) ||
           (current == down && nextDirection == up) ||
           (current == left && nextDirection == right) ||
           (current == right && nextDirection == left);
}

bool SnakeGame::setGateExit(SnakePiece& next, Gate* exitGate)
{
    int height, width;
    getmaxyx(board.getBoardWin(), height, width);

    int gateY = exitGate->getY();
    int gateX = exitGate->getX();
    int dirs[4];
    int dirCount = 4;

    if (gateY == 0)
    {
        dirs[0] = down;
        dirCount = 1;
    }
    else if (gateY == height - 1)
    {
        dirs[0] = up;
        dirCount = 1;
    }
    else if (gateX == 0)
    {
        dirs[0] = right;
        dirCount = 1;
    }
    else if (gateX == width - 1)
    {
        dirs[0] = left;
        dirCount = 1;
    }
    else
    {
        Direction current = snake.getDirection();
        dirs[0] = current;

        if (current == up)
        {
            dirs[1] = right;
            dirs[2] = left;
            dirs[3] = down;
        }
        else if (current == down)
        {
            dirs[1] = left;
            dirs[2] = right;
            dirs[3] = up;
        }
        else if (current == left)
        {
            dirs[1] = up;
            dirs[2] = down;
            dirs[3] = right;
        }
        else
        {
            dirs[1] = down;
            dirs[2] = up;
            dirs[3] = left;
        }
    }

    for (int i = 0; i < dirCount; i++)
    {
        int dy = 0;
        int dx = 0;

        if (dirs[i] == up) dy = -1;
        else if (dirs[i] == down) dy = 1;
        else if (dirs[i] == left) dx = -1;
        else if (dirs[i] == right) dx = 1;

        int nextY = gateY + dy;
        int nextX = gateX + dx;
        if (nextY < 0 || nextY >= height || nextX < 0 || nextX >= width) continue;

        chtype nextCell = mvwinch(board.getBoardWin(), nextY, nextX) & A_CHARTEXT;
        if (nextCell == ' ' || nextCell == '@' || nextCell == 'P' || nextCell == '!')
        {
            next.setY(nextY);
            next.setX(nextX);
            snake.setDirection(dirs[i]);
            p.first = nextY;
            p.second = nextX;
            return true;
        }
    }

    gameOver = true;
    return false;
}

void SnakeGame::createGates()
{
    int yA, xA, yB, xB;

    board.getWallCoordinates(yA, xA);
    do
    {
        board.getWallCoordinates(yB, xB);
    } while (yA == yB && xA == xB);

    gateA = new Gate(yA, xA);
    gateB = new Gate(yB, xB);
    board.add(*gateA);
    board.add(*gateB);
}

void SnakeGame::removeGates()
{
    if (gateA != nullptr)
    {
        gateA->setIcon('X');
        board.add(*gateA);
        delete gateA;
        gateA = nullptr;
    }

    if (gateB != nullptr)
    {
        gateB->setIcon('X');
        board.add(*gateB);
        delete gateB;
        gateB = nullptr;
    }

    gateInUse = false;
    p = std::make_pair(-1, -1);
}

void SnakeGame::updateState()
{
    if (gameOver) return;

    time_t curTime = time(nullptr); // 현재 시간
    // 성장 아이템 생성
    if (itemGrow == nullptr)
    {
        int y, x;
        board.getEmptyCoordinates(y, x);
        itemGrow = new ItemGrow(y, x);
        board.add(*itemGrow);
    }
    // 독 아이템 생성
    if (itemPoison == nullptr)
    {
        int y, x;
        board.getEmptyCoordinates(y, x);
        itemPoison = new ItemPoison(y, x);
        board.add(*itemPoison);
    }
    // 속도 아이템 생성
    if (itemSpeed == nullptr)
    {
        int y, x;
        board.getEmptyCoordinates(y, x);
        itemSpeed = new ItemSpeed(y, x);
        board.add(*itemSpeed);
    }
    // 벽 생성
    if (suddenWall == nullptr)
    {
        int y, x;
        board.getEmptyCoordinates(y, x);
        suddenWall = new SuddenWall(y, x);
        board.add(*suddenWall);
    }
    // 게이트 생성
    if (gateA == nullptr && gateB == nullptr && !gateInUse)
    {
        createGates();
    }
    SnakePiece next = snake.nextHead();

    // Gate에 들어가면 먼저 출구 좌표와 방향을 확정한다.
    if ((mvwinch(board.getBoardWin(), next.getY(), next.getX()) & A_CHARTEXT) == 'O') 
    {
        if (next.getX() == gateA->getX() && next.getY() == gateA->getY())
        {
            gateInUse = setGateExit(next, gateB);
        }
        else if (next.getX() == gateB->getX() && next.getY() == gateB->getY())
        {
            gateInUse = setGateExit(next, gateA);
        }
    }

    bool ateGrow = (next.getX() == itemGrow->getX() && next.getY() == itemGrow->getY());
    bool atePoison = (next.getX() == itemPoison->getX() && next.getY() == itemPoison->getY());
    bool ateSpeed = (next.getX() == itemSpeed->getX() && next.getY() == itemSpeed->getY());

    // Growth가 아닌 이동은 기본적으로 꼬리를 한 칸 지운다.
    if (!ateGrow)
    {
        int emptyRow = snake.tail().getY();
        int emptyCol = snake.tail().getX();
        next.setIcon('*');
        board.add(Empty(emptyRow, emptyCol));
        snake.removePiece();
    }
    else
    {
        next.setIcon('*');
        growNumber += 1;
        board.updateScoreGrow(growNumber);
        delete itemGrow;
        itemGrow = nullptr;
    }
    // 독을 먹은 경우
    if (atePoison)
    {
        poisonNumber += 1;
        board.updateScorePoison(poisonNumber);
        int emptyRow = snake.tail().getY();
        int emptyCol = snake.tail().getX();
        board.add(Empty(emptyRow, emptyCol));
        snake.removePiece();
        board.updateScoreCurSnake(snake.getSnakeSize());
        delete itemPoison;
        itemPoison = nullptr;
    }
    // 속도를 먹은 경우
    if (ateSpeed)
    {
        int randomSpeed = rand() % 500 + 200;
        wtimeout(getBoardWin(), randomSpeed); // 속도 변화를 1~ 500로
        
        delete itemSpeed;
        itemSpeed = nullptr;
    }
    // 다 통과하고 나서 되야함 >> snake 꼬리의 좌표가 게이트 출구와 일치한 경우로 판단
    if (gateInUse && snake.tail().getY() == p.first && snake.tail().getX() == p.second)
        {
            gateNumber += 1;
            board.updateScoreGate(gateNumber);
            //board.updateMissionGate(gateNumber);
            removeGates();
        }    

    // 헤드가 몸에 박았을 경우에 대한 처리
    // 헤드를 제외한 덱이 0이되는 경우가 발생할 수 있음 , 몸길이가 3미만 게임오버
    std::deque<SnakePiece> pieces = snake.getPiece(); // 헤드를 제외한 덱을 복사해서 구현

    if (pieces.size() < 1) 
    {
        gameOver = true;
        snake.addPiece(next);
        board.add(next);
    }

    for (auto& piece : pieces) {
        if (next.getX() == piece.getX() && next.getY() == piece.getY()) 
        {
            gameOver = true;
        }
    }
    // 헤드가 벽에 박았을 경우
    if (mvwinch(board.getBoardWin(), next.getY(), next.getX()) == 'X') 
    {
        next.setIcon('X');
        gameOver = true;
    }
    if (mvwinch(board.getBoardWin(), next.getY(), next.getX()) == '$')
    {
        next.setIcon('$');
        gameOver = true;
    }
    if (mvwinch(board.getBoardWin(), next.getY(), next.getX()) == 'x') 
    {
        next.setIcon('x');
        gameOver = true;
    }
    // 5초마다 아이템이 생겼다 사라짐
    if (itemGrow != nullptr && difftime(curTime, itemGrow->saveTime) >= 5.0) // difftime의 반환형은 double이다
    {
        int itemGrowRow = itemGrow->getY();
        int itemGrowCol = itemGrow->getX();
        board.add(Empty(itemGrowRow, itemGrowCol));
        delete itemGrow;
        itemGrow = nullptr;
    }
    // 위와 동일 독 아이템
    if (itemPoison != nullptr && difftime(curTime, itemPoison->saveTime) >= 5.0) // difftime의 반환형은 double이다
    {
        int itemPoisonRow = itemPoison->getY();
        int itemPoisonCol = itemPoison->getX();
        board.add(Empty(itemPoisonRow, itemPoisonCol));
        delete itemPoison;
        itemPoison = nullptr;
    }
    // 위와 동일 속도 아이템
    if (itemSpeed != nullptr && difftime(curTime, itemSpeed->saveTime) >= 5.0)
    {
        int itemSpeedRow = itemSpeed->getY();
        int itemSpeedCol = itemSpeed->getX();
        board.add(Empty(itemSpeedRow, itemSpeedCol));
        delete itemSpeed;
        itemSpeed = nullptr;
    }
    // 위와 동일 벽
    if (suddenWall != nullptr && difftime(curTime, suddenWall->saveTime) >= 3.0)
    {
        int suddenWallRow = suddenWall->getY();
        int suddenWallCol = suddenWall->getX();
        board.add(Empty(suddenWallRow, suddenWallCol));
        delete suddenWall;
        suddenWall = nullptr;
    }
    snake.addPiece(next);
    board.add(next);
    board.updateScoreCurSnake(snake.getSnakeSize());
    if (snake.getSnakeSize() > maxSnake)
    {
        maxSnake = snake.getSnakeSize();
        board.updateScoreMaxSnake(maxSnake);
    }
    if (snake.getPiece().size() > 1) 
    {
        SnakePiece body = snake.getPiece().back();
        body.setIcon('#');
        board.add(body);
    }
}
// 게이트가 나가는 곳이 가능한 곳인지 판별 후 가능한 곳의 좌표로 세팅해준다
void SnakeGame::moveGateAtoB(SnakePiece& next)
{   // 상하좌우
    if (snake.getDirection() == up)
    {
        int dxUp[4] = {0, 1, -1, 0}; // 상 우 좌 하
        int dyUp[4] = {-1, 0, 0, 1};
        int returndir[4] = {0, 3, 2, 1};
        for (int i = 0; i < 4; i++) // 상하좌우 4번만 탐색하면 된다
        {
            int dy = gateB->getY()+dyUp[i];
            int dx = gateB->getX()+dxUp[i];
            if (mvwinch(board.getBoardWin(), dy, dx) == ' ')
            {
                next.setY(dy);
                next.setX(dx);
                snake.setDirection(returndir[i]);
                p.first = dy;
                p.second = dx;
                break;
            }  
        }
    }

    if (snake.getDirection() == down)
    {
        int dxDown[4] = {0, -1, 1, 0}; // 하 좌 우 상
        int dyDown[4] = {1, 0, 0 ,-1};
        int returndir[4] = {1, 2, 3, 0}; 
        for (int i = 0; i < 4; i++)
        {
            int dy = gateB->getY()+dyDown[i];
            int dx = gateB->getX()+dxDown[i];
            if (mvwinch(board.getBoardWin(), dy, dx) == ' ')
            {
                next.setY(dy);
                next.setX(dx);
                snake.setDirection(returndir[i]);
                p.first = dy;
                p.second = dx;
                break;
            }   
        }
    }

    if (snake.getDirection() == left)
    {
        int dxLeft[4] = {-1, 0, 0, 1}; // 좌 상 하 우
        int dyLeft[4] = {0, -1, 1, 0};
        int returndir[4] = {2, 0, 1, 3};
        for (int i = 0; i < 4; i++)
        {
            int dy = gateB->getY()+dyLeft[i];
            int dx = gateB->getX()+dxLeft[i];
            if (mvwinch(board.getBoardWin(), dy, dx) == ' ')
            {
                next.setY(dy);
                next.setX(dx);
                snake.setDirection(returndir[i]);
                p.first = dy;
                p.second = dx;
                break;
            }   
        }
    }
    
    if (snake.getDirection() == right)
    {
    
        int dxRight[4] = {1, 0, 0, -1}; // 우 하 상 좌
        int dyRight[4] = {0, 1, -1, 0};
        int returndir[4] = {3, 1, 0, 2};
        for (int i = 0; i < 4; i++)
        {
            int dy = gateB->getY()+dyRight[i];
            int dx = gateB->getX()+dxRight[i];
            if (mvwinch(board.getBoardWin(), dy, dx) == ' ')
            {
                next.setY(dy);
                next.setX(dx);
                snake.setDirection(returndir[i]);
                p.first = dy;
                p.second = dx;
                break;
            }   
        }
    }
}
void SnakeGame::moveGateBtoA(SnakePiece& next)
{  
    if (snake.getDirection() == up)
    {
        int dxUp[4] = {0, 1, -1, 0}; // 상 우 좌 하
        int dyUp[4] = {-1, 0, 0, 1};
        int returndir[4] = {0, 3, 2, 1};
        for (int i = 0; i < 4; i++) // 상하좌우 4번만 탐색하면 된다
        {
            int dy = gateA->getY()+dyUp[i];
            int dx = gateA->getX()+dxUp[i];
            if (mvwinch(board.getBoardWin(), dy, dx) == ' ')
            {
                next.setY(dy);
                next.setX(dx);
                snake.setDirection(returndir[i]);
                p.first = dy;
                p.second = dx;
                break;
            }   
        }
    }

    if (snake.getDirection() == down)
    {
        int dxDown[4] = {0, -1, 1, 0}; // 하 좌 우 상
        int dyDown[4] = {1, 0, 0 ,-1};
        int returndir[4] = {1, 2, 3, 0};
        for (int i = 0; i < 4; i++)
        {
            int dy = gateA->getY()+dyDown[i];
            int dx = gateA->getX()+dxDown[i];
            if (mvwinch(board.getBoardWin(), dy, dx) == ' ')
            {
                next.setY(dy);
                next.setX(dx);
                snake.setDirection(returndir[i]);
                p.first = dy;
                p.second = dx;
                break;
            }   
        }
    }

    if (snake.getDirection() == left)
    {
        int dxLeft[4] = {-1, 0, 0, 1}; // 좌 상 하 우
        int dyLeft[4] = {0, -1, 1, 0};
        int returndir[4] = {2, 0, 1, 3};
        for (int i = 0; i < 4; i++)
        {
            int dy = gateA->getY()+dyLeft[i];
            int dx = gateA->getX()+dxLeft[i];
            if (mvwinch(board.getBoardWin(), dy, dx) == ' ')
            {
                next.setY(dy);
                next.setX(dx);
                snake.setDirection(returndir[i]);
                p.first = dy;
                p.second = dx;
                break;
            }   
        }
    }
    
    if (snake.getDirection() == right)
    {
        int dxRight[4] = {1, 0, 0, -1}; // 우 하 상 좌
        int dyRight[4] = {0, 1, -1, 0};
        int returndir[4] = {3, 1, 0, 2};
        for (int i = 0; i < 4; i++)
        {
            int dy = gateA->getY()+dyRight[i];
            int dx = gateA->getX()+dxRight[i];
            if (mvwinch(board.getBoardWin(), dy, dx) == ' ')
            {
                next.setY(dy);
                next.setX(dx);
                snake.setDirection(returndir[i]);
                p.first = dy;
                p.second = dx;
                break;
            }   
        }
    }
}

void SnakeGame::stageClear() // 할당 및 값 해제
{
    wtimeout(getBoardWin(), 200);
    growNumber = 0;
    poisonNumber = 0;
    gateNumber = 0;
    score = 0;
    board.updateScoreGrow(score);
    board.updateScorePoison(poisonNumber);
    board.updateScoreGate(gateNumber);
    board.updateMissionPoison(poisonNumber);
    board.updateMissionGrow(growNumber);
    board.updateScoreCurSnake(2); // 처음 길이는 항상 2임
    delete itemGrow;
    itemGrow = nullptr;
    delete itemPoison;
    itemPoison = nullptr;
    delete itemSpeed;
    itemSpeed = nullptr;
    delete gateA;
    gateA = nullptr;
    delete gateB;
    gateB = nullptr;
    delete suddenWall;
    suddenWall = nullptr;
    gateInUse = false;
    p = std::make_pair(-1, -1);
    snake.setDirection(up);
    snake.pieceClear();
    board.setStage(++stage);
    randomNumA = rand() % 4 + 2;
    randomNumB = rand() % 2 + 2;
    randomNumC = rand() % 2 + 2;
    randomNumD = rand() % 2 + 2;
    initialize();

}
void SnakeGame::missionCheck()
{
    if (randomNumA <= maxSnake) board.updateMissionCurSnakeCheck();
    if (randomNumB <= growNumber) board.updateMissionGrowCheck();
    if (randomNumC <= poisonNumber) board.updateMissionPoisonCheck();
    if (randomNumD <= gateNumber) board.updateMissionGateCheck();
    
}
bool SnakeGame::missionClear()
{
    if (randomNumA <= maxSnake && randomNumB <= growNumber && randomNumC <= poisonNumber && randomNumD <= gateNumber) return true;
    return false;
}
void SnakeGame::redraw()
{
    missionCheck();

    int height, width;
    if (gameOver)
    {
        getmaxyx(board.getBoardWin(), height, width);
        mvwprintw(board.getBoardWin(), height / 2 - 1, (width - 8) / 2, "Game Over");
    }

    if (missionClear() && board.getStage() < 4)
    {
        getmaxyx(board.getBoardWin(), height, width);
        mvwprintw(board.getBoardWin(), height / 2 - 1, (width - 8) / 2, "Stage Clear");
        board.refresh();
        napms(1500);
        if (board.getStage() == 3)
        {
            ++stage;
            return ;
        }
        stageClear();
        return ;
    }
    board.refresh();
}
void SnakeGame::gameRefresh()
{
    board.refresh();
}
void SnakeGame::updateGameTime(time_t startTime)
{
    time_t currentTime = time(nullptr);
    int seconds = static_cast<int>(difftime(currentTime, startTime));
    board.updateScoreTime(seconds);
}
int SnakeGame::getStage()
{
    return stage;
}
bool SnakeGame::isOver()
{
    return gameOver;
}
WINDOW* SnakeGame::getBoardWin() {
    return board.getBoardWin();
}

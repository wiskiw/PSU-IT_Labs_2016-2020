#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

typedef short int Dir; // [1..4]

typedef int bool;
#define true 1
#define false 0

void generateSnake();

void redrawScreen();

void drawWalls();

void drawFood();

void drawSnake();

void sleep(unsigned int mseconds);

void regenerateFood();

void increaseSnake();

int *getNewHead();

void createNewSnakesHead();

void removeSnakesTail();

void moveSnake();

Dir getDir(long key);

int getDirValue(Dir direction);

bool isHittingWalls();

bool isEating();

bool isMaxLength();

bool isHittingTial();

void gameOver();

void victory();


short int gameStatus = 1; // 1 - gaming ; 2 - game over; 3 - victory
const double GAME_SPEED = 0.7;
const int START_SNAKE_LENGTH = 5;
const Dir START_SNAKE_DIRECTION = 1;
const short SNAKE_HEAD_SYMBOL = 'O';
const short SNAKE_BODY_SYMBOL = 'o';
const short FOOD_SYMBOL = '%';

const short FIELD_BORDER_SYMBOL = '#';
const int FIELD_SIZE_X = 50;

const int FIELD_SIZE_Y = 15;


const int MAX_SNAKE_LENGTH = 99;
int snakeArr[100][2];
int food[2];


int main(int argc, char *argv[]) {
    generateSnake();

    regenerateFood();

    while (gameStatus == 1) {
        redrawScreen();
        sleep((unsigned int) (80 / GAME_SPEED));
        Dir newDirection;
        if (_kbhit()) {
            newDirection = getDir(_getch());
            if (newDirection != 0) snakeArr[0][0] = newDirection;
        }

        if (isHittingWalls() || isHittingTial()) {
            gameStatus = 2;
        } else if (isEating()) {
            increaseSnake();
            regenerateFood();
            if (isMaxLength()) {
                gameStatus = 3;
            }
        } else {
            moveSnake();
        }
    }

    switch (gameStatus) {
        case 2: {
            gameOver();
            break;
        }
        case 3: {
            victory();
            break;
        }
        default:
            return 0;
    }
    return 0;
}

void sleep(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

Dir getDir(long key) {
    switch (key) {
        case 119: { // w
            return 1;
        }
        case 97: { // a
            return 4;
        };
        case 115: { // s
            return 3;
        }
        case 100: { // d
            return 2;
        }
        default:
            return 0;
    }
}

void generateSnake() {
    int xHeadPos = FIELD_SIZE_X / 2;
    int yHeadPos = FIELD_SIZE_Y - START_SNAKE_LENGTH;

    snakeArr[0][0] = START_SNAKE_DIRECTION;
    snakeArr[0][1] = START_SNAKE_LENGTH;
    for (int i = 1; i <= START_SNAKE_LENGTH; ++i) {
        int posY = yHeadPos + i - 1;
        snakeArr[i][0] = xHeadPos;
        snakeArr[i][1] = posY;
    }

}

void redrawScreen() {
    _clrscr();
    drawFood();
    drawSnake();
    drawWalls();
    _gotoxy(FIELD_SIZE_X, FIELD_SIZE_Y);
}

void drawWalls() {
    for (int x = 1; x <= FIELD_SIZE_X; ++x) {
        _gotoxy(x, 1);
        printf("%c", FIELD_BORDER_SYMBOL);
        _gotoxy(x, FIELD_SIZE_Y);
        printf("%c", FIELD_BORDER_SYMBOL);
    }

    for (int y = 1; y <= FIELD_SIZE_Y; ++y) {
        _gotoxy(1, y);
        printf("%c", FIELD_BORDER_SYMBOL);
        _gotoxy(FIELD_SIZE_X, y);
        printf("%c", FIELD_BORDER_SYMBOL);
    }

}

void drawSnake() {
    _textcolor(12);
    int head_x = snakeArr[1][0];
    int head_y = snakeArr[1][1];
    _gotoxy(head_x, head_y);
    printf("%c", SNAKE_HEAD_SYMBOL);
    int snakeLength = snakeArr[0][1];
    for (int i = 2; i <= snakeLength; ++i) {
        int x = snakeArr[i][0];
        int y = snakeArr[i][1];
        _gotoxy(x, y);
        printf("%c", SNAKE_BODY_SYMBOL);
    }
    _textcolor(7);
}

void drawFood() {
    int x = food[0];
    int y = food[1];
    _gotoxy(x, y);
    _textcolor(10);
    printf("%c", FOOD_SYMBOL);
    _textcolor(7);
}

void regenerateFood() {
    // firs_value + rand() % last_value;
    srand(time(0));
    food[0] = 3 + rand() % (FIELD_SIZE_X - 3);
    srand(time(0));
    food[1] = 3 + rand() % (FIELD_SIZE_Y - 3);
}

void createNewSnakesHead() {
    int *newHeadPos = getNewHead();
    int snakeLength = snakeArr[0][1];
    snakeArr[0][1] = snakeLength + 1;
    for (int i = snakeLength; i > 1; i--) {
        snakeArr[i][0] = snakeArr[i - 1][0];
        snakeArr[i][1] = snakeArr[i - 1][1];

    }
    snakeArr[1][0] = newHeadPos[0];
    snakeArr[1][1] = newHeadPos[1];
}

void removeSnakesTail() {
    int snakeLength = snakeArr[0][1];
    snakeArr[0][1] = snakeLength - 1;
    snakeArr[snakeLength][0] = 0;
    snakeArr[snakeLength][1] = 0;
}

bool isHittingWalls() {
    int head_x = snakeArr[1][0];
    int head_y = snakeArr[1][1];
    return (head_x <= 1 || head_x >= FIELD_SIZE_X || head_y <= 1 || head_y >= FIELD_SIZE_Y);
}

bool isEating() {
    int head_x = snakeArr[1][0];
    int head_y = snakeArr[1][1];
    return (food[0] == head_x && food[1] == head_y);
}

bool isMaxLength() {
    return snakeArr[0][1] >= MAX_SNAKE_LENGTH;
}

void gameOver() {
    _clrscr();
    int score = (snakeArr[0][1] - START_SNAKE_LENGTH) * 10;
    char msg1[] = "Game Over!";
    char msg2[] = "Score: ";

    int start_x = FIELD_SIZE_X / 2;
    int start_y = FIELD_SIZE_Y - sizeof(msg1) / 2;
    _textcolor(12);
    _gotoxy(start_x, start_y);
    printf("%s", msg1);

    start_y = FIELD_SIZE_Y - (sizeof(msg2) + 3) / 2;
    _gotoxy(start_x, start_y + 1);
    printf("%3s%d", msg2, score);

    _textcolor(7);
    for (int i = 0; i < start_x / 2; ++i) {
        printf("\n");
    }
}

void victory() {
    _clrscr();
    char msg1[] = "You Won!";
    int start_x = FIELD_SIZE_X / 2;
    int start_y = FIELD_SIZE_Y - sizeof(msg1) / 2;
    _textcolor(10);
    _gotoxy(start_x, start_y);
    printf("%s", msg1);
    _textcolor(7);
    for (int i = 0; i < start_x / 2; ++i) {
        printf("\n");
    }
}


void increaseSnake() {
    createNewSnakesHead();
}

void moveSnake() {
    createNewSnakesHead();
    removeSnakesTail();
}

int *getNewHead() {
    Dir direction = (Dir) snakeArr[0][0];
    int new_head_x = snakeArr[1][0];
    int new_head_y = snakeArr[1][1];
    switch (direction) {
        case 1: {
            new_head_y--;
            break;
        }
        case 2: {
            new_head_x++;
            break;
        }
        case 3: {
            new_head_y++;
            break;
        }
        case 4: {
            new_head_x--;
            break;
        }
    }

    int newHeadPos[] = {new_head_x, new_head_y};
    return newHeadPos;
}

bool isHittingTial() {
    int head_x = snakeArr[1][0];
    int head_y = snakeArr[1][1];
    int snakeLength = snakeArr[0][1];
    for (int i = 2; i <= snakeLength; i++) {
        int x = snakeArr[i][0];
        int y = snakeArr[i][1];
        if (x == head_x && y == head_y) return true;
    }
    return false;
}

#include <iostream>
#include <GL/glut.h>
#include "io/IOProcessor.h"
#include "levels/LevelMaker.h"
#include <SFML/Graphics.hpp>

// размеры окна
const int WINDOW_X = 975;
const int WINDOW_Y = 605;
const int UI_BAR_HEIGHT = 97;

const long int MS_BEFORE_WATER = 25 * 1000; //sec время до воды
const long int MS_WATER_SLEEP_TIME = 1 * 1000; //sec задержка обновления воды

void *GAME_FONT = GLUT_BITMAP_TIMES_ROMAN_24; // шрифт

// текстуры
GLuint txtMenuBg;
GLuint txtGameBg;
GLuint txtTubeI;
GLuint txtTubeT;
GLuint txtTubeL;
GLuint txtTubeX;
GLuint txtWin;
GLuint txtLose;

const int GAME_STATE_MENU = 1; // главное меню
const int GAME_STATE_PLAY = 2; // в игре
const int GAME_STATE_LEVEL_COMPLETE = 3; // победа
const int GAME_STATE_LEVEL_FAILED = 4; // game over
int gameState = GAME_STATE_MENU; // состояние приложения

GameLevelField currentGame; // текущее игровое поле
int selectedLevel; // текущий уровень
int     CELL_SIZE = 75; // размеры ячейки поля (px)
long int untilWaterTimer = 0;
int movements = 0; // кол-во действий

// точка финиша
int finishPointX = -1;
int finishPointY = -1;

const int lastWaterBufferSize = 56;
int lastWaterBuffer[lastWaterBufferSize][2]; // буффер разлива

// структура цвета
struct GameColor {
    GLubyte R = 0;
    GLubyte G = 0;
    GLubyte B = 0;
    GLubyte A = 255;
};

// структура координат
struct GamePos {
    int x = 0;
    int y = 0;
    int z = 0;
};

// рандомное число от start до end
int utilsRandom(int start, int end) {
    return start + (rand() % (end - start + 1));
}

// рисование текста
void utilsDrawText(GamePos pos, GameColor color, std::string string) {
    // fonts https://www.opengl.org/resources/libraries/glut/spec3/node76.html

    size_t j = string.size();
    glColor4ub(color.R, color.G, color.B, color.A);
    glRasterPos3f(pos.x, pos.y, pos.z);
    for (int i = 0; i < j; i++) {
        glutBitmapCharacter(GAME_FONT, string[i]);
    }
}

// загрузка текстуры по имени
bool loadTexture(GLuint *texture, const std::string textureName) {
    sf::Image image;
    if (!image.loadFromFile("textures/" + textureName)) {
        return false;
    }
    image.flipVertically();

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y,
                      GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    return true;
}

// игра окончена
void gameOver() {
    std::cout << "[INFO] Game over!!! " << std::endl;
    gameState = GAME_STATE_LEVEL_FAILED;
}

// победа
void levelComplete() {
    std::cout << "[INFO] Level complete!!! " << std::endl;
    gameState = GAME_STATE_LEVEL_COMPLETE;
}

// рисование меню
void drawMenu() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txtMenuBg);

    // background
    glColor4ub(0, 0, 0, 200);
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1);
    glVertex2i(0, 0);
    glTexCoord2f(1, 1);
    glVertex2i(WINDOW_X, 0);
    glTexCoord2f(1, 0);
    glVertex2i(WINDOW_X, -WINDOW_Y);
    glTexCoord2f(0, 0);
    glVertex2i(0, -WINDOW_Y);
    glEnd();

}

// рисование игры
void drawGame() {

    if (untilWaterTimer < MS_BEFORE_WATER) {
        long int timeSec = (MS_BEFORE_WATER - untilWaterTimer) / 1000;
        std::string timeStr = "Before water: " + std::to_string(timeSec) + "s";
        utilsDrawText({150, -50, 4}, {255, 255, 255}, timeStr);
    } else {
        utilsDrawText({150, -50, 4}, {255, 255, 255}, "Water is coming!");
    }
    utilsDrawText({450, -50, 4}, {255, 255, 255}, "Movements: " + std::to_string(movements));
    utilsDrawText({800, -50, 4}, {255, 255, 255}, "Level: " + std::to_string(selectedLevel));


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txtGameBg);

    // background
    glColor4ub(0, 0, 0, 200);
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1);
    glVertex2i(0, 0);
    glTexCoord2f(1, 1);
    glVertex2i(WINDOW_X, 0);
    glTexCoord2f(1, 0);
    glVertex2i(WINDOW_X, -WINDOW_Y);
    glTexCoord2f(0, 0);
    glVertex2i(0, -WINDOW_Y);
    glEnd();

    int halfOfSize = CELL_SIZE / 2;
    for (int y = 0; y < S_GAME_GRID_Y; ++y) {
        for (int x = 0; x < S_GAME_GRID_X; ++x) {
            GameFieldItem item = currentGame.items[y][x];
            if (item.type == '*') {
                continue;
            } else {
                glPushMatrix();
                glTranslated(x * CELL_SIZE + halfOfSize, -y * CELL_SIZE - UI_BAR_HEIGHT - halfOfSize, 0);

                glPushMatrix();
                glRotated(item.orientation * -90, false, false, true);

                glEnable(GL_TEXTURE_2D);
                glColor3ub(0, 0, item.isFilled ? 50 : 0);
                switch (toupper(item.type)) {
                    case 'S':
                        glColor3ub(0, 100, 0);
                        glBindTexture(GL_TEXTURE_2D, txtTubeI);
                        break;
                    case 'W':
                        glColor3ub(100, 0, 0);
                        glBindTexture(GL_TEXTURE_2D, txtTubeI);
                        break;
                    case 'X':
                        glBindTexture(GL_TEXTURE_2D, txtTubeX);
                        break;
                    case 'T':
                        glBindTexture(GL_TEXTURE_2D, txtTubeT);
                        break;
                    case 'L':
                        glBindTexture(GL_TEXTURE_2D, txtTubeL);
                        break;
                    case 'I':
                        glBindTexture(GL_TEXTURE_2D, txtTubeI);
                        break;
                }

                glBegin(GL_POLYGON);

                glTexCoord2f(0, 1);
                glVertex2i(-halfOfSize, halfOfSize);
                glTexCoord2f(1, 1);
                glVertex2i(halfOfSize, halfOfSize);
                glTexCoord2f(1, 0);
                glVertex2i(halfOfSize, -halfOfSize);
                glTexCoord2f(0, 0);
                glVertex2i(-halfOfSize, -halfOfSize);

                glEnd();
                glPopMatrix();

                glDisable(GL_TEXTURE_2D);
                glScaled(0.8, 0.8, 1);


                glPopMatrix();
            }

        }
    }
    glDisable(GL_TEXTURE_2D);
}

// проверка: воординаты в пределах игрового поля
bool isIndexInField(int x, int y) {
    return x >= 0 && x < S_GAME_GRID_X && y >= 0 && y < S_GAME_GRID_Y;
}

// проверка трубы на А на герметичность с ячейкой Б
bool isCellsAirtight(int xIA, int yIA, int xIB, int yIB) {
    GameFieldItem tubeA = currentGame.items[yIA][xIA];
    GameFieldItem tubeB = currentGame.items[yIB][xIB];

    bool aOpen;
    bool bOpen;

    if (abs(xIA - xIB) == 1 && yIA == yIB) {
        // вдоль оХ
        if (xIA < xIB) {
            aOpen = tubeA.openSides[1]; // 1 - правая сторона трубы А
            bOpen = tubeB.openSides[3]; // 3 - левая сторона трубы B
        } else {
            aOpen = tubeA.openSides[3]; // 3 - левая сторона трубы А
            bOpen = tubeB.openSides[1]; // 1 - правая сторона трубы B
        }
        return aOpen && bOpen || !aOpen;
    } else if (abs(yIA - yIB) == 1 && xIA == xIB) {
        // вдоль оY
        if (yIA < yIB) {
            aOpen = tubeA.openSides[2]; // 2 - нижняя сторона трубы А
            bOpen = tubeB.openSides[0]; // 0 - верхняя сторона трубы B
        } else {
            aOpen = tubeA.openSides[0]; // 2 - верхняя сторона трубы А
            bOpen = tubeB.openSides[2]; // 0 - нижняя сторона трубы B
        }
        return aOpen && bOpen || !aOpen;
    } else {
        return false;
    }
}

void bufferSize() {
    // кол-во эллементов в буффере
    int k = 0;
    for (int i = 0; i < lastWaterBufferSize; ++i) {
        if (lastWaterBuffer[i][0] != -1) {
            k++;
        }
    }
    std::cout << "size: " << k << "\n";
}

// добавление в буффер
bool addToBuffer(int xI, int yI) {
    // добавление трубы в буффер разлив
    for (int i = 0; i < lastWaterBufferSize; ++i) {
        if (lastWaterBuffer[i][0] == xI && lastWaterBuffer[i][1] == yI) {
            return true;
        } else if (lastWaterBuffer[i][0] == -1) {
            lastWaterBuffer[i][0] = xI;
            lastWaterBuffer[i][1] = yI;
            return true;
        }
    }
    return false;
}

// перепросчет новых труб для разлива
bool DFS(int xI, int yI) {
    GameFieldItem *item = &currentGame.items[yI][xI];
    if (!isIndexInField(xI, yI) || item->type == '*') {
        return true;
    } else {
        item->isFilled = true;
        item->locked = true;
    }

    for (int i = 0; i < 4; ++i) {
        if (!item->openSides[i]) continue;
        int xIndexForCheck = xI + ((i == 1 || i == 3) ? 2 - i : 0);
        int yIndexForCheck = yI + ((i == 0 || i == 2) ? -1 + i : 0);
        if (!isIndexInField(xIndexForCheck, yIndexForCheck) ||
            !isCellsAirtight(xI, yI, xIndexForCheck, yIndexForCheck)) {
            gameOver();
            return false;
        }
    }


    for (int i = 0; i < 4; ++i) {
        if (!item->openSides[i]) continue;
        int xIndexForCheck = xI + ((i == 1 || i == 3) ? 2 - i : 0);
        int yIndexForCheck = yI + ((i == 0 || i == 2) ? -1 + i : 0);
        if (!currentGame.items[yIndexForCheck][xIndexForCheck].isFilled) {
            addToBuffer(xIndexForCheck, yIndexForCheck);
            if (xIndexForCheck == finishPointX && yIndexForCheck == finishPointY) {
                levelComplete();
            }
        }
    }
    return true;
}

// поворот трубы
void rotateTube(int xI, int yI, bool onClockArrow) {
    GameFieldItem *item = &currentGame.items[yI][xI];
    if (item->locked) {
        return;
    }

    if (onClockArrow) {
        // поворот по часовой
        item->orientation++;
        item->orientation = item->orientation > 3 ? 0 : item->orientation;

        // перепросчёт открытых сторон
        bool lastSide = item->openSides[3];
        for (int i = 3; i > 0; i--) {
            item->openSides[i] = item->openSides[i - 1];
        }
        item->openSides[0] = lastSide;
    } else {
        // повопрот против часовой
        item->orientation--;
        item->orientation = item->orientation < 0 ? 3 : item->orientation;

        // перепросчёт открытых сторон
        bool firstSide = item->openSides[0];
        for (int i = 0; i < 3; ++i) {
            item->openSides[i] = item->openSides[i + 1];
        }
        item->openSides[3] = firstSide;

    }

}

void onUpdateWaterTimer(int id) {
    // обработчик разлива воды
    if (gameState != GAME_STATE_PLAY) return;
    for (int i = 0; i < lastWaterBufferSize; ++i) {
        if (lastWaterBuffer[i][0] != -1) {
            if (DFS(lastWaterBuffer[i][0], lastWaterBuffer[i][1])) {
                // удаление элемента из буффера
                lastWaterBuffer[i][0] = -1;
                lastWaterBuffer[i][1] = -1;
            }
        }
    }
    // перезапуск таймера
    glutTimerFunc(MS_WATER_SLEEP_TIME, onUpdateWaterTimer, 1);
    //bufferSize();
}

void onWaterEnable(int id) {
    // обработчик тамера активации воды
    if (gameState != GAME_STATE_PLAY) return;
    if (untilWaterTimer < MS_BEFORE_WATER) {
        // обновляем таймер
        untilWaterTimer += 100;
        glutTimerFunc(100, onWaterEnable, 2);
    } else {
        // запускаем таймер разлива воды
        glutTimerFunc(MS_WATER_SLEEP_TIME, onUpdateWaterTimer, 1);
    }
}

void initSelectedLevel() {
    // подготовка выбранного уровня
    currentGame = getLevelField(selectedLevel);

    for (int i = 0; i < lastWaterBufferSize; ++i) {
        lastWaterBuffer[i][0] = -1;
        lastWaterBuffer[i][1] = -1;
    }

    for (int y = 0; y < S_GAME_GRID_Y; ++y) {
        for (int x = 0; x < S_GAME_GRID_X; ++x) {
            GameFieldItem *item = &currentGame.items[y][x];
            if (toupper(item->type) != 'S' && toupper(item->type) != 'W') {

                int randomk = utilsRandom(0, 3);
                for (int i = 0; i < randomk; ++i) {
                    rotateTube(x, y, true);
                }
            }
            switch (toupper(item->type)) {
                case 'S':
                    lastWaterBuffer[0][0] = x;
                    lastWaterBuffer[0][1] = y;
                    break;
                case 'W':
                    finishPointX = x;
                    finishPointY = y;
                    break;
            }

        }
    }
    if (lastWaterBuffer[0][0] == -1) {
        std::cout << "[ERROR] Bad map!!! " << std::endl;
    }

    untilWaterTimer = 0;
    glutTimerFunc(100, onWaterEnable, 2);
}

void onKeyPress(int key, int x, int y, bool special) {
    //std::cout << "[DEBUG] KEY PRESSED[" << (special ? 's' : 'n') << "]: " << key << std::endl;
    switch (gameState) {
        case GAME_STATE_MENU: // в меню
            // нажатие клавиш выбора уровня в меню
            if (!special && key >= '1' && key <= '3') {
                selectedLevel = key - 48;
                initSelectedLevel();
                gameState = GAME_STATE_PLAY;
            }
            break;
        case GAME_STATE_PLAY: // в игре
            if (!special && key == 27) {
                // ESC
                gameState = GAME_STATE_MENU;
            } else if (!special && (key == IO_MOUSE_LEFT_BUTTON || key == IO_MOUSE_RIGHT_BUTTON)) {
                // клик мыши
                int xI = x / CELL_SIZE;
                int yI = (y - UI_BAR_HEIGHT) / (CELL_SIZE);
                if (xI >= 0 && xI < S_GAME_GRID_X && yI >= 0 && yI < S_GAME_GRID_Y) {
                    rotateTube(xI, yI, key == IO_MOUSE_LEFT_BUTTON);
                    movements++;
                }
            }
            break;
        case GAME_STATE_LEVEL_COMPLETE:
        case GAME_STATE_LEVEL_FAILED:
            if (!special && (key == 27 || key == 13)) {
                // ESC или ENTER
                gameState = GAME_STATE_MENU;
            }
            break;
    }

}

void onChangeSize(int width, int height) {
    glutReshapeWindow(WINDOW_X, WINDOW_Y);
}

// функция рисования
void draw() {
    checkKeysBuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (gameState) {
        case GAME_STATE_MENU:
            drawMenu();
            break;
        case GAME_STATE_PLAY:
            drawGame();
            break;
        case GAME_STATE_LEVEL_COMPLETE:
            glEnable(GL_TEXTURE_2D);
            glColor4ub(0, 0, 0, 255);
            glBindTexture(GL_TEXTURE_2D, txtWin);
            glBegin(GL_POLYGON);
            glTexCoord2f(0, 1);
            glVertex2i(0, 0);
            glTexCoord2f(1, 1);
            glVertex2i(WINDOW_X, 0);
            glTexCoord2f(1, 0);
            glVertex2i(WINDOW_X, -WINDOW_Y);
            glTexCoord2f(0, 0);
            glVertex2i(0, -WINDOW_Y);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            utilsDrawText({WINDOW_X / 2 - 200, -WINDOW_Y / 2 - 100, 4}, {1, 1, 1},
                          "LEVEL №" + std::to_string(selectedLevel) + " COMPLETE (MOVEMENTS: " +
                          std::to_string(movements) + ")");
            break;
        case GAME_STATE_LEVEL_FAILED:
            glEnable(GL_TEXTURE_2D);
            glColor4ub(0, 0, 0, 255);
            glBindTexture(GL_TEXTURE_2D, txtLose);
            glBegin(GL_POLYGON);
            glTexCoord2f(0, 1);
            glVertex2i(0, 0);
            glTexCoord2f(1, 1);
            glVertex2i(WINDOW_X, 0);
            glTexCoord2f(1, 0);
            glVertex2i(WINDOW_X, -WINDOW_Y);
            glTexCoord2f(0, 0);
            glVertex2i(0, -WINDOW_Y);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            break;
    }
    glutSwapBuffers();
}

int main(int args, char **argv) {

    setKeyPressListener(onKeyPress);

    glutInit(&args, argv);

    int posX = (glutGet(GLUT_SCREEN_WIDTH) - WINDOW_X) / 2;
    int posY = (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_Y) / 2;

    glutInitWindowPosition(posX, posY); // координаты окна
    glutInitWindowSize(WINDOW_X, WINDOW_Y); // размеры окна
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Plumber 2D");
    glEnable(GL_BLEND);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0, 0, 0, 0); // цвет фона

    glViewport(0, 0, WINDOW_X, WINDOW_Y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_X, -WINDOW_Y, 0, -50, 50);
    glMatrixMode(GL_MODELVIEW);


    srand(time(0)); // для рандома

    // загрузка текстур
    loadTexture(&txtGameBg, "play-bg.png");
    loadTexture(&txtMenuBg, "menu-bg.png");
    loadTexture(&txtTubeI, "tube-i.png");
    loadTexture(&txtTubeL, "tube-l.png");
    loadTexture(&txtTubeT, "tube-t.png");
    loadTexture(&txtTubeX, "tube-x.png");
    loadTexture(&txtWin, "win-bg.png");
    loadTexture(&txtLose, "lose-bg.png");

    glutReshapeFunc(onChangeSize); // функция изменения размера окна

    // обработчики ввода
    glutKeyboardFunc(ioProcessNormalKeyDown);
    glutKeyboardUpFunc(ioProcessNormalKeyUp);
    glutSpecialFunc(ioProcessSpecialKeyDown);
    glutSpecialUpFunc(ioProcessSpecialKeyUp);
    glutMouseFunc(ioProcessMouseClick);
    glutMotionFunc(ioProcessMouseMove);
    glutPassiveMotionFunc(ioProcessMouseMove);

    glutDisplayFunc(draw); // функция рисования

    glutMainLoop(); // запуск цикла
    return 0;
}
//
// Created by wiskiw on 02.12.17.
//

#include <cstdlib>
#include <cmath>
#include <cstring>
#include "Utils.h"

int random(int start, int end) {
    return start + (rand() % (end - start + 1));
}

float random(float start, float end) {
    return static_cast<float>(start + fmod(rand(), (end - start + 1)));
}

void utilsDrawBorders(SW_Borders borders, SW_Color color, int width, float z) {
    glPushMatrix();

    glLineWidth(width);
    glBegin(GL_LINE_LOOP);
    glColor4ub(color.R, color.G, color.B, color.A);
    glVertex3f(borders.leftBottomX, borders.leftBottomY, z);
    glVertex3f(borders.leftBottomX, borders.rightTopY, z);
    glVertex3f(borders.rightTopX, borders.rightTopY, z);
    glVertex3f(borders.rightTopX, borders.leftBottomY, z);
    glEnd();
    glLineWidth(1);

    glPopMatrix();
}


void utilsDrawHitBox(SW_Borders borders, SW_Color color) {
    const GLfloat K = 1.1;

    borders.leftBottomX -= K;
    borders.leftBottomY -= K;
    borders.rightTopX += K;
    borders.rightTopY += K;

    utilsDrawBorders(borders, color, 2, PREF_HIT_BOX_Z_POS);
}


void utilsMoveBorers(SW_Borders *borders, SW_Pos movPosValue) {
    borders->leftBottomX += movPosValue.x;
    borders->leftBottomY += movPosValue.y;
    borders->rightTopX += movPosValue.x;
    borders->rightTopY += movPosValue.y;
}

void utilsMovePos(SW_Pos *pos, SW_Pos movPosValue) {
    pos->x += movPosValue.x;
    pos->y += movPosValue.y;
}

void utilsSelectColor(SW_Color color) {
    glColor4ub(color.R, color.G, color.B, color.A);
}

GLubyte concatColorChannels(int a, int b) {
    int newValue = a + b;
    if (newValue > 255) {
        return 255;
    } else if (newValue < 0) {
        return 0;
    } else {
        return static_cast<GLubyte>(newValue);
    }
}


void utilsConcatColors(SW_Color *colorResult, int r, int g, int b, int a) {
    colorResult->R = concatColorChannels(colorResult->R, r);
    colorResult->G = concatColorChannels(colorResult->G, g);
    colorResult->B = concatColorChannels(colorResult->B, b);
    colorResult->A = concatColorChannels(colorResult->A, a);
}


void utilsDrawText(SW_Pos pos, SW_Color color, void *font, char *string) {
    // fonts https://www.opengl.org/resources/libraries/glut/spec3/node76.html

    /*
     GLUT_BITMAP_9_BY_15


     */

    size_t j = strlen(string);
    utilsSelectColor(color);
    glRasterPos3f(pos.x, pos.y, pos.z);
    for (int i = 0; i < j; i++) {
        glutBitmapCharacter(font, string[i]);
    }
}

bool utilsIsPosInBorders(SW_Pos pos, SW_Borders borders) {
    const float bX = pos.x;
    const float bY = pos.y;

    if (bX >= borders.leftBottomX && bX <= borders.rightTopX &&
        bY >= borders.leftBottomY && bY <= borders.rightTopY) {
        // hit
        return true;
    } else {
        return false;
    }

}

void utilsConvertToGameWindowPosition(GameFieldStruct *thisGame, SW_Pos *pos) {
    pos->y = (thisGame->windowY - pos->y) / PREF_SCREEN_CROP_FACTOR;
    pos->x = pos->x / PREF_SCREEN_CROP_FACTOR;
}
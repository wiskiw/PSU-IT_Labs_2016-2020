//
// Created by wiskiw on 02.12.17.
//

#include <cstdlib>
#include <cmath>
#include "Utils.h"

int random(int start, int end) {
    return start + (rand() % (end - start + 1));
}

float random(float start, float end) {
    return static_cast<float>(start + fmod(rand(), (end - start + 1)));
}

void utilsDrawBorders(SW_Borders borders, SW_Color color, int width) {
    const GLfloat scale = 1.1;
    const GLfloat Z = 5;

    glPushMatrix();

    glLineWidth(width);
    glBegin(GL_LINE_LOOP);
    glColor4ub(color.R, color.G, color.B, color.A);
    glVertex3f(borders.leftBottomX - scale, borders.leftBottomY - scale, Z);
    glVertex3f(borders.leftBottomX - scale, borders.rightTopY + scale, Z);
    glVertex3f(borders.rightTopX + scale, borders.rightTopY + scale, Z);
    glVertex3f(borders.rightTopX + scale, borders.leftBottomY - scale, Z);
    glEnd();
    glLineWidth(1);

    glPopMatrix();
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
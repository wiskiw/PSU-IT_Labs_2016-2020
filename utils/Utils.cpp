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

void utilsDrawBorders(SW_Borders borders) {
    const GLfloat scale = 1.1;
    const GLfloat Z = 5;

    glPushMatrix();

    glBegin(GL_LINE_LOOP);
    glColor3ub(255, 0, 255);
    glVertex3f(borders.leftBottomX - scale, borders.leftBottomY - scale, Z);
    glVertex3f(borders.leftBottomX - scale, borders.rightTopY + scale, Z);
    glVertex3f(borders.rightTopX + scale, borders.rightTopY + scale, Z);
    glVertex3f(borders.rightTopX + scale, borders.leftBottomY - scale, Z);
    glEnd();

    glPopMatrix();

}
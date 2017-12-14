//
// Created by wiskiw on 01.12.17.
//

#include "ModuleBackground.h"
#include "../../utils/Utils.h"
#include "../../resources/TextureManager.h"

const int COLORS_NUMBER = 3;
const float STARS_OPACITY = 0.4f;
const float BACKGROUND_SPEED_K = 0.4f; //коэффициент скорости движения фона

const unsigned int PLANET_SPAWN_TICKS = 520;

void chooseColor(int color) {
    switch (color) {
        case 1:
            //white
            glColor4ub(255, 255, 255, static_cast<GLubyte>(255 * STARS_OPACITY));
            break;
        case 2:
            //yellow
            glColor4ub(255, 233, 79, static_cast<GLubyte>(200 * STARS_OPACITY));
            break;
        case 3:
            //reed
            glColor4ub(255, 93, 12, static_cast<GLubyte>(255 * STARS_OPACITY));
            break;
        case 4:
            //purple
            glColor4ub(125, 66, 165, static_cast<GLubyte>(255 * STARS_OPACITY));
            break;
    }
}

// установка основных характеристик звёзд
void setBaseStarPreferences(SW_Star *star) {
    star->pos.z = PREF_BACKGROUND_Z_POS;
    star->color = random(1, COLORS_NUMBER);
    star->size = random(0.7f, 0.85f);
    star->speed.y = random(2.4f, 3.1f) * BACKGROUND_SPEED_K * star->size;
}

void createNewPlanet(GameFieldStruct *thisGame) {
    thisGame->background.planet.textureIndex = txtGetRandomPlanerTextureIndex();
    thisGame->background.planet.size = random(1.0f, 1.6f);
    thisGame->background.planet.speed.y = -thisGame->background.planet.size * BACKGROUND_SPEED_K * 3.3f;

    SW_Pos pos;
    pos.x = random(thisGame->gameBorders.leftBottomX, thisGame->gameBorders.rightTopX);
    pos.y = thisGame->gameBorders.rightTopY +
            PREF_BACKGROUND_PLANET_SIZE * thisGame->background.planet.size;
    //pos.x = thisGame->gameBorders.leftBottomX;
    thisGame->background.planet.pos = pos;
}

// создание новой звезда с верху игрового поля
void createStar(GameFieldStruct *thisGame, SW_Star *star) {
    setBaseStarPreferences(star);
    star->pos.x = random(thisGame->gameBorders.leftBottomX, thisGame->gameBorders.rightTopX);
    star->pos.y = thisGame->gameBorders.rightTopY;
};

// первоначально заполнение массива звёзд
void mdlBackgroundInit(GameFieldStruct *thisGame) {
    const int number = thisGame->background.starNumber;
    for (int k = 0; k < number; k++) {
        SW_Star *star = &thisGame->background.stars[k];
        star->pos.x = random(thisGame->gameBorders.leftBottomX, thisGame->gameBorders.rightTopX);
        star->pos.y = random(thisGame->gameBorders.leftBottomY, thisGame->gameBorders.rightTopY);
        setBaseStarPreferences(star);
    }
}

void redrawPlanet(GameFieldStruct *thisGame) {
    SW_Planet *planet = &thisGame->background.planet;

    glPushMatrix();
    glTranslatef(planet->pos.x, planet->pos.y, PREF_BACKGROUND_Z_POS + 0.01f);
    glScalef(planet->size, planet->size, 0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txtGetPlanerTexture(planet->textureIndex));

    glBegin(GL_POLYGON);
    glColor4ub(0, 0, 0, PREF_BACKGROUND_PLANET_DARKNESS);
    glTexCoord2f(0, 0);
    glVertex2f(-PREF_BACKGROUND_PLANET_SIZE, -PREF_BACKGROUND_PLANET_SIZE);
    glTexCoord2f(0, 1);
    glVertex2f(-PREF_BACKGROUND_PLANET_SIZE, PREF_BACKGROUND_PLANET_SIZE);
    glTexCoord2f(1, 1);
    glVertex2f(PREF_BACKGROUND_PLANET_SIZE, PREF_BACKGROUND_PLANET_SIZE);
    glTexCoord2f(1, 0);
    glVertex2f(PREF_BACKGROUND_PLANET_SIZE, -PREF_BACKGROUND_PLANET_SIZE);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void mdlBackgroundUpdate(GameFieldStruct *thisGame) {
    redrawPlanet(thisGame);

    const int number = thisGame->background.starNumber;
    for (int k = 0; k < number; k++) {
        SW_Star *star = &thisGame->background.stars[k];

        glPushMatrix();
        glTranslatef(star->pos.x, star->pos.y, 0);
        glRotatef(random(0, 360), false, false, true);

        glBegin(GL_POLYGON);
        chooseColor(star->color);
        glVertex3f(0, 1 * star->size, star->pos.z);
        glVertex3f(1 * star->size, -1 * star->size, star->pos.z);
        glVertex3f(-1 * star->size, -1 * star->size, star->pos.z);
        glEnd();
        glPopMatrix();

        if (thisGame->gameState == GAME_STATE_PLAY) {
            star->pos.y -= star->speed.y;
            if (star->pos.y <= thisGame->gameBorders.leftBottomY) {
                // отрисовка новой звезды, если старая выходит за границы игрового поля
                createStar(thisGame, star);
            }
        }
    }

    if (thisGame->gameState == GAME_STATE_PLAY) {
        thisGame->background.planet.pos.y += thisGame->background.planet.speed.y;
        if (thisGame->globalTickTimer % PLANET_SPAWN_TICKS == 0 &&
            thisGame->background.planet.pos.y <= thisGame->gameBorders.leftBottomY -
                                                 PREF_BACKGROUND_PLANET_SIZE * thisGame->background.planet.size) {
            // отрисовка новой звезды, если старая выходит за границы игрового поля
            createNewPlanet(thisGame);
        }
    }

}


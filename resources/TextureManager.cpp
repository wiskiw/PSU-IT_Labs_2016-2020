//
// Created by wiskiw on 12.12.17.
//

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "../utils/Utils.h"

const std::string TEXTURE_PATH = "../resources/texture/";
const std::string TEXTURE_EXTENSION = ".png";


const int EGG_PLANET_INDEX = -10;
const int EGG_PLANET_CHANCE = 20; // 0 - 200


GLuint playerTexture;
GLuint menuBackgroundTexture;

const int planetTextureNumber = 10;
GLuint planetTextureList[planetTextureNumber];

const int enemyTextureNumber = 4;
GLuint enemyTextureList[enemyTextureNumber];

const int dropTextureNumber = 8;
GLuint dropTextureList[dropTextureNumber];

const int hitTextureNumber = 1;
GLuint hitTextureList[hitTextureNumber];

const int eggTextureNumber = 1;
GLuint eggTextureList[eggTextureNumber];


bool loadPngTexture(GLuint *texture, const sf::String textureName) {
    sf::Image image;
    if (!image.loadFromFile(TEXTURE_PATH + textureName + TEXTURE_EXTENSION)) {
        return false;
    }
    image.flipVertically();

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    //printf("%d x %d\n", image.getSize().x, image.getSize().y);

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

bool loadPngTextureList(GLuint *textureList, int size, const sf::String texturePrefixName) {
    for (int i = 0; i < size; ++i) {
        GLuint txt;
        if (loadPngTexture(&txt, texturePrefixName + '_' + std::to_string(i))) {
            textureList[i] = txt;
        } else {
            return false;
        }
    }
    return true;
}

void txtInit(GameFieldStruct *thisGame) {
    bool success = true;

    success = loadPngTexture(&playerTexture, "player") ? success : false;
    success = loadPngTexture(&menuBackgroundTexture, "menu_background") ? success : false;
    success = loadPngTextureList(planetTextureList,
                                 planetTextureNumber, "planet") ? success : false;
    success = loadPngTextureList(enemyTextureList, enemyTextureNumber, "enemy") ? success : false;
    success = loadPngTextureList(dropTextureList, dropTextureNumber, "drop") ? success : false;
    success = loadPngTextureList(hitTextureList, hitTextureNumber, "hit") ? success : false;
    success = loadPngTextureList(eggTextureList, eggTextureNumber, "egg") ? success : false;

    if (!success) {
        throw std::invalid_argument("could not open some texture files");
    }
}

GLuint txtGetMainMenuBackgroundTexture() {
    return menuBackgroundTexture;
}

GLuint txtGetEggTexture(int index) {
    index = index >= 0 && index < eggTextureNumber ? index : random(0, eggTextureNumber - 1);
    return eggTextureList[index];
}

GLuint txtGetPlayerTexture() {
    return playerTexture;
}

GLuint txtGetRandomHitTexture() {
    int index = random(0, hitTextureNumber - 1);
    return hitTextureList[index];
}

int txtGetRandomPlanerTextureIndex() {
    if (random(EGG_PLANET_CHANCE, 200) == 0) {
        return EGG_PLANET_INDEX;
    } else {
        return random(0, planetTextureNumber - 1);
    }
}

GLuint txtGetPlanerTexture(int index) {
    if (index == EGG_PLANET_INDEX) {
        return txtGetEggTexture(-1);
    } else {
        bool requiredNew = index < 0 || index >= planetTextureNumber;
        index = requiredNew ? txtGetRandomPlanerTextureIndex() : index;
        return planetTextureList[index];
    }
}

GLuint txtGetEnemyTexture(int index) {
    index = index >= 0 && index < enemyTextureNumber ? index : 0;
    return enemyTextureList[index];
}

GLuint txtGetDropTexture(int index) {
    index = index >= 0 && index < dropTextureNumber ? index : 0;
    return dropTextureList[index];
}





//
// Created by wiskiw on 05.12.17.
//


#include "bullet-list.h"

// https://www.allturtles.com/turtle-species/


SW_Bullet bulletsGetSideneckBullet() {
    SW_Bullet sideneck;

    sideneck.color = {255, 255, 0}; // RGBA
    sideneck.damage = 5;
    sideneck.speed.y = 7;

    return sideneck;
}


// enemy 1 bullet
SW_Bullet bulletsGetDiamondbackBullet() {
    SW_Bullet diamondback;
    diamondback.color = {255, 0, 255}; // RGBA
    diamondback.speed.y = -5;
    diamondback.damage = 0.5;
    return diamondback;
}
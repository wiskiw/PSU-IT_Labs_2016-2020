//
// Created by wiskiw on 05.12.17.
//

#include <iostream>
#include "gpeGun.h"

void gpeGunUpdateShootingDelay(SW_Gun *gun) {
    switch (gun->state){
        case GUN_STATE_RELOAD:
            // reload
            gun->waitBeforeShoot--;
            if (gun->waitBeforeShoot <= 0) {
                gun->state = GUN_STATE_OK;
                gun->ammorLeft = gun->ammorSize;
            }
            break;
        case GUN_STATE_SHOOTING_DELAY:
            // задержка после выстрела
            gun->waitBeforeShoot--;
            if (gun->waitBeforeShoot <= 0) {
                gun->state = GUN_STATE_OK;
            }
            break;
    }

}

SW_Bullet gpeGunShoot(SW_Gun *gun, SW_Pos position) {
    if (gun->state == GUN_STATE_OK){
        // ready
        if (gun->ammorLeft <= 0) {
            gun->state = GUN_STATE_RELOAD;
            gun->waitBeforeShoot = gun->reloadTicks;
        } else {
            gun->bullet.state = BULLET_STATE_NORMAL;
            gun->bullet.pos = position;

            gun->ammorLeft--;
            gun->state = GUN_STATE_SHOOTING_DELAY;
            gun->waitBeforeShoot = gun->gunSpeed;

            return gun->bullet;
        }
    }
    SW_Bullet nullBullet;
    nullBullet.state = BULLET_STATE_UNDEFINED;
    return nullBullet;
}
//
// Created by wiskiw on 05.12.17.
//

#include "gun-list.h"

// http://cattime.com/cat-breeds


// default player gun
SW_Gun gunsGetBengalGun(){
    SW_Gun bengal;
    bengal.gunSpeed = 10;
    bengal.ammorSize = 50; // размер обоймы
    bengal.ammorLeft = 50; // изначально кол-во патронов в обойме
    bengal.reloadTicks = 0; // длительность перезарядки
    return bengal;
}


// enemy 1 gun
SW_Gun gunsGetHimalayanGun(){
    SW_Gun himalayan;
    himalayan.gunSpeed = 15; // задержка между выстрелами
    himalayan.ammorSize = 15; // размер обоймы
    himalayan.ammorLeft = 15; // изначально кол-во патронов в обойме
    himalayan.reloadTicks = 150; // длительность перезарядки
    return himalayan;
}


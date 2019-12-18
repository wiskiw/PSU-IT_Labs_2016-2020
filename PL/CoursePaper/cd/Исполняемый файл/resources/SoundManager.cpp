//
// Created by wiskiw on 10.12.17.
//

#include <SFML/Audio.hpp>
#include <iostream>
#include "SoundManager.h"
#include "../utils/Utils.h"

const std::string SOUND_PATH = "resources/sound/";

struct SW_Sound {
    sf::SoundBuffer buffer;
    sf::Sound sound;
};

SW_Sound gun1;
SW_Sound gun2;
SW_Sound buttonSelect;
SW_Sound buttonClick;
SW_Sound damage;
SW_Sound enemyDead;
SW_Sound takeDrop;

bool loadSound(sf::SoundBuffer &buffer, sf::Sound &sound, const std::string &filename) {
    if (!buffer.loadFromFile(SOUND_PATH + filename)) {
        std::cout << "[ERR] Sound file not found: " << filename << std::endl;
        return false;
    } else {
        sound.setBuffer(buffer);
        return true;
    }
}

void sndInit(GameFieldStruct *thisGame) {
    if (!PREF_ENABLE_SOUNDS) {
        return;
    }

    bool success = true;

    success = loadSound(gun1.buffer, gun1.sound, "gun_0.wav") ? success : false;
    success = loadSound(gun2.buffer, gun2.sound, "gun_1.wav") ? success : false;
    success = loadSound(damage.buffer, damage.sound, "player_hit.wav") ? success : false;
    success = loadSound(buttonSelect.buffer, buttonSelect.sound, "button_select.wav") ? success : false;
    success = loadSound(buttonClick.buffer, buttonClick.sound, "button_click.wav") ? success : false;
    success = loadSound(enemyDead.buffer, enemyDead.sound, "enemy_dead.wav") ? success : false;
    success = loadSound(takeDrop.buffer, takeDrop.sound, "take_drop.wav") ? success : false;

    if (!success) {
        throw std::invalid_argument("could not open some sound files");
    }
}

void sndPlayerShot() {
    gun1.sound.setVolume(30);
    gun2.sound.setPitch(random(0.35f, 0.38f));
    gun1.sound.play();
}

void sndEnemyShot() {
    gun2.sound.setVolume(80);
    gun2.sound.setPitch(1.0);
    gun2.sound.play();
}

void sndPlayerDamage() {
    damage.sound.setVolume(60);
    damage.sound.setPitch(random(0.2f, 0.5f));
    damage.sound.play();
}

void sndEnemyDamage() {
    damage.sound.setVolume(60);
    damage.sound.setPitch(random(0.2f, 0.5f));
    damage.sound.play();
}

void sndEnemyDead() {
    enemyDead.sound.setVolume(50);
    enemyDead.sound.setPitch(random(1.5f, 2.1f));
    enemyDead.sound.play();
}

void sndButtonSelect() {
    buttonSelect.sound.setVolume(80);
    buttonSelect.sound.play();
}

void sndButtonClick() {
    buttonClick.sound.setVolume(85);
    buttonClick.sound.play();
}

void sndTakeDrop() {
    takeDrop.sound.setVolume(85);
    takeDrop.sound.play();
}


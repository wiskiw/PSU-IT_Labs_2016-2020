//
// Created by wiskiw on 10.12.17.
//

#include "MusicManager.h"
#include "../utils/Utils.h"
#include <SFML/Audio.hpp>
#include <iostream>

/*
    OST:

    https://soundcloud.com/sverigestelevision/sets/kung-fury

 */


const std::string MUSIC_PATH = "../resources/music/";
typedef int MusicType;


sf::Music *currentMusic;
MusicType currentMusicType = -1;
int currentVolume = RM_MUSIC_VOLUME_MIDLE;
float currentPitch = 1;
bool isCurrentLooped = false;


const MusicType MT_GAMEPLAY = 1;
const int GAMEPLAY_MUSIC_LIST_SIZE = 4;
int lastGameplayMusicIndex = -1;
sf::Music gameplayMusicList[GAMEPLAY_MUSIC_LIST_SIZE];


const MusicType MT_MENU = 2;
const int MENU_MUSIC_LIST_SIZE = 2;
int lastMenuMusicIndex = -1;
sf::Music menuMusicList[GAMEPLAY_MUSIC_LIST_SIZE];


bool loadMusic(sf::Music &musicObj, const std::string &filename) {
    if (!musicObj.openFromFile(MUSIC_PATH + filename)) {
        std::cout << "[ERR] Music file not found: " << filename << std::endl;
        return false;
    } else {
        return true;
    }
}

sf::Music *getMusic(bool stopPlay, sf::Music *musicList, int musicListSize, int *lastIndex) {
    sf::Music *music;
    if (*lastIndex != -1 && stopPlay) {
        music = &musicList[*lastIndex];
        music->stop();
    }

    if (*lastIndex == -1 || stopPlay) {
        *lastIndex = random(0, musicListSize - 1);
    }
    return &musicList[*lastIndex];
}

sf::Music *getMusicByType(bool stopPlay, MusicType type) {
    switch (type) {
        case MT_GAMEPLAY:
            return getMusic(stopPlay, gameplayMusicList, GAMEPLAY_MUSIC_LIST_SIZE, &lastGameplayMusicIndex);
        case MT_MENU:
            return getMusic(stopPlay, menuMusicList, MENU_MUSIC_LIST_SIZE, &lastMenuMusicIndex);
    }
}

void playCurrent() {
    currentMusic->setPitch(currentPitch);
    currentMusic->setVolume(currentVolume);
    currentMusic->setLoop(isCurrentLooped);
    currentMusic->play();
}

void mscPlayMenuMusic(bool stopPlay, int volume) {
    currentVolume = volume;
    if (currentMusicType == MT_MENU) {
        currentMusic->setVolume(volume);
    } else {
        currentMusicType = MT_MENU;
        currentMusic = getMusicByType(stopPlay, MT_MENU);
        currentPitch = 0.80f;
        isCurrentLooped = false;

        playCurrent();
    }
}

void mscPauseCurrentMusic() {
    if (currentMusicType != -1) {
        currentMusic->pause();
    }
}

void mscPlayGameplayMusic(bool stopPlay, int volume) {
    currentVolume = volume;
    if (currentMusicType == MT_GAMEPLAY) {
        currentMusic->setVolume(volume);
    } else {
        currentMusicType = MT_GAMEPLAY;
        currentMusic = getMusicByType(stopPlay, MT_GAMEPLAY);

        currentPitch = 1;
        isCurrentLooped = false;

        playCurrent();
    }

}

bool loadMusicList(int size, sf::Music *list, const std::string &namePrefix) {
    for (int i = 0; i < size; ++i) {
        std::string filename = namePrefix + std::to_string(i) + ".ogg";
        if (!loadMusic(list[i], filename)) {
            return false;
        }
    }
    return true;
}

void mscInit(GameFieldStruct *thisGame) {
    bool success = true;

    success = loadMusicList(MENU_MUSIC_LIST_SIZE, menuMusicList, "music_pause_menu_") ? success : false;
    success = loadMusicList(GAMEPLAY_MUSIC_LIST_SIZE, gameplayMusicList, "gameplay_music_") ? success : false;

    if (!success) {
        throw std::invalid_argument("could not open some music files");
    }
}

void mscCheckIfMusicEnd() {
    if (currentMusicType != -1) {
        std::cout << std::flush;
        if (!isCurrentLooped && currentMusic->getStatus() == sf::Music::Playing &&
            currentMusic->getDuration().asMilliseconds() - currentMusic->getPlayingOffset().asMilliseconds() <=
            PREF_MINIMAL_MILLISECONDS_MUSIC_OFFSET_TO_REPLAY) {
            currentMusic = getMusicByType(true, currentMusicType);
            playCurrent();
        }
    }
}


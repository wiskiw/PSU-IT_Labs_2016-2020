//
// Created by wiskiw on 10.12.17.
//

#ifndef COURSE_PAPER_RESOURCEMANAGER_H
#define COURSE_PAPER_RESOURCEMANAGER_H


#include "../GameStructs.h"

const int RM_MUSIC_VOLUME_LOW = 30;
const int RM_MUSIC_VOLUME_MIDLE = 45;
const int RM_MUSIC_VOLUME_HIGH = 60;

void mscInit(GameFieldStruct *thisGame);

void mscPlayMenuMusic(bool stopPlay, int volume);

void mscPlayGameplayMusic(bool stopPlay, int volume);

void mscPauseCurrentMusic();

void mscCheckIfMusicEnd();

#endif //COURSE_PAPER_RESOURCEMANAGER_H

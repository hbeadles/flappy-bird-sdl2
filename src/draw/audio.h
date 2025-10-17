//
// Created by Hayden Beadles on 10/12/25.
//

#ifndef FLAPPY_BIRD_SDL2_AUDIO_H
#define FLAPPY_BIRD_SDL2_AUDIO_H

#include <system/common.h>
void loadAudio();
Mix_Chunk* loadSound(const char* filename, const char* soundName);
Mix_Music* loadMusic(const char* filename, const char* musicName);
void playSound(const char* soundName);

#endif //FLAPPY_BIRD_SDL2_AUDIO_H
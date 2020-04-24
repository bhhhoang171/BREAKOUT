#ifndef AUDIO_H_
#define AUDIO_H_

#include"commonfunction.h"

class Audio
{
public:
    Audio();
    ~Audio();
    void LoadAudio();
    void GetAudioError();
    void FreeAudio();
    Mix_Chunk* score;
    Mix_Chunk* win_sfx;
    Mix_Chunk* lose_sfx;
    Mix_Chunk* menu_tick;
    Mix_Chunk* explo;
    Mix_Chunk* icebreak;
    Mix_Chunk* paddle;
};

#endif // AUDIO_H_

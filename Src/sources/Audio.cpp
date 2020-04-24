#include"Audio.h"

Audio::Audio()
{
    score = nullptr;
    win_sfx = nullptr;
    lose_sfx = nullptr;
    menu_tick = nullptr;
    explo = nullptr;
    icebreak = nullptr;
    paddle = nullptr;
}

Audio::~Audio()
{
    FreeAudio();
}

void Audio::LoadAudio()
{
    score = Mix_LoadWAV("data/audio/score.wav");
    if(score == nullptr)
        GetAudioError();
    win_sfx = Mix_LoadWAV("data/audio/win.wav");
    if(win_sfx == nullptr)
        GetAudioError();
    lose_sfx = Mix_LoadWAV("data/audio/lose.wav");
    if(lose_sfx == nullptr)
        GetAudioError();
    menu_tick = Mix_LoadWAV("data/audio/menu_tick.wav");
    if(menu_tick == nullptr)
        GetAudioError();
    explo = Mix_LoadWAV("data/audio/explosion.wav");
    if(explo == nullptr)
        GetAudioError();
    icebreak = Mix_LoadWAV("data/audio/icebreak.wav");
    if(icebreak == nullptr)
        GetAudioError();
    paddle = Mix_LoadWAV("data/audio/paddle.wav");
    if(paddle == nullptr)
        GetAudioError();
}

void Audio::GetAudioError()
{
    std::cout << "Load Audio Error: " << Mix_GetError() << std::endl;
    SDL_Quit();
    exit(1);
}

void Audio::FreeAudio()
{
    if(score != nullptr)
    {
        Mix_FreeChunk(score);
        score = nullptr;
    }
    if(win_sfx != nullptr)
    {
        Mix_FreeChunk(win_sfx);
        win_sfx = nullptr;
    }
    if(lose_sfx != nullptr)
    {
        Mix_FreeChunk(lose_sfx);
        lose_sfx = nullptr;
    }
    if(menu_tick != nullptr)
    {
        Mix_FreeChunk(menu_tick);
        menu_tick = nullptr;
    }
    if(explo != nullptr)
    {
        Mix_FreeChunk(explo);
        explo = nullptr;
    }
    if(icebreak != nullptr)
    {
        Mix_FreeChunk(icebreak);
        icebreak = nullptr;
    }
    if(paddle != nullptr)
    {
        Mix_FreeChunk(paddle);
        paddle = nullptr;
    }
}


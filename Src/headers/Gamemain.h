#ifndef GAME_MAIN_H_
#define GAME_MAIN_H_

#include"commonfunction.h"
#include"Board.h"
#include"Paddle.h"
#include"Ball.h"
#include"Audio.h"
#include"PictureLib.h"

Audio* audio = nullptr;
PictureLib* pictures = nullptr;
TTF_Font* g_font = nullptr;

int life = 0;
Text g_text;
std::fstream fp;
long long highscore;
int mul = 0;

Board* board = nullptr;
Paddle* pad = nullptr;
Ball* ball = nullptr;

bool is_quit = false;
bool win = false;
bool choosecontrol = false;
bool started = false;
bool paused = false;
bool musicplaying = false;
bool tut = false;
bool message = false;

void InitData();
void logSDLError(const std::string &msg, const bool& fatal = false);
void LoadGUI();
void close();
void Menu();
void SetDifficulty();
void Difficulty(const float& padspeed, const float& ballspeed,
                const int& bomb, const int& ice,
                const int& horarr, const int& verarr,
                const int& mul_, const int& life_);
void ChooseControl();
void Control(const bool& mouse);
void PlayAgain();
void Game();

#endif

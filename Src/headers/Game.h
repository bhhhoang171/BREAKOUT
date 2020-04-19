#ifndef GAME_H_
#define GAME_H_

#include"commonfunction.h"
#include"Board.h"
#include"Paddle.h"
#include"Ball.h"
#include"Picture.h"

Picture g_background;
Picture sidepic;
Picture tutorial;
Board* board = nullptr;
Paddle* pad = nullptr;
Ball* ball = nullptr;

Picture win_;
Picture lose_;
Picture again;
Picture again1;
Picture easy;
Picture easy1;
Picture medium;
Picture medium1;
Picture hard;
Picture hard1;
Picture menu;
Picture mouse;
Picture mouse1;
Picture keyboard;
Picture keyboard1;

bool is_quit = false;
bool win = false;
bool choosecontrol = false;
bool started = false;
bool paused = false;

void InitData();
void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void LoadGUI();
void SetDifficulty();
void ChooseControl();
void Game();
void PlayAgain();
void close();

#endif // GAME_H_

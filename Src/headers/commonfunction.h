#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include<fstream>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<cstring>
#include<vector>
#include<cmath>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

static SDL_Window* g_window = nullptr;
static SDL_Renderer* g_screen = nullptr;
static SDL_Event g_event;

//SCREEN
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//so luong brick theo y hang va x cot
#define MAX_BRICK_X 12
#define MAX_BRICK_Y 10

//do lon canh le
#define SIDE_SIZE_X 16
#define SIDE_SIZE_Y 600

#define FRAME_PER_SECOND  200
#define PI 3.14159265

//do lon 1 brick
static int BRICK_WIDTH = 64;
static int BRICK_HEIGHT = 24;

static int PADDLE_WIDTH = 100;
static int PADDLE_HEIGHT = 24;

static int BALL_SIZE = 24;

#endif // COMMON_FUNCTION_H







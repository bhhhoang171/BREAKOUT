#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include<fstream>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<cstring>
#include<cmath>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

static SDL_Window* g_window = nullptr;
static SDL_Renderer* g_screen = nullptr;
static SDL_Event g_event;

//SCREEN
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

//so luong brick theo y hang va x cot
#define MAX_BRICK_X 12
#define MAX_BRICK_Y 23
#define MAX_BRICK_RESET_Y 10

//do lon canh le
#define SIDE_SIZE_X 16
#define SIDE_SIZE_Y 600

#define FRAME_PER_SECOND  120
#define PI 3.14159265

//do lon 1 brick
#define BRICK_WIDTH 64
#define BRICK_HEIGHT 24

#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 24

#define BALL_SIZE 24

#endif // COMMON_FUNCTION_H







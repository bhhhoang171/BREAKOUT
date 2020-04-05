#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include<windows.h>
#include<cstdlib>
#include<ctime>
#include<string>
#include<cstring>
#include<cmath>
#include<SDL.h>
#include<SDL_image.h>

static SDL_Window* g_window = nullptr;
static SDL_Renderer* g_screen = nullptr;
static SDL_Event g_event;


const int FRAME_PER_SECOND = 200;
//SCREEN
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//so luong brick theo y hang va x cot
#define MAX_BRICK_X 12
#define MAX_BRICK_Y 10

//do lon canh le
#define SIDE_SIZE_X 16
#define SIDE_SIZE_Y 600

#define PI 3.14159265

//do lon 1 brick
static int BRICK_SIZE_X = 64;
static int BRICK_SIZE_Y = 24;

static int PADDLE_WIDTH = 100;
static int PADDLE_HEIGHT = 24;

static int BALL_SIZE = 24;

typedef struct Input
{
    bool left_;
    bool right_;
    bool space_;
    bool mouse_;
}Input;




#endif // COMMON_FUNCTION_H







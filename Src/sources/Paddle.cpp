#include"Paddle.h"

Paddle::Paddle()
{
    PAD_SPEED = 0;
    x_pos = SCREEN_WIDTH/2 - PADDLE_WIDTH/2;
    y_pos = SCREEN_HEIGHT - PADDLE_HEIGHT;
    x_spd = 0;
    input_right = false;
    input_left = false;
    input_mouse = false;
}

Paddle::~Paddle()
{

}

void Paddle::Show(SDL_Renderer* screen)
{
    rect_.x = x_pos;
    rect_.y = y_pos;
    SDL_Rect renderquad = {rect_.x, rect_.y, PADDLE_WIDTH, PADDLE_HEIGHT};
    SDL_RenderCopy(screen, texture, nullptr, &renderquad);
}

void Paddle::PadReset()
{
    x_pos = SCREEN_WIDTH/2 - PADDLE_WIDTH/2;
    y_pos = SCREEN_HEIGHT - PADDLE_HEIGHT;
    input_left = false;
    input_right = false;
}

void Paddle::HandleInputAction(SDL_Event& event, SDL_Renderer* screen)
{
    if(input_mouse == false)
    {
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                input_right = true;
                input_left = false;
                break;
            case SDLK_LEFT:
                input_left = true;
                input_right = false;
                break;
            case SDLK_a:
                input_left = true;
                input_right = false;
                break;
            case SDLK_d:
                input_right = true;
                input_left = false;
                break;
            }
        }
        else if(event.type == SDL_KEYUP)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                input_right = false;
                break;
            case SDLK_LEFT:
                input_left = false;
                break;
            case SDLK_a:
                input_left = false;
                break;
            case SDLK_d:
                input_right = false;
                break;
            }
        }
    }
}

void Paddle::PadMove()
{
    int mouseX, mouseY;
    if(input_mouse == true)
    {
        SDL_GetMouseState(&mouseX, &mouseY);
        x_pos = mouseX - 0.5f*PADDLE_WIDTH;
        if(x_pos + PADDLE_WIDTH >= SCREEN_WIDTH - SIDE_SIZE_X)
        {
            x_spd = 0;
            x_pos =  SCREEN_WIDTH - SIDE_SIZE_X - PADDLE_WIDTH;
        }
        if(x_pos <= SIDE_SIZE_X)
        {
            x_spd = 0;
            x_pos = SIDE_SIZE_X;
        }
    }
    else
    {
        x_spd = 0;
        if(input_left == true)
        {
            x_spd = -PAD_SPEED;
        }
        else if(input_right == true)
        {
            x_spd = PAD_SPEED;
        }
        if(x_spd < 0)
        {
            if(x_pos <= SIDE_SIZE_X)
            {
                x_spd = 0;
                x_pos = SIDE_SIZE_X;
            }
        }
        else if(x_spd > 0)
        {
            if(x_pos + PADDLE_WIDTH >= SCREEN_WIDTH - SIDE_SIZE_X)
            {
                x_spd = 0;
                x_pos =  SCREEN_WIDTH - SIDE_SIZE_X - PADDLE_WIDTH;
            }
        }
        x_pos += x_spd;
    }
}















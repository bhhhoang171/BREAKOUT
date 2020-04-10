#include"Paddle.h"

Paddle::Paddle()
{
    PAD_SPEED = 0;
    x_pos = SCREEN_WIDTH/2 - PADDLE_WIDTH/2;
    y_pos = SCREEN_HEIGHT - PADDLE_HEIGHT;
    x_spd = 0;
    input_type.right_ = false;
    input_type.left_ = false;
    input_type.space_ = false;
    input_type.mouse_ = false;
}

Paddle::~Paddle()
{

}

void Paddle::Show(SDL_Renderer* des)
{
    rect_.x = x_pos;
    rect_.y = y_pos;
    SDL_Rect renderquad = {rect_.x, rect_.y, PADDLE_WIDTH, PADDLE_HEIGHT};
    SDL_RenderCopy(des, p_object, nullptr, &renderquad);
}

void Paddle::PadReset()
{
    x_pos = SCREEN_WIDTH/2 - PADDLE_WIDTH/2;
    y_pos = SCREEN_HEIGHT - PADDLE_HEIGHT;
    input_type.left_ = false;
    input_type.right_ = false;
}

void Paddle::HandleInputAction(SDL_Event event, SDL_Renderer* screen)
{
    if(input_type.mouse_ == false)
    {
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                {
                    input_type.right_ = true;
                    input_type.left_ = false;
                }
                break;
            case SDLK_LEFT:
                {
                    input_type.left_ = true;
                    input_type.right_ = false;
                }
                break;
            case SDLK_a:
                {
                    input_type.left_ = true;
                    input_type.right_ = false;
                }
                break;
            case SDLK_d:
                {
                    input_type.right_ = true;
                    input_type.left_ = false;
                }
                break;
            }
        }
        else if(event.type == SDL_KEYUP)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                {
                    input_type.right_ = false;
                }
                break;
            case SDLK_LEFT:
                {
                    input_type.left_ = false;
                }
                break;
            case SDLK_a:
                {
                    input_type.left_ = false;
                }
                break;
            case SDLK_d:
                {
                    input_type.right_ = false;
                }
                break;
            }
        }
    }
}

void Paddle::PadMove()
{
    int mouseX, mouseY;
    if(input_type.mouse_ == true)
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
        if(input_type.left_ == true)
        {
            x_spd = -PAD_SPEED;
        }
        else if(input_type.right_ == true)
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















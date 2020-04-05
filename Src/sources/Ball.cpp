#include"Ball.h"

Ball::Ball()
{
    BALL_SPEED = 0;
    x_pos = SCREEN_WIDTH/2 - BALL_SIZE/2;
    y_pos = SCREEN_HEIGHT - PADDLE_HEIGHT - BALL_SIZE;
    x_val = 0;
    y_val = 0;
    input_type.space_ = false;
    input_type.left_ = false;
    input_type.right_ = false;
}

Ball::~Ball()
{

}

void Ball::BallReset()
{
    x_pos = SCREEN_WIDTH/2 - BALL_SIZE/2;
    y_pos = SCREEN_HEIGHT - PADDLE_HEIGHT - BALL_SIZE;
    input_type.space_ = false;
}

void Ball::ShowBall(SDL_Renderer* des)
{
    rect_.x = x_pos;
    rect_.y = y_pos;
    SDL_Rect renderquad = {rect_.x, rect_.y, BALL_SIZE, BALL_SIZE};
    SDL_RenderCopy(des, p_object, nullptr, &renderquad);
}


void Ball::HandleInputAction(SDL_Event event, SDL_Renderer* screen)
{
    if(event.type == SDL_KEYDOWN)
    {
        if(event.key.keysym.sym == SDLK_SPACE)
        {
            input_type.space_ = true;
        }
    }
    else if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        if(event.button.button == SDL_BUTTON_LEFT)
        {
            input_type.space_ = true;
        }
    }
}

void Ball::BallMove(Paddle* pad, bool& is_quit, Brick_data** brickdata, int& brickcount)
{
    if(input_type.space_ == false)
    {
        x_pos = pad->Getxpos() + PADDLE_WIDTH/2 - BALL_SIZE/2;
        y_pos = pad->Getypos() - BALL_SIZE;
    }
    if(input_type.space_ == true)
    {
        BallCollision(pad, is_quit, brickdata, brickcount);
        x_pos += x_val;
        y_pos += y_val;
    }
}

void Ball::BallCollision(Paddle* pad, bool& is_quit, Brick_data** brickdata, int& brickcount)
{
    float ballcenter_x = x_pos + 0.5f*BALL_SIZE;
    float ballcenter_y = y_pos + 0.5f*BALL_SIZE;
    //xu ly cham paddle
    if(y_pos >= SCREEN_HEIGHT - PADDLE_HEIGHT - BALL_SIZE)
    {
        float padcenter_x = pad->Getxpos() + 0.5f*PADDLE_WIDTH;
        float padcenter_y = pad->Getypos() + 0.5f*PADDLE_HEIGHT;

        if(y_pos >= SCREEN_HEIGHT - BALL_SIZE)
        {
            is_quit = true;
            return;
        }
        else if (x_pos <= pad->Getxpos() + PADDLE_WIDTH &&
            x_pos + BALL_SIZE >= pad->Getxpos() &&
            y_pos <= pad->Getypos() + PADDLE_HEIGHT &&
            y_pos + BALL_SIZE >= pad->Getypos())
        {
            float ymin = 0;
            if (pad->Getypos() > y_pos)
            {
                ymin = pad->Getypos();
            }
            else
            {
                ymin = y_pos;
            }

            float ymax = 0;
            if (pad->Getypos() + PADDLE_HEIGHT < y_pos + BALL_SIZE)
            {
                ymax = pad->Getypos() + PADDLE_HEIGHT;
            }
            else
            {
                ymax = y_pos + BALL_SIZE;
            }

            float ysize = ymax - ymin;

            float xmin = 0;
            if (pad->Getxpos() > x_pos)
            {
                xmin = pad->Getxpos();
            }
            else
            {
                xmin = x_pos;
            }

            float xmax = 0;
            if (pad->Getxpos() + PADDLE_WIDTH < x_pos + BALL_SIZE)
            {
                xmax = pad->Getxpos() + PADDLE_WIDTH;
            }
            else
            {
                xmax = x_pos + BALL_SIZE;
            }

            float xsize = xmax - xmin;

            if (xsize > ysize)
            {
                    // Top
                y_pos -= ysize + 0.01f;
                int fix = abs(padcenter_x - ballcenter_x);
                if(x_val > 0)
                {
                    x_val = sqrt(2) * BALL_SPEED * cos((75-fix) * PI / 180);
                    y_val = -sqrt(2) * BALL_SPEED * sin((75-fix) * PI / 180);
                }
                else
                {
                    x_val = -sqrt(2) * BALL_SPEED * cos((75-fix) * PI / 180);
                    y_val = -sqrt(2) * BALL_SPEED * sin((75-fix) * PI / 180);
                }
            }
            else
            {
                if (ballcenter_x < padcenter_x)
                {
                    // Left
                    x_pos -= xsize + 0.01f;
                    pad->input_type.left_ = false;
                    pad->input_type.right_ = false;
                    BallBrickResponse(0);
                    return;
                }
                else
                {
                    // Right
                    x_pos += xsize + 0.01f;
                    pad->input_type.right_ = false;
                    pad->input_type.left_ = false;
                    BallBrickResponse(2);
                    return;
                }
            }
            return;
        }
    }

    //xu ly cham side
    if(x_pos <= SIDE_SIZE_X)
    {
        if(x_val < 0) x_val = -x_val;
        return;
    }
    else if(x_pos + BALL_SIZE >= SCREEN_WIDTH - SIDE_SIZE_X)
    {
        if(x_val > 0) x_val = -x_val;
        return;
    }

    //xu ly cham tran
    else if(y_pos <= 0)
    {
        y_val = -y_val;
        return;
    }

    //xu ly cham brick
    else
    {
        for (int i = 0; i < MAX_BRICK_Y; i++)
        {
            for (int j = 0; j < MAX_BRICK_X; j++)
            {
                if (brickdata[i][j].state)
                {
                    float brickcenter_x = brickdata[i][j].x_pos + 0.5f*BRICK_SIZE_X;
                    float brickcenter_y = brickdata[i][j].y_pos + 0.5f*BRICK_SIZE_Y;

                    if (x_pos <= brickdata[i][j].x_pos + BRICK_SIZE_X &&
                        x_pos + BALL_SIZE >= brickdata[i][j].x_pos &&
                        y_pos <= brickdata[i][j].y_pos + BRICK_SIZE_Y &&
                        y_pos + BALL_SIZE >= brickdata[i][j].y_pos)
                    {

                        brickdata[i][j].state = false;
                        --brickcount;
                        float ymin = 0;
                        if (brickdata[i][j].y_pos > y_pos)
                        {
                            ymin = brickdata[i][j].y_pos;
                        }
                        else
                        {
                            ymin = y_pos;
                        }

                        float ymax = 0;
                        if (brickdata[i][j].y_pos + BRICK_SIZE_Y < y_pos + BALL_SIZE)
                        {
                            ymax = brickdata[i][j].y_pos + BRICK_SIZE_Y;
                        }
                        else
                        {
                            ymax = y_pos + BALL_SIZE;
                        }

                        float ysize = ymax - ymin;

                        float xmin = 0;
                        if (brickdata[i][j].x_pos > x_pos)
                        {
                            xmin = brickdata[i][j].x_pos;
                        }
                        else
                        {
                            xmin = x_pos;
                        }

                        float xmax = 0;
                        if (brickdata[i][j].x_pos + BRICK_SIZE_X < x_pos + BALL_SIZE)
                        {
                            xmax = brickdata[i][j].x_pos + BRICK_SIZE_X;
                        }
                        else
                        {
                            xmax = x_pos + BALL_SIZE;
                        }

                        float xsize = xmax - xmin;

                        if (xsize > ysize)
                        {
                            if (ballcenter_y > brickcenter_y)
                            {
                                // Bottom
                                y_pos += ysize + 0.01f;
                                BallBrickResponse(3);
                            }
                            else
                            {
                                // Top
                                y_pos -= ysize + 0.01f;
                                BallBrickResponse(1);
                            }
                        }
                        else
                        {
                            if (ballcenter_x < brickcenter_x)
                            {
                                // Left
                                x_pos -= xsize + 0.01f;
                                BallBrickResponse(0);
                            }
                            else
                            {
                                // Right
                                x_pos += xsize + 0.01f;
                                BallBrickResponse(2);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Ball::BallBrickResponse(int dirindex) {

    int mulx = 1;
    int muly = 1;

    if (x_val > 0) {
        if (y_val > 0) {
            if (dirindex == 0 || dirindex == 3)
            {
                mulx = -1;
            }
            else
            {
                muly = -1;
            }
        }
        else if (y_val < 0)
        {
            if (dirindex == 0 || dirindex == 1)
            {
                mulx = -1;
            }
            else
            {
                muly = -1;
            }
        }
    }
    else if (x_val < 0)
    {
        if (y_val > 0) {
            if (dirindex == 2 || dirindex == 3)
            {
                mulx = -1;
            }
            else
            {
                muly = -1;
            }
        }
        else if (y_val < 0)
        {
            if (dirindex == 1 || dirindex == 2)
            {
                mulx = -1;
            }
            else
            {
                muly = -1;
            }
        }
    }
    x_val *= mulx;
    y_val *= muly;
    return;
}











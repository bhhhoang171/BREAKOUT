#include"Ball.h"

Ball::Ball()
{
    BALL_SPEED = 0;
    x_pos = SCREEN_WIDTH/2 - BALL_SIZE/2;
    y_pos = SCREEN_HEIGHT - PADDLE_HEIGHT - BALL_SIZE;
    x_spd = 0;
    y_spd = 0;
    input_space = false;
}

Ball::~Ball()
{

}

void Ball::BallReset()
{
    x_pos = SCREEN_WIDTH/2 - BALL_SIZE/2;
    y_pos = SCREEN_HEIGHT - PADDLE_HEIGHT - BALL_SIZE;
    input_space = false;
}

void Ball::ShowBall(SDL_Renderer* screen, Picture& ball_)
{
    ball_.SetposRect(x_pos, y_pos);
    ball_.Render(screen);
}


void Ball::HandleInputAction(SDL_Event& event, SDL_Renderer* screen, Mix_Chunk* chunk)
{
    if(event.type == SDL_KEYDOWN)
    {
        if(event.key.keysym.sym == SDLK_SPACE)
        {
            input_space = true;
            Mix_PlayChannel(-1, chunk, 0);
        }
    }
    else if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        if(event.button.button == SDL_BUTTON_LEFT)
        {
            input_space = true;
            Mix_PlayChannel(-1, chunk, 0);
        }
    }
}

void Ball::BallMove(Paddle* pad, bool& is_quit, Brick_data** brickdata, Board* board, Audio* audio, int& life)
{
    if(input_space == false)
    {
        x_pos = pad->Getxpos() + PADDLE_WIDTH/2 - BALL_SIZE/2;
        y_pos = pad->Getypos() - BALL_SIZE;
    }
    if(input_space == true)
    {
        BallCollision(pad, is_quit, brickdata, board, audio, life);
        x_pos += x_spd;
        y_pos += y_spd;
    }
}

void Ball::BallCollision(Paddle* pad, bool& is_quit, Brick_data** brickdata, Board* board, Audio* audio, int& life)
{
    float ballcenter_x = x_pos + 0.5f*BALL_SIZE;
    float ballcenter_y = y_pos + 0.5f*BALL_SIZE;
    //Ball Paddle collision
    if(y_pos >= SCREEN_HEIGHT - PADDLE_HEIGHT - BALL_SIZE)
    {
        float padcenter_x = pad->Getxpos() + 0.5f*PADDLE_WIDTH;
        float padcenter_y = pad->Getypos() + 0.5f*PADDLE_HEIGHT;
        if(y_pos >= SCREEN_HEIGHT - BALL_SIZE)
        {
            BallReset();
            pad->PadReset();
            if(x_spd < 0)
                x_spd = -x_spd;
            --life;
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
                Mix_PlayChannel(-1, audio->paddle, 0);
                y_pos -= ysize + 0.01f;
                int fix = abs(padcenter_x - ballcenter_x);
                if(x_spd > 0)
                {
                    x_spd = sqrt(2) * BALL_SPEED * cos((75-fix) * PI / 180);
                    y_spd = -sqrt(2) * BALL_SPEED * sin((75-fix) * PI / 180);
                }
                else
                {
                    x_spd = -sqrt(2) * BALL_SPEED * cos((75-fix) * PI / 180);
                    y_spd = -sqrt(2) * BALL_SPEED * sin((75-fix) * PI / 180);
                }
            }
            else
            {
                if (ballcenter_x < padcenter_x)
                {
                    x_pos -= xsize + 0.01f;
                    pad->input_left = false;
                    pad->input_right = false;
                    BallResponse('L');
                    return;
                }
                else
                {
                    x_pos += xsize + 0.01f;
                    pad->input_right = false;
                    pad->input_left = false;
                    BallResponse('R');
                    return;
                }
            }
            return;
        }
    }

    //Ball Side collision
    if(x_pos <= SIDE_SIZE_X)
    {
        if(x_spd < 0) x_spd = -x_spd;
        return;
    }
    else if(x_pos + BALL_SIZE >= SCREEN_WIDTH - SIDE_SIZE_X)
    {
        if(x_spd > 0) x_spd = -x_spd;
        return;
    }
    else if(y_pos <= 0)
    {
        y_spd = -y_spd;
        return;
    }

    //Ball Brick collision
    int col = (x_pos - SIDE_SIZE_X) / BRICK_WIDTH;
    int row = y_pos / BRICK_HEIGHT;
    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            if(row+i >= 0 && col+j >= 0
            && row+i < MAX_BRICK_Y && col+j < 12)
            {
                if (brickdata[row+i][col+j].state > 0)
                {
                    float brickcenter_x = brickdata[row+i][col+j].x_pos + 0.5f*BRICK_WIDTH;
                    float brickcenter_y = brickdata[row+i][col+j].y_pos + 0.5f*BRICK_HEIGHT;

                    if (x_pos <= brickdata[row+i][col+j].x_pos + BRICK_WIDTH &&
                        x_pos + BALL_SIZE >= brickdata[row+i][col+j].x_pos &&
                        y_pos <= brickdata[row+i][col+j].y_pos + BRICK_HEIGHT &&
                        y_pos + BALL_SIZE >= brickdata[row+i][col+j].y_pos)
                    {
                        board->Explosion(row+i, col+j, audio);
                        float ymin = 0;
                        if (brickdata[row+i][col+j].y_pos > y_pos)
                        {
                            ymin = brickdata[row+i][col+j].y_pos;
                        }
                        else
                        {
                            ymin = y_pos;
                        }

                        float ymax = 0;
                        if (brickdata[row+i][col+j].y_pos + BRICK_HEIGHT < y_pos + BALL_SIZE)
                        {
                            ymax = brickdata[row+i][col+j].y_pos + BRICK_HEIGHT;
                        }
                        else
                        {
                            ymax = y_pos + BALL_SIZE;
                        }

                        float ysize = ymax - ymin;

                        float xmin = 0;
                        if (brickdata[row+i][col+j].x_pos > x_pos)
                        {
                            xmin = brickdata[row+i][col+j].x_pos;
                        }
                        else
                        {
                            xmin = x_pos;
                        }

                        float xmax = 0;
                        if (brickdata[row+i][col+j].x_pos + BRICK_WIDTH < x_pos + BALL_SIZE)
                        {
                            xmax = brickdata[row+i][col+j].x_pos + BRICK_WIDTH;
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
                                BallResponse('B');
                            }
                            else
                            {
                                // Top
                                y_pos -= ysize + 0.01f;
                                BallResponse('T');
                            }
                        }
                        else
                        {
                            if (ballcenter_x < brickcenter_x)
                            {
                                // Left
                                x_pos -= xsize + 0.01f;
                                BallResponse('L');
                            }
                            else
                            {
                                // Right
                                x_pos += xsize + 0.01f;
                                BallResponse('R');
                            }
                        }
                    }
                }
            }
        }
    }
}

void Ball::BallResponse(const char& direction)
{
    if (x_spd > 0) {
        if (y_spd > 0) {
            if (direction == 'L' || direction == 'B')
            {
                x_spd = -x_spd;
            }
            else
            {
                y_spd = -y_spd;
            }
        }
        else if (y_spd < 0)
        {
            if (direction == 'L' || direction == 'T')
            {
                x_spd = -x_spd;
            }
            else
            {
                y_spd = -y_spd;
            }
        }
    }
    else if (x_spd < 0)
    {
        if (y_spd > 0) {
            if (direction == 'R' || direction == 'B')
            {
                x_spd = -x_spd;
            }
            else
            {
                y_spd = -y_spd;
            }
        }
        else if (y_spd < 0)
        {
            if (direction == 'T' || direction == 'R')
            {
                x_spd = -x_spd;
            }
            else
            {
                y_spd = -y_spd;
            }
        }
    }
    return;
}











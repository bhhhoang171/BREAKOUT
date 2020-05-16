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
    else
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
    board->update = false;
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
            board->update = true;
            float y_low = 0;
            if (pad->Getypos() > y_pos)
            {
                y_low = pad->Getypos();
            }
            else
            {
                y_low = y_pos;
            }
            float y_high = 0;
            if (pad->Getypos() + PADDLE_HEIGHT < y_pos + BALL_SIZE)
            {
                y_high = pad->Getypos() + PADDLE_HEIGHT;
            }
            else
            {
                y_high = y_pos + BALL_SIZE;
            }

            float y_size = y_high - y_low;

            float x_low = 0;
            if (pad->Getxpos() > x_pos)
            {
                x_low = pad->Getxpos();
            }
            else
            {
                x_low = x_pos;
            }

            float x_high = 0;
            if (pad->Getxpos() + PADDLE_WIDTH < x_pos + BALL_SIZE)
            {
                x_high = pad->Getxpos() + PADDLE_WIDTH;
            }
            else
            {
                x_high = x_pos + BALL_SIZE;
            }

            float x_size = x_high - x_low;

            if (x_size > y_size)
            {
                Mix_PlayChannel(-1, audio->paddle, 0);
                y_pos -= y_size + 0.01f;
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
                return;
            }
            else
            {
                if (ballcenter_x < padcenter_x)
                {
                    x_pos -= x_size + 0.01f;
                    pad->input_left = false;
                    pad->input_right = false;
                    BallResponse(LEFT);
                    return;
                }
                else
                {
                    x_pos += x_size + 0.01f;
                    pad->input_right = false;
                    pad->input_left = false;
                    BallResponse(RIGHT);
                    return;
                }
            }
            return;
        }
    }

    //Ball Side collision
    if(x_pos <= SIDE_SIZE_X)
    {
        x_pos = SIDE_SIZE_X + 0.01f;
        if(x_spd < 0)
            BallResponse(RIGHT);
        return;
    }
    else if(x_pos + BALL_SIZE >= SCREEN_WIDTH - SIDE_SIZE_X)
    {
        x_pos = SCREEN_WIDTH - SIDE_SIZE_X - BALL_SIZE - 0.01f;
        if(x_spd > 0)
            BallResponse(LEFT);
        return;
    }
    else if(y_pos <= 0)
    {
        y_pos = 0.01f;
        BallResponse(BOTTOM);
        return;
    }

    //Ball Brick collision
    int col = (x_pos - SIDE_SIZE_X) / BRICK_WIDTH;
    int row = y_pos / BRICK_HEIGHT;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if(row+i >= 0 && col+j >= 0
            && row+i < MAX_BRICK_Y && col+j < 12)
            {
                if (brickdata[row+i][col+j].state != NULL)
                {
                    float brickcenter_x = brickdata[row+i][col+j].x_pos + 0.5f*BRICK_WIDTH;
                    float brickcenter_y = brickdata[row+i][col+j].y_pos + 0.5f*BRICK_HEIGHT;

                    if (x_pos <= brickdata[row+i][col+j].x_pos + BRICK_WIDTH &&
                        x_pos + BALL_SIZE >= brickdata[row+i][col+j].x_pos &&
                        y_pos <= brickdata[row+i][col+j].y_pos + BRICK_HEIGHT &&
                        y_pos + BALL_SIZE >= brickdata[row+i][col+j].y_pos)
                    {
                        board->Explosion(row+i, col+j, audio);
                        float y_low = 0;
                        if (brickdata[row+i][col+j].y_pos > y_pos)
                        {
                            y_low = brickdata[row+i][col+j].y_pos;
                        }
                        else
                        {
                            y_low = y_pos;
                        }

                        float y_high = 0;
                        if (brickdata[row+i][col+j].y_pos + BRICK_HEIGHT < y_pos + BALL_SIZE)
                        {
                            y_high = brickdata[row+i][col+j].y_pos + BRICK_HEIGHT;
                        }
                        else
                        {
                            y_high = y_pos + BALL_SIZE;
                        }

                        float y_size = y_high - y_low;

                        float x_low = 0;
                        if (brickdata[row+i][col+j].x_pos > x_pos)
                        {
                            x_low = brickdata[row+i][col+j].x_pos;
                        }
                        else
                        {
                            x_low = x_pos;
                        }

                        float x_high = 0;
                        if (brickdata[row+i][col+j].x_pos + BRICK_WIDTH < x_pos + BALL_SIZE)
                        {
                            x_high = brickdata[row+i][col+j].x_pos + BRICK_WIDTH;
                        }
                        else
                        {
                            x_high = x_pos + BALL_SIZE;
                        }

                        float x_size = x_high - x_low;

                        if (x_size > y_size)
                        {
                            if (ballcenter_y > brickcenter_y)
                            {
                                y_pos += y_size + 0.01f;
                                BallResponse(BOTTOM);
                            }
                            else
                            {
                                y_pos -= y_size + 0.01f;
                                BallResponse(TOP);
                            }
                        }
                        else
                        {
                            if (ballcenter_x < brickcenter_x)
                            {
                                x_pos -= x_size + 0.01f;
                                BallResponse(LEFT);
                            }
                            else
                            {
                                x_pos += x_size + 0.01f;
                                BallResponse(RIGHT);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Ball::BallResponse(const int& direction)
{
    if (x_spd > 0) {
        if (y_spd > 0) {
            if (direction == LEFT || direction == BOTTOM)
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
            if (direction == LEFT || direction == TOP)
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
            if (direction == RIGHT || direction == BOTTOM)
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
            if (direction == TOP || direction == RIGHT)
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











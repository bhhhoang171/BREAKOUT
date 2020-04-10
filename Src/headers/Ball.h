#ifndef BALL_H
#define BALL_H

#include"commonfunction.h"
#include"Picture.h"
#include"Paddle.h"
#include"Board.h"

class Ball : public Picture
{
public:
    Ball();
    ~Ball();
    void ShowBall(SDL_Renderer* des);
    void BallMove(Paddle* pad, bool& is_quit, Brick_data** brickdata, int& brickcount);
    void BallReset();
    void BallCollision(Paddle* pad, bool& is_quit, Brick_data** brickdata, int& brickcount);
    void HandleInputAction(SDL_Event event, SDL_Renderer* screen);
    void BallBrickResponse(int dirindex);
    float BALL_SPEED;
    float x_pos;
    float y_pos;
    float x_spd;
    float y_spd;
    Input input_type;
};






#endif // BALL_H





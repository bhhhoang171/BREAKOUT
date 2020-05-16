#ifndef BALL_H
#define BALL_H

#include"commonfunction.h"
#include"Graphic.h"
#include"Paddle.h"
#include"Board.h"
#include"Audio.h"

class Ball
{
public:
    Ball();
    ~Ball();
    enum direction {
        TOP = 1, RIGHT = 2, BOTTOM = 3, LEFT = 4
    };
    float BALL_SPEED;
    float x_spd;
    float y_spd;
    bool input_space;
    float Getxpos() const {return x_pos;}
    float Getypos() const {return y_pos;}
    void ShowBall(SDL_Renderer* screen, Picture& ball_);
    void BallMove(Paddle* pad, bool& is_quit, Brick_data** brickdata, Board* board, Audio* audio, int& life);
    void BallReset();
    void BallCollision(Paddle* pad, bool& is_quit, Brick_data** brickdata, Board* board, Audio* audio, int& life);
    void HandleInputAction(SDL_Event& event, SDL_Renderer* screen, Mix_Chunk* chunk);
    void BallResponse(const int& direction);
private:
    float x_pos;
    float y_pos;
};


#endif // BALL_H





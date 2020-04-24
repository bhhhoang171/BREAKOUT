#ifndef BALL_H
#define BALL_H

#include"commonfunction.h"
#include"Graphic.h"
#include"Paddle.h"
#include"Board.h"
#include"Audio.h"

class Ball : public Picture
{
public:
    Ball();
    ~Ball();
    float BALL_SPEED;
    float x_spd;
    float y_spd;
    bool input_space;
    void ShowBall(SDL_Renderer* screen);
    void BallMove(Paddle* pad, bool& is_quit, Brick_data** brickdata, Board* board, Audio* audio, int& life);
    void BallReset();
    void BallCollision(Paddle* pad, bool& is_quit, Brick_data** brickdata, Board* board, Audio* audio, int& life);
    void HandleInputAction(SDL_Event& event, SDL_Renderer* screen, Mix_Chunk* chunk);
    void BallResponse(const char& direction);
private:
    float x_pos;
    float y_pos;
};


#endif // BALL_H





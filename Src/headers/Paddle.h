
#ifndef PADDLE_H
#define PADDLE_H

#include"commonfunction.h"
#include"Picture.h"

class Paddle : public Picture
{
public:
    Paddle();
    ~Paddle();
    float Getxpos() {return x_pos;}
    float Getypos() {return y_pos;}
    void Show(SDL_Renderer* des);
    void PadReset();
    void HandleInputAction(SDL_Event event, SDL_Renderer* screen);
    void PadMove();
    float PAD_SPEED;
    Input input_type;
private:
    float x_spd;
    float x_pos;
    float y_pos;
};



#endif // PADDLE_H











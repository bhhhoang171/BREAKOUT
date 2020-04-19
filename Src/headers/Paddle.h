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
    float PAD_SPEED;
    Input input_type;
    void Show(SDL_Renderer* screen);
    void PadReset();
    void HandleInputAction(SDL_Event event, SDL_Renderer* screen);
    void PadMove();
private:
    float x_spd;
    float x_pos;
    float y_pos;
};



#endif // PADDLE_H











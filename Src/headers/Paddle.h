#ifndef PADDLE_H
#define PADDLE_H

#include"commonfunction.h"
#include"Graphic.h"

class Paddle : public Picture
{
public:
    Paddle();
    ~Paddle();
    float Getxpos() const {return x_pos;}
    float Getypos() const {return y_pos;}
    float PAD_SPEED;
    bool input_left;
    bool input_right;
    bool input_mouse;
    void Show(SDL_Renderer* screen);
    void PadReset();
    void HandleInputAction(SDL_Event& event, SDL_Renderer* screen);
    void PadMove();
private:
    float x_spd;
    float x_pos;
    float y_pos;
};



#endif // PADDLE_H











#ifndef BOARD_H
#define BOARD_H
#include"commonfunction.h"
#include"Picture.h"

class Brick_pic : public Picture
{
public:
    Brick_pic() {;}
    ~Brick_pic() {;}
};

class Brick_data
{
public:
    Brick_data() {;}
    ~Brick_data() {;}
    int x_pos;
    int y_pos;
    bool state;
    int tile;
};

class Board
{

public:
    Board();
    ~Board();
    Brick_data** brickdata;
    int brickcount;
    void LoadBoard();
    void Loadtile(SDL_Renderer* screen);
    void DrawBoard(SDL_Renderer* screen);
    void Reset();
private:
    Brick_pic* brickpic;
};




#endif // BOARD_H

#ifndef BOARD_H
#define BOARD_H
#include"commonfunction.h"
#include"Graphic.h"
#include"Audio.h"

class Brick_data
{
public:
    Brick_data() { state = 0; }
    ~Brick_data() {;}
    int x_pos;
    int y_pos;
    int state;
};

class Board
{
public:
    Board();
    ~Board();
    Brick_data** brickdata;
    int brickcount;
    int bombcount;
    int icecount;
    int horcount;
    int vercount;
    long long point;
    bool update;
    void LoadBoard();
    void Loadtile(SDL_Renderer* screen);
    void DrawBoard(SDL_Renderer* screen);
    void DrawBoard1(SDL_Renderer* screen, const Picture& ball, const Picture& pad);
    void Explosion(const int& row, const int& col, Audio* audio);
    void Updateboard(SDL_Renderer* screen, const Picture& ball, const Picture& pad);
    void Reset();
    void Renderbackground(SDL_Renderer* screen) const
    {
        backgroundboard.Render(screen);
    }
private:
    Picture brickpic;
    Picture bomb;
    Picture ice;
    Picture arrowver;
    Picture arrowhor;
    Picture backgroundboard;
};




#endif // BOARD_H

#include"Board.h"

Board::Board()
{
    brickpic = new Brick_pic [4];
    brickdata = new Brick_data *[MAX_BRICK_Y];
    for(int i = 0; i < MAX_BRICK_Y; ++i)
    {
        brickdata[i] = new Brick_data [MAX_BRICK_X];
    }
    brickcount = MAX_BRICK_X * MAX_BRICK_Y;
}

Board::~Board()
{
    for(int i = 0; i < MAX_BRICK_Y; ++i)
    {
        delete [] brickdata[i];
    }
    delete [] brickdata;
    delete [] brickpic;
    brickpic = nullptr;
    brickdata = nullptr;
}

void Board::LoadBoard()
{
    srand(time(0));
    for(int i = 0; i < MAX_BRICK_Y; ++i)
    {
        for(int j = 0 ; j < MAX_BRICK_X; ++j)
        {
            brickdata[i][j].tile = rand() % 4 + 1;
            brickdata[i][j].x_pos = SIDE_SIZE_X + j*BRICK_WIDTH;
            brickdata[i][j].y_pos = i*BRICK_HEIGHT;
        }
    }
}

void Board::Loadtile(SDL_Renderer* screen)
{
    char file_img[30] = "data/pics/Brick1.png";
    for(int i = 0; i < 4; ++i)
    {
        file_img[15] = char(i+49);
        brickpic[i].LoadImg(file_img, screen);
    }

}

void Board::DrawBoard(SDL_Renderer* screen)
{
    for(int i = 0; i < MAX_BRICK_Y; ++i)
    {
        for(int j = 0; j < MAX_BRICK_X; ++j)
        {
            int val = brickdata[i][j].tile - 1;
            if(brickdata[i][j].state == true)
            {
                brickpic[val].SetposRect(brickdata[i][j].x_pos, brickdata[i][j].y_pos);
                brickpic[val].Render(screen, nullptr);
            }
        }
    }
}

void Board::Reset()
{
    for(int i = 0; i < MAX_BRICK_Y; ++i)
    {
        for(int j = 0; j < MAX_BRICK_X; ++j)
        {
            brickdata[i][j].state = true;
        }
    }
}










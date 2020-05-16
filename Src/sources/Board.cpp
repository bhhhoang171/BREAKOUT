#include"Board.h"

Board::Board()
{
    brickdata = new Brick_data *[23];
    for(int i = 0; i < 23; ++i)
    {
        brickdata[i] = new Brick_data [MAX_BRICK_X];
    }
    brickcount = MAX_BRICK_X * MAX_BRICK_RESET_Y;
    bombcount = 0;
    icecount = 0;
    horcount = 0;
    vercount = 0;
    point = 0;
}

Board::~Board()
{
    for(int i = 0; i < 23; ++i)
    {
        delete [] brickdata[i];
    }
    delete [] brickdata;
    brickdata = nullptr;
}

void Board::LoadBoard()
{
    for(int i = 0; i < 23; ++i)
    {
        for(int j = 0 ; j < MAX_BRICK_X; ++j)
        {
            brickdata[i][j].x_pos = SIDE_SIZE_X + j*BRICK_WIDTH;
            brickdata[i][j].y_pos = i*BRICK_HEIGHT;
        }
    }
}

void Board::Loadtile(SDL_Renderer* screen)
{
    arrowhor.LoadImg("data/pics/hor.png", screen);
    arrowver.LoadImg("data/pics/ver.png", screen);
    bomb.LoadImg("data/pics/bomb.png", screen);
    ice.LoadImg("data/pics/ice.png", screen);
    brickpic.LoadImg("data/pics/brick.png", screen);
    backgroundboard.LoadImg("data/pics/backgroundboard.png", screen);
    backgroundboard.SetposRect(SIDE_SIZE_X, 0);
}

void Board::DrawBoard(SDL_Renderer* screen)
{
    for(int i = 0; i < 23; ++i)
    {
        for(int j = 0; j < MAX_BRICK_X; ++j)
        {
            switch(brickdata[i][j].state)
            {
            case NORMAL:
                brickpic.SetposRect(brickdata[i][j].x_pos, brickdata[i][j].y_pos);
                brickpic.Render(screen);
                break;
            case ICE:
                ice.SetposRect(brickdata[i][j].x_pos, brickdata[i][j].y_pos);
                ice.Render(screen);
                break;
            case BOMB:
                bomb.SetposRect(brickdata[i][j].x_pos, brickdata[i][j].y_pos);
                bomb.Render(screen);
                break;
            case HORIZONTAL_ARROW:
                arrowhor.SetposRect(brickdata[i][j].x_pos, brickdata[i][j].y_pos);
                arrowhor.Render(screen);
                break;
            case VERTICAL_ARROW:
                arrowver.SetposRect(brickdata[i][j].x_pos, brickdata[i][j].y_pos);
                arrowver.Render(screen);
                break;
            }
        }
    }
}

void Board::DrawBoard1(SDL_Renderer* screen, const Picture& ball, const Picture& pad)
{
    int frame = 12;
    while(frame > 1)
    {
        backgroundboard.Render(screen);
        ball.Render(screen);
        pad.Render(screen);
        for(int i = 0; i < 23; ++i)
        {
            for(int j = 0; j < MAX_BRICK_X; ++j)
            {
                switch(brickdata[i][j].state)
                {
                case NORMAL:
                    brickpic.SetposRect(brickdata[i][j].x_pos, brickdata[i][j].y_pos - frame*2);
                    brickpic.Render(screen);
                    break;
                case ICE:
                    ice.SetposRect(brickdata[i][j].x_pos, brickdata[i][j].y_pos - frame*2);
                    ice.Render(screen);
                    break;
                case BOMB:
                    bomb.SetposRect(brickdata[i][j].x_pos, brickdata[i][j].y_pos - frame*2);
                    bomb.Render(screen);
                    break;
                case HORIZONTAL_ARROW:
                    arrowhor.SetposRect(brickdata[i][j].x_pos, brickdata[i][j].y_pos - frame*2);
                    arrowhor.Render(screen);
                    break;
                case VERTICAL_ARROW:
                    arrowver.SetposRect(brickdata[i][j].x_pos, brickdata[i][j].y_pos - frame*2);
                    arrowver.Render(screen);
                    break;
                }
            }
        }
        frame--;
        SDL_Delay(20);
        SDL_RenderPresent(screen);
    }
}

void Board::Reset()
{
    for(int i = 0; i < 23; ++i)
    {
        for(int j = 0; j < MAX_BRICK_X; ++j)
        {
            if(i >= MAX_BRICK_RESET_Y)
            {
                 brickdata[i][j].state = NULL;
            }
            else brickdata[i][j].state = NORMAL;
        }
    }
    while(bombcount > 0)
    {
        int i = rand() % 10;
        int j = rand() % 12;
        if(brickdata[i][j].state == NORMAL)
        {
            brickdata[i][j].state = BOMB;
            bombcount--;
        }
    }
    while(icecount > 0)
    {
        int i = rand() % 10;
        int j = rand() % 12;
        if(brickdata[i][j].state == NORMAL)
        {
            brickdata[i][j].state = ICE;
            icecount--;
        }
    }
    while(horcount > 0)
    {
        int i = rand() % 10;
        int j = rand() % 12;
        if(brickdata[i][j].state == NORMAL)
        {
            brickdata[i][j].state = HORIZONTAL_ARROW;
            horcount--;
        }
    }
    while(vercount > 0)
    {
        int i = rand() % 10;
        int j = rand() % 12;
        if(brickdata[i][j].state == NORMAL)
        {
            brickdata[i][j].state = HORIZONTAL_ARROW;
            vercount--;
        }
    }
}

void Board::Explosion(const int& row, const int& col, Audio* audio)
{
    if(brickdata[row][col].state == BOMB)
    {
        brickdata[row][col].state = NULL;
        brickcount--;
        point++;
        Mix_PlayChannel(-1, audio->explo, 0);
        for(int i = -1; i <= 1; ++i)
            for(int j = -1; j <= 1; ++j)
            {
                if(i != 0 || j != 0)
                {
                    if(row+i >= 0 && row+i < 23 &&
                       col+j >= 0 && col+j < MAX_BRICK_X)
                    {
                        Explosion(row+i, col+j, audio);
                        continue;
                    }
                }
            }
    }
    else if(brickdata[row][col].state == NORMAL)
    {
        brickdata[row][col].state = NULL;
        brickcount--;
        point++;
        Mix_PlayChannel(-1, audio->score, 0);
        return;
    }
    else if(brickdata[row][col].state == ICE)
    {
        brickdata[row][col].state = NORMAL;
        Mix_PlayChannel(-1, audio->icebreak, 0);
        return;
    }
    else if(brickdata[row][col].state == HORIZONTAL_ARROW)
    {
        brickdata[row][col].state = NULL;
        brickcount--;
        point++;
        Mix_PlayChannel(-1, audio->explo, 0);
        for(int i = 0; i < MAX_BRICK_X; ++i)
        {
            if(col != i)
            {
                Explosion(row, i, audio);
            }
        }
    }
    else if(brickdata[row][col].state == VERTICAL_ARROW)
    {
        brickdata[row][col].state = NULL;
        brickcount--;
        point++;
        Mix_PlayChannel(-1, audio->explo, 0);
        for(int i = 0; i < 23; ++i)
        {
            if(row != i)
            {
                Explosion(i, col, audio);
            }
        }
    }
    else if(brickdata[row][col].state == NULL)
        return;
}

void Board::Updateboard(SDL_Renderer* screen, const Picture& ball, const Picture& pad)
{
    if(brickcount < 80 && update == true)
    {
        update = false;
        brickcount += 12;
        for(int i = MAX_BRICK_Y - 1; i > 0; --i)
        {
            for(int j = 0; j < MAX_BRICK_X; ++j)
            {
                brickdata[i][j].state = brickdata[i-1][j].state;
            }
        }
        for(int j = 0; j < MAX_BRICK_X; ++j)
        {
            int r = rand() % 30;
            if(r == 2 || r == 6 || r == 10 || r == 14 || r == 13)
            {
                brickdata[0][j].state = ICE;
            }
            else if(r == 3 || r == 5)
            {
                brickdata[0][j].state = BOMB;
            }
            else if(r == 1)
            {
                brickdata[0][j].state = HORIZONTAL_ARROW;
            }
            else if(r == 0)
            {
                brickdata[0][j].state = VERTICAL_ARROW;
            }
            else brickdata[0][j].state = NORMAL;
        }
        DrawBoard1(screen, ball, pad);
    }
}






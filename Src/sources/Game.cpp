#include"commonfunction.h"
#include"Board.h"
#include"Paddle.h"
#include"Ball.h"
#include"Picture.h"

Picture g_background;
Picture sidepic;
Picture tutorial;
Board* board = nullptr;
Paddle* pad = nullptr;
Ball* ball = nullptr;
Picture win_;
Picture lose_;
Picture again;
Picture again1;
Picture easy;
Picture easy1;
Picture medium;
Picture medium1;
Picture hard;
Picture hard1;
Picture menu;
Picture mouse;
Picture mouse1;
Picture keyboard;
Picture keyboard1;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_EVERYTHING);
    if(ret < 0)
        return false;
    //cai dat chat luong
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    g_window = SDL_CreateWindow("BREAKOUT",
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SCREEN_WIDTH + 200, SCREEN_HEIGHT,
                                 SDL_WINDOW_SHOWN);
    if(g_window == nullptr)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == nullptr)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);

            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
    }
    return success;
}


void close()
{
    g_background.Free();
    sidepic.Free();
    tutorial.Free();
    win_.Free();
    lose_.Free();
    again.Free();
    again1.Free();
    menu.Free();
    easy.Free();
    easy1.Free();
    medium.Free();
    medium1.Free();
    hard1.Free();
    hard.Free();
    mouse.Free();
    mouse1.Free();
    keyboard.Free();
    keyboard1.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = nullptr;

    SDL_DestroyWindow(g_window);
    g_window = nullptr;

    delete pad;
    delete board;
    delete ball;
    ball = nullptr;
    pad = nullptr;
    board = nullptr;
    IMG_Quit();
    SDL_Quit();

}



void ChooseControl(Paddle* pad, bool& choosecontrol, bool& started)
{
    int mouseX = 0, mouseY = 0;
    unsigned int time = 0;
    while(choosecontrol && !started)
    {
        time = SDL_GetTicks();
        while(SDL_PollEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                exit(0);
            }
            else if(g_event.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&mouseX, &mouseY);
                if(mouseX >= 100 && mouseY >= 175
                && mouseX <= 412 && mouseY <= 425)
                {
                    if(g_event.button.button == SDL_BUTTON_LEFT)
                    {
                        started = true;
                        pad->input_type.mouse_ = false;
                        return;
                    }
                }
                else if(mouseX >= 600 && mouseY >= 175
                && mouseX <= 840 && mouseY <= 425)
                {
                    if(g_event.button.button == SDL_BUTTON_LEFT)
                    {
                        started = true;
                        pad->input_type.mouse_ = true;
                        return;
                    }
                }
            }
        }
        menu.Render(g_screen, nullptr);
        if(g_event.motion.x >= 100 && g_event.motion.y >= 175
        && g_event.motion.x <= 412 && g_event.motion.y <= 425)
        {
            keyboard1.Render(g_screen, nullptr);
        }
        else keyboard.Render(g_screen, nullptr);
        if(g_event.motion.x >= 600 && 175
        && g_event.motion.x <= 840 && g_event.motion.y <= 425)
        {
            mouse1.Render(g_screen, nullptr);
        }
        else mouse.Render(g_screen, nullptr);
        SDL_RenderPresent(g_screen);
        int real_time = SDL_GetTicks() - time;
        int time_one_frame = 1000/FRAME_PER_SECOND; //ms
        if(real_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_time;
            SDL_Delay(delay_time);
        }
    }
}


void SetDifficulty(Paddle* pad, Ball* ball, bool& choosecontrol, bool& started)
{

    int mouseX = 0, mouseY = 0;
    unsigned int time = 0;
    while(!choosecontrol)
    {
        time = SDL_GetTicks();
        while(SDL_PollEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                exit(0);
            }
            else if(g_event.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&mouseX, &mouseY);
                if(mouseX >= 250 && mouseY >= SCREEN_HEIGHT/2 - 120 - 42
                && mouseX <= 500 && mouseY <= SCREEN_HEIGHT/2 - 120 + 42)
                {
                    if(g_event.button.button == SDL_BUTTON_LEFT)
                    {
                        choosecontrol = true;
                        pad->PAD_SPEED = 2;
                        ball->BALL_SPEED = 1.5;
                        ball->x_spd = ball->BALL_SPEED;
                        ball->y_spd = -ball->BALL_SPEED;
                        ChooseControl(pad, choosecontrol, started);
                        return;
                    }
                }
                else if(mouseX >= (SCREEN_WIDTH+200)/2 - 125 && mouseY >= SCREEN_HEIGHT/2 - 42
                && mouseX <= (SCREEN_WIDTH+200)/2 + 125 && mouseY <= SCREEN_HEIGHT/2 + 42)
                {
                    if(g_event.button.button == SDL_BUTTON_LEFT)
                    {
                        choosecontrol = true;
                        pad->PAD_SPEED = 2.5;
                        ball->BALL_SPEED = 2;
                        ball->x_spd = ball->BALL_SPEED;
                        ball->y_spd = -ball->BALL_SPEED;
                        ChooseControl(pad, choosecontrol, started);
                        return;
                    }
                }
                else if(mouseX >= 500 && mouseY >= SCREEN_HEIGHT/2 + 36 + 42
                && mouseX <= 750 && mouseY <= SCREEN_HEIGHT/2 + 36 + 126)
                {
                    if(g_event.button.button == SDL_BUTTON_LEFT)
                    {
                        choosecontrol = true;
                        pad->PAD_SPEED = 3;
                        ball->BALL_SPEED = 2.5;
                        ball->x_spd = ball->BALL_SPEED;
                        ball->y_spd = -ball->BALL_SPEED;
                        ChooseControl(pad, choosecontrol, started);
                        return;
                    }
                }
            }
        }
        menu.Render(g_screen, nullptr);
        if(g_event.motion.x >= 250 && g_event.motion.y >= SCREEN_HEIGHT/2 - 120 - 42
        && g_event.motion.x <= 500 && g_event.motion.y <= SCREEN_HEIGHT/2 - 120 + 42)
        {
            easy1.Render(g_screen, nullptr);
        }
        else easy.Render(g_screen, nullptr);
        if(g_event.motion.x >= (SCREEN_WIDTH+200)/2 - 125 && g_event.motion.y >= SCREEN_HEIGHT/2 - 42
        && g_event.motion.x <= (SCREEN_WIDTH+200)/2 + 125 && g_event.motion.y <= SCREEN_HEIGHT/2 + 42)
        {
            medium1.Render(g_screen, nullptr);
        }
        else medium.Render(g_screen, nullptr);
        if(g_event.motion.x >= 500 && g_event.motion.y >= SCREEN_HEIGHT/2 + 36 + 42
        && g_event.motion.x <= 750 && g_event.motion.y <= SCREEN_HEIGHT/2 + 36 + 126)
        {
            hard1.Render(g_screen, nullptr);
        }
        else hard.Render(g_screen, nullptr);
        SDL_RenderPresent(g_screen);
        int real_time = SDL_GetTicks() - time;
        int time_one_frame = 1000/FRAME_PER_SECOND; //ms
        if(real_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_time;
            SDL_Delay(delay_time);
        }
    }
}


void Game(bool& is_quit, bool& win, bool& choosecontrol, bool& paused)
{

    unsigned int time = 0;
    while(!is_quit)
    {
        time = SDL_GetTicks();
        if(board->brickcount == 0)
        {
            is_quit = true;
            win = true;
        }
        while(SDL_PollEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit = true;
                exit(0);
            }
            else if(g_event.type == SDL_KEYDOWN)
            {
                if(g_event.key.keysym.sym == SDLK_p)
                {
                    paused = true;
                    break;
                }
                else if(g_event.key.keysym.sym == SDLK_SPACE)
                {
                    paused = false;
                }
            }
            else if(g_event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(g_event.button.button == SDL_BUTTON_LEFT)
                {
                    paused = false;
                }
            }
            pad->HandleInputAction(g_event, g_screen);
            ball->HandleInputAction(g_event, g_screen);
        }
        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, nullptr);
        sidepic.SetposRect(0, 0);
        sidepic.Render(g_screen, nullptr);
        sidepic.SetposRect(SCREEN_WIDTH - SIDE_SIZE_X, 0);
        sidepic.Render(g_screen, nullptr);
        tutorial.Render(g_screen, nullptr);

        board->DrawBoard(g_screen);
        if(!paused)
        {
            pad->PadMove();
            ball->BallMove(pad, is_quit, board->brickdata, board->brickcount);
        }

        ball->ShowBall(g_screen);
        pad->Show(g_screen);

        SDL_RenderPresent(g_screen);
        int real_time = SDL_GetTicks() - time;
        int time_one_frame = 1000/FRAME_PER_SECOND; //ms
        if(real_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_time;
            SDL_Delay(delay_time);
        }
    }
    return;
}

int main(int argc, char* argv[])
{
    if(!InitData())
        return -1;

    board = new Board;
    pad = new Paddle;
    ball = new Ball;

    bool is_quit = false;
    bool win = false;
    bool choosecontrol = false;
    bool started = false;
    bool paused = false;
    int mouseX = 0, mouseY = 0;
    unsigned int time = 0;

    g_background.LoadImg("data/pics/background.png", g_screen);
    sidepic.LoadImg("data/pics/side.png", g_screen);
    tutorial.LoadImg("data/pics/tutorial.png", g_screen);
    tutorial.SetposRect(800, 0);

    board->LoadBoard();
    board->Loadtile(g_screen);
    board->Reset();

    pad->LoadImg("data/pics/paddle.png", g_screen);
    ball->LoadImg("data/pics/ball.png", g_screen);

    win_.LoadImg("data/pics/win.png", g_screen);
    lose_.LoadImg("data/pics/lose.png", g_screen);
    again.LoadImg("data/pics/playagain.png", g_screen);
    again1.LoadImg("data/pics/playagain2.png", g_screen);

    win_.SetposRect(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2 - 52);
    win_.SetsizeRect(300, 105);
    lose_.SetposRect(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2 - 52);
    lose_.SetsizeRect(300, 105);
    again.SetposRect(SCREEN_WIDTH/2 - 70, SCREEN_HEIGHT/2 + 40);
    again.SetsizeRect(140, 70);
    again1.SetposRect(SCREEN_WIDTH/2 - 70, SCREEN_HEIGHT/2 + 40);
    again1.SetsizeRect(140, 70);

    //menu
    menu.LoadImg("data/pics/menu.png", g_screen);
    menu.SetposRect(0, 0);
    easy.LoadImg("data/pics/easy.png", g_screen);
    easy.SetposRect(250, SCREEN_HEIGHT/2 - 120 - 42);
    easy.SetsizeRect(250, 84);
    easy1.LoadImg("data/pics/easy1.png", g_screen);
    easy1.SetposRect(250, SCREEN_HEIGHT/2 - 120 - 42);
    easy1.SetsizeRect(250, 84);
    medium.LoadImg("data/pics/medium.png", g_screen);
    medium.SetposRect((SCREEN_WIDTH+200)/2 - 125, SCREEN_HEIGHT/2 - 42);
    medium.SetsizeRect(250, 84);
    medium1.LoadImg("data/pics/medium1.png", g_screen);
    medium1.SetposRect((SCREEN_WIDTH+200)/2 - 125, SCREEN_HEIGHT/2 - 42);
    medium1.SetsizeRect(250, 84);
    hard.LoadImg("data/pics/hard.png", g_screen);
    hard.SetposRect(500, SCREEN_HEIGHT/2 + 36 + 42);
    hard.SetsizeRect(250, 84);
    hard1.LoadImg("data/pics/hard1.png", g_screen);
    hard1.SetposRect(500, SCREEN_HEIGHT/2 + 36 + 42);
    hard1.SetsizeRect(250, 84);
    mouse.LoadImg("data/pics/mouse.png", g_screen);
    mouse.SetposRect(600, 175);
    mouse1.LoadImg("data/pics/mouse1.png", g_screen);
    mouse1.SetposRect(600, 175);
    keyboard.LoadImg("data/pics/keyboard.png", g_screen);
    keyboard.SetposRect(100, 175);
    keyboard1.LoadImg("data/pics/keyboard1.png", g_screen);
    keyboard1.SetposRect(100, 175);

    SetDifficulty(pad, ball, choosecontrol, started);

    while(true)
    {
        time = SDL_GetTicks();
        if(is_quit)
        {
            while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    is_quit = true;
                    exit(0);
                }
                else if(g_event.type == SDL_MOUSEBUTTONDOWN)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if(mouseX >= SCREEN_WIDTH/2 - 70 && mouseY >= SCREEN_HEIGHT/2 + 40
                    && mouseX <= SCREEN_WIDTH/2 + 70 && mouseY <= SCREEN_HEIGHT/2 + 110)
                    {
                        if(g_event.button.button == SDL_BUTTON_LEFT)
                        {
                            started = false;
                            choosecontrol = false;
                            SetDifficulty(pad, ball, choosecontrol, started);
                            is_quit = false;
                            win = false;
                            board->LoadBoard();
                            board->Loadtile(g_screen);
                            board->Reset();
                            board->brickcount = MAX_BRICK_X * MAX_BRICK_Y;
                            pad->PadReset();
                            ball->BallReset();
                            break;
                        }
                    }
                }
            }
            if(win)
            {
                g_background.Render(g_screen, nullptr);
                sidepic.SetposRect(0, 0);
                sidepic.Render(g_screen, nullptr);
                sidepic.SetposRect(SCREEN_WIDTH - SIDE_SIZE_X, 0);
                sidepic.Render(g_screen, nullptr);
                tutorial.Render(g_screen, nullptr);
                win_.Render(g_screen, nullptr);
                if(g_event.motion.x >= SCREEN_WIDTH/2 - 70 && g_event.motion.y >= SCREEN_HEIGHT/2 + 40
                && g_event.motion.x <= SCREEN_WIDTH/2 + 70 && g_event.motion.y <= SCREEN_HEIGHT/2 + 110)
                {
                    again1.Render(g_screen, nullptr);
                }
                else again.Render(g_screen, nullptr);

            }
            else if(!win)
            {
                g_background.Render(g_screen, nullptr);
                sidepic.SetposRect(0, 0);
                sidepic.Render(g_screen, nullptr);
                sidepic.SetposRect(SCREEN_WIDTH - SIDE_SIZE_X, 0);
                sidepic.Render(g_screen, nullptr);
                tutorial.Render(g_screen, nullptr);
                lose_.Render(g_screen, nullptr);
                if(g_event.motion.x >= SCREEN_WIDTH/2 - 70 && g_event.motion.y >= SCREEN_HEIGHT/2 + 40
                && g_event.motion.x <= SCREEN_WIDTH/2 + 70 && g_event.motion.y <= SCREEN_HEIGHT/2 + 110)
                {
                    again1.Render(g_screen, nullptr);
                }
                else again.Render(g_screen, nullptr);
            }
            SDL_RenderPresent(g_screen);
            int real_time = SDL_GetTicks() - time;
            int time_one_frame = 1000/FRAME_PER_SECOND; //ms
            if(real_time < time_one_frame)
            {
                int delay_time = time_one_frame - real_time;
                SDL_Delay(delay_time);
            }
            continue;
        }
        else Game(is_quit, win, choosecontrol, paused);
    }
    close();
    return 0;
}












#include"Gamemain.h"

int main(int argc, char* argv[])
{
    InitData();
    LoadGUI();
    SetDifficulty();

    srand(time(0));
    unsigned int time = 0;
    while(true)
    {
        time = SDL_GetTicks();
        if(is_quit)
        {
            PlayAgain();
            fp.open("data/highscore.txt");
            fp >> highscore;
            fp.close();
        }
        else Game();
        SDL_RenderPresent(g_screen);
        int real_time = SDL_GetTicks() - time;
        int time_one_frame = 1000/FRAME_PER_SECOND;
        if(real_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_time;
            SDL_Delay(delay_time);
        }
    }
    close();
    exit(0);
}

void InitData()
{
    if(SDL_Init(SDL_INIT_EVERYTHING))
        logSDLError("SDL_Init", true);
    g_window = SDL_CreateWindow("BREAKOUT",
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SCREEN_WIDTH + 200, SCREEN_HEIGHT,
                                 SDL_WINDOW_SHOWN);
    if(g_window == nullptr)
    {
        logSDLError("CreateWindow", true);
    }
    g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if(g_screen == nullptr)
    {
        logSDLError("CreateRenderer", true);
    }
    SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
    if(!IMG_Init(IMG_INIT_PNG))
    {
        std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    if(TTF_Init() == -1)
    {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    g_font = TTF_OpenFont("data/Minecraft.ttf", 24);
    if(g_font == nullptr)
    {
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}

void logSDLError(const std::string &msg, bool fatal)
{
    std::cout << msg << " Error: " << SDL_GetError() << std::endl;
    if(fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

void LoadGUI()
{
    board = new Board;
    pad = new Paddle;
    ball = new Ball;
    board->LoadBoard();
    board->Loadtile(g_screen);
    pad->LoadImg("data/pics/paddle.png", g_screen);
    ball->LoadImg("data/pics/ball.png", g_screen);
    audio = new Audio;
    audio->LoadAudio();
    pictures = new PictureLib;
    pictures->LoadPictureLib(g_screen);
    std::fstream fp;
    fp.open("data/highscore.txt");
    fp >> highscore;
    fp.close();
}

void close()
{
    SDL_DestroyRenderer(g_screen);
    g_screen = nullptr;
    SDL_DestroyWindow(g_window);
    g_window = nullptr;
    TTF_CloseFont(g_font);
    g_font = nullptr;

    delete pictures;
    delete audio;
    delete pad;
    delete board;
    delete ball;

    pictures = nullptr;
    audio = nullptr;
    ball = nullptr;
    pad = nullptr;
    board = nullptr;

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void ChooseControl()
{
    int mouseX = 0, mouseY = 0;
    unsigned int time = 0;
    while(choosecontrol && !started)
    {
        time = SDL_GetTicks();
        if(SDL_WaitEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                close();
                exit(0);
            }
            else if(g_event.type == SDL_KEYDOWN)
            {
                if(g_event.key.keysym.sym = SDLK_ESCAPE)
                {
                    choosecontrol = false;
                    SetDifficulty();
                }
            }
            else if(g_event.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&mouseX, &mouseY);
                if(mouseX >= 100 && mouseY >= 175
                && mouseX <= 412 && mouseY <= 425)
                {
                    if(g_event.button.button == SDL_BUTTON_LEFT)
                    {
                        Control(false);
                        return;
                    }
                }
                else if(mouseX >= 600 && mouseY >= 175
                && mouseX <= 840 && mouseY <= 425)
                {
                    if(g_event.button.button == SDL_BUTTON_LEFT)
                    {
                        Control(true);
                        return;
                    }
                }
            }
        }
        pictures->menu.Render(g_screen);
        if(g_event.motion.x >= 100 && g_event.motion.y >= 175
        && g_event.motion.x <= 412 && g_event.motion.y <= 425)
        {
            pictures->keyboard1.Render(g_screen);
        }
        else pictures->keyboard.Render(g_screen);
        if(g_event.motion.x >= 600 && 175
        && g_event.motion.x <= 840 && g_event.motion.y <= 425)
        {
            pictures->mouse1.Render(g_screen);
        }
        else pictures->mouse.Render(g_screen);
        g_text.Settext("Choose Control");
        g_text.SetColor(255, 255, 0);
        g_text.LoadText(g_font, g_screen);
        g_text.Render(g_screen, 10, 550);
        g_text.Freettf();
        SDL_RenderPresent(g_screen);
        int real_time = SDL_GetTicks() - time;
        int time_one_frame = 1000/FRAME_PER_SECOND;
        if(real_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_time;
            SDL_Delay(delay_time);
        }
    }
}

void Control(const bool& mouse)
{
    Mix_PlayChannel(-1, audio->menu_tick, 0);
    started = true;
    pad->input_mouse = mouse;
    return;
}

void SetDifficulty()
{
    int mouseX = 0, mouseY = 0;
    unsigned int time = 0;
    while(!choosecontrol)
    {
        time = SDL_GetTicks();
        if(SDL_WaitEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                close();
                exit(0);
            }
            else if(g_event.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&mouseX, &mouseY);
                if(mouseX >= 250 && mouseY >= SCREEN_HEIGHT/2 - 162
                && mouseX <= 500 && mouseY <= SCREEN_HEIGHT/2 - 78)
                {
                    if(g_event.button.button == SDL_BUTTON_LEFT)
                    {
                        Difficulty(2, 1.5, 7, 12, 5, 5, 10, 3);
                        return;
                    }
                }
                else if(mouseX >= (SCREEN_WIDTH+200)/2 - 125 && mouseY >= SCREEN_HEIGHT/2 - 42
                && mouseX <= (SCREEN_WIDTH+200)/2 + 125 && mouseY <= SCREEN_HEIGHT/2 + 42)
                {
                    if(g_event.button.button == SDL_BUTTON_LEFT)
                    {
                        Difficulty(2.5, 2, 6, 15, 4, 4, 20, 2);
                        return;
                    }
                }
                else if(mouseX >= 500 && mouseY >= SCREEN_HEIGHT/2 + 78
                && mouseX <= 750 && mouseY <= SCREEN_HEIGHT/2 + 162)
                {
                    if(g_event.button.button == SDL_BUTTON_LEFT)
                    {
                        Difficulty(3, 2.5, 5, 18, 3, 3, 30, 1);
                        return;
                    }
                }
                else if(mouseX >= 10 && mouseY >= 262
                && mouseX <= 209 && mouseY <= 338);
                {
                    if(g_event.button.button == SDL_BUTTON_LEFT)
                    {
                        Mix_PlayChannel(-1, audio->menu_tick, 0);
                        tut = true;
                        LoadTutorial();
                        return;
                    }
                }
            }
        }
        pictures->menu.Render(g_screen);
        if(g_event.motion.x >= 250 && g_event.motion.y >= SCREEN_HEIGHT/2 - 162
        && g_event.motion.x <= 500 && g_event.motion.y <= SCREEN_HEIGHT/2 - 78)
        {
            pictures->easy1.Render(g_screen);
        }
        else pictures->easy.Render(g_screen);
        if(g_event.motion.x >= (SCREEN_WIDTH+200)/2 - 125 && g_event.motion.y >= SCREEN_HEIGHT/2 - 42
        && g_event.motion.x <= (SCREEN_WIDTH+200)/2 + 125 && g_event.motion.y <= SCREEN_HEIGHT/2 + 42)
        {
            pictures->medium1.Render(g_screen);
        }
        else pictures->medium.Render(g_screen);
        if(g_event.motion.x >= 500 && g_event.motion.y >= SCREEN_HEIGHT/2 + 78
        && g_event.motion.x <= 750 && g_event.motion.y <= SCREEN_HEIGHT/2 + 162)
        {
            pictures->hard1.Render(g_screen);
        }
        else pictures->hard.Render(g_screen);
        if(g_event.motion.x >= 10 && g_event.motion.y >= 262
        && g_event.motion.x <= 209 && g_event.motion.y <= 338)
        {
            pictures->tutorial2.Render(g_screen);
        }
        else pictures->tutorial1.Render(g_screen);
        g_text.Settext("Choose Difficulty");
        g_text.SetColor(255, 255, 0);
        g_text.LoadText(g_font, g_screen);
        g_text.Render(g_screen, 10, 550);
        g_text.Freettf();
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

void LoadTutorial()
{
    unsigned int time = 0;
    while(tut)
    {
        time = SDL_GetTicks();
        if(SDL_WaitEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                close();
                exit(0);
            }
            else if(g_event.type == SDL_KEYDOWN)
            {
                if(g_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    tut = false;
                    SetDifficulty();
                }
            }
        }
        pictures->tutorial.Render(g_screen);
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

void Difficulty(const float& padspeed, const float& ballspeed,
                const int& bomb, const int& ice,
                const int& horarr, const int& verarr,
                const int& mul_, const int& life_)
{
    Mix_PlayChannel(-1, audio->menu_tick, 0);
    choosecontrol = true;
    pad->PAD_SPEED = padspeed;
    ball->BALL_SPEED = ballspeed;
    ball->x_spd = ball->BALL_SPEED;
    ball->y_spd = -ball->BALL_SPEED;
    board->bombcount = bomb;
    board->icecount = ice;
    board->horcount = horarr;
    board->vercount = verarr;
    board->Reset();
    mul = mul_;
    life = life_;
    ChooseControl();
    return;
}

void Game()
{
    if(board->brickcount == 0)
        is_quit = true;
    if(life == 0)
        is_quit = true;
    for(int i = 0; i < MAX_BRICK_X; ++i)
    {
        if(board->brickdata[22][i].state > 0)
        {
            is_quit = true;
            break;
        }
    }
    while(SDL_PollEvent(&g_event) != 0)
    {
        if(g_event.type == SDL_QUIT)
        {
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
            else if(g_event.key.keysym.sym == SDLK_ESCAPE)
            {
                message = true;
                MessageBox();
                return;
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
        ball->HandleInputAction(g_event, g_screen, audio->menu_tick);
    }
    SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
    SDL_RenderClear(g_screen);

    pictures->g_background.Render(g_screen);
    pictures->sidepic.SetposRect(0, 0);
    pictures->sidepic.Render(g_screen);
    pictures->sidepic.SetposRect(SCREEN_WIDTH - SIDE_SIZE_X, 0);
    pictures->sidepic.Render(g_screen);
    board->Renderbackground(g_screen);
    pictures->heart.Render(g_screen);
    g_text.SetColor(255, 255, 255);
    g_text.Settext("Your score:");
    g_text.LoadText(g_font, g_screen);
    g_text.Render(g_screen, 830, 300);
    g_text.Freettf();
    g_text.Settext("High score:");
    g_text.LoadText(g_font, g_screen);
    g_text.Render(g_screen, 830, 100);
    g_text.Freettf();
    g_text.Settext(std::to_string(board->point*mul));
    g_text.LoadText(g_font, g_screen);
    g_text.Render(g_screen, 870, 330);
    g_text.Freettf();
    g_text.Settext(std::to_string(highscore*10));
    g_text.LoadText(g_font, g_screen);
    g_text.Render(g_screen, 870, 130);
    g_text.Freettf();
    g_text.Settext("x" + std::to_string(life));
    g_text.LoadText(g_font, g_screen);
    g_text.Render(g_screen, 885, 11);
    g_text.Freettf();

    board->Updateboard(g_screen);
    board->DrawBoard(g_screen);
    if(!paused)
    {
        pictures->pause.Render(g_screen);
        pad->PadMove();
        ball->BallMove(pad, is_quit, board->brickdata, board, audio, life);
    }
    else pictures->start.Render(g_screen);
    ball->ShowBall(g_screen);
    pad->Show(g_screen);
}

void PlayAgain()
{
    int mouseX = 0, mouseY = 0;
    while(SDL_PollEvent(&g_event) != 0)
    {
        if(g_event.type == SDL_QUIT)
        {
            close();
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
                    Mix_PlayChannel(-1, audio->menu_tick, 0);
                    started = false;
                    choosecontrol = false;
                    SetDifficulty();
                    is_quit = false;
                    win = false;
                    board->LoadBoard();
                    board->brickcount = MAX_BRICK_X * MAX_BRICK_Y;
                    board->point = 0;
                    pad->PadReset();
                    ball->BallReset();
                    musicplaying = false;
                    return;
                }
            }
        }
    }
    if(board->point*mul/10 > highscore)
    {
        fp.open("data/highscore.txt");
        fp << board->point*mul/10;
        fp.close();
    }
    if(board->point*mul/10 > highscore) win = true;
    pictures->g_background.Render(g_screen);
    pictures->sidepic.SetposRect(0, 0);
    pictures->sidepic.Render(g_screen);
    pictures->sidepic.SetposRect(SCREEN_WIDTH - SIDE_SIZE_X, 0);
    pictures->sidepic.Render(g_screen);
    board->Renderbackground(g_screen);
    if(win)
    {
        if(!musicplaying)
        {
            Mix_HaltChannel(-1);
            Mix_PlayChannel(-1, audio->win_sfx, 0);
            musicplaying = true;
        }
        pictures->win_.Render(g_screen);
    }
    else
    {
        if(!musicplaying)
        {
            Mix_HaltChannel(-1);
            Mix_PlayChannel(-1, audio->lose_sfx, 0);
            musicplaying = true;
        }
        pictures->lose_.Render(g_screen);
    }
    if(g_event.motion.x >= SCREEN_WIDTH/2 - 70 && g_event.motion.y >= SCREEN_HEIGHT/2 + 40
    && g_event.motion.x <= SCREEN_WIDTH/2 + 70 && g_event.motion.y <= SCREEN_HEIGHT/2 + 110)
    {
        pictures->again1.Render(g_screen);
    }
    else pictures->again.Render(g_screen);
    g_text.SetColor(255, 255, 255);
    g_text.Settext("Your score:");
    g_text.LoadText(g_font, g_screen);
    g_text.Render(g_screen, 830, 300);
    g_text.Freettf();
    g_text.Settext("High score:");
    g_text.LoadText(g_font, g_screen);
    g_text.Render(g_screen, 830, 100);
    g_text.Freettf();
    g_text.Settext(std::to_string(board->point*mul));
    g_text.LoadText(g_font, g_screen);
    g_text.Render(g_screen, 870, 330);
    g_text.Freettf();
    g_text.Settext(std::to_string(highscore*10));
    g_text.LoadText(g_font, g_screen);
    g_text.Render(g_screen, 870, 130);
    g_text.Freettf();
}

void MessageBox()
{
    int mouseX, mouseY;
    while(message)
    {
        if(SDL_WaitEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                close();
                exit(0);
            }
            else if(g_event.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&mouseX, &mouseY);
                if(mouseX >= 315 && mouseY >= 354
                && mouseX <= 355 && mouseY <= 370)
                {
                    if(g_event.button.button == SDL_BUTTON_LEFT)
                    {
                        Mix_PlayChannel(-1, audio->menu_tick, 0);
                        paused = false;
                        started = false;
                        choosecontrol = false;
                        board->LoadBoard();
                        board->brickcount = MAX_BRICK_X * MAX_BRICK_Y;
                        board->point = 0;
                        pad->PadReset();
                        ball->BallReset();
                        musicplaying = false;
                        is_quit = false;
                        win = false;
                        SetDifficulty();
                        return;
                    }
                }
                else if(mouseX >= 442 && mouseY >= 354
                     && mouseX <= 472 && mouseY <= 370)
                {
                    if(g_event.button.button == SDL_BUTTON_LEFT)
                    {
                        Mix_PlayChannel(-1, audio->menu_tick, 0);
                        message = false;
                        paused = true;
                        return;
                    }
                }
            }
        }
        pictures->g_background.Render(g_screen);
        pictures->sidepic.SetposRect(0, 0);
        pictures->sidepic.Render(g_screen);
        pictures->sidepic.SetposRect(SCREEN_WIDTH - SIDE_SIZE_X, 0);
        pictures->sidepic.Render(g_screen);
        board->Renderbackground(g_screen);
        pictures->heart.Render(g_screen);

        g_text.SetColor(255, 255, 255);
        g_text.Settext("Your score:");
        g_text.LoadText(g_font, g_screen);
        g_text.Render(g_screen, 830, 300);
        g_text.Freettf();
        g_text.Settext("High score:");
        g_text.LoadText(g_font, g_screen);
        g_text.Render(g_screen, 830, 100);
        g_text.Freettf();
        g_text.Settext(std::to_string(board->point*mul));
        g_text.LoadText(g_font, g_screen);
        g_text.Render(g_screen, 870, 330);
        g_text.Freettf();
        g_text.Settext(std::to_string(highscore*10));
        g_text.LoadText(g_font, g_screen);
        g_text.Render(g_screen, 870, 130);
        g_text.Freettf();
        g_text.Settext("x" + std::to_string(life));
        g_text.LoadText(g_font, g_screen);
        g_text.Render(g_screen, 885, 11);
        g_text.Freettf();
        board->Updateboard(g_screen);
        board->DrawBoard(g_screen);
        ball->ShowBall(g_screen);
        pad->Show(g_screen);
        pictures->messagebox.Render(g_screen);
        if(g_event.motion.x >= 315 && g_event.motion.y >= 354
        && g_event.motion.x <= 355 && g_event.motion.y <= 370)
        {
            pictures->yes.Render(g_screen);
        }
        if(g_event.motion.x >= 442 && g_event.motion.y >= 354
        && g_event.motion.x <= 472 && g_event.motion.y <= 370)
        {
            pictures->no.Render(g_screen);
        }
        SDL_RenderPresent(g_screen);
    }
}







#include"PictureLib.h"

PictureLib::PictureLib()
{

}

PictureLib::~PictureLib()
{
    FreePictureLib();
}

void PictureLib::FreePictureLib()
{
    g_background.Free();
    sidepic.Free();
    tutorial.Free();
    tutorial1.Free();
    tutorial2.Free();
    easy.Free();
    easy1.Free();
    medium.Free();
    medium1.Free();
    hard.Free();
    hard1.Free();
    pause.Free();
    start.Free();
    win_.Free();
    lose_.Free();
    again.Free();
    again1.Free();
    menu.Free();
    mouse.Free();
    mouse1.Free();
    keyboard.Free();
    keyboard1.Free();
    heart.Free();
    messagebox.Free();
    no.Free();
    yes.Free();
    ball_.Free();
    pad_.Free();
}

void PictureLib::LoadPictureLib(SDL_Renderer* screen)
{
    g_background.LoadImg("data/pics/background.png", screen);
    sidepic.LoadImg("data/pics/side.png", screen);

    tutorial.LoadImg("data/pics/tutorial.png", screen);
    tutorial1.LoadImg("data/pics/tutorial1.png", screen);
    tutorial2.LoadImg("data/pics/tutorial2.png", screen);
    tutorial1.SetposRect(10, 262);
    tutorial2.SetposRect(10, 262);

    pause.LoadImg("data/pics/paused.png", screen);
    start.LoadImg("data/pics/started.png", screen);
    win_.LoadImg("data/pics/win.png", screen);
    lose_.LoadImg("data/pics/lose.png", screen);
    again.LoadImg("data/pics/playagain.png", screen);
    again1.LoadImg("data/pics/playagain2.png", screen);

    pause.SetposRect(864, 480);
    start.SetposRect(864, 480);
    win_.SetposRect(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2 - 52);
    win_.SetsizeRect(300, 105);
    lose_.SetposRect(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2 - 52);
    lose_.SetsizeRect(300, 105);
    again.SetposRect(SCREEN_WIDTH/2 - 70, SCREEN_HEIGHT/2 + 40);
    again.SetsizeRect(140, 70);
    again1.SetposRect(SCREEN_WIDTH/2 - 70, SCREEN_HEIGHT/2 + 40);
    again1.SetsizeRect(140, 70);

    //menu
    menu.LoadImg("data/pics/menu.png", screen);
    menu.SetposRect(0, 0);
    easy.LoadImg("data/pics/easy.png", screen);
    easy.SetposRect(250, SCREEN_HEIGHT/2 - 162);
    easy.SetsizeRect(250, 84);
    easy1.LoadImg("data/pics/easy1.png", screen);
    easy1.SetposRect(250, SCREEN_HEIGHT/2 - 162);
    easy1.SetsizeRect(250, 84);
    medium.LoadImg("data/pics/medium.png", screen);
    medium.SetposRect((SCREEN_WIDTH+200)/2 - 125, SCREEN_HEIGHT/2 - 42);
    medium.SetsizeRect(250, 84);
    medium1.LoadImg("data/pics/medium1.png", screen);
    medium1.SetposRect((SCREEN_WIDTH+200)/2 - 125, SCREEN_HEIGHT/2 - 42);
    medium1.SetsizeRect(250, 84);
    hard.LoadImg("data/pics/hard.png", screen);
    hard.SetposRect(500, SCREEN_HEIGHT/2 + 78);
    hard.SetsizeRect(250, 84);
    hard1.LoadImg("data/pics/hard1.png", screen);
    hard1.SetposRect(500, SCREEN_HEIGHT/2 + 78);
    hard1.SetsizeRect(250, 84);
    mouse.LoadImg("data/pics/mouse.png", screen);
    mouse.SetposRect(600, 175);
    mouse1.LoadImg("data/pics/mouse1.png", screen);
    mouse1.SetposRect(600, 175);
    keyboard.LoadImg("data/pics/keyboard.png", screen);
    keyboard.SetposRect(100, 175);
    keyboard1.LoadImg("data/pics/keyboard1.png", screen);
    keyboard1.SetposRect(100, 175);

    heart.LoadImg("data/pics/heart.png", screen);
    heart.SetposRect(850, 10);

    messagebox.LoadImg("data/pics/messagebox.png", screen);
    messagebox.SetposRect(SCREEN_WIDTH/2 - 140, SCREEN_HEIGHT/2 - 95);
    yes.LoadImg("data/pics/yes.png", screen);
    yes.SetposRect(315, 354);
    no.LoadImg("data/pics/no.png", screen);
    no.SetposRect(442, 354);

    ball_.LoadImg("data/pics/ball.png", screen);
    ball_.SetsizeRect(BALL_SIZE, BALL_SIZE);
    pad_.LoadImg("data/pics/paddle.png", screen);
    pad_.SetsizeRect(PADDLE_WIDTH, PADDLE_HEIGHT);
}

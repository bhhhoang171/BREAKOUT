#ifndef PICTURE_LIB_H_
#define PICTURE_LIB_H_

#include"Graphic.h"
#include"commonfunction.h"

class PictureLib
{
public:
    PictureLib();
    ~PictureLib();
    void LoadPictureLib(SDL_Renderer* screen);
    void FreePictureLib();
    Picture g_background;
    Picture sidepic;
    Picture tutorial;
    Picture tutorial1;
    Picture tutorial2;
    Picture pause;
    Picture start;
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
    Picture heart;
    Picture yes;
    Picture no;
    Picture messagebox;
    Picture ball_;
    Picture pad_;
};

#endif

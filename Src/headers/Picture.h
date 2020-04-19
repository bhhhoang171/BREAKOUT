#ifndef PICTURE_H
#define PICTURE_H

#include"commonfunction.h"

class Picture
{
public:
    Picture();
    ~Picture();
    void SetposRect(const int& x, const int& y) { rect_.x = x; rect_.y = y; }
    void SetsizeRect(const int& w, const int& h) { rect_.w = w; rect_.h = h;}
    void LoadImg(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = nullptr);
    void Free();
protected:
    SDL_Texture* p_object;
    SDL_Rect rect_;
};


#endif // PICTURE_H

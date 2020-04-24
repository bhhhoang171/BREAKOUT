#ifndef GRAPHIC_H
#define GRAPHIC_H

#include"commonfunction.h"

class Picture
{
public:
    Picture();
    ~Picture();
    void SetposRect(const int& x, const int& y) { rect_.x = x; rect_.y = y; }
    void SetsizeRect(const int& w, const int& h) { rect_.w = w; rect_.h = h;}
    virtual void LoadImg(const std::string& path, SDL_Renderer* screen);
    void Render(SDL_Renderer* screen) const;
    void Free();
protected:
    SDL_Texture* texture;
    SDL_Rect rect_;
};

class Text
{
public:
    Text();
    ~Text();
    void LoadText(TTF_Font* font, SDL_Renderer* screen);
    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    void Render(SDL_Renderer* screen,
                const int& x_pos, const int& y_pos) const;
    void SetsizeRect(const int& w, const int& h) { width = w; height = h;}
    void Settext(const std::string& text) {str = text;}
    void Freettf();
private:
    std::string str;
    SDL_Texture* texture;
    SDL_Color text_color;
    int width;
    int height;
};

#endif // GRAPHIC_H

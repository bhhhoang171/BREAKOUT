#include"Graphic.h"

Picture::Picture()
{
    texture = nullptr;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

Picture::~Picture()
{
    Free();
}

void Picture::LoadImg(const std::string& path, SDL_Renderer* screen)
{
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if(load_surface == nullptr)
    {
        std::cout << "IMG_Load Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    else
    {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 255, 255, 255));
        texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if(texture)
        {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }
}

void Picture::Render(SDL_Renderer* screen) const
{
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(screen, texture, nullptr, &renderquad);
}

void Picture::Free()
{
    if(texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        rect_.w = 0;
        rect_.h = 0;
    }
}
//////////////////////////////////////////////////////Picture End/////////////////////////////////////////////////////////////////////////
Text::Text()
{
    texture = nullptr;
    text_color.r = 255;
    text_color.g = 255;
    text_color.b = 255;
}

Text::~Text()
{
    Freettf();
}

void Text::LoadText(TTF_Font* font, SDL_Renderer* screen)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, str.c_str(), text_color);
    if(text_surface)
    {
        texture = SDL_CreateTextureFromSurface(screen, text_surface);
        width = text_surface->w;
        height = text_surface->h;
    }
    SDL_FreeSurface(text_surface);
}

void Text::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    text_color.r = red;
    text_color.g = green;
    text_color.b = blue;
}

void Text::Render(SDL_Renderer* screen,
                  const int& x_pos, const int& y_pos) const
{
    SDL_Rect renderquad = {x_pos, y_pos, width, height};
    SDL_RenderCopy(screen, texture, nullptr, &renderquad);
}

void Text::Freettf()
{
    if(texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

//////////////////////////////////////////////////////TTF End/////////////////////////////////////////////////////////////////////////





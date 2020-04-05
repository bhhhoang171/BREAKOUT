
#include"Picture.h"

Picture::Picture()
{
    p_object = nullptr;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;

}

Picture::~Picture()
{
    Free();
}

bool Picture::LoadImg(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* new_texture = nullptr;
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if(load_surface != nullptr)
    {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 255, 255, 255));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if(new_texture != nullptr)
        {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;
        }

        SDL_FreeSurface(load_surface);
    }

    p_object = new_texture;

    return p_object != nullptr;

}

void Picture::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(des, p_object, clip, &renderquad);
}

void Picture::Free()
{
    if(p_object != nullptr)
    {
        SDL_DestroyTexture(p_object);
        p_object = nullptr;
        rect_.w = 0;
        rect_.h = 0;
    }
}
















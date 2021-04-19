#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

class LTexture
{
public:
    void free();
    LTexture();
    ~LTexture();
    SDL_FRect GetRect() const {return rect_;}
    SDL_Texture* GetObject() const {return texture;}
    bool loadImg(SDL_Renderer*, string path);
    void render(SDL_Renderer*, const SDL_Rect* clip = NULL);

private:
    SDL_Texture* texture;
    SDL_FRect rect_;
};

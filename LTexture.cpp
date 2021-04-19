#include "LTexture.h"
#include <string>

void LTexture::free()
{
	if( texture != NULL )
	{
		SDL_DestroyTexture( texture );
		texture = NULL;
        rect_.x = 0;
        rect_.y = 0;
        rect_.w = 0;
        rect_.h = 0;
	}
}

LTexture::LTexture()
{
	texture = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

LTexture::~LTexture()
{
	free();
}
bool LTexture::loadImg( SDL_Renderer *renderer, string path )
{
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if(load_surface != NULL)
    {
        new_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
        if(new_texture != NULL)
        {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;
        }

        SDL_FreeSurface(load_surface);
    }

    texture = new_texture;

    return texture != NULL;
}

void LTexture::render( SDL_Renderer *renderer, const SDL_Rect* clip )
{
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(renderer, texture, clip, &renderquad);
}

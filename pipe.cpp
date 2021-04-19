#include "pipe.h"
#include "game.h"
#include <time.h>

using namespace std;

int temp;
void Pipe::free()
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
Pipe::Pipe()
{
    rect_.x = game::SCREEN_WIDTH;
    rect_.y = 0;
    rect_.w = game::PIPE_WIDTH;
    rect_.h = game::PIPE_HEIGHT;

    x_val_ = 0;
    y_val_ = 0;
}
Pipe::~Pipe()
{
    free();
}
void Pipe::HandleMove1()
{
    rect_.x -= x_val_;
    if(rect_.x < -100)
    {
        rect_.x = game::SCREEN_WIDTH - game::PIPE_WIDTH;
        rect_.y = -(rand()%115+411);
        temp = rect_.y;
    }
}

void Pipe::HandleMove2()
{
    rect_.x -= x_val_;
    if(rect_.x < -100)
    {
        rect_.x = game::SCREEN_WIDTH - game::PIPE_WIDTH;
        rect_.y = temp + 600 + game::PIPE_GAP;
    }
}
void Pipe::render(SDL_Renderer* renderer)
{
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(renderer, texture, NULL, &renderquad);
}
bool Pipe::loadImg( SDL_Renderer *renderer, string path )
{
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if(load_surface != NULL)
    {
        SDL_SetColorKey( load_surface, SDL_TRUE, SDL_MapRGB( load_surface->format, 0xFF, 0xFF, 0xFF ) );
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

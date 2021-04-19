#include "text.h"


Text::Text(void)
{
  text_color_.r = 255;
  text_color_.g = 255;
  text_color_.b = 255;
}


Text::~Text(void)
{
}


bool Text::loadFromRenderedText(TTF_Font* gFont, SDL_Renderer* renderer)
{
  SDL_Surface* load_surface = TTF_RenderText_Solid(gFont, str_val_.c_str(), text_color_);
  if( load_surface != NULL )
  {
    texture = SDL_CreateTextureFromSurface(renderer, load_surface );
    if( texture != NULL )
    {
      rect_.w = load_surface->w;
      rect_.h = load_surface->h;
    }

    SDL_FreeSurface( load_surface );
  }
  return texture != NULL;
}

void Text::Free()
{
  if(texture != NULL)
  {
    SDL_DestroyTexture(texture);
    texture = NULL;
  }
}
void Text::setColor(int type)
{
  if (type == 0)
  {
    SDL_Color color = {255, 0, 0};
    text_color_ = color;
  }
  else if (type == 1)
  {
    SDL_Color color = {255, 255, 255};
    text_color_ = color;
  }
  else
  {
    SDL_Color color = {0, 0, 0};
    text_color_ = color;
  }
}
void Text::render(SDL_Renderer* renderer, int x, int y)
{
  SDL_Rect renderQuad = { x, y, rect_.w, rect_.h };
  SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}

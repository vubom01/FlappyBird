#pragma once

#include "game.h"
#include <string>

using namespace std;

class Text
{
public:
  Text(void);
  ~Text(void);

  bool loadFromRenderedText(TTF_Font* gFont, SDL_Renderer* screen);
  void Free();
  void setColor(int type);
  void render(SDL_Renderer* screen, int x, int y);
  void SetText(const string& text) {str_val_ = text;}
  string GetText() const {return str_val_;}

private:
  string str_val_;
  SDL_FRect rect_;
  SDL_Color text_color_;
  SDL_Texture* texture;
};



#pragma once

#include <bits/stdc++.h>
#include "bird.h"
#include <SDL.h>

using namespace std;

class Pipe
{
public:
    void free();
    Pipe();
    ~Pipe();
    void SetRect(double x, double y)
    {
        rect_.x=x, rect_.y=y;
    }
    void HandleMove1();
    void HandleMove2();
    void render(SDL_Renderer*);
    void set_x_val(const double&val){x_val_ = val;}
    void set_y_val(const int&val){y_val_ = val;}
    SDL_FRect GetRect() const {return rect_;}
    bool loadImg(SDL_Renderer*, string path);
private:
    SDL_FRect rect_;
    SDL_Texture* texture;

    double x_val_;
    int y_val_;
};

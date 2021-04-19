#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <string>

class Bird
{
public:
    Bird(SDL_Renderer *);
    int getmPosX();
    int getmPosY();
    SDL_FRect GetRect() const {return rect_;}
    void changeY(float accel);
    void handleEvent( SDL_Event& e, Mix_Chunk*  );
    void move(int &loseFlag);
    void render(SDL_Renderer *);
private:
    int x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    SDL_Texture *bird;
//    SDL_Texture *bird1;
//    SDL_Texture *bird2;
    SDL_FRect rect_;

    int mPosX=60, mPosY=0;
    float mVelY=0;
};

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

class game
{
public:
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;

    static const int BIRD_WIDTH = 47;
    static const int BIRD_HEIGHT = 33;

    static const int PIPE_WIDTH = 50;
    static const int PIPE_HEIGHT = 500;
    static const int PIPE_GAP = 199;

    void Clear();
    game();
    int run();
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    Mix_Chunk* g_sound_wing;
    Mix_Chunk* g_sound_point;
    Mix_Chunk* g_sound_hit;
    Mix_Chunk* g_sound_die;
    Mix_Chunk* g_sound_over;

    TTF_Font* font = NULL;
    TTF_Font* font1 = NULL;

};

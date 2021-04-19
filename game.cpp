#include "game.h"
#include "LTexture.h"
#include "bird.h"
#include "pipe.h"
#include "text.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

LTexture Menu;
LTexture GameOver;
LTexture background;

using namespace std;

bool CheckCollision(SDL_FRect pipeTop, SDL_FRect pipeBottom, Bird b)
{
    int pipeTopLeft = pipeTop.x;
	int pipeTopRight = pipeTop.x + pipeTop.w;
	int pipeTopTop = -1;
	int pipeTopBottom = pipeTop.y + pipeTop.h;

	int pipeBottomLeft = pipeBottom.x;
	int pipeBottomRight = pipeBottom.x + pipeBottom.w;
	int pipeBottomTop = pipeBottom.y;
	int pipeBottomBottom = pipeBottom.y + pipeBottom.h;

	SDL_FRect birdXCollision = { b.getmPosX() - 2, b.getmPosY() + 18, game::BIRD_WIDTH + 4, game::BIRD_HEIGHT - 15 };
	SDL_FRect birdYCollision = { b.getmPosX() + 10, b.getmPosY(), game::BIRD_WIDTH - 15, game::BIRD_HEIGHT + 5};

	int birdXLeft = birdXCollision.x;
	int birdXRight = birdXCollision.x + birdXCollision.w;
	int birdXTop = birdXCollision.y;
	int birdXBottom = birdXCollision.y + birdXCollision.h;

	int birdYLeft = birdYCollision.x;
	int birdYRight = birdYCollision.x + birdYCollision.w;
	int birdYTop = birdYCollision.y;
	int birdYBottom = birdYCollision.y + birdYCollision.h;

	if (pipeTopBottom > birdXTop && pipeTopTop < birdXBottom && pipeTopRight > birdXLeft && pipeTopLeft < birdXRight)
		return true;
	if (pipeTopBottom > birdYTop && pipeTopTop < birdYBottom && pipeTopRight > birdYLeft && pipeTopLeft < birdYRight)
		return true;
	if (pipeBottomBottom > birdXTop && pipeBottomTop < birdXBottom && pipeBottomRight > birdXLeft && pipeBottomLeft < birdXRight)
		return true;
	if (pipeBottomBottom > birdYTop && pipeBottomTop < birdYBottom && pipeBottomRight > birdYLeft && pipeBottomLeft < birdYRight)
		return true;

	return false;
}
bool CheckPoint(SDL_FRect pipe, Bird b)
{
    if (b.getmPosX()-2 > pipe.x + pipe.w)
        return true;
    return false;
}
string to_string (int a)
{
    if (a==0) return "0";
    string s="";
    while (a>0)
    {
        s=char(a%10+48)+s;
        a=a/10;
    }
    return s;
}
void game::Clear()
{
    background.free();
    Menu.free();
    GameOver.free();

	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;
    IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}
game::game()
{
// Windows
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) cout << "Error";
    window = SDL_CreateWindow
    (
        "MADE BY LEHUYVU",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if( window == NULL ) cout << "Error";
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( renderer == NULL ) cout << "Error";
    else
    {
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) ) cout << "Error";
    }

// Sound
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096)==-1) cout << "Error";

    g_sound_wing = Mix_LoadWAV("sound/sfx_wing.wav");
    g_sound_hit = Mix_LoadWAV("sound/sfx_hit.wav");
    g_sound_point = Mix_LoadWAV("sound/sfx_point.wav");
    g_sound_die = Mix_LoadWAV("sound/sfx_die.wav");
    g_sound_over = Mix_LoadWAV("sound/nope.wav");

    if(g_sound_wing == NULL || g_sound_hit == NULL || g_sound_point == NULL || g_sound_die == NULL || g_sound_over==NULL)
        cout << "Error";

// TTF
    if (TTF_Init() < 0 ) cout << "Error";
    font = TTF_OpenFont("font.ttf", 60);
    if (font == NULL) cout << "Error";
    font1 = TTF_OpenFont("font.ttf", 55);
    if (font1 == NULL) cout << "Error";
}

int game::run()
{
    srand(time(NULL));

    if( !background.loadImg(renderer, "img/background.png" ) ) return 0;
    if (!GameOver.loadImg(renderer,"img/GameOver.png")) return 0;
    if (!Menu.loadImg(renderer,"img/menu.png")) return 0;

    bool quit = false;
    bool join = false;

    int HI_Score = 0;

PlayAgain:
    SDL_Event e;

    float speed = 3;
    float accel=0.5;
    int lose=0;

    Bird bird(renderer);

    int y_val_;
// pipe 1
    y_val_ = -(rand()%115+411);

    Pipe pipe1_t = Pipe();
    if ( !pipe1_t.loadImg(renderer, "img/pipetop.png")) return 0;
    pipe1_t.SetRect(2*SCREEN_WIDTH/3 - PIPE_WIDTH/3, y_val_);
    pipe1_t.set_x_val(speed);

    Pipe pipe1_d = Pipe();
    if ( !pipe1_d.loadImg(renderer, "img/pipedown.png")) return 0;
    pipe1_d.SetRect(2*SCREEN_WIDTH/3 - PIPE_WIDTH/3, y_val_ + 600 + PIPE_GAP);
    pipe1_d.set_x_val(speed);

// pipe 2
    y_val_ = -(rand()%115+411);

    Pipe pipe2_t = Pipe();
    if ( !pipe2_t.loadImg(renderer, "img/pipetop.png")) return 0;
    pipe2_t.SetRect(SCREEN_WIDTH, y_val_);
    pipe2_t.set_x_val(speed);

    Pipe pipe2_d = Pipe();
    if ( !pipe2_d.loadImg(renderer, "img/pipedown.png")) return 0;
    pipe2_d.SetRect(SCREEN_WIDTH, y_val_ + 600 + PIPE_GAP);
    pipe2_d.set_x_val(speed);

// pipe 3
    y_val_ = -(rand()%115+411);

    Pipe pipe3_t = Pipe();
    if ( !pipe3_t.loadImg(renderer, "img/pipetop.png")) return 0;
    pipe3_t.SetRect(4*SCREEN_WIDTH/3 + PIPE_WIDTH/3, y_val_);
    pipe3_t.set_x_val(speed);

    Pipe pipe3_d = Pipe();
    if ( !pipe3_d.loadImg(renderer, "img/pipedown.png")) return 0;
    pipe3_d.SetRect(4*SCREEN_WIDTH/3 + PIPE_WIDTH/3, y_val_ + 600 + PIPE_GAP);
    pipe3_d.set_x_val(speed);
//
    bool point_1 = false;
    bool point_2 = false;
    bool point_3 = false;

    int Score = 0;

    Text cnt;
    Text point;
    cnt.setColor(1);
    point.setColor(2);

    while (1)
    {
// menu
        while (!join)
        {
            Menu.render(renderer, NULL);
            SDL_RenderPresent(renderer);
            SDL_Event ee;
            if (SDL_PollEvent(&ee))
            {
                if(ee.type == SDL_KEYDOWN && ee.key.keysym.sym == SDLK_SPACE)
                {
                    join = true;
                    break;
                }
                if(ee.type == SDL_KEYDOWN && ee.key.keysym.sym == SDLK_ESCAPE)
                    goto Exit;
            }
        }
//
        while (!quit && join)
        {
            while (SDL_PollEvent(&e))
            {
                switch (e.type)
                {
                case SDL_QUIT:
                    quit = true;
                    break;

                }
                bird.handleEvent(e, g_sound_wing);
            }
            bird.changeY(accel);
            bird.move(lose);
// CheckCollision
            if (CheckCollision(pipe1_t.GetRect(), pipe1_d.GetRect(), bird)
                || CheckCollision(pipe2_t.GetRect(), pipe2_d.GetRect(), bird)
                || CheckCollision(pipe3_t.GetRect(), pipe3_d.GetRect(), bird))
                {
                    lose = 1;
                }

// CheckPoint
            if (CheckPoint(pipe1_t.GetRect(), bird) && point_1 == false)
            {
                Mix_PlayChannel(-1, g_sound_point, 0);
                Score++;
                point_1 = true;
            }
            if (CheckPoint(pipe2_t.GetRect(), bird) && point_2 == false)
            {
                Mix_PlayChannel(-1, g_sound_point, 0);
                Score++;
                point_2 = true;
                point_3 = false;
            }
            if (CheckPoint(pipe3_t.GetRect(), bird) && point_3 == false)
            {
                Mix_PlayChannel(-1, g_sound_point, 0);
                Score++;
                point_3 = true;
                point_1 = false;
                point_2 = false;
            }
//
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);

            background.render(renderer, NULL);

            if (lose == 1)
            {
                Mix_PlayChannel(-1, g_sound_hit, 0);
                SDL_Delay(700);
                Mix_PlayChannel(-1, g_sound_die, 0);
                SDL_Delay(1000);
                speed = 0;
                quit = true;
            }

            bird.render(renderer);

            pipe1_t.render(renderer);
            pipe1_t.HandleMove1();
            pipe1_d.render(renderer);
            pipe1_d.HandleMove2();

            pipe2_t.render(renderer);
            pipe2_t.HandleMove1();
            pipe2_d.render(renderer);
            pipe2_d.HandleMove2();

            pipe3_t.render(renderer);
            pipe3_t.HandleMove1();
            pipe3_d.render(renderer);
            pipe3_d.HandleMove2();

            string cnt_str = to_string(Score);
            cnt.SetText(cnt_str);
            cnt.loadFromRenderedText(font, renderer);
            cnt.render(renderer, SCREEN_WIDTH/2, 50);

// hitbox
//            SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
//            SDL_Rect birdXCollision = { bird.getmPosX() - 2, bird.getmPosY() + 18, BIRD_WIDTH + 4, BIRD_HEIGHT - 15 };
//            SDL_Rect birdYCollision = { bird.getmPosX() + 10, bird.getmPosY(), BIRD_WIDTH - 15, BIRD_HEIGHT + 5};
//            SDL_RenderDrawRect(renderer, &birdXCollision);
//            SDL_RenderDrawRect(renderer, &birdYCollision);

            SDL_RenderPresent(renderer);
        }
// gameover
        while (quit)
        {
            GameOver.render(renderer, NULL);
// Score
            string p_str = to_string(Score);
            point.SetText(p_str);
            point.loadFromRenderedText(font1, renderer);
            point.render(renderer, 25, 135);
// HighScore
            if (HI_Score < Score) HI_Score = Score;
            p_str = to_string(HI_Score);
            point.SetText(p_str);
            point.loadFromRenderedText(font1, renderer);
            point.render(renderer, 25, 225);

            SDL_RenderPresent(renderer);
            SDL_Event ee;
            if (SDL_PollEvent(&ee))
            {
                if (ee.type == SDL_KEYDOWN && ee.key.keysym.sym != SDLK_SPACE && ee.key.keysym.sym != SDLK_ESCAPE)
                {
                    quit = false;
                    join = false;
                    goto PlayAgain;
                }
                if (ee.type == SDL_KEYDOWN && ee.key.keysym.sym == SDLK_ESCAPE)
                {
                    goto Exit;
                }
            }

        }
    }
Exit:
    Clear();

    return 0;
}

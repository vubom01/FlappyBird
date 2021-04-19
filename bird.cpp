#include "bird.h"
#include "game.h"

SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *fileName)
{
    SDL_Surface *surface = IMG_Load(fileName);
    if (!surface) return false;
    SDL_Texture *res = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return res;
}

Bird::Bird(SDL_Renderer *renderer):
//    bird1(loadTexture(renderer, "img/bird1.png")),
//    bird2(loadTexture(renderer, "img/bird2.png")),
    bird(loadTexture(renderer, "img/bird.png"))
{}
int Bird::getmPosX()
{
	return mPosX;
}
int Bird::getmPosY()
{
	return mPosY;
}
void Bird::changeY(float accel)
{
	mVelY += accel;
}

void Bird::handleEvent( SDL_Event& e, Mix_Chunk* wing_sound )
{
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_SPACE)
    {
		mVelY = -12;
        Mix_PlayChannel(-1, wing_sound, 0);
	}
}

void Bird::move(int &loseFlag)
{
    mPosY += mVelY;

	if (mPosY < 0)
	{
		mPosY = 0;
		loseFlag = 1;
	}
    if( mPosY + game::BIRD_HEIGHT > game::SCREEN_HEIGHT )
    {
        mPosY = game::SCREEN_HEIGHT - game::BIRD_HEIGHT ;
		loseFlag = 1;
    }
}

void Bird::render(SDL_Renderer *renderer)
{
    SDL_Rect r;
    r.x = mPosX-10;
    r.y = mPosY-5;
    r.w = 62;
    r.h = 47;
    SDL_RenderCopyEx(renderer, bird, nullptr, &r, mVelY*2, nullptr, SDL_FLIP_NONE);
}

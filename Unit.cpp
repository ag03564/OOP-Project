#include "Unit.h"

Unit::Unit()
{

}

Unit::Unit(SDL_Texture* img, int x, int y)
{
    image = img;
    int w, h;
    SDL_QueryTexture(image, NULL, NULL, &w, &h);

    this->x = x;
    this->y = y;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = w;
    srcRect.h = h;

    mover.x = x - w/2;
    mover.y = y - h/2;
    mover.w = w;
    mover.h = h;
}

Unit::Unit(SDL_Texture* bodyImg, SDL_Texture* turretImg, int x, int y)
{

}

Unit::~Unit()
{
    image = NULL;
}

void Unit::Move(int direction)
{
    if(direction==LEFT)
    {
        mover.x+=1;
        if(mover.x<0)
        {
            //mover.x=0;
        }
    }

    //if direction is right, then increase the time to enable RIGHTWARDS movement
    if(direction==RIGHT)
    {
        mover.x-=1;
        if(mover.x>800)
        {
            //mover.x=800;
        }
    }
}

void Unit::Draw(SDL_Renderer* gRenderer)
{

    SDL_RenderCopy( gRenderer, image, &srcRect, &mover );
}


#pragma once
#include "Screen.h"

class GameScreen:public Screen
{
private:
    LTexture* buttonScreen; //the small screen over which buttons are drawn
public:
    GameScreen(LTexture*,LTexture*,LTexture*);
    void Render(long int& frame,SDL_Renderer*);
    virtual ~GameScreen();
};

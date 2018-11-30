#pragma once
#include "Screen.h"

class menuScreen:public Screen
{
private:
    LTexture* buttonScreen; //the small screen over which buttons are drawn
public:
    menuScreen(LTexture*,LTexture*,LTexture*);
    void Render(long int& frame,SDL_Renderer*);
    virtual ~menuScreen();
};


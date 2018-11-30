#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "iostream"
#include "string"
#include "Characters.h"
#include "LTexture.h"
using namespace std;

class Character
{
    public:
        Character();
        Character(LTexture* gSpriteSheetTexture, char c, int x_pos, int y_pos);
        void render(SDL_Renderer* gRenderer);
        void setPosition(int x, int y);
        void setChar(char c);
        void setTexture(char c, LTexture* gSpriteSheetTexture, int x_pos, int y_pos);
    private:
        int x,y;
        SDL_Rect charRect;
        char shownChar;
        int character_value = 0;
        LTexture* CharTexture;
};

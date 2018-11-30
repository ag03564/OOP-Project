#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "iostream"
#include "string"
#include "Words.h"
#include "LTexture.h"
#include "Characters.h"
using namespace std;

class Word
{
public:
    Word(string str ,LTexture* gSpriteSheetTexture, int x, int y);
    void render(SDL_Renderer* gRenderer);
    void setText(string str);
    int getTextLength();
private:
    int x_pos, y_pos;
    string renderWord;
    LTexture* charTexture;
    Character* characters;
};

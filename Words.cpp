#include "SDL.h"
#include "SDL_image.h"
#include "iostream"
#include "string"
#include "Words.h"


Word::Word(string str, LTexture* gSpriteSheetTexture, int x, int y)
{
    this->charTexture = gSpriteSheetTexture;
    this->renderWord = str;
    this->x_pos = x;
    this->y_pos = y;
    this->setText(renderWord);
}

int Word::getTextLength()
{
    return this->renderWord.length();
}

void Word::render(SDL_Renderer* gRenderer)
{
    for (int i = 0; i < this->renderWord.length(); i++)
    {
        characters[i].render(gRenderer);
    }
}

void Word::setText(string str)
{
    characters = new Character[this->renderWord.length()];
    for (int i = 0; i < this->renderWord.length(); i++)
    {
        characters[i].setTexture(str[i], this->charTexture, x_pos+(39*i), y_pos+8);
    }
    cout << "Success" << endl;
}

#include "SDL.h"
#include "SDL_image.h"
#include "iostream"
#include "string"
#include "Characters.h"

Character::Character()
{
    CharTexture = NULL;
}


Character::Character(LTexture* gSpriteSheetTexture, char c, int x_pos, int y_pos)
{
    this->shownChar = c;
    this->CharTexture = gSpriteSheetTexture;
    this->charRect.w = 42;
    this->charRect.h = 28;
    this->setPosition(x_pos, y_pos);
    this->setChar(c);
    this->CharTexture->setHeight(0);
    this->CharTexture->setWidth(0);
}


void Character::setTexture(char c, LTexture* gSpriteSheetTexture, int x_pos, int y_pos)
{
    this->shownChar = c;
    this->CharTexture = gSpriteSheetTexture;
    this->charRect.w = 42;
    this->charRect.h = 28;
    this->setPosition(x_pos, y_pos);
    this->setChar(c);
    this->CharTexture->setHeight(0);
    this->CharTexture->setWidth(0);
}



void Character::setPosition(int x , int y)
{
    this->x = x;
    this->y = y;
}


void Character::render(SDL_Renderer* gRenderer)
{
    CharTexture->render(this->x, this->y, gRenderer, &charRect);
}


void Character::setChar(char c)
{
    int ascii = c;
//    if (ascii <= 90 && ascii >= 65)
//    {
//        ascii-=65;
//        this->charRect.x = (ascii%11)*44;
//        this->charRect.y = ((int)(ascii/11))*48;
//    }
//    else
//    {
//       charRect.x = 0;
//       charRect.y = 0;
//       charRect.w = 33;
//       charRect.h = 41;
//    }
    int diff=0;

    ///selects the Character image according to its ascii value
    if(ascii==32)
    {
        charRect.x=168;
        charRect.y=256;
        charRect.w=10;
    }
    else if(ascii==33)
    {
        charRect.x=294;
        charRect.y=224;
    }
    else if(ascii>=48 && ascii<=57)
    {
        character_value=48;
        charRect.x = 168;
        charRect.y = 192;

        diff=ascii-character_value;
        if (diff>3)
        {
            charRect.x = 0;
            charRect.y +=33;
            character_value+=4;
            diff=ascii-character_value;
        }
        charRect.x+=42*diff;
    }
    else if(ascii==63)
    {
        charRect.x=252;
        charRect.y=224;
    }
    else if((ascii>=65 && ascii<=90) || (ascii>=97 && ascii<=122))
    {
        if((ascii>=97) && (ascii<=122))
            ascii-=32;
        character_value = 65;
        charRect.x = 0;
        charRect.y = 0;
        diff=ascii-character_value;
        charRect.y +=32*(diff/8);
        character_value+=8*(diff/8);
        diff=ascii-character_value;
        charRect.x+=42*diff;
    }

}

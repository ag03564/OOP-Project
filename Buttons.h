//#pragma once
//#include "SDL.h"
//#include "SDL_image.h"
//#include "iostream"
//#include "string"
//#include "Words.h"
//#include "Characters.h"
//#include "LTexture.h"
//using namespace std;
//
//enum State{Normal, Hover, Clicked};
//enum ButtonSprite
//{
//	BUTTON_SPRITE_MOUSE_OUT = 0,
//	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
//	BUTTON_SPRITE_MOUSE_DOWN = 2,
//	BUTTON_SPRITE_MOUSE_UP = 3,
//	BUTTON_SPRITE_TOTAL = 4
//};
//
//class Button
//{
//public:
//    Button(string Text, LTexture* CharTexture, LTexture* Texture, SDL_Rect Clip, int x_pos, int y_pos, int x_size = 0, int y_size = 0);
//    void render(SDL_Renderer* gRenderer);
//    void UpdateClip(SDL_Rect);
//private:
//    SDL_Rect spriteClips;
//    LTexture* btnTexture;
//    Word* BtnText;
//    int state;
//    int x_pos;
//    int y_pos;
//};
#pragma once
#include "LTexture.h"
#include "Point.h"
#include "Words.h"

enum State{Normal, Hover, Clicked};                                 ///Enumerating three states of buttons

enum ButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};


class Button
{
private:
    int width;  //width of each of the three parts of the button
    int ButtonWidth; //final width of the Button
    int height; //height of the Button
    std::string text;//Text on the button
    Word* word; //object of word class to be rendered over the button
    SDL_Rect spriteClips[3]; //sprite clips for each state of the button
    LTexture* spriteSheetTexture; //Texture of image consisting of Buttons
    Point position;//Position of the Button
    int state; //current state of the Button

public:
    ButtonSprite mCurrentSprite;
    void handleEvent( SDL_Event* e,SDL_Renderer* gRenderer );
    Button();
    Button(LTexture*,std::string, float, float);
    void Render(SDL_Renderer*);
    void Renderpause(SDL_Renderer*);
    ~Button();
    Point getPosition();
    int getWidth();
    int getHeight();
    std::string getText(); //get the text of the button
    void changeState(State); //changes the current state of the button
    void operator = (const Button& cpy); //operator overloading for assignment operator
    bool clicked(); //tells whether button is clicked or not
    int getstate();

//    void mouseMotionEvents(int x, int y);
//    void ChangeButtonState(State val, int ind);


};


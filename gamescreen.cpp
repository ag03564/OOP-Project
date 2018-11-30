#include "GameScreen.h"
GameScreen::GameScreen(LTexture* bgImage, LTexture* fontSprite,LTexture* buttonScreen) : Screen(bgImage,fontSprite)
{
    this->bgImage = bgImage;
    this->buttonScreen = buttonScreen;
//    std::string ButtonText[1]={" PAUSE "}; //Text on the buttons
    float posX=width-240;
    int posY=20;
//    ButtonCount = 1;
//    buttons = new Button[1];
//    for(int i=0; i<ButtonCount; i++)
//    {
//        buttons[i] = Button(fontSprite,ButtonText[i],posX, posY);
//
//    }
    ButtonCount = 1;
    buttons = new Button[1];
    buttons[0] = Button (fontSprite,"PAUSE",posX,posY);
}

void GameScreen::Render(long int& frame,SDL_Renderer* gRenderer)
{
    bgImage->render( 0, 0,gRenderer, NULL);
    //buttonScreen->render(0,0,gRenderer,NULL);

    buttons[0].Renderpause(gRenderer);
}

GameScreen::~GameScreen()
{
    std::cout<<"Menu Screen Destroyed"<<endl;
}



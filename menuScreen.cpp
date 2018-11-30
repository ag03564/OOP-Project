#include "menuScreen.h"
menuScreen::menuScreen(LTexture* bgImage, LTexture* fontSprite,LTexture* buttonScreen) : Screen(bgImage,fontSprite)
{
    this->bgImage = bgImage;
    this->buttonScreen = buttonScreen;
    std::string ButtonText[3]={"  START ", "  LOAD  ","  QUIT  "}; //Text on the buttons
    float posX=(width/4)*2.75;
    float posY=height/2-200;
    ButtonCount = 3;
    buttons = new Button[3];
    for(int i=0; i<ButtonCount; i++)
    {
        buttons[i] = Button(fontSprite,ButtonText[i],posX, posY + 100);
        posY+=100;
    }

}

void menuScreen::Render(long int& frame,SDL_Renderer* gRenderer)
{
    bgImage->render( 0, 0,gRenderer, NULL);
    //buttonScreen->render(0,0,gRenderer,NULL);
    for(int i=0; i<ButtonCount; i++)
    {
        buttons[i].Render(gRenderer);
    }
}

menuScreen::~menuScreen()
{
    std::cout<<"Menu Screen Destroyed"<<endl;
}


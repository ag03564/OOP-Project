#include "Buttons.h"
#include<vector>
#include<sstream>

using namespace std;

Button::Button()
{
    width=0;
    height=0;
    ButtonWidth=0;
    state=0;
    word = NULL;
}

Button::Button(LTexture* image,string text, float x, float y)
{
    state = Normal;                                               ///initial state of button is always Normal
    position.x = x;
    position.y = y;

    spriteSheetTexture=image;
    this->text=text;

    spriteClips[Normal].x = 0;
    spriteClips[Normal].y = 256;
    spriteClips[Normal].w = 32;
    spriteClips[Normal].h = 60;
    spriteClips[Hover].x = 0;
    spriteClips[Hover].y = 326;
    spriteClips[Hover].w = 32;
    spriteClips[Hover].h = 60;
    spriteClips[Clicked].x = 0;
    spriteClips[Clicked].y = 396;
    spriteClips[Clicked].w = 32;
    spriteClips[Clicked].h = 60;

    this->width = spriteClips[0].w;
    this->height = spriteClips[0].h;
//    int textLength= text.size();             ///size of the text
//    if(textLength%2==0)                     ///Button Width is decided on whether text size is even or odd
//        textLength=textLength-1;
//    ButtonWidth=width*(textLength+2);

    word = new Word(text,spriteSheetTexture,position.x+25,position.y+17);

}

void Button::Renderpause(SDL_Renderer* gRenderer) //FOR PAUSE BUTTON
{
    int textLength = word->getTextLength();

    spriteClips[state].x = 0;  ///selects the spriteClip according to Button State
    spriteSheetTexture->render( position.x, position.y, gRenderer, &spriteClips[state]);
    spriteClips[state].x=48;        ///Middle part of the Button

    int a=0;
    int posX=32;
    ///rendering middle part of the button as a background for each character in the Word
    for(int i=1; i<6; i++)
    {

        spriteSheetTexture->render( position.x+(32*i), position.y, gRenderer, &spriteClips[state]);

    }

    spriteClips[state].x=112;       ///Right part of the Button
    spriteSheetTexture->render( position.x+175, position.y , gRenderer, &spriteClips[state]);
    word->render(gRenderer);
}
void Button::Render(SDL_Renderer* gRenderer)
{
    int textLength = word->getTextLength();
    ///Position for the left part of the button


    spriteClips[state].x = 0;  ///selects the spriteClip according to Button State
    spriteSheetTexture->render( position.x, position.y, gRenderer, &spriteClips[state]);
    spriteClips[state].x=48;        ///Middle part of the Button

    int posX=32;
    ///rendering middle part of the button as a background for each character in the Word
    for(int i=1; i<9; i++)
    {

        spriteSheetTexture->render( position.x+(32*i), position.y, gRenderer, &spriteClips[state]);

    }

    spriteClips[state].x=112;       ///Right part of the Button
    spriteSheetTexture->render( position.x+287, position.y , gRenderer, &spriteClips[state]);
    word->render(gRenderer);
}

void Button::handleEvent( SDL_Event* e, SDL_Renderer* gRenderer )
{
    int textLength = word->getTextLength();
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if(( x < position.x) || ( x > position.x+320  ))
		{
		    state=0;
			inside = false;
		}
		else if(( y < position.y ) || ( y > position.y+50))
        {
		    state=0;
			inside = false;
		}
		//Mouse is outside button
		if( !inside )
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				state=1;
				break;

				case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				state=2;
				break;

				case SDL_MOUSEBUTTONUP:
				state=0;
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;
			}
		}
	}
}

Point Button::getPosition()
{
    return position;
}

int Button::getWidth()
{
    return ButtonWidth;
}
int Button::getstate()
{
    return state;
}
int Button::getHeight()
{
    return height;
}

string Button::getText()
{
    return text;
}

void Button::changeState(State val)
{
    state=val;
}
bool Button::clicked()
{
    return (state == Clicked);
}
Button::~Button()
{
    cout <<"Button " << text << " is destroyed" << endl;
    if (word != NULL)
    {
        delete word;
        word = NULL;
    }
}

void Button::operator = (const Button& cpy)
{
    state=cpy.state;
    position.x=cpy.position.x;
    position.y=cpy.position.y;
    spriteSheetTexture=cpy.spriteSheetTexture;
    text=cpy.text;
    spriteClips[Normal]=cpy.spriteClips[Normal];
    spriteClips[Hover]=cpy.spriteClips[Hover];
    spriteClips[Clicked]=cpy.spriteClips[Clicked];
    width=cpy.width;
    height=cpy.height;
    ButtonWidth = cpy.ButtonWidth;
    this->word = new Word(text,spriteSheetTexture,position.x,position.y+8);
}



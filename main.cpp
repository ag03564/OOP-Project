
//Using SDL, SDL_image, standard math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "iostream"
#include "Buttons.h"
#include <SDL_image.h>
#include "menuScreen.h"
#include "Screen.h"
#include "LTexture.h"
#include "Words.h"
#include "gamescreen.h"
//#include "pausescreen.h"

using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gBackgroundSurface = NULL;

SDL_Surface* loadSurface( std::string path );
SDL_Texture* addBackground();

LTexture Background;
LTexture ButtonTextureSheet;
LTexture FontTextureSheet;
LTexture GameTextureSheet;
LTexture PauseTextureSheet;

SDL_Rect ButtonTextureClip;
SDL_Rect Backgroundclip;
SDL_Rect Admiclip;


const int SCREEN_WIDTH = 1230;
const int SCREEN_HEIGHT = 540;


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
					success = false;
				}
                //Get window surface
                gScreenSurface = SDL_GetWindowSurface( gWindow );


			}
		}
	}

	return success;
}



bool loadMedia()
{
    bool success = true;
	if( !Background.loadFromFile( "Background.png", gRenderer) )
	{
		printf( "Failed to Background sheet texture!\n" );
		success = false;
	}

	if( !FontTextureSheet.loadFromFile( "XiroidFinal2.png", gRenderer) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}

    if( !ButtonTextureSheet.loadFromFile( "XiroidFinal2.png", gRenderer) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}

    if( !GameTextureSheet.loadFromFile( "newgame.png", gRenderer) )
	{
		printf( "Failed to game sprite sheet texture!\n" );
		success = false;
	}

	else
    {

    }
	return success;
}

void close()
{

	//Destroy window
	Background.free();
    FontTextureSheet.free();
    ButtonTextureSheet.free();


	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


SDL_Surface* loadSurface( std::string path )
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}


int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{

		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
            long int frame = 0;

			//Main loop flag
			bool mouseClicked=false;
			bool menusc=true;
			bool gamesc=false;
			bool pausesc=false;
			bool quit = false;
            //int x,y;

			//Event handler
			SDL_Event e;
//            SDL_Rect background;
//            background.x = 0;    background.y = 0;
//            background.w = SCREEN_WIDTH;    background.h = SCREEN_HEIGHT;
//            SDL_BlitScaled( gBackgroundSurface, NULL, gScreenSurface, &background );
//            SDL_UpdateWindowSurface(gWindow);
            //Button start(&FontTextureSheet,"START",SCREEN_WIDTH/2+200,SCREEN_HEIGHT/2-150);
            menuScreen menu(&Background,&FontTextureSheet,&FontTextureSheet);
            GameScreen gamestart(&GameTextureSheet,&FontTextureSheet,&FontTextureSheet);

            //Button btn(&FontTextureSheet,"  START  ",((SCREEN_WIDTH/4)*2.75),SCREEN_HEIGHT/2-200);
//            Button btn1(&FontTextureSheet,"  LOAD  ",((SCREEN_WIDTH/4)*2.75),SCREEN_HEIGHT/2-100);
//            Word aa("HELLO",&FontTextureSheet,SCREEN_WIDTH/2+300,100);

            SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);

//			Button btnstart("START", &FontTextureSheet, &ButtonTextureSheet, ButtonTextureClip, SCREEN_WIDTH/2+200, SCREEN_HEIGHT/2-150, 300, 60);
//			Button btnstart1("START", &FontTextureSheet, &ButtonTextureSheet, ButtonTextureClip, SCREEN_WIDTH/2+200, SCREEN_HEIGHT/2-150, 300, 60);
//
//			Button btnload("LOAD", &FontTextureSheet, &ButtonTextureSheet, ButtonTextureClip, SCREEN_WIDTH/2+200, SCREEN_HEIGHT/2-50, 300, 60);
//			Button btnload1("LOAD", &FontTextureSheet, &ButtonTextureSheet, ButtonTextureClip, SCREEN_WIDTH/2+200, SCREEN_HEIGHT/2, 300, 60);
//
//			Button btnsetting("SETTING", &FontTextureSheet, &ButtonTextureSheet, ButtonTextureClip, SCREEN_WIDTH/2+200, SCREEN_HEIGHT/2+50, 300, 60);
//
//
//			Button btnquit("QUIT", &FontTextureSheet, &ButtonTextureSheet, ButtonTextureClip, SCREEN_WIDTH/2+200, SCREEN_HEIGHT/2+150, 300, 60);
//			Button btnquit1("QUIT", &FontTextureSheet, &ButtonTextureSheet, ButtonTextureClip, SCREEN_WIDTH/2+200, SCREEN_HEIGHT/2+150, 300, 60);

            //While application is running`
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
//                    btn.handleEvent(&e,gRenderer);
//                    btn1.handleEvent(&e,gRenderer);
//					SDL_GetMouseState(&x,&y);
//                    if (e.type == SDL_MOUSEMOTION) //to handle all mouse motion events for all screens
//                    {
//                        btn.mouseMotionEvents(x,y);
//                    }
//
//                    if(e.type == SDL_MOUSEBUTTONUP && mouseClicked) //tp handle all mouse click events for all screens
//                    {
//
//                        btn.mouseClickEvents(x,y,buttonClick);
//
//                    }

//                    if (e.type==SDL_MOUSEBUTTONDOWN)
//                    {
//                        if(e.button.button==SDL_BUTTON_LEFT)
//                            mouseClicked=true;
//                    }
//                    if (e.type == SDL_MOUSEMOTION) //to handle all mouse motion events for all screens
//                    {
//                        menu.mouseMotionEvents( &e,gRenderer);
//                    }
//                    if(e.type == SDL_MOUSEBUTTONUP)
//                    {
//                        cout<<"aaaaaaaaa";
//                        menu.mouseMotionEvents(&e,gRenderer);
//
//                    }


				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				if (menusc)
                {
                    menu.Render(frame,gRenderer);
                    menu.mouseMotionEvents(&e,gRenderer);
                    if (menu.getButtons()[2].getstate()==2)
                    {
                        quit=true;
                    }
                    else if (menu.getButtons()[0].getstate()==2)
                    {
                        menusc=false;
                        gamesc=true;
                        cout<<"menu exit"<<endl;
                    }

                }
                if (gamesc)
                {
                    gamestart.Render(frame,gRenderer);
                    gamestart.mouseMotionEvents(&e,gRenderer);

                    cout<<"Game screen entered"<<endl;
                    if (gamestart.getButtonCount()[0].getstate()=2)
                    {
                        gamesc=false;
                        pausesc=true;

                    }

//
//                }
				}
//				if (pausesc)
//                {
//
//                }


                //gamestart.Render(frame,gRenderer);



				//Adding background.
                //SDL_RenderCopy(gRenderer, bgTexture, NULL, NULL);
                //btn.Render(gRenderer);
//                btn1.Render(gRenderer);
				SDL_RenderPresent( gRenderer );
			}
		}
	}
	}

	//Free resources and close SDL
	close();

	return 0;
}




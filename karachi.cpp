#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "Unit.h"
#include <string>

//The dimensions of the level
const int LEVEL_WIDTH = 1000;
const int LEVEL_HEIGHT = 600;
//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;
//global reference to png image sheets
SDL_Texture* road1 = NULL;
SDL_Texture* building1 = NULL;
SDL_Texture* teentalwar = NULL;
SDL_Texture* hbl = NULL;
SDL_Texture* chaarMinar = NULL;
SDL_Texture* tomb = NULL;
SDL_Texture* altafHussain = NULL;
//Scene textures


class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );

		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();


	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
        int mWidth;
		int mHeight;
};

//The dot that will move around on the screen
class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 10;

		//Initializes the variables
		Dot();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move();

		//Shows the dot on the screen relative to the camera
		void render( int camX, int camY );

		//Position accessors
		int getPosX();
		int getPosY();

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;
};

LTexture gDotTexture;
LTexture gBGTexture;


LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}


	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

Dot::Dot()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Dot::handleEvent( SDL_Event& e )
{

    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case
            SDLK_UP: mVelY -= DOT_VEL;break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case
            SDLK_LEFT: mVelX -= DOT_VEL;
            break;
            case
            SDLK_RIGHT: mVelX += DOT_VEL;
            break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case
            SDLK_LEFT: mVelX += DOT_VEL;
            break;
            case
            SDLK_RIGHT: mVelX -= DOT_VEL;
            break;
        }
    }
}

void Dot::move()
{
    //Move the dot left or right
    mPosX += mVelX;

    //If the dot went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > LEVEL_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the dot up or down
    mPosY += mVelY;

    //If the dot went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > LEVEL_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
    }
}

void Dot::render( int camX, int camY )
{
    //Show the dot relative to the camera
	gDotTexture.render( mPosX - camX, mPosY - camY );
}

int Dot::getPosX()
{
	return mPosX;
}

int Dot::getPosY()
{
	return mPosY;
}


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
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	if( !gBGTexture.loadFromFile( "bg.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	//load tank body
	road1 = loadTexture("road.jpeg");
    if(road1==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }


    building1 = loadTexture("buildings.png");
    if(building1==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }

    teentalwar = loadTexture("teentalwar.png");
    if(teentalwar==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }

    hbl = loadTexture("hbl.png");
    if(teentalwar==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }

    chaarMinar = loadTexture("chaarminar.png");
    if(chaarMinar==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }

    tomb = loadTexture("tomb.png");
    if(tomb==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }

    altafHussain = loadTexture("bhai.gif");
    if(altafHussain==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}

void close()
{
	//Free loaded images
	gDotTexture.free();
	gBGTexture.free();
	SDL_DestroyTexture(road1);
	road1 = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
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
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;
			SDL_Event e;

			Dot dot;

			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
			int cVelX = 0;
            camera.x = ( dot.getPosX() + Dot::DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
            camera.y = ( dot.getPosY() + Dot::DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

			Unit* r1 = new Unit(road1, 500, 550);
			Unit* r2 = new Unit(road1,  r1->x+ r1->mover.w, 550);
			Unit* r3 = new Unit(road1, r2->x + r2->mover.w, 550);
			Unit* r4 = new Unit(road1, r3->x + r3->mover.w, 550);
			Unit* r5 = new Unit(road1, r4->x + r4->mover.w, 550);
			Unit* r6 = new Unit(road1, r5->x + r5->mover.w, 550);
			Unit* r7 = new Unit(road1, r6->x + r6->mover.w, 550);
			Unit* b1 = new Unit(building1, 250, 350);
			Unit* b2 = new Unit(teentalwar, 950, 270);
			Unit* b3 = new Unit(hbl, 1500, 240);
			Unit* b4 = new Unit(building1, 2050, 457);
			Unit* b5 = new Unit(chaarMinar, 2800, 220);
			Unit* b6 = new Unit(building1, 3400, 380);
            Unit* b7 = new Unit(building1, 4200, 350);
            Unit* b8 = new Unit(tomb, 5000, 270);
            Unit* b9 = new Unit(altafHussain, 5800, 200);
            Unit* b10 = new Unit(building1, 6500, 457);
            bool pressed = NULL;
            int z = 0;
            //Event handler

			//While application is running
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

					dot.handleEvent( e );
					if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
                    {
                        pressed=true;
                    //Adjust the velocity
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_LEFT:
                                cVelX-=1;
                                z=2;
                                break;
                            case SDLK_RIGHT:
                                cVelX+=1;
                                z=3;
                                break;
                        }
                    }
                    //If a key was released
                    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
                    {
                        pressed=false;
                    //Adjust the velocity
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_LEFT:
                                cVelX+=1;
                                //z=2;
                                break;
                            case SDLK_RIGHT:
                                cVelX-=1;
                                //z=3;
                                break;
                        }
                    }
				}
                camera.x += cVelX;
                if ((pressed==true) & (camera.x < gBGTexture.getWidth() - camera.w) & (camera.x >0))
                {
                    r1->Move(z);
                    r2->Move(z);
                    r3->Move(z);
                    r4->Move(z);
                    r5->Move(z);
                    r6->Move(z);
                    r7->Move(z);
                    b1->Move(z);
                    b2->Move(z);
                    b3->Move(z);
                    b4->Move(z);
                    b5->Move(z);
                    b6->Move(z);
                    b7->Move(z);
                    b8->Move(z);
                    b9->Move(z);
                    b10->Move(z);
                }

                /*else if ((pressed == false) & (z == 2))
                {
                    a->Move(3);
                    b->Move(3);
                    c->Move(3);
                }
                else if ((pressed == false) & (z == 3))
                {
                    a->Move(2);
                    b->Move(2);
                    c->Move(2);
                }*/

				//Move the dot
				dot.move();

				//Center the camera over the dot

				//Keep the camera in bounds
				if( camera.x < 0 )
				{
					camera.x = 0;

				}
				if( camera.y < 0 )
				{
					camera.y = 0;
				}
				if(camera.x > gBGTexture.getWidth() - camera.w)
                {
                    camera.x = gBGTexture.getWidth() - camera.w;

                }
				if( camera.y > LEVEL_HEIGHT - camera.h )
				{
					camera.y = LEVEL_HEIGHT - camera.h;
				}
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

//
                    gBGTexture.render( 0, 0, &camera );

                    r1->Draw(gRenderer);
                    r2->Draw(gRenderer);
                    r3->Draw(gRenderer);
                    r4->Draw(gRenderer);
                    r5->Draw(gRenderer);
                    r6->Draw(gRenderer);
                    r7->Draw(gRenderer);
                    b1->srcRect.h = 200;
                    b1->mover.h = 400;
                    b1->mover.w = 800;
                    b1->Draw(gRenderer);
                    b2->Draw(gRenderer);
                    b3->mover.h = 500;
                    b3->Draw(gRenderer);
                    b4->srcRect.y=250;
                    b4->srcRect.h = 200;
                    b4->mover.h = 400;
                    b4->mover.w = 800;
                    b4->Draw(gRenderer);
                    b5->Draw(gRenderer);
                    b6->srcRect.y= 400;
                    b6->srcRect.h = 200;
                    b6->mover.h = 400;
                    b6->mover.w = 800;
                    b6->Draw(gRenderer);
                    b7->srcRect.h = 200;
                    b7->mover.h = 400;
                    b7->mover.w = 800;
                    b7->Draw(gRenderer);
                    b8->Draw(gRenderer);
                    b9->Draw(gRenderer);
                    b10->srcRect.y=250;
                    b10->srcRect.h = 200;
                    b10->mover.h = 400;
                    b10->mover.w = 800;
                    b10->Draw(gRenderer);
				//Update screen
                    SDL_Delay(1);
                    SDL_RenderPresent( gRenderer );
            }

				//Clear screen

		}
			//delete a;
	}
    close();

	return 0;
}

	//Free resources and close SDL

 //In today's lab you will make a new tank say, "NewTank" that inherits from
 //Unit class and Display it on screen
 //You will then create a linked list that will load up 10 tanks and newtanks
 //and show them on screen. When the program finishes, everything must deallocate.

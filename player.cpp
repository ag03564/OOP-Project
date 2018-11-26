#include "Player.h"
#include<SDL_image.h>
#include<iostream>


Player::Player(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int framesX, int framesY)
{
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	positionRect.x = x;
	positionRect.y = y;

	//textureWidth = cropRect.w;

	cropRect.w /= framesX;
	cropRect.h /= framesY;

	frameWidth = 40;
	 positionRect.w  = 40;
    cropRect.w = 40;

	frameHeight = 60 ;
	positionRect.h = 60;
	cropRect.h = 60;


	isActive = false;

	static int playerNumber = 0;
	//playerNumber++;

	if(playerNumber == 1)
	{
		keys[0] = SDL_SCANCODE_W;
		keys[1] = SDL_SCANCODE_S;
		keys[2] = SDL_SCANCODE_A;
		keys[3] = SDL_SCANCODE_D;
	}
	else
	{
		keys[0] = SDL_SCANCODE_UP;
		//keys[1] = SDL_SCANCODE_DOWN;
		keys[2] = SDL_SCANCODE_LEFT;
		keys[3] = SDL_SCANCODE_RIGHT;
	}

	moveSpeed = 600.0f;
	//jump = 200.0f;
}


Player::~Player()
{
	SDL_DestroyTexture(texture);
}

void Player:: Update(float delta, const Uint8 *keyState)
{
    const int jumpHeight= 10;
    bool isJumping= false;
    bool isFalling= false;
    int jump = 0;
    int up = 200.0f;

	if(keyState[keys[0]])
	{
	    if(isJumping != true)
        {
            isJumping = true;
        }
        		//Jumping
            while (isJumping == true )
            {
                    if( jump >= jumpHeight || isFalling == true )
                    {
                            jump--;
                            if(jump == 0)
                            {
                                isFalling = false;
                                isJumping = false;
                            }
                            positionRect.y+= 20;
                            isFalling = true;
                    }
                    else if( jump <= 0 && isFalling == true )
                    {
                            jump - 0;
                            isFalling = false;
                            isJumping = false;
                    }
                    else
                    {
                        //isFalling = true;
                            jump++;
                            //positionRect.y--;
                            positionRect.y -= 20; //* 0.1;
                    }
            }
	    //int val = positionRect.y;
		//positionRect.y -= up * 0.1;
		//positionRect.y = val;
		//cropRect.y = frameHeight * 3;
	}
	/*else if(keyState[keys[1]])
	{
		positionRect.y += moveSpeed * delta;
		cropRect.y = 0;
	}*/
	else if(keyState[keys[2]])
	{
		positionRect.x -= moveSpeed * delta;
		cropRect.y = frameHeight;
	}
	else if(keyState[keys[3]])
	{
		positionRect.x += moveSpeed * delta;
		cropRect.y = frameHeight * 2;
	}
	else
		isActive = false;

	if(isActive)
	{
		frameCounter += delta;

		if(frameCounter >= 0.25f)
		{
			frameCounter = 0;
			cropRect.x += frameWidth;
			if(cropRect.x >= textureWidth)
				cropRect.x = 0;
		}
	}
	else
	{
		frameCounter = 0;
		cropRect.x = frameWidth;
	}
}

void Player::Draw(SDL_Renderer *renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}

bool Player::IntersectsWith(Player &p)
{
	if(positionRect.x + positionRect.w < p.positionRect.x || positionRect.x > p.positionRect.x + p.positionRect.w ||
		positionRect.y + positionRect.h < p.positionRect.y || positionRect.y > p.positionRect.y + p.positionRect.h)
	{
		SDL_SetTextureColorMod(texture, 255, 255, 255);
		return false;
	}
		SDL_SetTextureColorMod(texture, 255, 0, 0);
	return true;
}


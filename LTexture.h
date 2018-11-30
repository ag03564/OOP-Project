#pragma once
#include "string"
#include "iostream"
#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>

class LTexture
{
public:
    LTexture();
    ~LTexture();
    //Loads image at specified path
    bool loadFromFile( std::string path, SDL_Renderer* gRenderer);
    //Deallocates texture
    void free();
    //Renders texture at given point
    void render( int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip);
    //Gets image dimensions
    int getWidth();
    int getHeight();
    void setWidth(int);
    void setHeight(int);
private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    //Image dimensions
    int mWidth;
    int mHeight;

};

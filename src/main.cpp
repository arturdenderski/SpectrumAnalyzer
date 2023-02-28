#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "../include/app.h"

int main()
{
    const char* filePath = "../res/audioFile8.wav";

    App app;
    app.run(filePath);

    return 0;
}
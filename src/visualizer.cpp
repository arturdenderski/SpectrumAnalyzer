#include <iostream>

#include "../include/visualizer.h"

Visualizer::Visualizer()
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "Failed to init SDL Video, error: " << SDL_GetError();
        return;
    }

    int win_width = 2047;
    int win_height = 720;

    this->sdl_window = SDL_CreateWindow(
        "Spectrum Analyzer",                        // window title
        SDL_WINDOWPOS_UNDEFINED,                    // initial x position
        SDL_WINDOWPOS_UNDEFINED,                    // initial y position
        win_width,                                  // width, in pixels
        win_height,                                 // height, in pixels
        SDL_WINDOW_OPENGL                           // flags
    );

    if (this->sdl_window == nullptr)
    {
        std::cerr << "Could not create a window: " << SDL_GetError();
    }

    this->sdl_renderer = SDL_CreateRenderer(this->sdl_window, -1, 0);
}

void Visualizer::displaySpectrum(CArray &complexFFT, double samplesPerSecond)
{
    SDL_Renderer* renderer = this->sdl_renderer;

    SDL_RenderClear(renderer);

    for(int i = 1; i < complexFFT.size() / 2; i++)
    {
        double dbValue = 10 * log10(fabs(complexFFT[i]) / (255 * complexFFT.size()));

        if(dbValue < -40.0)
        {
            dbValue = 0.001;
        }
        else
        {
            if(dbValue <= 0)
            {
                dbValue = (dbValue + 40.0) / 40.0;
            }
            else
            {
                dbValue = 1.0;
            }
        }

        SDL_Rect rect;
        rect.w = 1;
        rect.h = std::ceil(dbValue * 720);
        rect.x = i - 1;
        rect.y = 720 - rect.h;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }

    SDL_RenderPresent(renderer);
}
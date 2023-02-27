#include <iostream>

#include "../include/visualizer.h"

Visualizer::Visualizer()
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "Failed to init SDL Video, error: " << SDL_GetError();
        return;
    }

    this->sdl_window = SDL_CreateWindow(
        "Spectrum Analyzer",                        // window title
        SDL_WINDOWPOS_UNDEFINED,                    // initial x position
        SDL_WINDOWPOS_UNDEFINED,                    // initial y position
        this->WINDOW_WIDTH,                         // width, in pixels
        this->WINDOW_HEIGHT,                        // height, in pixels
        SDL_WINDOW_OPENGL                           // flags
    );

    if (this->sdl_window == nullptr)
    {
        std::cerr << "Could not create a window: " << SDL_GetError();
    }

    this->sdl_renderer = SDL_CreateRenderer(this->sdl_window, -1, 0);
}

void Visualizer::displayWrap(CArray &complexFFT, double samplesPerSecond, CArray fftArray)
{
    SDL_SetRenderDrawColor(this->sdl_renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->sdl_renderer);

    this->renderSpectrum(complexFFT, samplesPerSecond);
    this->renderWaveform(fftArray);
    
    SDL_SetRenderDrawColor(this->sdl_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(this->sdl_renderer);
}

void Visualizer::renderSpectrum(CArray &complexFFT, double samplesPerSecond)
{
    
    for(int i = 1; i < complexFFT.size() / 2; i++)
    {
        double dbValue = 10 * log10(fabs(complexFFT[i]) / (255 * complexFFT.size()));

        if(dbValue < -45.0)
        {
            dbValue = 0.001;
        }
        else
        {
            if(dbValue <= 0)
            {
                dbValue = (dbValue + 45.0) / 45.0;
            }
            else
            {
                dbValue = 1.0;
            }
        }

        SDL_Rect rect;
        rect.w = 1;
        rect.h = std::ceil(dbValue * 600);
        rect.x = i - 1;
        rect.y = this->WINDOW_HEIGHT - rect.h;
        
        SDL_SetRenderDrawColor(this->sdl_renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(this->sdl_renderer, &rect);
    }
}

void Visualizer::renderWaveform(CArray preFFT)
{
    SDL_SetRenderDrawColor(this->sdl_renderer, 255, 255, 255, 255);
    for(int i = 0; i < this->WINDOW_WIDTH; i++)
    {
        //SDL_RenderDrawPoint(this->sdl_renderer, i , 150 + (static_cast<int>(real(preFFT[i]) / 255.0 * 150.0)));

        SDL_RenderDrawLine(this->sdl_renderer, i, 150 + (static_cast<int>(real(preFFT[i]) / 255.0 * 150.0)), i + 1, 150 + (static_cast<int>(real(preFFT[i + 1]) / 255.0 * 150.0)));
        
        // int scaledSample = static_cast<int>(real(preFFT[i]) / 255.0 * 150.0);

        // SDL_Rect rect;
        // rect.w = 1;
        // rect.h = scaledSample < 0 ? -scaledSample : scaledSample;
        // rect.x = i;
        // rect.y = scaledSample < 0 ? 150 : 150 - rect.h;
        // SDL_RenderFillRect(this->sdl_renderer, &rect);
    }
}

void Visualizer::resize(int width)
{
    this->WINDOW_WIDTH = width;
    SDL_SetWindowSize(this->sdl_window, width, this->WINDOW_HEIGHT);
    SDL_DestroyRenderer(this->sdl_renderer);
    this->sdl_renderer = SDL_CreateRenderer(this->sdl_window, -1, 0);
}
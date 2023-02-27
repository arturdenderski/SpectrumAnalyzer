#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <SDL2/SDL.h>
#include <valarray>
#include <complex>
#include <vector>
#include <math.h>
#include <memory>

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

class Visualizer
{
private:
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;
public:
    Visualizer();
    void displaySpectrum(CArray &complexFFT, double samplesPerSecond);
};

struct AudioData
{
	Uint8* pos;
	Uint32 length;
    SDL_AudioSpec spec;
    int numChannels;
    int bytesPerSample;
    bool isBigEndian;
    double binSize;
    std::shared_ptr<Visualizer> visualizer;
};

#endif
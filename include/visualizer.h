#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <SDL2/SDL.h>
#include <valarray>
#include <complex>
#include <vector>
#include <math.h>
#include <memory>
#include <map>

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

class Visualizer
{
private:
    int WINDOW_WIDTH = 1600;
    int WINDOW_HEIGHT = 900;
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;
public:
    Visualizer();
    void displayWrap(CArray &complexFFT, double samplesPerSecond, CArray fftArray);
    void renderSpectrum(CArray &complexFFT, double samplesPerSecond);
    void renderWaveform(CArray preFFT);
    void resize(int width);
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
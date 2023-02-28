#ifndef APP_H
#define APP_H

#include <memory>

#include "visualizer.h"
#include "dataprocess.h"

void customCallback(void *audioData, Uint8 *stream, int streamLength);

class App
{
private:
    std::shared_ptr<Visualizer> visualizer;
    AudioData audioData;
    SDL_AudioSpec audioSpec;
    SDL_AudioSpec deviceSpec;
    SDL_AudioDeviceID audioDeviceID;
public:
    App();
    void run(const char* filePath);
};

#endif
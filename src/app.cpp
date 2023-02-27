#include <iostream>

#include "../include/app.h"

void customCallback(void *audioData, Uint8 *stream, int streamLength)
{
    AudioData* audio = static_cast<AudioData*>(audioData);

    if(audio->length == 0)
    {
        return;
    }

    Uint32 length = streamLength;
    length = (length > audio->length ? audio->length : length);

    SDL_memcpy(stream, audio->pos, length);

    CArray fftArray = dataProcess::streamToCArray(audio->pos, length, audio->numChannels, audio->bytesPerSample, audio->isBigEndian);
    dataProcess::fft(fftArray);
    audio->visualizer->displaySpectrum(fftArray, static_cast<double>(audio->spec.freq));
    
    audio->pos += length;
    audio->length -= length;
}

App::App()
{
    this->visualizer = std::make_shared<Visualizer>();
    this->audioData.visualizer = this->visualizer;
}

void App::run(const char* filePath)
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    SDL_setenv("SDL_AUDIODRIVER", "directsound", 1);
    #endif

    if(SDL_Init(SDL_INIT_AUDIO))
    {
        std::cerr << "Failed to init SDL Audio, error: " << SDL_GetError();
        return;
    }

    if(!SDL_LoadWAV(filePath, &(this->audioSpec), &(this->audioData.pos), &(this->audioData.length)))
    {
        std::cerr << "Could not load a file!";
        return;
    }

    Uint8* wavStart = this->audioData.pos;
    Uint32 wavLength = this->audioData.length;

    this->audioData.numChannels = static_cast<int>(this->audioSpec.channels);
    this->audioData.bytesPerSample = static_cast<int>(SDL_AUDIO_BITSIZE(this->audioSpec.format)) / 8;
    this->audioData.isBigEndian = SDL_AUDIO_ISBIGENDIAN(this->audioSpec.format);
    this->audioData.spec = this->audioSpec;
    this->audioData.binSize = this->audioSpec.freq / (this->audioSpec.samples);

    this->audioSpec.callback = customCallback;
    this->audioSpec.userdata = &(this->audioData);
    
    this->audioDeviceID = SDL_OpenAudioDevice(NULL, 0, &(this->audioSpec), NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

    if(this->audioDeviceID == 0)
    {
        std::cerr << "Could not access the audio device!" << SDL_GetError();
        return;
    }

    bool isRunning = true;
    bool isPlaying = false;
    SDL_Event sdl_event;

    SDL_PauseAudioDevice(this->audioDeviceID, 0);

    while(isRunning)
    {
        if(SDL_PollEvent(&sdl_event) != 0)
        {
            if(sdl_event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            if(sdl_event.type == SDL_KEYUP && sdl_event.key.keysym.sym == SDLK_SPACE)
            {
                isPlaying = isPlaying ? 0 : 1;
                SDL_PauseAudioDevice(this->audioDeviceID, isPlaying);
            }
        }
        else if(this->audioData.length <= 0)
        {
            this->audioData.pos = wavStart;
            this->audioData.length = wavLength;
        }
    }

    SDL_PauseAudioDevice(this->audioDeviceID, 1);
    SDL_CloseAudioDevice(this->audioDeviceID);
    SDL_FreeWAV(wavStart);
}
#ifndef DATAPROCESS_H
#define DATAPROCESS_H

#include "visualizer.h"

namespace dataProcess
{
    const double PI = 3.141592653589793238460;
    void fft(CArray &samples);
    CArray streamToCArray(Uint8 *stream, Uint32 &length, int &numChannels, int &bytesPerSample, bool &isBigEndian);
}

#endif
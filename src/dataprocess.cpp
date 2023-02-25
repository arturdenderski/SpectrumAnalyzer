#include <iostream>

#include "../include/dataprocess.h"

namespace dataProcess
{
    //https://rosettacode.org/wiki/Fast_Fourier_transform#C++
    void fft(CArray &samples)
    {
        const size_t N = samples.size();
        if (N <= 1) return;

        CArray even = samples[std::slice(0, N/2, 2)];
        CArray  odd = samples[std::slice(1, N/2, 2)];

        fft(even);
        fft(odd);

        for (size_t k = 0; k < N/2; ++k)
        {
            Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
            samples[k    ] = even[k] + t;
            samples[k+N/2] = even[k] - t;
        }
    }

    CArray streamToCArray(Uint8 *stream, Uint32 &length, int &numChannels, int &bytesPerSample, bool &isBigEndian)
    {
        CArray samples = CArray(length / (bytesPerSample * numChannels));

        for(int i = 0; i < length; i += bytesPerSample * numChannels)
        {
            samples[i / (bytesPerSample * numChannels)] = Complex(static_cast<double>(stream[i] + stream[i + 1]) / 2.0, 0.0);
        }

        return samples;
    }
}
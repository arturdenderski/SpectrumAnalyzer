#include "../include/app.h"

int main()
{
    const char* filePath = "../res/audioFile16.wav";

    App app;
    app.run(filePath);

    return 0;
}
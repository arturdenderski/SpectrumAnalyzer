#include "../include/app.h"

int main()
{
    const char* filePath = "../res/audioFile8.wav";

    App app;
    app.run(filePath);

    return 0;
}
# Simple Spectrum Analyzer using SDL and FFT algorithm

![App Preview](https://github.com/arturdenderski/SpectrumAnalyzer/blob/main/res/appGif.gif)

## Dependencies

**On Debian/Ubuntu based distributions:**

- [Git](https://git-scm.com/)
- [C++ Compiler (gcc)](https://gcc.gnu.org/)
- [Cmake](https://cmake.org/)
- [SDL2](https://www.libsdl.org/)

```
sudo apt-get install git build-essential pkg-config cmake cmake-data libsdl2-dev
```

## Build instructions

```sh
# Clone this repo
git clone https://github.com/arturdenderski/SpectrumAnalyzer
cd SpectrumAnalyzer
# Create a build folder
mkdir build
cd build
# Build
cmake ..
make
# Run
./SpectrumAnalyzer
```

## Controls:

- Space - Pause
# Simple Spectrum Analyzer Using SDL And FFT Algorithm

<p align="center">
<img width="80%" alt="App Preview" src="https://github.com/arturdenderski/SpectrumAnalyzer/blob/main/res/appGif.gif">
</p>

## Dependencies

**On Debian/Ubuntu based distributions:**

- [Git](https://git-scm.com/)
- [C++ Compiler (gcc)](https://gcc.gnu.org/)
- [Cmake](https://cmake.org/)
- [SDL2](https://www.libsdl.org/)

```sh
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

## Controls

- Space - Pause

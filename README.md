# Image Reader `WIP`
Implement Interface for common image format

- Read/Write PNG, JPEG and TIFF.
- Implement basic image processing operations.

## Depednecy
- CMake
- Boost
- Qt5 `For Testing`
- LibPNG
- LibJPEG
- libTIFF
- libZLIB

### Fedora 24
```sh
$ sudo dnf install cmake cmake-gui        # Some time I preface using cmake-gui instead of cmake
$ sudo dnf install qt-creator.x86_64      # I install all qt and qtcreator
$ sudo dnf install boost-devel.x86_64
$ sudo dnf install turbojpeg-devel.x86_64
$ sudo dnf install libpng-devel.x86_64
$ sudo dnf install libtiff-devel.x86_64
```

### Usage
```c++
#include "ImageReader.hpp"

int main(int argc, char* argv[]){
    BaseImage im("Lenna.jpg");
    im.save("Lenna.png");
}
```

> Feel free to give advice.

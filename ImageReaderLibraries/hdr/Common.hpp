#ifndef COMMON_H
#define COMMON_H

#pragma once
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <chrono>

using uchar = unsigned char;
using uint = unsigned int;

struct Timer{
    Timer(){
        t1 = std::chrono::high_resolution_clock::now();
    }

    void reset(){
        t1 = std::chrono::high_resolution_clock::now();
    }

    template<class _castTime>
    std::string end()
    {
        auto t2 = std::chrono::high_resolution_clock::now();

        return std::to_string(std::chrono::duration_cast<_castTime>(t2-t1).count());
    }

protected:
    std::chrono::_V2::system_clock::time_point t1;
};

template<typename T>
struct RGB{
    T R;
    T G;
    T B;
};

static inline void
writeImage(const std::string& _imageName, char* _data, const std::size_t fileSize){
    std::ofstream out(_imageName, std::ofstream::binary);
    out.write(_data, fileSize);
    out.close();
}

using RGB8 = RGB<uchar>;

#endif //COMMON_H

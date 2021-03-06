#ifndef COMMON_HPP
#define COMMON_HPP

#pragma once
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <chrono>
#include <boost/format.hpp>

using uchar = unsigned char;
using uint = unsigned int;

template<typename T>
struct TimerName{
    static std::string type(){
        return typeid(T).name();
    }
};

template<>
struct TimerName<std::chrono::seconds>{
    static std::string type(){
        return std::string("seconds");
    }
};

template<>
struct TimerName<std::chrono::milliseconds>{
    static std::string type(){
        return std::string("milliseconds");
    }
};

template<>
struct TimerName<std::chrono::nanoseconds>{
    static std::string type(){
        return std::string("nanoseconds");
    }
};


struct Timer{
    Timer(){
        t1 = std::chrono::high_resolution_clock::now();
    }

    void reset(){
        t1 = std::chrono::high_resolution_clock::now();
    }

    template<class _castTime>
    double end()
    {
        auto t2 = std::chrono::high_resolution_clock::now();

        return std::chrono::duration_cast<_castTime>(t2-t1).count();
    }

    template<class _castTime>
    void end(std::ostream& _stream, std::string _prefix){
        const auto t2 = std::chrono::high_resolution_clock::now();
        _stream << boost::format("%1% : %2% %3%\n")
            % ((_prefix.empty()) ? "Time : " : std::move(_prefix))
            %  std::chrono::duration_cast<_castTime>(t2-t1).count()
            % TimerName<_castTime>::type();
    }

protected:
    std::chrono::_V2::system_clock::time_point t1;
};

enum class ImageFormat {
  None = -1,
  JPEG = 0,
  PNG,
  GIF,
  TIF,
};

enum class PixelFormat {
    None = -1,
    Gray = 0,
    RGB8,
    YUV,
    Bayer,
    NV12
};

template<typename T>
struct RGB{
    T R;
    T G;
    T B;
};

using RGB8 = RGB<uchar>;

static inline void
writeImage(const std::string& _imageName, char* _data, const std::size_t fileSize){
    std::ofstream out(_imageName, std::ofstream::binary);
    out.write(_data, static_cast<long>(fileSize));
    out.close();
}

#endif //COMMON_HPP

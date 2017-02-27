#ifndef IMAGE_PROCESSING_ALGORIRHM
#define IMAGE_PROCESSING_ALGORIRHM
#pragma once
#include <cmath>
#include <functional>
#include "ImageReader.hpp"

namespace ConvertImageFormat{
template<template<typename> typename T = RGB, typename I = uchar>
std::vector<I> toSoA(const std::vector<I>&  _ptr, const int _width, const int _height){
    using pixel = T<I>;

    auto temp = std::vector<I>(_ptr.size());
    auto imageSize = _width * _height;

    auto tempR = temp.data();
    auto tempB = tempR + imageSize;
    auto tempG = tempB + imageSize;

    auto ptr = reinterpret_cast<pixel const*>(&_ptr[0]);
    for(int j = 0; j < _height; ++j){
        for(int i = 0; i < _width; ++i){
            auto tempPixel = *ptr++;
            *tempR++ = tempPixel.R;
            *tempG++ = tempPixel.G;
            *tempB++ = tempPixel.B;
        }
    }
    return temp;
}
template<template<typename> typename T = RGB, typename I = uchar>
std::vector<I> toAoS(const std::vector<I>& _ptr, const int _width, const int _height){
    using pixel = T<I>;

    auto imageSize = _width * _height;
    auto tempR = _ptr.data();
    auto tempB = tempR + imageSize;
    auto tempG = tempB + imageSize;

    auto temp = std::vector<I>(_ptr.size());
    auto ptr = reinterpret_cast<pixel*>(&temp[0]);
    for(int j = 0; j < _height; ++j){
        for(int i = 0; i < _width; ++i){
            *ptr++ = {*tempR++, *tempG++, *tempB++};
        }
    }
    return temp;
}
}

namespace Scale{
    std::vector<uchar>
    scale(const std::vector<uchar> &_input,
          int _w1, int _h1,
          int _w2, int _h2){
        std::vector<uchar> output(_w2 * _h2);
        double x_ratio = _w1 / (double) _w2;
        double y_ratio = _h1 / (double) _h2;

        double px = 0.0, py = 0.0;
        for(int j = 0; j < _h2; ++j){
            for(int i = 0; i < _w2; ++i){
                px = std::floor(i*x_ratio);
                py = std::floor(j*y_ratio);

                output[(j * _w2) + i] = _input[(int)(py * _w1) + px];
            }
        }

        return output;
    }

    std::vector<uchar>
    scale2(const std::vector<uchar> &_input,
          int _w1, int _h1,
          int _w2, int _h2){
        std::vector<uchar> output(_w2 * _h2);
        int x_ratio = (int)((_w1<<16)/_w2) + 1;
        int y_ratio = (int)((_h1<<16)/_h2) + 1;

        int px = 0, py = 0;
        for(int j = 0; j < _h2; ++j){
            for(int i = 0; i < _w2; ++i){
                px = ((i*x_ratio)>>16);
                py = ((j*y_ratio)>>16);

                output[(j * _w2) + i] = _input[(int)(py * _w1) + px];
            }
        }

        output;
    }

    std::vector<uchar>
    scale3(const std::vector<uchar> &_input,
          int _w1, int _h1,
          int _w2, int _h2){
        std::vector<uchar> output(_w2 * _h2);
        int x_ratio = (int)((_w1<<16)/_w2) + 1;
        int y_ratio = (int)((_h1<<16)/_h2) + 1;

        int px = 0, py = 0;
        auto outputPtr = output.data();
        for(int j = 0; j < _h2; ++j){
            for(int i = 0; i < _w2; ++i){
                px = ((i*x_ratio)>>16);
                py = ((j*y_ratio)>>16);

                *(outputPtr++) = _input[(int)(py * _w1) + px];
            }
        }

        return output;
    }

    std::vector<uchar>
    scale4(const std::vector<uchar> &_input,
          int _w1, int _h1,
          int _w2, int _h2){
        std::vector<uchar> output(_w2 * _h2);
        int x_ratio = (int)((_w1<<16)/_w2) + 1;
        int y_ratio = (int)((_h1<<16)/_h2) + 1;

        int x2, y2 ;
        for (int i=0;i<_h2;i++)
        {
            auto t = output.data() + i*_w2;
            y2 = ((i*y_ratio)>>16);
            auto p = _input.data() + y2*_w1;
            int rat = 0;
            for (int j=0;j<_w2;j++)
            {
                x2 = (rat>>16);
                *t++ = p[x2];
                rat += x_ratio;
            }
        }

        return output;
    }
}

namespace RGB2Gray{
    inline uchar Lightness(const RGB8& _value){
        return (std::min(_value.R, std::min(_value.B, _value.G)) +
                (std::max(_value.R, std::max(_value.B, _value.G))))/2;
    }
    inline uchar Average(const RGB8& _value){
        return (_value.R + _value.G + _value.B) / 3;
    }
    inline uchar Luminosity(const RGB8& _value){
        return static_cast<uchar>(
                    0.21 * _value.R +
                    0.72 * _value.G +
                    0.07 * _value.B);
    }

    auto
    convertColor(BaseImage& _image, std::function<uchar (const RGB8&)> _fun){
        auto width = _image.getWidth();
        auto height = _image.getHeight();

        std::vector<uchar> returnVec(width * height);
        uchar* out = &returnVec[0];
        auto ptr = _image.get();
        for(int j = 0; j < height; ++j){
            for(int i = 0; i < width; ++i){
                RGB8 temp = *reinterpret_cast<RGB8*>(ptr);
                *(out++) = _fun(temp);
                ptr += 3;
            }
        }

        return returnVec;
    }
}

namespace Convolution{
    enum class Padding{
        Clip,
        Mirror,
        Repetition
    };

    uchar*
    Filter(BaseImage& _image, std::function<uchar ()> _fun, Padding _padding){
        return nullptr;
    }
}
#endif //!IMAGE_PROCESSING_ALGORIRHM

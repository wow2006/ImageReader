#ifndef ENCODER_TIFF_HPP
#define ENCODER_TIFF_HPP
#pragma once
#include "Encoder.hpp"

namespace Encoder {
    class TiffEncoder : public EncoderInterface{
    public:
        bool encode(uchar *_uncompressedPtr, const int _width, const int _height, const int _channels,
                    std::vector<uchar> &_compressedPtr, std::size_t &_fileSize, const int JPEG_QUALITY);
    };
}

#endif //!ENCODER_TIFF_HPP

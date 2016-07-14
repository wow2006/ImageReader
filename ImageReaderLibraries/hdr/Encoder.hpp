#ifndef EECODER_HPP
#define EECODER_HPP
#pragma once
#include "Common.hpp"
#include "ImageReader.hpp"

namespace Encoder {
    class EncoderInterface{
    public:
        virtual ~EncoderInterface(){}

        virtual bool encode(uchar *_uncompressedPtr, const int _width, const int _height, const int _channels,
                       std::vector<uchar> &_compressedPtr, std::size_t& _fileSize, const int JPEG_QUALITY = 75) = 0;
    };

    std::unique_ptr<EncoderInterface> getEncoder(BaseImage::ImageFormat _format);
}

#endif //!DECODER_HPP

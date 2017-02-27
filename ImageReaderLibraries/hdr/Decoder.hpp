#ifndef DECODER_HPP
#define DECODER_HPP

#pragma once
#include "ImageReader.hpp"

namespace Decoder{
    class DecoderInterface{
    public:
        virtual ~DecoderInterface() = 0;

        virtual bool decode(std::vector<uchar>& _inputPtr, std::vector<uchar>&_output,
                             int &_width, int &_height, int &_channel) = 0;

        static std::unique_ptr<DecoderInterface>
        getDecoder(ImageFormat _format);
    };
}

#endif // !DECODER_HPP

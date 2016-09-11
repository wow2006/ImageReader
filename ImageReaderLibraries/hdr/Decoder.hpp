#ifndef DECODER_HPP
#define DECODER_HPP

#pragma once
#include "Common.hpp"
#include "ImageReader.hpp"
#include <memory>

namespace Decoder{
    class DecoderInterface{
    public:
        virtual ~DecoderInterface(){}

        virtual bool decode(std::vector<uchar>& _inputPtr, std::vector<uchar>&_output,
                             int &_width, int &_height, int &_channel) = 0;
    };

    std::unique_ptr<DecoderInterface> getDecoder(ImageFormat _format);
}

#endif // !DECODER_HPP

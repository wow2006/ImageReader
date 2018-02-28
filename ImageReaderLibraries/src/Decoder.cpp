// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <exception>
#include "Decoder.hpp"
#include "DecoderJPEG.cpp"
#include "DecoderPNG.cpp"
#include "DecoderTIFF.cpp"

namespace Decoder{
    DecoderInterface::~DecoderInterface() = default;

    std::unique_ptr<DecoderInterface>
    DecoderInterface::getDecoder(ImageFormat _format) {
        std::unique_ptr<DecoderInterface> decoder;

        switch (_format)
        {
            case ImageFormat::None:
                throw std::runtime_error("None Image Format\n");
                break;
            case ImageFormat::JPEG:
                decoder = std::make_unique<JPEG_Decoder>();
                break;
            case ImageFormat::PNG:
                decoder = std::make_unique<PNG_Decoder>();
                break;
            case ImageFormat::GIF:
                throw std::runtime_error("GIF is not supported.\n");
                break;
            case ImageFormat::TIF:
                decoder = std::make_unique<TiffDecoder>();
                break;
        }

        return decoder;
    }
} // namespace Decoder

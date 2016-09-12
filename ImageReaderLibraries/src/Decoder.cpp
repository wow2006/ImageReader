#include <exception>
#include "Decoder.hpp"
#include "DecoderJPEG.cpp"
#include "DecoderPNG.cpp"
#include "DecoderTIFF.cpp"

namespace Decoder{
    std::unique_ptr<DecoderInterface>
    getDecoder(ImageFormat _format) {
        std::unique_ptr<DecoderInterface> decoder(nullptr);

        switch (_format)
        {
            case ImageFormat::None:
                throw std::runtime_error("None Image Format\n");
                break;
            case ImageFormat::JPEG:
                decoder.reset(new JPEG_Decoder());
                break;
            case ImageFormat::PNG:
                decoder.reset(new PNG_Decoder());
                break;
            case ImageFormat::GIF:
                throw std::runtime_error("GIF is not supported.\n");
                break;
            case ImageFormat::TIF:
                decoder.reset(new TiffDecoder());
                break;
            default:
                throw std::runtime_error("Undefined Type.\n");
                break;
        }

        return decoder;
    }
}

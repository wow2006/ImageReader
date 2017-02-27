#include "Encoder.hpp"
#include "EncoderTIFF.hpp"
#include "EncoderJPEG.hpp"
#include "EncoderPNG.hpp"
#include <cstdio>

namespace Encoder {

EncoderInterface::~EncoderInterface(){}

std::unique_ptr<EncoderInterface>
EncoderInterface::getEncoder(ImageFormat _format) {
    std::unique_ptr<EncoderInterface> temp;
    switch (_format) {
        case ImageFormat::PNG:
            temp.reset(new PngEncoder());
        break;
    case ImageFormat::JPEG:
            temp.reset(new JpegEncoder());
        break;
    case ImageFormat::TIF:
            temp.reset(new TiffEncoder());
        break;
    case ImageFormat::GIF:
        std::runtime_error("GIF is not supported!");
        break;
    case ImageFormat::None:
        std::runtime_error("No Supprted Format Found!");
        break;
  }
  return temp;
}

}

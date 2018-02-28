// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Encoder.hpp"
#include "EncoderTIFF.hpp"
#include "EncoderJPEG.hpp"
#include "EncoderPNG.hpp"
#include <cstdio>

namespace Encoder {

EncoderInterface::~EncoderInterface() = default;

std::unique_ptr<EncoderInterface> EncoderInterface::getEncoder(
    ImageFormat _format) {
  std::unique_ptr<EncoderInterface> temp;
  switch (_format) {
    case ImageFormat::PNG:
      temp = std::make_unique<PngEncoder>();
      break;
    case ImageFormat::JPEG:
      temp = std::make_unique<JpegEncoder>();
      break;
    case ImageFormat::TIF:
      temp = std::make_unique<TiffEncoder>();
      break;
    case ImageFormat::GIF:
      throw std::runtime_error("GIF is not supported!");
      break;
    case ImageFormat::None:
      throw std::runtime_error("No Supprted Format Found!");
      break;
  }
  return temp;
}

}  // namespace Encoder

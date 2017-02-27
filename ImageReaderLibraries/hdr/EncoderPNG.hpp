#ifndef ENCODER_PNG_HPP
#define ENCODER_PNG_HPP
#pragma once
#include <png.h>
#include "Encoder.hpp"

namespace Encoder {
    class PngEncoder : public EncoderInterface {
    public:
      PngEncoder();
      virtual ~PngEncoder();

      /**
       * @brief PngEncoder::encode Encode Image to PNG support RGB and Gray Only
       * @param _uncompressedPtr
       * @param _width
       * @param _height
       * @param _channels
       * @param _compressedPtr
       * @param _fileSize
       * @return
       */
      bool encode(uchar *_uncompressedPtr, const int _width, const int _height,
                  const int _channels, std::vector<uchar> &_compressedPtr,
                  std::size_t &_fileSize, const int JPEG_QUALITY);

    protected:
      png_structp mPng_ptr = nullptr;
      png_infop mInfo_ptr = nullptr;
    };
}
#endif// !ENCODER_PNG_HPP

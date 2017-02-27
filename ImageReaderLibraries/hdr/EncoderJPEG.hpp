#ifndef ENCODER_JPEG_HPP
#define ENCODER_JPEG_HPP

#pragma once

#include "Encoder.hpp"
#include <turbojpeg.h>

namespace Encoder {
    class JpegEncoder : public EncoderInterface {
    public:
      JpegEncoder();
      virtual ~JpegEncoder();
      bool encode(uchar *_uncompressedPtr, const int _width, const int _height,
                  const int _channels, std::vector<uchar> &_compressedPtr,
                  std::size_t &_fileSize, const int JPEG_QUALITY) override;

    protected:
      tjhandle mHandler;
    };
}

#endif//!ENCODER_JPEG_HPP

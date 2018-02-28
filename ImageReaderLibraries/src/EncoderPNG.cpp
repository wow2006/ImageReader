// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <cstring>
#include <streambuf>
#include <boost/interprocess/streams/bufferstream.hpp>
#include "EncoderPNG.hpp"

using bufferstream = boost::interprocess::bufferstream;

namespace Encoder {

PngEncoder::PngEncoder() {
  // Initialize write structure
  mPng_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if (mPng_ptr == nullptr) {
    std::cerr << "Could not allocate write struct\n";
    return;
  }

  // Initialize info structure
  mInfo_ptr = png_create_info_struct(mPng_ptr);
  if (mInfo_ptr == nullptr) {
    std::cerr << "Could not allocate write struct\n";
    return;
  }

  // Setup Exception handling
  if (setjmp(png_jmpbuf(mPng_ptr))) {
    std::cerr << "Error during png creation\n";
    return;
  }
}

PngEncoder::~PngEncoder() {
  if (mInfo_ptr != nullptr) png_free_data(mPng_ptr, mInfo_ptr, PNG_FREE_ALL, -1);
  if (mPng_ptr != nullptr) png_destroy_write_struct(&mPng_ptr, (png_infopp)nullptr);
}

bool PngEncoder::encode(uchar *_uncompressedPtr, const int _width,
                        const int _height, const int _channels,
                        std::vector<uchar> &_compressedPtr,
                        std::size_t &_fileSize, const int) {
  char *temp = nullptr;
  // TODO find windows Version
  FILE *fp = open_memstream(reinterpret_cast<char **>(&temp), &_fileSize);
  if (fp == nullptr) return false;

  png_init_io(mPng_ptr, fp);

  // Write header (8 bit colour depth)
  png_set_IHDR(mPng_ptr, mInfo_ptr, _width, _height, 8, PNG_COLOR_TYPE_RGB,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
               PNG_FILTER_TYPE_BASE);

  png_write_info(mPng_ptr, mInfo_ptr);

  auto rowSize = _width * _channels;
  auto row = _uncompressedPtr;
  // Write image data
  for (int y = 0; y < _height; y++) {
    png_write_row(mPng_ptr, row);
    row += rowSize;
  }

  // End write
  png_write_end(mPng_ptr, nullptr);

  // TODO Copy memory
  fflush(fp);
  _compressedPtr.resize(_fileSize);
  std::memcpy(_compressedPtr.data(), temp, _fileSize);
  if (fp != nullptr) fclose(fp);
  free(temp);

  return true;
}
}  // namespace Encoder

#include "Encoder.hpp"
#include <cstring>
#include <png.h>
#include <turbojpeg.h>


namespace Encoder {
static inline void writeBinary(const std::string &_fileName, char *_ptr,
                               const std::size_t _fileSize) {
  std::ofstream fileHandler(_fileName);
  fileHandler.write(_ptr, _fileSize);
  fileHandler.close();
}

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

class PngEncoder : public EncoderInterface {
public:
  PngEncoder();
  virtual ~PngEncoder();

public:
  bool encode(uchar *_uncompressedPtr, const int _width, const int _height,
              const int _channels, std::vector<uchar> &_compressedPtr,
              std::size_t &_fileSize, const int JPEG_QUALITY);
};

std::unique_ptr<EncoderInterface>
getEncoder(BaseImage::ImageFormat _format) {
  std::unique_ptr<EncoderInterface> temp;
  switch (_format) {
  case BaseImage::ImageFormat::JPEG:
    temp.reset(new JpegEncoder());
    break;
  }
  return std::move(temp);
}

JpegEncoder::JpegEncoder() { mHandler = tjInitCompress(); }

JpegEncoder::~JpegEncoder() { tjDestroy(mHandler); }

bool JpegEncoder::encode(uchar *_uncompressedPtr, const int _width,
                         const int _height, const int _channels,
                         std::vector<uchar> &_compressedPtr, std::size_t &_fileSize,
                         const int JPEG_QUALITY) {
    uchar* compressedPtr = nullptr;
  tjCompress2(mHandler, _uncompressedPtr, _width, 0, _height,
              (_channels == 3) ? TJPF_RGB : TJPF_GRAY, &compressedPtr,
              &_fileSize, (_channels == 3) ? TJSAMP_444 : TJSAMP_GRAY,
              JPEG_QUALITY, TJFLAG_FASTDCT);
  _compressedPtr.resize(_fileSize);
  std::memcpy(_compressedPtr.data(), compressedPtr, _fileSize);
  tjFree(compressedPtr);
  return true;
}

PngEncoder::PngEncoder() {}

PngEncoder::~PngEncoder() {}

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
bool PngEncoder::encode(uchar *_uncompressedPtr, const int _width,
                        const int _height, const int _channels,
                        std::vector<uchar> &_compressedPtr, std::size_t &_fileSize,
                        const int) {
  png_structp p =
      png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info_ptr = png_create_info_struct(p);
  png_set_IHDR(p, info_ptr, static_cast<uint>(_width),
               static_cast<uint>(_height), 8,
               (_channels == 3) ? PNG_COLOR_TYPE_RGB : PNG_COLOR_TYPE_GRAY,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);
  std::vector<uchar *> rows(_height);
  for (int y = 0; y < _height; ++y)
    rows[y] = _uncompressedPtr + _height * _width * _channels;
  png_set_rows(p, info_ptr, &rows[0]);
  png_set_write_fn(p, _compressedPtr.data(),
                   [](png_structp _png_ptr, png_bytep _data, png_size_t _length) {
                        auto ptr = static_cast<std::vector<uchar>*>(png_get_io_ptr(_png_ptr));
                        auto data = reinterpret_cast<char*>(_data);
                        ptr->insert(ptr->end(), data, data + _length);
                   },
                   NULL);
  png_write_png(p, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);



  return false;
}
}

#include <cstring>
#include "ImageReader.hpp"
#include "Decoder.hpp"

namespace ImageFormatUtility {
static bool checkJPEG(uchar header[4]) {
  static constexpr int JPEG_HEX[] = {0xFF, 0xD8, 0xFF, 0xE0, 0xE1};

  bool match = true;
  for (int i = 0; i < 3; ++i) {
    match &= (JPEG_HEX[i] == header[i]);
  }
  match &= (JPEG_HEX[3] == header[3] || JPEG_HEX[4] == header[3]);
  return match;
}
static bool checkPNG(uchar header[8]) {
  static constexpr uchar PNG_HEX[]{0x89, 0x50, 0x4E, 0x47,
                                   0x0D, 0x0A, 0x1A, 0x0A};
  bool match = true;
  int i = -1;
  for (const auto &item : PNG_HEX) {
    match &= (item == header[++i]);
  }
  return match;
}
static bool checkGIF(uchar header[4]) {
  static constexpr uchar GIF_HEX[]{0x47, 0x49, 0x46, 0x38};

  bool match = true;
  int i = -1;
  for (const auto &item : GIF_HEX) {
    match &= (item == header[++i]);
  }
  return match;
}
static bool checkTIF(uchar header[4]) {
  // Motorola - big endian [MM.*]
  static constexpr uchar TIF_HEX_M[]{0x4d, 0x4d, 0x00, 0x2a};
  // Intel - little endian [II*.]
  static constexpr uchar TIF_HEX_I[]{0x49, 0x49, 0x2a, 0x00};

  bool match = true;
  int i = -1;
  for (const auto &item : TIF_HEX_M) {
    match &= (item == header[++i]);
  }

  i = -1;
  if (!match) {
    match = true;
    for (const auto &item : TIF_HEX_I) {
        auto v = (item == header[++i]);
        match &= v;
    }
  }

  return match;
}
}

using namespace ImageFormatUtility;

BaseImage::BaseImage(const std::string &_imageName) {
    read(_imageName);
}

bool
BaseImage::read(const std::string &_imageName){
    // Read Image
    std::ifstream file(_imageName, std::ifstream::binary | std::ifstream::ate);
    if (!file.is_open())
        return false;

    auto fileSize = file.tellg();
    file.seekg(std::ifstream::beg);

    auto ptr = std::vector<uchar>(fileSize, 0);
    file.read(reinterpret_cast<char *>(ptr.data()), fileSize);
    file.close();

    readImage(ptr, mImageFormat);

    auto decoder = Decoder::getDecoder(mImageFormat);
    decoder->decode(ptr, mImagePtr, mWidth, mHeight, mChannels);
    return true;
}

BaseImage::~BaseImage() {
}

void BaseImage::readImage(std::vector<uchar> _ptr,
                          ImageFormat &_imageFormat) {
  uchar header[8]{0};

  std::memcpy(header, _ptr.data(), 8);

  if (checkJPEG(header))
    _imageFormat = ImageFormat::JPEG;
  else if (checkPNG(header))
    _imageFormat = ImageFormat::PNG;
  else if (checkGIF(header))
    _imageFormat = ImageFormat::GIF;
  else if (checkTIF(header))
    _imageFormat = ImageFormat::TIF;
}

#include <cstring>
#include "ImageReader.hpp"

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
    for (const auto &item : TIF_HEX_I) {
      match &= (item == header[++i]);
    }
  }

  return match;
}
}

using namespace ImageFormatUtility;

BaseImage::BaseImage(const std::string &_imageName) {
  // Read Image
  std::ifstream file(_imageName, std::ifstream::binary | std::ifstream::ate);
  if (file.is_open()) {
    auto fileSize = file.tellg();
    file.seekg(std::ifstream::beg);

    auto ptr = new uchar[fileSize]{0};
    file.read(reinterpret_cast<char *>(ptr), fileSize);

    readImage(ptr, fileSize, mImageFormat);

    delete[] ptr;
  }
  file.close();
}

BaseImage::~BaseImage() {
  if (mImagePtr != nullptr) {
    delete[] mImagePtr;
    mImagePtr = nullptr;
  }
}

void BaseImage::readImage(const uchar *_ptr, const int _fileSize,
                          ImageFormat &_imageFormat) {
  uchar header[8]{0};

  std::memcpy(header, _ptr, 8);

  if (checkJPEG(header))
    _imageFormat = ImageFormat::JPEG;
  else if (checkPNG(header))
    _imageFormat = ImageFormat::PNG;
  else if (checkGIF(header))
    _imageFormat = ImageFormat::GIF;
  else if (checkTIF(header))
    _imageFormat = ImageFormat::TIF;
}

#include <cstring>
#include <boost/algorithm/string.hpp>
#include "ImageReader.hpp"
#include "Decoder.hpp"
#include "Encoder.hpp"
#include "ImageProcessingAlgorithms.hpp"

namespace ImageFormatUtility {

auto getEncoder(const std::string& _fileName){
    std::vector<std::string> strs;
    {
        boost::split(strs, _fileName, boost::is_any_of("."));
    }
    boost::to_lower(strs.back());
    auto& exten = strs.back();
    std::unique_ptr<Encoder::EncoderInterface> ptr;
    if(exten == "jpeg" || exten == "jpg"){
        ptr = Encoder::EncoderInterface::getEncoder(ImageFormat::JPEG);
    }
    else if(exten == "png"){
        ptr = Encoder::EncoderInterface::getEncoder(ImageFormat::PNG);
    }
    else if(exten == "tif" || exten == "tiff"){
        ptr = Encoder::EncoderInterface::getEncoder(ImageFormat::TIF);
    }
    return std::move(ptr);
}

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

BaseImage::BaseImage(const std::string &_imageName) {
    open(_imageName);
}

bool
BaseImage::open(const std::string &_imageName){
    std::ifstream file(_imageName, std::ifstream::binary | std::ifstream::ate);
    if (!file.is_open())
        return false;

    auto fileSize = file.tellg();
    file.seekg(std::ifstream::beg);

    auto ptr = std::vector<uchar>(fileSize, 0);
    file.read(reinterpret_cast<char *>(ptr.data()), fileSize);
    file.close();

    readImage(ptr, mImageFormat);

    auto decoder = Decoder::DecoderInterface::getDecoder(mImageFormat);
    if(decoder)
        return decoder->decode(ptr, mImagePtr, mWidth, mHeight, mChannels);
    return false;
}

bool BaseImage::save(const std::string &_imageName, const int JPEG_QUALITY) {
    std::unique_ptr<Encoder::EncoderInterface> encoder = ImageFormatUtility::getEncoder(_imageName);
    if(encoder){
        std::vector<uchar> outputData;
        std::size_t fileSize = 0;
        encoder->encode(mImagePtr.data(), mWidth, mHeight, mChannels,
                        outputData, fileSize, JPEG_QUALITY);
        writeImage(_imageName, reinterpret_cast<char*>(outputData.data()), fileSize);
        return true;
    }
    return false;
}

void BaseImage::convert()
{
    auto x = ConvertImageFormat::toSoA(mImagePtr, mWidth, mHeight);
    mImagePtr = ConvertImageFormat::toAoS(x, mWidth, mHeight);
}

void BaseImage::readImage(const std::vector<uchar>& _ptr,
                          ImageFormat &_imageFormat) {
  uchar header[8]{0};

  std::memcpy(header, _ptr.data(), 8);

  if (ImageFormatUtility::checkJPEG(header))
    _imageFormat = ImageFormat::JPEG;
  else if (ImageFormatUtility::checkPNG(header))
    _imageFormat = ImageFormat::PNG;
  else if (ImageFormatUtility::checkGIF(header))
    _imageFormat = ImageFormat::GIF;
  else if (ImageFormatUtility::checkTIF(header))
    _imageFormat = ImageFormat::TIF;
}

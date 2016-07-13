#ifndef IMAGE_READER_HPP
#define IMAGE_READER_HPP
#include "Common.hpp"

class BaseImage {
public:
  enum class ImageFormat {
    None = -1,
    JPEG = 0,
    PNG,
    GIF,
    TIF,
  };
  enum class PixelFormat {
      None = -1,
      Gray = 0,
      RGB8,
      YUV,
      Bayer,
      NV12
  };

  BaseImage(const std::string &_imageName);
  virtual ~BaseImage();

  inline uchar *get() { return mImagePtr; }
  inline uint getWidth() { return mWidth; }
  inline uint getheight() { return mHeight; }

protected:
  ImageFormat mImageFormat = ImageFormat::None;
  uchar *mImagePtr = nullptr;
  uint mWidth = 0;
  uint mHeight = 0;
  PixelFormat mFormat = PixelFormat::None;

private:
  static void readImage(const uchar *_ptr, const int _fileSize,
                        ImageFormat &_imageFormat);
  BaseImage(const BaseImage &) = delete;
  void operator=(const BaseImage &) = delete;
};
#endif // !IMAGE_READER_HPP

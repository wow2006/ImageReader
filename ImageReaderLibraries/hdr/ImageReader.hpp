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

  inline uchar *get() { return mImagePtr.data(); }
  inline int getWidth() const { return mWidth; }
  inline int getHeight() const { return mHeight; }
  inline int getChannels() const { return mChannels; }

protected:
  ImageFormat mImageFormat = ImageFormat::None;
  std::vector<uchar> mImagePtr;
  int mWidth = 0;
  int mHeight = 0;
  int mChannels = 0;
  PixelFormat mFormat = PixelFormat::None;

private:
  static void readImage(std::vector<uchar> _ptr, ImageFormat &_imageFormat);
  BaseImage(const BaseImage &) = delete;
  void operator=(const BaseImage &) = delete;
};
#endif // !IMAGE_READER_HPP

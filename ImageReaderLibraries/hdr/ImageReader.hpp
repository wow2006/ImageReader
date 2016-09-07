#ifndef IMAGE_READER_HPP
#define IMAGE_READER_HPP
#include "Common.hpp"

struct rowAccess{
    rowAccess(uchar* _ptr) : temp(_ptr){

    }
    uchar* temp = nullptr;
    RGB<uchar> operator[](const int _index){
        return *reinterpret_cast<RGB<uchar>*>(&temp[_index * 3]);
    }
};

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

  BaseImage(){}
  BaseImage(const std::string &_imageName);
  virtual ~BaseImage();

  bool read(const std::string &_imageName);

  inline uchar *get() { return mImagePtr.data(); }
  inline int getWidth() const { return mWidth; }
  inline int getHeight() const { return mHeight; }
  inline int getChannels() const { return mChannels; }
  inline rowAccess operator[](const int _index){
      return rowAccess(&mImagePtr[_index * mWidth * mChannels]);
  }

protected:
  ImageFormat mImageFormat = ImageFormat::None;
  std::vector<uchar> mImagePtr;
  int mWidth = 0;
  int mHeight = 0;
  int mChannels = 0;
  PixelFormat mFormat = PixelFormat::None;

private:
  static void readImage(const std::vector<uchar>&, ImageFormat &_imageFormat);
  BaseImage(const BaseImage &) = delete;
  void operator=(const BaseImage &) = delete;
};
#endif // !IMAGE_READER_HPP

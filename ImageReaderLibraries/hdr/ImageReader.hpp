#ifndef IMAGE_READER_HPP
#define IMAGE_READER_HPP
#include "Common.hpp"

template<template<class> class T = RGB, class I = uchar>
struct rowAccess{
    using  Pixel = T<I>;
    rowAccess(I* _ptr) : temp(_ptr){}
    I* temp = nullptr;
    Pixel operator[](const int _index){
        static constexpr int PixelWidth = sizeof(T<I>) / sizeof(I);
        return *reinterpret_cast<Pixel*>(&temp[_index * PixelWidth]);
    }
};

class BaseImage {
public:
  BaseImage(){}
  explicit BaseImage(const std::string &_imageName);
  virtual ~BaseImage(){}

  bool open(const std::string &_imageName);
  bool save(const std::string &_imageName, const int JPEG_QUALITY = 75);

  inline uchar *get() { return mImagePtr.data(); }
  inline int getWidth() const { return mWidth; }
  inline int getHeight() const { return mHeight; }
  inline int getChannels() const { return mChannels; }
  inline rowAccess<RGB, uchar> operator[](const int _index){
      return rowAccess<RGB, uchar>(&mImagePtr[_index * mWidth * mChannels]);
  }

  void convert();

protected:
  std::vector<uchar> mImagePtr;
  int mWidth = 0, mHeight = 0, mChannels = 0;
  ImageFormat mImageFormat = ImageFormat::None;
  PixelFormat mFormat = PixelFormat::None;

private:
  static void readImage(const std::vector<uchar>&, ImageFormat &_imageFormat);

  BaseImage(const BaseImage &) = delete;
  void operator=(const BaseImage &) = delete;

  BaseImage(BaseImage &&) = delete;
  void operator=(BaseImage &&) = delete;
};
#endif // !IMAGE_READER_HPP

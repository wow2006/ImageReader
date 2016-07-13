#include <iostream>
#include <fstream>
#include "Decoder.hpp"

template<unsigned... args>
struct ArrayHolder{
    static const unsigned data[sizeof...(args)];
};
template<unsigned... args>
const unsigned ArrayHolder<args...>::data[sizeof...(args)] = { args... };

int
main(int argc, char *argv[]) {
    //std::cout << ArrayHolder<1, 2, 3>::data[0] << std::endl;
    //return 0;

  if (argc != 3){
      std::cerr << "Useage:\n" << argv[0] << " image1 image2\n";
      return 1;
  }

  uchar* outPtr = nullptr;
  int width = 0, height = 0, channel = 0;
  {
      auto decoder = DecoderFactory::getDecoder(BaseImage::ImageFormat::PNG);
      decoder->Decoder(argv[1], outPtr, width, height, channel);
      delete decoder;
      decoder = nullptr;
  }

  std::cout
      << "Image width : " << width
      << ", height : " << height
      << ", channel : " << channel << '\n';
  {
      std::ofstream outputFile("Lenna.bin", std::ofstream::binary);
      outputFile.write(reinterpret_cast<char*>(outPtr), width * height * channel);
      outputFile.close();
  }

  delete[] outPtr;
  outPtr = nullptr;

  return 0;
}

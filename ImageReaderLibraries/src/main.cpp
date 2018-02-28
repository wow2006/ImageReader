// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
  if (argc != 3){
      std::cerr << "Useage:\n" << argv[0] << " image1 image2\n";
      return 1;
  }

  uchar* outPtr = nullptr;
  int width = 0, height = 0, channel = 0;
  {
      auto decoder = Decoder::DecoderInterface::getDecoder(ImageFormat::PNG);

      std::ifstream file(argv[1], std::ifstream::binary | std::ifstream::ate);
      std::size_t fileSize = file.tellg();
      file.seekg(std::ifstream::beg);
      std::vector<uchar> encodedPtr(fileSize, 0);
      file.read(reinterpret_cast<char*>(encodedPtr.data()), fileSize);

      std::vector<uchar> outPtr;
      decoder->decode(encodedPtr, outPtr, width, height, channel);
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

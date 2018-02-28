// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Decoder.hpp"
#include <tiffio.h>
#include <tiffio.hxx>

#include <boost/interprocess/streams/bufferstream.hpp>
using bufferstream = boost::interprocess::bufferstream;

namespace Decoder {
class TiffDecoder : public DecoderInterface {
  public:
  bool decode(std::vector<uchar> &_inputPtr, std::vector<uchar> &_output,
              int &_width, int &_height, int &_channel) override {
    bufferstream input_stream(reinterpret_cast<char *>(_inputPtr.data()),
                              _inputPtr.size());
    auto buffer = dynamic_cast<std::istream *>(&input_stream);
    if (buffer == nullptr) {
      return false;
    }
    TIFF *mem_TIFF = TIFFStreamOpen("MemTIFF", buffer);

    TIFFGetField(mem_TIFF, TIFFTAG_IMAGEWIDTH, &_width);
    TIFFGetField(mem_TIFF, TIFFTAG_IMAGELENGTH, &_height);
    _channel = 4;

    _output.resize(_width * _height * _channel);
    return TIFFReadRGBAImageOriented(mem_TIFF, _width, _height,
                                     reinterpret_cast<uint32 *>(_output.data()),
                                     0) == 1;
  }
};
}  // namespace Decoder

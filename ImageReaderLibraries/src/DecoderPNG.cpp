// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Decoder.hpp"
#include <cstring>
#include <png++/png.hpp>
#include <png++/rgb_pixel.hpp>

#include <boost/interprocess/streams/bufferstream.hpp>
using bufferstream = boost::interprocess::bufferstream;

namespace Decoder {
class PNG_Decoder : public DecoderInterface {
  public:
  bool decode(std::vector<uchar> &_inputPtr, std::vector<uchar> &_outPtr,
              int &_width, int &_height, int &_channel) override {
    bufferstream input_stream(reinterpret_cast<char *>(_inputPtr.data()),
                              _inputPtr.size());
    auto buffer = dynamic_cast<std::istream *>(&input_stream);
    if (buffer == nullptr) {
      return false;
    }

    png::image<png::rgb_pixel> inputImage(*buffer);

    _width   = inputImage.get_width();
    _height  = inputImage.get_height();
    _channel = 3; // TODO remove constant

    int raws = _width * _channel;
    _outPtr.resize(_height * raws);
    auto oPtr = _outPtr.data();

    for (int j = 0; j < _height; ++j) {
      auto iPtr = reinterpret_cast<uchar *>(inputImage.get_row(j).data());
      std::memcpy(oPtr, iPtr, raws);
      oPtr += raws;
    }

    return true;
  }
};
}  // namespace Decoder

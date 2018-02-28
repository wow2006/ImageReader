// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Decoder.hpp"
#include <turbojpeg.h>

namespace Decoder {
class JPEG_Decoder : public DecoderInterface {
  public:
  JPEG_Decoder() { pHandler = tjInitDecompress(); }

  ~JPEG_Decoder() override { tjDestroy(pHandler); }

  bool decode(std::vector<uchar> &_inputPtr, std::vector<uchar> &_output,
              int &_width, int &_height, int &_channel) override {
    auto tempPtr = reinterpret_cast<uchar *>(_inputPtr.data());
    auto fileSize = _inputPtr.size();

    int jpegSubsamp = 0;
    _channel = 3; // TODO remove constant

    tjDecompressHeader2(pHandler, tempPtr, fileSize, &_width, &_height,
                        &jpegSubsamp);

    _output.resize(_width * _height * _channel);

    tjDecompress2(pHandler, tempPtr, fileSize, _output.data(), _width, 0,
                  _height, TJPF_RGB, TJFLAG_FASTDCT);

    return true;
  }

  protected:
  tjhandle pHandler = nullptr;
};
}  // namespace Decoder

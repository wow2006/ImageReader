#include "Decoder.hpp"
#include <turbojpeg.h>

namespace Decoder{
    class JPEG_Decoder : public DecoderInterface{
    public:
        JPEG_Decoder(){
            pHandler = tjInitDecompress();
        }

        virtual ~JPEG_Decoder(){
            tjDestroy(pHandler);
        }

        bool decode(std::vector<uchar>& _inputPtr, std::vector<uchar>&_output,
                     int &_width, int &_height, int &_channel) override{
            auto tempPtr = reinterpret_cast<uchar*>(_inputPtr.data());
            auto fileSize = _inputPtr.size();

            auto jpegSubsamp = 0;
            _channel = 3;

            tjDecompressHeader2(pHandler, tempPtr, fileSize, &_width, &_height, &jpegSubsamp);

            _output.resize(_width * _height * _channel);

            tjDecompress2(pHandler, tempPtr, fileSize, _output.data(), _width, 0, _height, TJPF_RGB, TJFLAG_FASTDCT);

            return true;
        }

    protected:
        tjhandle pHandler = 0;
    };
}

#include "Decoder.hpp"
#include <iostream>
#include <istream>
#include <streambuf>
#include <vector>
#include <exception>
#include <turbojpeg.h>
#include <png++/png.hpp>
#include <png++/rgb_pixel.hpp>

#include <boost/interprocess/streams/bufferstream.hpp>
using namespace boost::interprocess;

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

    class PNG_Decoder : public DecoderInterface {
    public:
        // Inherited via DecoderFactory
        bool decode(std::vector<uchar>& _inputPtr, std::vector<uchar>&_outPtr,
                          int &_width, int &_height, int &_channel) override{

            bufferstream input_stream(reinterpret_cast<char*>(_inputPtr.data()), _inputPtr.size());
            auto buffer = dynamic_cast<std::istream*>(&input_stream);
            if(buffer != nullptr){
                png::image<png::rgb_pixel> inputImage(*buffer);

                _width = inputImage.get_width();
                _height = inputImage.get_height();
                _channel = 3;

                int raws = _width * _channel;
                _outPtr.resize(_height * raws);
                auto oPtr = _outPtr.data();

                for(int j = 0; j < _height; ++j){
                    auto iPtr = reinterpret_cast<uchar*>(inputImage.get_row(j).data());
                    std::memcpy(oPtr, iPtr, raws);
                    oPtr += raws;
                }

                return true;
            }
            return false;
        }
    };

    class TiffDecoder : public DecoderInterface{
    public:
        ~TiffDecoder(){

        }

        bool decode(std::vector<uchar> &_inputPtr, std::vector<uchar> &_output, int &_width, int &_height, int &_channel){
            return false;
        }
    };

    std::unique_ptr<DecoderInterface>
    getDecoder(BaseImage::ImageFormat _format) {
        std::unique_ptr<DecoderInterface> decoder;

        switch (_format)
        {
            case BaseImage::ImageFormat::None:
                throw std::runtime_error("None Image Format\n");
                break;
            case BaseImage::ImageFormat::JPEG:
                decoder.reset(new JPEG_Decoder());
                break;
            case BaseImage::ImageFormat::PNG:
                decoder.reset(new PNG_Decoder());
                break;
            case BaseImage::ImageFormat::GIF:
                throw std::runtime_error("GIF is not supported.\n");
                break;
            case BaseImage::ImageFormat::TIF:
                throw std::runtime_error("TIF is not supported.\n");
                break;
            default:
                throw std::runtime_error("Undefined Type.\n");
                break;
        }

        return std::move(decoder);
    }
}

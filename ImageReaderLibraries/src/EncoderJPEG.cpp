#include <memory>
#include <cstring>
#include "EncoderJPEG.hpp"

namespace Encoder {
    JpegEncoder::JpegEncoder() { mHandler = tjInitCompress(); }

    JpegEncoder::~JpegEncoder() { tjDestroy(mHandler); }

    bool JpegEncoder::encode(uchar *_uncompressedPtr, const int _width,
                             const int _height, const int _channels,
                             std::vector<uchar> &_compressedPtr, std::size_t &_fileSize,
                             const int JPEG_QUALITY) {
        uchar* compressedPtr = nullptr;
        tjCompress2(mHandler, _uncompressedPtr, _width, 0, _height,
        (_channels == 3) ? TJPF_RGB : TJPF_GRAY, &compressedPtr,
            &_fileSize, (_channels == 3) ? TJSAMP_444 : TJSAMP_GRAY,
            JPEG_QUALITY, TJFLAG_FASTDCT);
        _compressedPtr.resize(_fileSize);
        std::memcpy(_compressedPtr.data(), compressedPtr, _fileSize);
        tjFree(compressedPtr);
        return true;
    }
}


#ifndef TIFF_ENCODER_CPP
#define TIFF_ENCODER_CPP
#include "Encoder.hpp"
#include <tiffio.h>
#include <tiffio.hxx>
#include <sstream>
#include <cstring>

namespace Encoder {
class TiffEncoder : public EncoderInterface{
public:

public:
    bool encode(uchar *_uncompressedPtr, const int _width, const int _height, const int _channels,
                std::vector<uchar> &_compressedPtr, std::size_t &_fileSize, const int JPEG_QUALITY) {
        std::ostringstream output_TIFF_stream;
        TIFF* tif = TIFFStreamOpen("MemTIFF", &output_TIFF_stream);


        TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, _width);
        TIFFSetField(tif, TIFFTAG_IMAGELENGTH, _height);
        TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
        TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, _channels);
        TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
        TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
        TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

        TIFFSetField(tif, TIFFTAG_XRESOLUTION, 72);
        TIFFSetField(tif, TIFFTAG_YRESOLUTION, 72);
        TIFFSetField(tif, TIFFTAG_RESOLUTIONUNIT, RESUNIT_INCH);

        TIFFWriteEncodedStrip(tif, 0, _uncompressedPtr, _width * _height * _channels);

        TIFFWriteDirectory(tif);
        TIFFClose(tif);

        output_TIFF_stream.seekp(0, std::ostringstream::end);
        _fileSize = output_TIFF_stream.tellp();
        output_TIFF_stream.seekp(0, std::ios_base::beg);
        _compressedPtr.resize(_fileSize);

        std::memcpy(_compressedPtr.data(), output_TIFF_stream.str().data(), _fileSize);
        return true;
    }
};
}
#endif // !TIFF_ENCODER_CPP

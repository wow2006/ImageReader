// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "EncoderTIFF.hpp"
#include <tiffio.h>
#include <tiffio.hxx>
#include <sstream>
#include <cstring>

namespace Encoder {
bool TiffEncoder::encode(uchar *_uncompressedPtr, const int _width,
                         const int _height, const int _channels,
                         std::vector<uchar> &_compressedPtr,
                         std::size_t &_fileSize, const int JPEG_QUALITY) {
  std::ostringstream output_TIFF_stream;
  TIFF *tif = TIFFStreamOpen("MemTIFF", &output_TIFF_stream);

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

  std::memcpy(_compressedPtr.data(), output_TIFF_stream.str().data(),
              _fileSize);
  return true;
}
}  // namespace Encoder

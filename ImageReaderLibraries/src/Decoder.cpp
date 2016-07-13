#include "Decoder.hpp"
#include <iostream>
#include <cstring>
#include <png++/png.hpp>
#include <png.h>
#include <exception>
#include <tiffio.h>

class PNG_Decoder : public DecoderInterface {
public:
	PNG_Decoder() {
		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png_ptr) {
			return;
		}

		info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr) {
			png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
			return;
		}

		//create png info struct
		end_info = png_create_info_struct(png_ptr);
		if (!end_info) {
			png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
			return;
		}

		//png error stuff, not sure libpng man suggests this.
		if (setjmp(png_jmpbuf(png_ptr))) {
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			return;
		}
	}

	virtual ~PNG_Decoder() {
		//clean up memory and close stuff
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	}
	// Inherited via DecoderFactory
	bool Decoder(const std::string _fileName, uchar *&_outPtr,
		int &_width, int &_height, int &_channel) override {
		FILE *fp = fopen(_fileName.c_str(), "rb");

		//init png reading
		png_init_io(png_ptr, fp);


		// read all the info up to the image data
		png_read_info(png_ptr, info_ptr);

		//variables to pass to get info
		int bit_depth, color_type;
		png_uint_32 twidth, theight;

		// get info about png
		png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type,
			NULL, NULL, NULL);

		//update width and height based on png info
		_width = twidth;
		_height = theight;

		// Update the png info struct.
		png_read_update_info(png_ptr, info_ptr);

		// Row size in bytes.
		int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

		_channel = rowbytes / _width;

		// Allocate the image_data as a big block, to be given to OpenGL
		_outPtr = new png_byte[rowbytes * _height];
		if (!_outPtr) {
			fclose(fp);
			return false;
		}

		//row_pointers is for pointing to image_data for reading the png with libpng
		png_bytep *row_pointers = new png_bytep[_height];
		if (!row_pointers) {
			delete[] _outPtr;
			_outPtr = nullptr;
			fclose(fp);
			return false;
		}
		// set the individual row_pointers to point at the correct offsets of image_data
		for (int i = 0; i < _height; ++i)
			row_pointers[i] = _outPtr + i * rowbytes;

		//read the png into image_data through row_pointers
		png_read_image(png_ptr, row_pointers);

		delete[] row_pointers;
		fclose(fp);
		return true;
	}
protected:
	png_structp png_ptr;
	png_infop info_ptr;
	png_infop end_info;
};

class TIFF_Decoder : public DecoderInterface{
public:
    TIFF_Decoder(){}
    virtual ~TIFF_Decoder(){}

    bool Decoder(const std::string _fileName, uchar *&_outPtr,
            int &_width, int &_height, int &_channel) override{
        auto flag  = false;
        TIFF* tif = TIFFOpen(_fileName.c_str(), "r");
        if(tif){
            uint32 w = 0, h = 0;
            std::size_t npixels = 0;

            TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
            TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
            npixels = w * h;
            auto raster = (uint32*) _TIFFmalloc(npixels * sizeof (uint32));
            if (raster != NULL) {
                if (TIFFReadRGBAImage(tif, w, h, raster, 0)) {
                    _outPtr = new uchar[npixels]();
                    std::memcpy(_outPtr, raster, npixels * sizeof(uint32));
                    flag = true;
                }
                _TIFFfree(raster);
            }
            TIFFClose(tif);
        }
        return flag;
    }
protected:
};

DecoderInterface*
DecoderFactory::getDecoder(BaseImage::ImageFormat _format) {
    DecoderInterface* decoder = nullptr;

    switch (_format)
    {
    case BaseImage::ImageFormat::None:
        throw std::runtime_error("None Image Format\n");
        break;
    case BaseImage::ImageFormat::JPEG:
        throw std::runtime_error("JPEG is not supported.\n");
        break;
    case BaseImage::ImageFormat::PNG:
        decoder = new PNG_Decoder();
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

    return decoder;
}

#ifndef DECODER_HPP
#define DECODER_HPP

#pragma once
#include "Common.hpp"
#include "ImageReader.hpp"

class DecoderInterface {
public:
    virtual ~DecoderInterface(){
    }
	 virtual bool Decoder(const std::string _fileName, uchar *&_outPtr,
		int &_width, int &_height, int &_channel) = 0;
};

class DecoderFactory {
public:
	static DecoderInterface*
	getDecoder(BaseImage::ImageFormat _format);
};


#endif // !DECODER_HPP

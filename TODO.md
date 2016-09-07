- [x] Decode TIFF
- [ ] Encode TIFF
- [ ] Add Define for earch supported Format
    """
    #ifdef JPEG_FOUND
                decoder.reset(new JPEG_Decoder());
    #else
                throw std::runtime_error("JPEG is not supported\n");
    #endif
    """

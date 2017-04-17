# - Try to find png++
#
# The following are set after configuration is done: 
#  png++_FOUND
#  png++_INCLUDE_DIRS
#  png++_LIBRARIES

find_package(PNG REQUIRED)

if(${PNG_FOUND})
    find_path(png++_INCLUDE_DIR
        NAMES
            png++/color.hpp
            png++/config.hpp
            png++/consumer.hpp
            png++/convert_color_space.hpp
            png++/end_info.hpp
            png++/error.hpp
            png++/ga_pixel.hpp
            png++/generator.hpp
            png++/gray_pixel.hpp
            png++/image.hpp
            png++/image_info.hpp
            png++/index_pixel.hpp
            png++/info.hpp
            png++/info_base.hpp
            png++/io_base.hpp
            png++/packed_pixel.hpp
            png++/palette.hpp
            png++/pixel_buffer.hpp
            png++/pixel_traits.hpp
            png++/png.hpp
            png++/reader.hpp
            png++/require_color_space.hpp
            png++/rgb_pixel.hpp
            png++/rgba_pixel.hpp
            png++/streaming_base.hpp
            png++/tRNS.hpp
            png++/types.hpp
            png++/writer.hpp
        PATHS
            ${png++_ROOT_DIR}
        PATH_SUFFIXES
            src)

    if(png++_INCLUDE_DIR)
        set(png++_INCLUDE_DIRS ${png++_INCLUDE_DIR} ${PNG_INCLUDE_DIRS})
        set(png++_LIBRARIES ${PNG_LIBRARIES})
        set(png++_FOUND TRUE)

        mark_as_advanced(png++_INCLUDE_DIRS png++_LIBRARIES png++_FOUND)
    else()
        set(png++_FOUND FALSE)
        mark_as_advanced(png++_FOUND)
    endif()

endif()

# Find TIFFXX
#
# The following are set after configuration is done: 
# TIFFXX_FOUND
# TIFFXX_INCLUDE_DIRS
# TIFFXX_LIBRARIES

find_package(TIFF REQUIRED)

if(${TIFF_FOUND})
    find_path(TIFFXX_INCLUDE_DIRS
        NAMES
        tiffio.hxx
    )
    
    if(TIFFXX_INCLUDE_DIRS)
        find_library(
            TIFFXX_LIBRARIES
            NAMES libtiffxx.a libtiffxx.so
            PATHS
            /usr/lib/x86_64-linux-gnu/
            /usr/lib/
            /usr/lib64/
        )

        if(TIFFXX_LIBRARIES)
            set(TIFFXX_FOUND TRUE)
            set(TIFFXX_INCLUDE_DIRS ${TIFFXX_INCLUDE_DIRS} ${TIFF_INCLUDE_DIR})
            set(TIFFXX_LIBRARIES ${TIFFXX_LIBRARIES} ${TIFF_LIBRARIES})
            mark_as_advanced(TIFFXX_FOUND TIFFXX_INCLUDE_DIRS TIFFXX_LIBRARIES)
        endif()
    else()
        set(TIFFXX_FOUND FALSE)
    endif()

endif()

set(IMAGE_HEADER
    ${LIBRARY_PATH}/image-converter/utils/bmp_data.h
    ${LIBRARY_PATH}/image-converter/utils/image_data.h
    ${LIBRARY_PATH}/image-converter/image_converter.h
    )

set(IMAGE_SOURCE
    ${LIBRARY_PATH}/image-converter/image_converter.cpp
    )

add_library(image-converter STATIC ${IMAGE_HEADER} ${IMAGE_SOURCE})
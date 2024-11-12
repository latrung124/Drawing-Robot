/*
* image_converter.h
* Author: Trung La
* Date: 2021-09-26
* Description: This file contains the image converter class.
*/

#ifndef IMAGE_CONVERTER_H
#define IMAGE_CONVERTER_H

#include <vector>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include "utils/image_data.h"

namespace image_converter {

using bytes= std::vector<uint8_t>;

class image_converter {
public:
    using image_16bit_data = utils::image_data::image_16bit_data;
    using color_table = utils::image_data::color_table;
    using color = utils::image_data::color;
    image_converter() = default;
    ~image_converter() = default;

    void setPixel(int x, int y, uint16_t color);

    bytes createImage(const image_16bit_data &image);
    bytes_16bit gridToImageBytes(const std::vector<std::vector<uint16_t>> &grid);
};

} // namespace image_converter

#endif // IMAGE_CONVERTER_H
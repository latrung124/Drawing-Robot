/*
* bmp_data.h
* Author: Trung La
* Date: 2021-09-26
* Description: This file contains the image data struct.
*/

#include <cstdint>
#include <vector>

namespace image_converter {

using bytes_16bit = uint16_t*;

namespace utils{

namespace image_data {

/**
 * @brief Struct representing the color without alpha.
 */
struct color {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

/**
 * @brief Struct representing the Color table.
 */
struct color_table {
    std::vector<color> colors;
};

/**
 * @brief Struct representing the image with 16 bits depth and rgb 565.
 */
struct image_16bit_data {
    uint32_t width;  ///< Image width in pixels.
    uint32_t height; ///< Image height in pixels.
    size_t size;     ///< Image size in bytes.
    bytes_16bit data;  ///< Image data.
    color_table colorTable; ///< Color table. should be 565.
};

} // namespace image_converter::utils::image_data

} // namespace image_converter::utils

} // namespace image_converter
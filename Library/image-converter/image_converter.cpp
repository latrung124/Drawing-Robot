/*
* image_converter.cpp
* Author: Trung La
* Date: 2021-09-26
* Description: This file contains the image converter class.
*/

#include "image_converter.h"
#include "utils/bmp_data.h"

namespace image_converter {

bytes image_converter::createImage(const image_16bit_data& image) {

    using namespace utils::bmp_data;

    if (image.data == nullptr) {
        throw std::invalid_argument("Image data is null.");
    } else if (image.width == 0 || image.height == 0) {
        throw std::invalid_argument("Image dimensions are invalid.");
    }

    // Create the DIB header
    dib_header dibHeader;
    dibHeader.width = image.width;
    dibHeader.height = -image.height;
    dibHeader.imageSize = image.width * image.height * sizeof(uint16_t); // 16-bit per pixel
    dibHeader.redMask = 0xF800;   // 5 bits red
    dibHeader.greenMask = 0x07E0; // 6 bits green
    dibHeader.blueMask = 0x001F;  // 5 bits blue

    // Create the BMP header
    bmp_header bmpHeader;
    bmpHeader.fileSize = sizeof(bmp_header) + sizeof(dib_header) + 3 * sizeof(uint32_t) + dibHeader.imageSize;
    bmpHeader.offsetData = sizeof(bmp_header) + sizeof(dib_header) + 3 * sizeof(uint32_t);

    // Create the BMP file
    bytes bmpFileBytes(bmpHeader.fileSize, 0);

    // Insert BMP and DIB headers
    std::memcpy(bmpFileBytes.data(), &bmpHeader, sizeof(bmp_header));
    std::memcpy(bmpFileBytes.data() + sizeof(bmp_header), &dibHeader, sizeof(dib_header));

    // Insert RGB565 bit masks (RGB565 format specification)
    std::memcpy(bmpFileBytes.data() + sizeof(bmp_header) + sizeof(dib_header), &dibHeader.redMask, sizeof(uint32_t));
    std::memcpy(bmpFileBytes.data() + sizeof(bmp_header) + sizeof(dib_header) + sizeof(uint32_t), &dibHeader.greenMask, sizeof(uint32_t));
    std::memcpy(bmpFileBytes.data() + sizeof(bmp_header) + sizeof(dib_header) + 2 * sizeof(uint32_t), &dibHeader.blueMask, sizeof(uint32_t));

    // Write the image data
    std::memcpy(bmpFileBytes.data() + bmpHeader.offsetData, image.data, dibHeader.imageSize);

    return bmpFileBytes;
}


bytes_16bit image_converter::gridToImageBytes(const std::vector<std::vector<uint16_t>>& grid) {
    int height = grid.size();
    if (height == 0) return {};

    int width = grid[0].size();
    uint16_t* imageBytes = new uint16_t[width * height];

    // Define RGB565 colors for white and black
    uint16_t white = 0xFFFF; // RGB565 for white
    uint16_t black = 0x0000; // RGB565 for black

    // Convert the grid to an image byte array
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Set pixel to black or white based on the grid value
            imageBytes[y * width + x] = grid[y][x] == 0 ? black : white;
        }
    }

    return imageBytes;
}

} // namespace image_converter
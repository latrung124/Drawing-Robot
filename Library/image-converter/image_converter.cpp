/*
 * image_converter.cpp
 * Author: Trung La
 * Date: 2021-09-26
 * Description: This file contains the image converter class.
 */

#include "image_converter.h"
#include "utils/bmp_data.h"

namespace image_converter {

bytes image_converter::createImage(const image_16bit_data &image)
{
	using namespace utils::bmp_data;

	if (image.data == nullptr) {
		throw std::invalid_argument("Image data is null.");
	} else if (image.width == 0 || image.height == 0) {
		throw std::invalid_argument("Image dimensions are invalid.");
	}

	// Calculate row padding and sizes
	int rowSize = image.width * sizeof(uint16_t); // 2 bytes per pixel
	int padding = (4 - (rowSize % 4)) % 4; // Calculate padding to align rows to 4 bytes
	int paddedRowSize = rowSize + padding;

	// Create the DIB header
	dib_header dibHeader;
	dibHeader.width = image.width;
	dibHeader.height = -image.height; // Negative for top-down image
	dibHeader.imageSize = paddedRowSize * image.height;
	// Other fields are already initialized with the default values in the struct

	// Create the BMP header
	bmp_header bmpHeader;
	bmpHeader.fileSize = sizeof(bmp_header) + sizeof(dib_header) + dibHeader.imageSize;
	bmpHeader.offsetData = sizeof(bmp_header) + sizeof(dib_header);

	// Create the BMP file with padding
	bytes bmpFileBytes(bmpHeader.fileSize, 0);

	// Write headers
	std::memcpy(bmpFileBytes.data(), &bmpHeader, sizeof(bmp_header));
	std::memcpy(bmpFileBytes.data() + sizeof(bmp_header), &dibHeader, sizeof(dib_header));

	// Write image data with padding
	uint8_t *dst = bmpFileBytes.data() + bmpHeader.offsetData;
	const uint8_t *src = reinterpret_cast<const uint8_t *>(image.data);

	for (int y = 0; y < image.height; y++) {
		// Copy row data
		std::memcpy(dst, src + y * rowSize, rowSize);
		// Move to next row (padding bytes are already zeroed)
		dst += paddedRowSize;
	}

	return bmpFileBytes;
}

bytes_16bit image_converter::gridToImageBytes(const std::vector<std::vector<uint16_t>> &grid)
{
	int height = grid.size();
	if (height == 0) {
		return nullptr;
	}

	int width = grid[0].size();
	if (width == 0) {
		return nullptr;
	}

	// Allocate memory
	uint16_t *imageBytes = new uint16_t[width * height];
	std::memset(imageBytes, 0, width * height * sizeof(uint16_t));

	// Define RGB565 colors
	constexpr uint16_t white = 0xFFFF;
	constexpr uint16_t black = 0x0000;

	// Convert grid to image bytes
	for (int y = 0; y < height; ++y) {
		if (grid[y].size() != width) {
			delete[] imageBytes;
			throw std::runtime_error("Inconsistent row width in grid");
		}
		for (int x = 0; x < width; ++x) {
			imageBytes[y * width + x] = grid[y][x] == 0 ? black : white;
		}
	}

	return imageBytes;
}

} // namespace image_converter

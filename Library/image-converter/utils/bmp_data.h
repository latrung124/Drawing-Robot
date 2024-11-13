/*
 * bmp_data.h
 * Author: Trung La
 * Date: 2021-09-26
 * Description: This file contains the BMP file header and DIB header structs.
 */
#include <cstdint>

namespace image_converter::utils::bmp_data {

#pragma pack(push, 1) // Ensure the BMP header is packed correctly

/**
 * @brief Struct representing the BMP file header.
 */
struct bmp_header
{
	uint16_t fileType{0x4D42}; ///< Specifies the BMP file type ('BM').
	uint32_t fileSize; ///< Size of the file in bytes.
	uint16_t reserved1{0}; ///< Reserved, must be zero.
	uint16_t reserved2{0}; ///< Reserved, must be zero.
	uint32_t offsetData; ///< Offset from start of file to pixel data.
};

/**
 * @brief Struct representing the DIB (Device Independent Bitmap) header.
 *
 * This header describes the image properties such as dimensions, color depth, and compression.
 * A device-independent bitmap (DIB) contains a color table.
 * A color table describes how pixel values correspond to RGB color values, which describe colors
 * that are produced by emitting light.
 */
struct dib_header
{
	uint32_t size{40}; ///< Size of the DIB header (usually 40 bytes). 4 bytes
	int32_t width; ///< Image width in pixels. 4 bytes
	int32_t height; ///< Image height in pixels (negative for top-down). 4 bytes
	uint16_t planes{1}; ///< Number of color planes, always set to 1. 2 bytes
	uint16_t bitCount{16}; ///< Color depth in bits (16 for RGB565). 2 bytes
	uint32_t compression{3}; ///< Compression method (3 = BI_BITFIELDS for RGB565). 4 bytes
	uint32_t imageSize; ///< Size of raw bitmap data in bytes. 4 bytes
	int32_t xPixelsPerMeter{2835}; ///< Horizontal resolution in pixels per meter (72 DPI). 4 bytes
	int32_t yPixelsPerMeter{2835}; ///< Vertical resolution in pixels per meter (72 DPI). 4 bytes
	uint32_t colorsUsed{0}; ///< Number of colors used (0 = all colors used). 4 bytes
	uint32_t colorsImportant{
	    0}; ///< Number of important colors (0 = all colors are important). 4 bytes
	int32_t redMask{0xF800}; ///< Mask for red channel in RGB565. 4 bytes
	int32_t greenMask{0x07E0}; ///< Mask for green channel in RGB565. 4 bytes
	int32_t blueMask{0x001F}; ///< Mask for blue channel in RGB565. 4 bytes
};

} // namespace image_converter::utils::bmp_data

#pragma pack(pop)

/*
 * draw_data.h
 * Author: Trung La
 * Date: 2021-09-26
 * Description: This file contains the draw data class.
 */

#ifndef DRAW_DATA_H
#define DRAW_DATA_H

#include <vector>

namespace draw_algorithm { namespace utils {

enum class draw_type
{
	LINE,
	CIRCLE,
};

struct position
{
	int x;
	int y;
};

struct grid_data
{
	int width;
	int height;
	std::vector<std::vector<uint16_t>> data;
};

struct draw_data
{
	grid_data grid;
	draw_type type;
	position start;
	position end;
};

}} // namespace draw_algorithm::utils

#endif // DRAW_DATA_H

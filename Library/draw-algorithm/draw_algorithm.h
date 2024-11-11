/*
* draw_algorithm.h
* Author: Trung La
* Date: 2021-09-26
* This file contains the implementation of the draw algorithm.
*/

#ifndef DRAW_ALGORITHM_H
#define DRAW_ALGORITHM_H

#include "utils/draw_data.h"

namespace draw_algorithm {

using draw_data = utils::draw_data;
using position = utils::position;

class draw_algorithm {

public:
    draw_algorithm() = default;
    ~draw_algorithm() = default;

    std::vector<position> drawLine(const draw_data &data);

private:
    std::vector<position> findPath(const draw_data &data);
};

} // namespace draw_algorithm

#endif //DRAW_ALGORITHM_H
set(ALGORITHM_HEADER
    ${LIBRARY_PATH}/draw-algorithm/utils/draw_data.h
    ${LIBRARY_PATH}/draw-algorithm/draw_algorithm.h
    )

set(ALGORITHM_SOURCE
    ${LIBRARY_PATH}/draw-algorithm/draw_algorithm.cpp
    )

add_library(draw-algorithm STATIC ${ALGORITHM_HEADER} ${ALGORITHM_SOURCE})
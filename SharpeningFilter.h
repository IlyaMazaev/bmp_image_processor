#pragma once

#include "MatrixFilter.h"

const std::vector<std::vector<float>> SHARPENING_MATRIX = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

class SharpeningFilter : public MatrixFilter {
public:
    SharpeningFilter() : MatrixFilter(SHARPENING_MATRIX) {
    }
};
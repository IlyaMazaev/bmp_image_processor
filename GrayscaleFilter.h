#pragma once

#include "Filter.h"

const float R_GRAY_COEFFICIENT = 0.299;
const float G_GRAY_COEFFICIENT = 0.587;
const float B_GRAY_COEFFICIENT = 0.114;

class GrayscaleFilter : public Filter {
public:
    ~GrayscaleFilter() override = default;

    void ApplyFilter(BmpImage &image) const final;
};

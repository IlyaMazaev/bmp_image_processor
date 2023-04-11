#pragma once

#include "Filter.h"

#include <algorithm>
#include <cmath>

const int GAUSS_SIGMA_COEFFICIENT = 4;

class GaussianBlurFilter : public Filter {
public:
    explicit GaussianBlurFilter(double sigma);

    ~GaussianBlurFilter() override = default;

    void ApplyFilter(BmpImage &image) const final;

private:
    double sigma_;
};
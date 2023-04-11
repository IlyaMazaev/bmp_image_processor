#pragma once

#include "Filter.h"

const int DISTANCE_DIVIDER_COEF = 100;
const double INTENSITY = 0.9;

class CustomFilter : public Filter {
public:
    ~CustomFilter() override = default;

    void ApplyFilter(BmpImage &image) const final;

    explicit CustomFilter(double distance);

private:
    double distance_;
};

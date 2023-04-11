#pragma once

#include "Filter.h"

class ThresholdFilter : public Filter {
public:
    ~ThresholdFilter() override = default;

    void ApplyFilter(BmpImage &image) const final;

    explicit ThresholdFilter(double threshold);

private:
    double threshold_;
};
#pragma once

#include "Filter.h"

class CropFilter : public Filter {
public:
    ~CropFilter() override = default;

    void ApplyFilter(BmpImage &image) const final;

    explicit CropFilter(int target_width, int target_height);

private:
    int target_width_;
    int target_height_;
};

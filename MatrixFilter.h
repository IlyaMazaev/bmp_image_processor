#pragma once

#include "Filter.h"

class MatrixFilter : public Filter {
public:
    ~MatrixFilter() override = default;

    explicit MatrixFilter(const std::vector<std::vector<float>> &matrix);

    void ApplyFilter(BmpImage &image) const final;

private:
    std::vector<std::vector<float>> matrix_;
};
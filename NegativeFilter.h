#pragma once

#include "Filter.h"

class NegativeFilter : public Filter {
public:
    ~NegativeFilter() override = default;

    void ApplyFilter(BmpImage &image) const final;
};
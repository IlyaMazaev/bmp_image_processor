#pragma once

#include "BmpImage.h"

class FilterException : public CustomException {
public:
    explicit FilterException(std::string msg) : CustomException(msg) {
    }
};

class Filter {
public:
    virtual void ApplyFilter(BmpImage &image) const = 0;

    virtual ~Filter() = default;
};
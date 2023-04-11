#pragma once

#include "CompositeFilter.h"
#include "GrayscaleFilter.h"
#include "MatrixFilter.h"
#include "ThresholdFilter.h"

const std::vector<std::vector<float>> EDGE_DETECTION_MATRIX = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

class EdgeDetectionFilter : public CompositeFilter {
public:
    explicit EdgeDetectionFilter(double threshold) : CompositeFilter({}) {
        AddFilter(std::make_unique<GrayscaleFilter>());
        AddFilter(std::make_unique<MatrixFilter>(EDGE_DETECTION_MATRIX));
        AddFilter(std::make_unique<ThresholdFilter>(threshold));
    }
};
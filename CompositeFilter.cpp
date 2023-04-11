#include "CompositeFilter.h"

CompositeFilter::CompositeFilter(std::vector<std::unique_ptr<Filter>> filters) : filters_(std::move(filters)) {
}

void CompositeFilter::ApplyFilter(BmpImage &image) const {
    for (const auto &filter : filters_) {
        filter->ApplyFilter(image);
    }
}

void CompositeFilter::AddFilter(std::unique_ptr<Filter> filter_ptr) {
    filters_.push_back(std::move(filter_ptr));
}
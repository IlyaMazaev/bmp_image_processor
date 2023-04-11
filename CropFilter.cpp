#include "CropFilter.h"

void CropFilter::ApplyFilter(BmpImage &image) const {
    if (target_height_ <= 0 or target_width_ <= 0) {
        throw FilterException("crop size must be > 0");
    }
    if (target_height_ < image.GetHeight() or target_width_ < image.GetWidth()) {
        // std::copy(image_data_->begin(), image_data_->end() + target_height, image_data_->begin());
        Pixelmap *cropped_image_data = new Pixelmap;

        int target_height = std::min(target_height_, image.GetHeight());
        int target_width = std::min(target_width_, image.GetWidth());

        for (int i = (image.GetHeight() - target_height); i < image.GetHeight(); ++i) {
            std::vector<Pixel> new_line(target_width);
            std::move(image.GetImageData()->at(i).begin(), image.GetImageData()->at(i).begin() + target_width,
                      new_line.begin());
            cropped_image_data->push_back(new_line);
        }

        std::swap(*cropped_image_data, *image.GetImageData());
        delete cropped_image_data;

        image.SetSize(target_width, target_height);
    }
}

CropFilter::CropFilter(int target_width, int target_height)
    : target_width_(target_width), target_height_(target_height) {
}

#include "ThresholdFilter.h"

ThresholdFilter::ThresholdFilter(double threshold) : threshold_(threshold) {
}

void ThresholdFilter::ApplyFilter(BmpImage &image) const {
    if (threshold_ <= 0 or threshold_ >= 1) {
        throw FilterException("invalid value for threshold parameter in threshold filter(must be 0 < double < 1)");
    }
    Pixelmap *new_image = new Pixelmap;
    for (int x = 0; x < image.GetHeight(); x++) {
        std::vector<Pixel> new_line;
        for (int y = 0; y < image.GetWidth(); y++) {
            Pixel new_pixel;
            if (image.GetImageData()->at(x).at(y).R > WHITE_PIXEL_VALUE * threshold_ and
                image.GetImageData()->at(x).at(y).G > WHITE_PIXEL_VALUE * threshold_ and
                image.GetImageData()->at(x).at(y).B > WHITE_PIXEL_VALUE * threshold_) {
                new_pixel.R = WHITE_PIXEL_VALUE;
                new_pixel.G = WHITE_PIXEL_VALUE;
                new_pixel.B = WHITE_PIXEL_VALUE;
            } else {
                new_pixel.R = 0;
                new_pixel.G = 0;
                new_pixel.B = 0;
            }

            new_line.push_back(new_pixel);
        }
        new_image->push_back(new_line);
    }

    std::swap(*new_image, *image.GetImageData());
    delete new_image;
}

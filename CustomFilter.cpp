#include <cmath>
#include "CustomFilter.h"

void CustomFilter::ApplyFilter(BmpImage &image) const {
    if (distance_ < 0 or distance_ > 4) {
        throw FilterException("invalid value for distance parameter in threshold filter(must be 0 <= double <= 4)");
    }
    int distance = ceil(image.GetWidth() / DISTANCE_DIVIDER_COEF * distance_);
    Pixelmap *new_image = new Pixelmap;
    for (int x_0 = 0; x_0 < image.GetHeight(); x_0++) {
        std::vector<Pixel> new_line;
        for (int y_0 = 0; y_0 < image.GetWidth(); y_0++) {
            if (y_0 + distance < image.GetWidth() - 1 and x_0 + distance < image.GetHeight() - 1) {
                Pixel new_pixel;
                new_pixel.R = static_cast<unsigned char>(image.GetImageData()->at(x_0 + distance).at(y_0 + distance).R *
                                                         INTENSITY);
                new_pixel.G = image.GetImageData()->at(x_0).at(y_0).G;
                new_pixel.B = image.GetImageData()->at(x_0).at(y_0).B;

                new_line.push_back(new_pixel);
            }
        }
        new_image->push_back(new_line);
    }
    image.SetSize(image.GetWidth() - distance - 1, image.GetHeight() - distance - 1);
    std::swap(*image.GetImageData(), *new_image);
    delete new_image;
}

CustomFilter::CustomFilter(double distance) : distance_(distance) {
    if (distance_ < 0 or distance_ > 4) {
        throw FilterException("invalid value for distance parameter in threshold filter(must be 0 <= double <= 4)");
    }
}

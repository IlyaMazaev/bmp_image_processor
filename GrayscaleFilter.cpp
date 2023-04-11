#include "GrayscaleFilter.h"

void GrayscaleFilter::ApplyFilter(BmpImage &image) const {
    for (std::vector<Pixel> &line : *image.GetImageData()) {
        for (Pixel &pixel : line) {
            unsigned char gray(static_cast<unsigned char>(R_GRAY_COEFFICIENT * static_cast<float>(pixel.R) +
                                                          G_GRAY_COEFFICIENT * static_cast<float>(pixel.G) +
                                                          B_GRAY_COEFFICIENT * static_cast<float>(pixel.B)));
            pixel.R = gray;
            pixel.G = gray;
            pixel.B = gray;
        }
    }
}

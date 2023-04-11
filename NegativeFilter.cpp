#include "NegativeFilter.h"

void NegativeFilter::ApplyFilter(BmpImage &image) const {
    for (std::vector<Pixel> &line : *image.GetImageData()) {
        for (Pixel &pixel : line) {
            pixel.R = WHITE_PIXEL_VALUE - pixel.R;
            pixel.G = WHITE_PIXEL_VALUE - pixel.G;
            pixel.B = WHITE_PIXEL_VALUE - pixel.B;
        }
    }
}

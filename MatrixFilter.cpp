#include "MatrixFilter.h"

void MatrixFilter::ApplyFilter(BmpImage &image) const {
    Pixelmap *new_image = new Pixelmap;
    for (int x = 0; x < image.GetHeight(); x++) {
        std::vector<Pixel> new_line;
        for (int y = 0; y < image.GetWidth(); y++) {
            Pixel new_pixel;
            new_pixel.R = std::min(
                static_cast<int>(WHITE_PIXEL_VALUE),
                std::max(
                    0,
                    static_cast<int>(
                        matrix_[0][1] * static_cast<float>(image.GetImageData()->at(x).at(std::max(y - 1, 0)).R) +
                        matrix_[1][0] * static_cast<float>(image.GetImageData()->at(std::max(x - 1, 0)).at(y).R) +
                        matrix_[1][1] * static_cast<float>(image.GetImageData()->at(x).at(y).R) +
                        matrix_[1][2] * static_cast<float>(
                                            image.GetImageData()->at(std::min(x + 1, image.GetHeight() - 1)).at(y).R) +
                        matrix_[2][1] * static_cast<float>(
                                            image.GetImageData()->at(x).at(std::min(y + 1, image.GetWidth() - 1)).R))));

            new_pixel.G = std::min(
                static_cast<int>(WHITE_PIXEL_VALUE),
                std::max(
                    0,
                    static_cast<int>(
                        matrix_[0][1] * static_cast<float>(image.GetImageData()->at(x).at(std::max(y - 1, 0)).G) +
                        matrix_[1][0] * static_cast<float>(image.GetImageData()->at(std::max(x - 1, 0)).at(y).G) +
                        matrix_[1][1] * static_cast<float>(image.GetImageData()->at(x).at(y).G) +
                        matrix_[1][2] * static_cast<float>(
                                            image.GetImageData()->at(std::min(x + 1, image.GetHeight() - 1)).at(y).G) +
                        matrix_[2][1] * static_cast<float>(
                                            image.GetImageData()->at(x).at(std::min(y + 1, image.GetWidth() - 1)).G))));

            new_pixel.B = std::min(
                static_cast<int>(WHITE_PIXEL_VALUE),
                std::max(
                    0,
                    static_cast<int>(
                        matrix_[0][1] * static_cast<float>(image.GetImageData()->at(x).at(std::max(y - 1, 0)).B) +
                        matrix_[1][0] * static_cast<float>(image.GetImageData()->at(std::max(x - 1, 0)).at(y).B) +
                        matrix_[1][1] * static_cast<float>(image.GetImageData()->at(x).at(y).B) +
                        matrix_[1][2] * static_cast<float>(
                                            image.GetImageData()->at(std::min(x + 1, image.GetHeight() - 1)).at(y).B) +
                        matrix_[2][1] * static_cast<float>(
                                            image.GetImageData()->at(x).at(std::min(y + 1, image.GetWidth() - 1)).B))));

            new_line.push_back(new_pixel);
        }
        new_image->push_back(new_line);
    }

    std::swap(*new_image, *image.GetImageData());
    delete new_image;
}

MatrixFilter::MatrixFilter(const std::vector<std::vector<float>> &matrix) : matrix_(matrix) {
}

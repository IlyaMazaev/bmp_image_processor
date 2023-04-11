#include "GaussianBlurFilter.h"

GaussianBlurFilter::GaussianBlurFilter(double sigma) : sigma_(sigma) {
}

void GaussianBlurFilter::ApplyFilter(BmpImage &image) const {
    if (sigma_ <= 0) {
        throw FilterException("invalid value for sigma parameter in gauss filter(must be double > 0)");
    }

    const int gauss_matrix_size = static_cast<int>(ceil(GAUSS_SIGMA_COEFFICIENT * sigma_));

    std::vector<double> gauss_coefficients;
    double gauss_coefficients_sum = 0;
    for (int i = 0; i < (gauss_matrix_size * 2 + 1); ++i) {
        double gauss_coefficient = (1 / (2 * M_PI * pow(sigma_, 2))) *
                                   pow(M_E, -(pow((i - (gauss_matrix_size * 2 + 1) / 2), 2)) / (2 * pow(sigma_, 2)));
        gauss_coefficients.push_back(gauss_coefficient);
        gauss_coefficients_sum += gauss_coefficient;
    }

    for (int i = 0; i < (gauss_matrix_size * 2 + 1); i++) {
        gauss_coefficients[i] /= gauss_coefficients_sum;
    }

    Pixelmap *new_image = new Pixelmap(image.GetHeight(), std::vector<Pixel>(image.GetWidth()));
    for (int x_0 = 0; x_0 < image.GetHeight(); x_0++) {
        for (int y_0 = 0; y_0 < image.GetWidth(); y_0++) {
            double r_value = 0;
            double g_value = 0;
            double b_value = 0;

            for (int x = -gauss_matrix_size; x <= gauss_matrix_size; x++) {
                Pixel current_pixel =
                    image.GetImageData()->at(std::max(0, std::min(image.GetHeight() - 1, x_0 + x))).at(y_0);
                r_value += current_pixel.R * gauss_coefficients[x + gauss_matrix_size];
                g_value += current_pixel.G * gauss_coefficients[x + gauss_matrix_size];
                b_value += current_pixel.B * gauss_coefficients[x + gauss_matrix_size];
            }
            new_image->at(x_0).at(y_0).R = static_cast<unsigned char>(r_value);
            new_image->at(x_0).at(y_0).G = static_cast<unsigned char>(g_value);
            new_image->at(x_0).at(y_0).B = static_cast<unsigned char>(b_value);
        }
    }

    for (int x_0 = 0; x_0 < image.GetHeight(); x_0++) {
        for (int y_0 = 0; y_0 < image.GetWidth(); y_0++) {
            double r_value = 0;
            double g_value = 0;
            double b_value = 0;
            for (int y = -gauss_matrix_size; y <= gauss_matrix_size; y++) {
                Pixel current_pixel = new_image->at(x_0).at(std::max(0, std::min(image.GetWidth() - 1, y_0 + y)));
                r_value += current_pixel.R * gauss_coefficients[y + gauss_matrix_size];
                g_value += current_pixel.G * gauss_coefficients[y + gauss_matrix_size];
                b_value += current_pixel.B * gauss_coefficients[y + gauss_matrix_size];
            }
            image.GetImageData()->at(x_0).at(y_0).R = static_cast<unsigned char>(r_value);
            image.GetImageData()->at(x_0).at(y_0).G = static_cast<unsigned char>(g_value);
            image.GetImageData()->at(x_0).at(y_0).B = static_cast<unsigned char>(b_value);
        }
    }
    delete new_image;
}

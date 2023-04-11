#include "BmpImage.h"
#include "Filter.h"
#include "CompositeFilter.h"
#include "GrayscaleFilter.h"
#include "NegativeFilter.h"
#include "CropFilter.h"
#include "SharpeningFilter.h"
#include "EdgeDetectionFilter.h"
#include "GaussianBlurFilter.h"
#include "CustomFilter.h"
#include "CustomException.h"

#include <iostream>
#include <algorithm>

class ArgParserException : public CustomException {
public:
    explicit ArgParserException(std::string msg) : CustomException(msg) {
    }
};

int main(int argc, char **argv) {
    try {
        std::cout << std::endl;
        if (argc == 1) {
            std::cout << "Приложение, позволяющее применять к изображениям различные фильтры, аналогичные фильтрам в "
                         "популярных графических редакторах."
                      << std::endl;

            std::cout << "Входные и выходные графические файлы должны быть в формате BMP." << std::endl;
            std::cout << "Описание формата аргументов командной строки:" << std::endl;
            std::cout
                << "{имя программы} {путь к входному файлу} {путь к выходному файлу} [-{имя фильтра 1} [параметр "
                   "фильтра "
                   "1] [параметр фильтра 2] ...] [-{имя фильтра 2} [параметр фильтра 1] [параметр фильтра 2] ...] ..."
                << std::endl;
            std::cout << "Доступные фильтры:" << std::endl;
            std::cout << "Crop (-crop width height)" << std::endl;
            std::cout << "Grayscale (-gs)" << std::endl;
            std::cout << "Negative (-neg)" << std::endl;
            std::cout << "Sharpening (-sharp)" << std::endl;
            std::cout << "Edge Detection (-edge threshold)" << std::endl;
            std::cout << "Gaussian Blur (-blur sigma)" << std::endl;
            std::cout << "3D like filter (-3d distance) (0 <= distance <= 4)" << std::endl;

        } else if (argc == 2) {
            throw ArgParserException("No output file path (not enough arguments)");

        } else {
            std::string executable_path = std::string(argv[0]);
            std::string input_path = std::string(argv[1]);
            std::string output_path = std::string(argv[2]);
            std::cout << "EXECUTABLE FILE: " << executable_path << std::endl;
            std::cout << "INPUT FILE: " << input_path << std::endl;
            std::cout << "OUTPUT FILE: " << output_path << std::endl;

            BmpImage image(&input_path);
            std::vector<std::unique_ptr<Filter>> filters = {};
            for (int i = 3; i < argc; ++i) {
                auto str = std::string(argv[i]);

                if (str == "-crop") {
                    int width = 0;
                    int height = 0;
                    try {
                        width = stoi(std::string(argv[++i]));
                        height = stoi(std::string(argv[++i]));
                    } catch (std::exception &e) {
                        std::cerr << "invalid crop arguments(must be int int)" << std::endl;
                        return 0;
                    }
                    std::cout << "applying crop (width: " << width << " height: " << height << ")" << std::endl;
                    filters.push_back(std::make_unique<CropFilter>(width, height));

                } else if (str == "-gs") {
                    std::cout << "applying grayscale" << std::endl;
                    filters.push_back(std::make_unique<GrayscaleFilter>());

                } else if (str == "-neg") {
                    std::cout << "applying negative" << std::endl;
                    filters.push_back(std::make_unique<NegativeFilter>());

                } else if (str == "-sharp") {
                    std::cout << "applying sharpening" << std::endl;
                    filters.push_back(std::make_unique<SharpeningFilter>());

                } else if (str == "-edge") {
                    double threshold = -1;
                    if (i < (argc - 1)) {
                        threshold = atof(argv[++i]);
                    } else {
                        throw ArgParserException("no threshold argument for edge filter");
                    }
                    std::cout << "applying edge detection (threshold: " << threshold << ")" << std::endl;
                    filters.push_back(std::make_unique<EdgeDetectionFilter>(threshold));

                } else if (str == "-blur") {
                    double sigma = -1;
                    if (i < (argc - 1)) {
                        sigma = atof(argv[++i]);
                    } else {
                        throw ArgParserException("no sigma argument for gauss blur filter");
                    }
                    std::cout << "applying gaussian blur (sigma: " << sigma << ")" << std::endl;
                    filters.push_back(std::make_unique<GaussianBlurFilter>(sigma));

                } else if (str == "-3d") {
                    double distance = -1;
                    if (i < (argc - 1)) {
                        distance = atof(argv[++i]);
                    } else {
                        throw ArgParserException("no distance argument for 3D filter");
                    }
                    std::cout << "applying 3d filter" << std::endl;
                    filters.push_back(std::make_unique<CustomFilter>(distance));

                } else {
                    throw ArgParserException("unknown filter: " + std::string(argv[i]));
                }
            }
            try {
                CompositeFilter composite_filter = CompositeFilter(std::move(filters));
                composite_filter.ApplyFilter(image);

            } catch (FilterException &e) {
                image.~BmpImage();
                std::cerr << "Error while applying filter: " << e.what() << std::endl;
                return 0;
            }
            image.SaveImage(&output_path);
        }
        return 0;
    } catch (BmpOpenException &e) {
        std::cerr << "Failed to open input image (" << e.what() << ")" << std::endl;
        return 0;

    } catch (BmpCloseException &e) {
        std::cerr << "Failed to save image (" << e.what() << ")" << std::endl;
        return 0;

    } catch (ArgParserException &e) {
        std::cerr << "Invalid argument: (" << e.what() << ")" << std::endl;
        return 0;
    }
}
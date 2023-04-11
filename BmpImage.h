#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include "CustomException.h"

const uint8_t WHITE_PIXEL_VALUE = 255;

class BmpOpenException : public CustomException {
public:
    explicit BmpOpenException(std::string msg) : CustomException(msg) {
    }
};

class BmpCloseException : public CustomException {
public:
    explicit BmpCloseException(std::string msg) : CustomException(msg) {
    }
};

struct Pixel {
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

using Pixelmap = std::vector<std::vector<Pixel>>;

class BmpImage {
public:
    explicit BmpImage(std::string *filename);

    void SaveImage(std::string *filename);

    ~BmpImage();

    int GetHeight() const;

    int GetWidth() const;

    Pixelmap *GetImageData() const;

    void SetSize(int target_width, int target_height);

private:
    int height_;
    int width_;
    std::vector<unsigned char> header_data_;
    Pixelmap *image_data_;
};
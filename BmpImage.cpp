#include "BmpImage.h"
#include "iostream"
#include <filesystem>

const int HEADER_WIDTH_BYTE = 18;
const int HEADER_HEIGHT_BYTE = 22;
const int HEADER_BYTE_SIZE = 54;

const char BYTE = 8;

int BmpImage::GetHeight() const {
    return height_;
}

int BmpImage::GetWidth() const {
    return width_;
}

Pixelmap *BmpImage::GetImageData() const {
    return image_data_;
}

void BmpImage::SetSize(int target_width, int target_height) {
    header_data_[HEADER_WIDTH_BYTE] = static_cast<unsigned char>(target_width);
    header_data_[HEADER_WIDTH_BYTE + 1] = static_cast<unsigned char>(target_width >> BYTE);
    header_data_[HEADER_WIDTH_BYTE + 2] = static_cast<unsigned char>(target_width >> BYTE * 2);
    header_data_[HEADER_WIDTH_BYTE + 3] = static_cast<unsigned char>(target_width >> BYTE * 3);
    header_data_[HEADER_HEIGHT_BYTE] = static_cast<unsigned char>(target_height);
    header_data_[HEADER_HEIGHT_BYTE + 1] = static_cast<unsigned char>(target_height >> BYTE);
    header_data_[HEADER_HEIGHT_BYTE + 2] = static_cast<unsigned char>(target_height >> BYTE * 2);
    header_data_[HEADER_HEIGHT_BYTE + 3] = static_cast<unsigned char>(target_height >> BYTE * 3);

    height_ = target_height;
    width_ = target_width;
}

BmpImage::BmpImage(std::string *filename) {
    if (!((filename->at(filename->size() - 3) == 'b') and (filename->at(filename->size() - 2) == 'm') and
          (filename->at(filename->size() - 1) == 'p'))) {
        throw BmpOpenException("input file is not a bmp image");
    }

    FILE *f = std::fopen(filename->c_str(), "rb");

    if (!f) {
        throw BmpOpenException("file does not exist");
    }

    unsigned char info[HEADER_BYTE_SIZE];
    fread(info, sizeof(unsigned char), HEADER_BYTE_SIZE, f);  // read the 54-byte header
    for (unsigned char info_byte : info) {
        header_data_.push_back(info_byte);
    }

    if (!((header_data_[0] == 'B') and (header_data_[1] == 'M'))) {
        throw BmpOpenException("image is not a bmp BM format");
    }

    // extract image height and width from header
    width_ = *reinterpret_cast<int *>(&info[HEADER_WIDTH_BYTE]);
    height_ = *reinterpret_cast<int *>(&info[HEADER_HEIGHT_BYTE]);

    if (width_ <= 0 or height_ <= 0) {
        throw BmpOpenException("negative or zero size");
    }

    std::cout << std::endl;
    std::cout << "  Name: " << *filename << std::endl;
    std::cout << " Width: " << width_ << std::endl;
    std::cout << "Height: " << height_ << std::endl;

    int row_padded = (width_ * 3 + 3) & (~3);
    unsigned char *data = new unsigned char[row_padded];

    Pixelmap *image_data = new Pixelmap;

    for (int i = 0; i < height_; i++) {
        fread(data, sizeof(unsigned char), row_padded, f);
        std::vector<Pixel> line;
        for (int j = 0; j < width_ * 3; j += 3) {
            line.push_back(Pixel{data[j + 2], data[j + 1], data[j]});
        }
        image_data->push_back(line);
    }
    fclose(f);
    image_data_ = std::move(image_data);
    delete[] data;
}

BmpImage::~BmpImage() {
    std::cout << "deleted image data" << std::endl;
    delete image_data_;
}

void BmpImage::SaveImage(std::string *filename) {
    if (!((filename->at(filename->size() - 3) == 'b') and (filename->at(filename->size() - 2) == 'm') and
          (filename->at(filename->size() - 1) == 'p'))) {
        throw BmpCloseException("output file is not a bmp image");
    }

    FILE *f = fopen(filename->c_str(), "wb");
    unsigned char header[HEADER_BYTE_SIZE];
    std::copy(header_data_.begin(), header_data_.end(), header);
    if (!f) {
        delete image_data_;
        throw BmpCloseException(
            "Failed to write to output file(probably target dir doesn't exist)(image data was deleted)");
    }
    fwrite(header, 1, HEADER_BYTE_SIZE, f);

    int padding_size = (4 - (width_ * 3) % 4) % 4;
    unsigned char padding[3] = {0, 0, 0};

    for (const std::vector<Pixel> &line : *image_data_) {
        for (Pixel pixel : line) {
            unsigned char pixel_char[3] = {pixel.B, pixel.G, pixel.R};
            fwrite(pixel_char, 1, 3, f);
        }
        fwrite(padding, 1, padding_size, f);
    }
    fclose(f);
    std::cout << "Successfully saved image at " << *filename << std::endl;
}

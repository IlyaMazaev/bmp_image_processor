#include "CustomException.h"

CustomException::CustomException(std::string msg) : message_(msg) {
}

const char *CustomException::what() const noexcept {
    return message_.c_str();
}
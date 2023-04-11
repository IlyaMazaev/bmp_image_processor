#pragma once

#include <string>

class CustomException : public std::exception {
public:
    explicit CustomException(std::string msg);

    const char *what() const noexcept override;

private:
    std::string message_;
};
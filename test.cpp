#include <catch.hpp>

#include "BmpImage.h"
#include "CustomFilter.h"

TEST_CASE("Input is not BMP File"){
    try{
        std::string path = "data/image.jpg";
        BmpImage test(&path);
    } catch (BmpOpenException &e){
        REQUIRE(e.what() == std::string("input file is not a bmp image"));
    }
}

TEST_CASE("Invalid path to input file (can not open)"){
    try{
        std::string path = "data/image.bmp";
        BmpImage test(&path);
    } catch (BmpOpenException &e){
        REQUIRE(e.what() == std::string("file does not exist"));
    }
}

TEST_CASE("Invalid 3d filter param"){
    try{
        const double distance_input = 10;
        CustomFilter filter = CustomFilter(distance_input);
    } catch (FilterException &e){
        REQUIRE(e.what() == std::string("invalid value for distance parameter in threshold filter(must be 0 <= double <= 4)"));
    }
}
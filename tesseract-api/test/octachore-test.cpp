#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "octachore.hpp"
#include <boost/filesystem.hpp>

std::string imagePath{"lorem-ipsum-mini.tif"};
std::string currentPath = boost::filesystem::current_path().string();
std::string text = Octachore::getAllText(currentPath + "/../test/" + imagePath);

TEST_CASE("getAllText have to return some good text") {
    REQUIRE(text.find("Lorem ipsum dolor sit amet") != std::string::npos);
}
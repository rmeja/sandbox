#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "octachore.hpp"
#include <boost/filesystem.hpp>

std::string currentPath = boost::filesystem::current_path().string();
std::string imagePath{currentPath + "/test/lorem-ipsum-mini.tif"};
std::string text = Octachore::getAllText(imagePath, "eng", tesseract::PSM_AUTO);
Boxa *blockBoxes = Octachore::getAllComponentImage(imagePath, tesseract::RIL_BLOCK);

TEST_CASE("getAllText have to return some good text") {
  REQUIRE(text.find("Lorem ipsum dolor sit amet") != std::string::npos);
}

TEST_CASE("getAllComponentImage should return some block segmentation information") {
  REQUIRE(blockBoxes->n == 1);
  REQUIRE(blockBoxes->box[0]->x == 33);
  REQUIRE(blockBoxes->box[0]->y == 37);
  REQUIRE(blockBoxes->box[0]->w == 518);
  REQUIRE(blockBoxes->box[0]->h == 37);
}
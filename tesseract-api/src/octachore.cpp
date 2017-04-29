#include "octachore.hpp"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

std::string Octachore::getAllText(std::string imagePath) {
    const char *cstrImagePath = imagePath.c_str();
    Pix *image = pixRead(cstrImagePath);
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    api->Init(NULL, "eng");
    api->SetPageSegMode(tesseract::PSM_AUTO);
    api->SetImage(image);
    api->Recognize(0);
    char *text = api->GetUTF8Text();
    std::string outputText{text};
    api->End();
    pixDestroy(&image);
    return outputText;
}
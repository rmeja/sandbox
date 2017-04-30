#include "octachore.hpp"
#include <vector>

std::string Octachore::getAllText(std::string imagePath) {
    Pix *image = pixRead(imagePath.c_str());
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

Boxa* Octachore::getAllComponentImage(std::string imagePath, tesseract::PageIteratorLevel blockType) {
    Pix *image = pixRead(imagePath.c_str());
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    api->Init(NULL, "eng");
    api->SetPageSegMode(tesseract::PSM_AUTO);
    api->SetImage(image);
    return api->GetComponentImages(blockType, true, NULL, NULL);
}
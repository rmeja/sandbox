#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

int main() {

    Pix *image = pixRead("/home/meja/Dev/envrac/tiff/test.tif");
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    api->Init(NULL, "eng");
    api->SetImage(image);
    Boxa *boxes = api->GetComponentImages(tesseract::RIL_PARA, true, NULL, NULL);
    printf("Found %d paragraph image components.\n", boxes->n);
    for (int i = 0; i < boxes->n; i++) {
        BOX *box = boxaGetBox(boxes, i, L_CLONE);
        api->SetRectangle(box->x, box->y, box->w, box->h);
        std::cout << "Box[" << i <<"]: x="<< box->x <<", y="<< box->y <<", w="<< box->w <<", h="<< box->h << std::endl;
    }

    // Destroy used object and release memory
    api->End();
    pixDestroy(&image);

    return 0;
}
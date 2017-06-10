#include <iostream>
#include <vector>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

using namespace std;

int main(int argc, char *argv[]) {
    auto input = argv[1];
    if (argc < 2) {
        cout << "argument missing" << std::endl;
        exit(1);
    }
    Pix *image = pixRead(input);
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    api->Init(NULL, "eng");
    api->SetPageSegMode(tesseract::PSM_AUTO);
    api->SetImage(image);

    struct boxComponentImage { string name; Boxa* box; };
    boxComponentImage blockBoxes = { "blockBoxes", api->GetComponentImages(tesseract::RIL_BLOCK, true, NULL, NULL)};
    boxComponentImage paragraphBoxes = {"paragraphBoxes", api->GetComponentImages(tesseract::RIL_PARA, true, NULL, NULL)};
    boxComponentImage textLineBoxes = {"textLineBoxes", api->GetComponentImages(tesseract::RIL_TEXTLINE, true, NULL, NULL)};

    vector<boxComponentImage> boxesComponentImage{ blockBoxes, paragraphBoxes, textLineBoxes };
    for (const boxComponentImage boxComponentImage : boxesComponentImage) {
        cout << "Found " << boxComponentImage.box->n << " " << boxComponentImage.name << " image components.\n" << endl;
        for (int i = 0; i < boxComponentImage.box->n; i++) {
            BOX *box = boxaGetBox(boxComponentImage.box, i, L_CLONE);
            std::cout << "Box[" << i << "]: x=" << box->x << ", y=" << box->y << ", w=" << box->w << ", h=" << box->h
                      << std::endl;
        }
    }

    api->Recognize(0);
    // char* outText = api->GetUTF8Text();
    // cout << outText << endl;
    // delete [] outText;
    tesseract::ResultIterator* ri = api->GetIterator();
    tesseract::PageIteratorLevel level = tesseract::RIL_BLOCK;
    if (ri != 0) {
        do {
        const char* word = ri->GetUTF8Text(level);
        float conf = ri->Confidence(level);
        int x1, y1, x2, y2;
        ri->BoundingBox(level, &x1, &y1, &x2, &y2);
        printf("word: '%s';  \tconf: %.2f; BoundingBox: %d,%d,%d,%d;\n",
                word, conf, x1, y1, x2, y2);
        int blocktype = static_cast<int>(ri->BlockType());
        printf("blocktype: %d\n", blocktype);
        delete[] word;
        } while (ri->Next(level));
    }
    api->End();
    pixDestroy(&image);
    return 0;
}

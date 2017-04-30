#ifndef OCTACHORE_H
#define OCTACHORE_H

#include <string>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

namespace Octachore {
    std::string getAllText(std::string imagePath);
    struct boxComponentImage { std::string name; Boxa* box; };
    Boxa* getAllComponentImage(std::string imagePath, tesseract::PageIteratorLevel blockType);
}

#endif // !OCTACHORE_H


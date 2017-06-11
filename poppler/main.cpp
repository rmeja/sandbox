#include <iostream>
#include <memory>

#include <poppler-document.h>
#include <poppler-page.h>
using namespace std;

int main(int argc, char *argv[]) {
    auto input = argv[1];
    shared_ptr<poppler::document> doc{ poppler::document::load_from_file(input) };
    const int pagesNbr = doc->pages();
    cout << "page count: " << pagesNbr << endl;

    for (int i = 0; i < pagesNbr; ++i) {
        shared_ptr<poppler::page> currentPage{ doc->create_page(i) };
        auto byteArrayResult = currentPage->text().to_utf8();
        string result{byteArrayResult.begin(), byteArrayResult.end()};
        cout << result << endl;
    }
}

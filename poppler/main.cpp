#include <iostream>
#include <memory>
#include <poppler-document.h>
#include <poppler-page.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
  auto input = argv[1];
  shared_ptr<poppler::document> doc{poppler::document::load_from_file(input)};
  if (doc == NULL) {
    return 1;
  }
  const int pagesNbr = doc->pages();
  cout << "Page count : " << pagesNbr << endl;
  vector<string> infoKeys{doc->info_keys()};
  for_each(infoKeys.begin(), infoKeys.end(), [doc](string &infoKey){
    cout << infoKey << " : " << doc->info_key(infoKey).to_latin1() << endl;  
  });
  
  for (int i = 0; i < pagesNbr; ++i) {
    shared_ptr<poppler::page> currentPage{doc->create_page(i)};
    auto byteArrayResult = currentPage->text().to_utf8();
    string result{byteArrayResult.begin(), byteArrayResult.end()};
    cout << result << endl;
  }
}

#include "lib/gserrors.h"
#include "lib/iapi.h"
#include <cstring>
#include <ctime>
#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class Ghostscript {
private:
  Ghostscript() = default;
  Ghostscript(const Ghostscript&) = delete;
  Ghostscript& operator=(const Ghostscript&) = delete;

  void* minst;
  static unique_ptr<Ghostscript> instance;
  static once_flag onceFlag;
  static int gsdll_stdin(void* instance, char* buf, int len) {
    int ch;
    int count = 0;
    while (count < len) {
      ch = fgetc(stdin);
      if (ch == EOF)
        return 0;
      *buf++ = (char)ch;
      count++;
      if (ch == '\n')
        break;
    }
    return count;
  }
  static int gsdll_stdout(void* instance, const char* str, int len) { return len; }
  static int gsdll_stderr(void* instance, const char* str, int len) { return len; }

public:
  void initInstance() {
    int gscode = gsapi_new_instance(&minst, NULL);
    if (gscode < 0)
      throw runtime_error("could not create a new ghostscript instance");
    gsapi_set_stdio(minst, gsdll_stdin, gsdll_stdout, gsdll_stderr);
    gscode = gsapi_set_arg_encoding(minst, GS_ARG_ENCODING_UTF8);
    if (gscode < 0)
      throw runtime_error("could not set encoding in ghostscript instance");
  }

  void execute(vector<string> args) {
    if (args.size() == 0)
      throw runtime_error("empty command for ghostscript interpreter");

    unsigned int gsargc = (unsigned int)args.size() + 1;
    char* gsargv[gsargc];
    gsargv[0] = (char*)"gs";
    for (int unsigned i = 0; i < args.size(); i++) {
      char* argsToChar = new char[args[i].length() + 1];
      strcpy(argsToChar, args[i].c_str());
      gsargv[i + 1] = argsToChar;
    }

    int gscode = gsapi_init_with_args(minst, gsargc, gsargv);
    if (gscode < 0)
      throw runtime_error("ghostscript interpreter failed. Code error : " + to_string(gscode));
  }

  void exitInstance() {
    int gscode = gsapi_exit(minst);
    if (gscode < 0)
      throw runtime_error("failed to exit ghostscript instance");
  }

  void deleteInstance() { gsapi_delete_instance(minst); }

  static Ghostscript& getInstance() {
    std::call_once(Ghostscript::onceFlag, []() {
      Ghostscript* gs = new Ghostscript();
      gs->initInstance();
      instance.reset(gs);
    });
    return *(instance.get());
  }
};

std::unique_ptr<Ghostscript> Ghostscript::instance;
std::once_flag Ghostscript::onceFlag;

int main(int argc, char* argv[]) {
  vector<string> args1 = {"-dNOPAUSE", "-dBATCH", "-sDEVICE=tiff24nc", "-r300", "-sOutputFile=test1-%03d.tiff", "test1.pdf"};
  vector<string> args2 = {"-dNOPAUSE", "-dBATCH", "-sDEVICE=tiff24nc", "-r300", "-sOutputFile=test2-%03d.tiff", "test2.pdf"};
  Ghostscript& gs1 = Ghostscript::getInstance();
  Ghostscript& gs2 = Ghostscript::getInstance();
  gs1.execute(args1);
  gs2.execute(args2);
  gs1.exitInstance();
  gs2.deleteInstance();
}
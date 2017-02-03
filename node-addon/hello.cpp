// hello.cc
#include <nan.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace Nan;
using namespace v8;

class HelloAsync : public AsyncWorker {
    public: HelloAsync(Callback * callback) : AsyncWorker(callback) {}

    // Executes in worker thread
    void Execute() {
        std::this_thread::sleep_for(chrono::milliseconds(1000));
    }
    // Executes in event loop
    void HandleOKCallback () {
        Local<String> world = Nan::New<String>("... world").ToLocalChecked();
        Local<Value> argv[] = { world };
        callback->Call(1, argv);
    }
};

NAN_METHOD(helloAsync) {
    Callback *callback = new Callback(info[0].As<Function>());
    AsyncQueueWorker(new HelloAsync(callback));
}

NAN_METHOD(hello) {
    info.GetReturnValue().Set(Nan::New<String>("world").ToLocalChecked());
}

NAN_MODULE_INIT(Init) {
  Nan::Set(target, New<String>("hello").ToLocalChecked(),
      GetFunction(New<FunctionTemplate>(hello)).ToLocalChecked());
  Nan::Set(target, New<String>("helloAsync").ToLocalChecked(),
          GetFunction(New<FunctionTemplate>(helloAsync)).ToLocalChecked());
}

NODE_MODULE(addon, Init)

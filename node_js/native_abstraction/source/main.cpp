#include <nan.h>
#include <string>

using v8::Function;
using v8::Local;
using v8::Number;
using v8::Value;
using Nan::AsyncQueueWorker;
using Nan::AsyncWorker;
using Nan::Callback;
using Nan::HandleScope;
using Nan::New;
using Nan::Null;
using Nan::To;

class NodeWorker : public AsyncWorker
{
public:
    NodeWorker(const char* input, Callback* callback)
        : AsyncWorker(callback)
        , _input(input)
    {
    }

    ~NodeWorker()
    {
    }

    // Executed inside the worker-thread.
    // It is not safe to access V8, or V8 data structures
    // here, so everything we need for input and output
    // should go on `this`.
    void Execute()
    {
        printf("AsyncWorker - Execute - Input: %s \n", _input.c_str());
        printf("AsyncWorker - Enter a letter and press Enter to continue: \n");
        _output = getchar();
        _output = "{'result':'";
        _output += _input;
        _output += " - Execute with Success'}\n";
    }

    // Executed when the async work is complete
    // this function will be run inside the main event loop
    // so it is safe to use V8 again
    void HandleOKCallback()
    {
        printf("AsyncWorker - OKCallback\n");

        HandleScope scope;
        auto message = Nan::New(_output.c_str()).ToLocalChecked();
        Local<Value> argv[] = {Null(), message};
        callback->Call(2, argv);
    }

private:
    std::string _input;
    std::string _output;
};

NAN_METHOD(RunAsync)
{
    if (info.Length() < 2)
    {
        auto message = Nan::New("{'error_description': 'Invalid Number of parameters'}").ToLocalChecked();
        info.GetReturnValue().Set(message);
        return;
    }

    if (!info[0]->IsString())
    {
        auto message = Nan::New("{'error_description': 'First Parameter should be string'}").ToLocalChecked();
        info.GetReturnValue().Set(message);
        return;
    }

    if (!info[1]->IsFunction())
    {
        auto message = Nan::New("{'error_description': 'Second Parameter should be a callback function'}").ToLocalChecked();
        info.GetReturnValue().Set(message);
        return;
    }

    std::string input(*v8::String::Utf8Value(info[0]->ToString()));
    Nan::Callback* callback = new Nan::Callback(info[1].As<v8::Function>());
    AsyncQueueWorker(new NodeWorker(input.c_str(), callback));
}

NAN_METHOD(Run)
{
    std::string parameter;
    if (info.Length() < 1)
    {
        auto message = Nan::New("{'error_description': 'Invalid Number of parameters'}").ToLocalChecked();
        info.GetReturnValue().Set(message);
        return;
    }

    if (!info[0]->IsString())
    {
        auto message = Nan::New("{'error_description': 'First Parameter should be string'}").ToLocalChecked();
        info.GetReturnValue().Set(message);
        return;
    }

    parameter = *v8::String::Utf8Value(info[0]->ToString());
    printf("Run - Parameter: %s \n", parameter.c_str());

    std::string output = "{'result':'";
    output += parameter.c_str();
    output += " - Executed with success'}\n";

    auto message = Nan::New(output.c_str()).ToLocalChecked();
    info.GetReturnValue().Set(message);
}

// Module initialization logic
NAN_MODULE_INIT(Initialize)
{
    // Export the `Run` function (equivalent to `export function Hello (...)` in JS)
    NAN_EXPORT(target, RunAsync);
    NAN_EXPORT(target, Run);
}

// Create the module called "addon" and initialize it with `Initialize` function (created with NAN_MODULE_INIT macro)
NODE_MODULE(native_addon, Initialize);

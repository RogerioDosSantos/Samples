#include <nan.h>

// NAN_METHOD is a Nan macro enabling convenient way of creating native node functions.
// It takes a method's name as a param. By C++ convention, I used the Capital cased name.
NAN_METHOD(Run)
{
    // Create an instance of V8's String type
    auto message = Nan::New("Hello from Native C++ code!").ToLocalChecked();
    // 'info' is a macro's "implicit" parameter - it's a bridge object between C++ and JavaScript runtimes
    // You would use info to both extract the parameters passed to a function as well as set the return value.
    info.GetReturnValue().Set(message);
}

// Module initialization logic
NAN_MODULE_INIT(Initialize)
{
    // Export the `Run` function (equivalent to `export function Hello (...)` in JS)
    NAN_EXPORT(target, Run);
}

// Create the module called "addon" and initialize it with `Initialize` function (created with NAN_MODULE_INIT macro)
NODE_MODULE(native_addon, Initialize);

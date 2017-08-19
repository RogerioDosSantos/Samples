#include <nan.h>
#include <string>

// NAN_METHOD is a Nan macro enabling convenient way of creating native node functions.
// It takes a method's name as a param. By C++ convention, I used the Capital cased name.
NAN_METHOD(Run)
{
	if (info.Length() > 0)
	{
		if (info[0]->IsString())
		{
			std::string parameter(*v8::String::Utf8Value(info[0]->ToString()));
			printf("Run - Parameter: %s \n", parameter.c_str());
		}
	}

	auto message = Nan::New("Hello from Native C++ code!").ToLocalChecked();
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

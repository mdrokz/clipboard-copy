#include <node.h>
#include <windows.h>
#include <iostream>
#include <string>
namespace demo
{

using v8::Context;
using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

void Method(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();
    // Check the number of arguments passed.
    if (args.Length() < 1)
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "wrong number of arguments", NewStringType::kNormal).ToLocalChecked()));
        return;
    }

    // Check the argument types
    // if (!args[0]->IsNumber() || !args[1]->IsNumber())
    // {
    //     isolate->ThrowException(Exception::TypeError(
    //         String::NewFromUtf8(isolate,
    //                             "Wrong arguments",
    //                             NewStringType::kNormal)
    //             .ToLocalChecked()));
    //     return;
    // }

    // double value =
    //     args[0].As<Number>()->Value() + args[1].As<Number>()->Value();
    // Local<Number> num = Number::New(isolate, value);
    Local<String> value =
        args[0].As<String>()->ToString(context).ToLocalChecked();
    // String str = String::NewFromUtf8(isolate, value, NewStringType::kNormal).ToLocalChecked();

    // Set the return value (using the passed in
    // FunctionCallbackInfo<Value>&)
    v8::String::Utf8Value param1(args[0]->ToString());
    std::string from = std::string(*param1);
    const char *val = from.c_str();
    const size_t len = strlen(val) + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), val, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
    
    args.GetReturnValue().Set(value);
    //   args.GetReturnValue().Set(String::NewFromUtf8(
    //       isolate, "world", NewStringType::kNormal).ToLocalChecked());
    // args.GetReturnValue().Set("args");
}

void Initialize(Local<Object> exports)
{
    NODE_SET_METHOD(exports, "writeToClipboard", Method);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

} // namespace demo
// #ifdef __cplusplus
// extern "C" {
// #endif

// int foo (int param){
//   int ret = 0;
//   // do C++ things
//   return ret;
// }

// int bar(){
//   int ret = 0;
//   // do C++ things
//   return ret;
// }

// #ifdef __cplusplus
// }
// #endif

#include <string>
#include <iostream>
#include <windows.h>
class clipboard
{
  void writeToClipboard(
      std::string name)
  {
    std::cout
        << "Hello, "
        << name << "!\n";
    const char *val = value.c_str();
    const size_t len = strlen(val) + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), val, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
  }
};

#include "nbind/nbind.h"

NBIND_CLASS(clipboard)
{
  method(writeToClipboard);
}
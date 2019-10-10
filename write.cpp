#include <windows.h>
#include <iostream>
#include <string>

void writeToClipboard(std::string value)
{   const char* val = value.c_str(); 
    const size_t len = strlen(val) + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), val, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}


int main()
{
    writeToClipboard("hello");
}
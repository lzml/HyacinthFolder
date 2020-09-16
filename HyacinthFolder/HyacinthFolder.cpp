// HyacinthFolder.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "HyacinthFolder.h"

DWORD kExceptionCode = 12345;
WPARAM kCrashMsg = 98765;


LRESULT CALLBACK TestWindowProc(HWND hwnd, UINT message,
    WPARAM wparam, LPARAM lparam) {
    if (message == kCrashMsg)
        RaiseException(kExceptionCode, 0, 0, NULL);
    return DefWindowProc(hwnd, message, wparam, lparam);
}



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    std::wstring class_name(CLASSNAME);

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = base::win::WrappedWindowProc<TestWindowProc>;
    wc.hInstance = hInstance;
    wc.lpszClassName = class_name.c_str();
    RegisterClass(&wc);

    HWND window = CreateWindow(class_name.c_str(),0 ,0, 0, 0, 200, 2000, 0, 0,
        hInstance, 0);

    
 
    return 0;
}



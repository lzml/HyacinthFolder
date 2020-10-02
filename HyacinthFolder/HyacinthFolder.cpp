// HyacinthFolder.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "HyacinthFolder.h"
#include "MainWnd.h"
#include "res2/SResLoader.h"
#include <base/at_exit.h>
#include "res2/resString.h"

//DWORD kExceptionCode = 12345;
//WPARAM kCrashMsg = 98765;


typedef struct {
    wkeWebView window;
    std::wstring url;
} Application;

Application app;

bool isOneInstance()
{
    HANDLE mutex = CreateMutexW(NULL, TRUE, L"Hello HyacinthFolder");
    if ((mutex != NULL) && (GetLastError() == ERROR_ALREADY_EXISTS)) {
        ReleaseMutex(mutex);
        return false;
    }
    return true;
}


//jsValue onMsg(jsExecState es, void* param)
//{
//    int argCount = jsArgCount(es);
//    if (argCount < 1)
//        return jsUndefined();
//
//    jsType type = jsArgType(es, 0);
//    if (JSTYPE_STRING != type)
//        return jsUndefined();
//
//    jsValue arg0 = jsArg(es, 0);
//    std::string msgOutput = "eMsg:";
//    std::string msg = jsToTempString(es, arg0);
//    msgOutput = msgOutput + msg;
//    msgOutput += "\n";
//    OutputDebugStringA(msgOutput.c_str());
//
//    if ("close" == msg) {
//        //blinkClose();
//    }
//    else if ("max" == msg) {
//        //blinkMaximize();
//    }
//    else if ("min" == msg) {
//        //blinkMinimize();
//    }
//
//    return jsUndefined();
//}
//
//jsValue WKE_CALL_TYPE onShellExec(jsExecState es, void* param)
//{
//    if (0 == jsArgCount(es))
//        return jsUndefined();
//    jsValue arg0 = jsArg(es, 0);
//    if (!jsIsString(arg0))
//        return jsUndefined();
//
//    std::string path;
//    path = jsToTempString(es, arg0);
//    if ("runEchars" == path) {
//        //createECharsTest();
//    }
//    else if ("wkeBrowser" == path) {
//       // wkeBrowserMain(nullptr, nullptr, nullptr, TRUE);
//    }
//
//    path += "\n";
//    OutputDebugStringA(path.c_str());
//
//    return jsUndefined();
//}


void runMessageLoop(Application* app)
{
    MSG msg = { 0 };
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //base::MessageLoop loop(base::MessageLoop::TYPE_UI);
    //std::wstring class_name(CLASSNAME);

    //WNDCLASS wc = { 0 };
    //wc.lpfnWndProc = base::win::WrappedWindowProc<TestWindowProc>;
    //wc.hInstance = hInstance;
    //wc.lpszClassName = class_name.c_str();
    //RegisterClass(&wc);

    //HWND window = CreateWindow(class_name.c_str(), L"123" , WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0,
    //    400, 600, 0, 0,  hInstance, 0);

    //ShowWindow(window, SW_SHOWNORMAL);

    //loop.Run();
	if (!isOneInstance()) {
		::MessageBoxW(NULL, L"该进程已经启动", L"错误", MB_OK);
		return 0;
	}


    {	//单例生命期范围
		base::AtExitManager exit_manager;
		SResStringLoader::GetInstance()->initInstance();
	
		do
		{
			base::FilePath  path_current_dir;
			if (!base::PathProvider(base::BasePathKey::DIR_EXE, &path_current_dir))
			{
				break;
			}
#ifdef _DEBUG
			base::FilePath path_mb(L"E:\\HyacinthFolder\\miniblink\\miniblink_x64.dll");// path_current_dir.AppendASCII("..\\..\\miniblink\\node.dll");
#else
#endif // DEBUG


			std::vector<wchar_t> vmbPath;
			std::wstring tmp = path_mb.AsUTF16Unsafe();
			vmbPath.assign(tmp.begin(), tmp.end());
			vmbPath.push_back('\0');

			wkeSetWkeDllPath(&vmbPath[0]);
			if (!wkeInitialize())
			{
				break;
			}

			MainWnd mainWindow;
			if (!WebWindow::createWebWindow(GETRESSTRINGW(ResString::title_main), &mainWindow, L"E:\\HyacinthFolder\\webres\\index.html",
				WKE_WINDOW_TYPE_TRANSPARENT, NULL, 0, 0, 1920, 1048))
			{
				PostQuitMessage(0);
				break;
			}



			runMessageLoop(&app);

		} while (0);

		wkeFinalize();
    }
    


    return 0;
}



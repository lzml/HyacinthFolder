// HyacinthFolder.cpp : 定义应用程序的入口点。
//
#include <functional>
#include <vector>
#include "framework.h"
#include "HyacinthFolder.h"
#include "MainWnd.h"
#include "res2/SResLoader.h"
#include <base/at_exit.h>
#include <base/threading/thread.h>
#include <base/memory/weak_ptr.h>
#include "res2/resString.h"
#include "MsgThreadManager.h"

#include "FileSearcher.h"
#include "FileSearcherThread.h"

#include "Any.hpp"


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


void test123(base::Any ddd)
{
	int sss = 0;
}

class testClass456 : public base::SupportsWeakPtr<testClass456>
{
public:
	void test456(FileSearcherThread::SearcherDataList ddd)
	{
		int sss = 0;
	}

private:

};




void runMessageLoop(Application* app)
{
    MSG msg = { 0 };
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

void ToggleValue(bool* value) {
	//处理没有导入lib，导致的这个宏无法使用，注释或者导入lib都可以
  //ANNOTATE_BENIGN_RACE(value, "Test-only data race on boolean "
  //                     "in base/thread_unittest");
	Sleep(5000);
	*value = !*value;

}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	if (!isOneInstance()) {
		::MessageBoxW(NULL, L"该进程已经启动", L"错误", MB_OK);
		return 0;
	}

    {
		//消息循环
		base::MessageLoopForUI loop;
		//单例生命期范围
		base::AtExitManager exit_manager;
		SResStringLoader::GetInstance()->initInstance();		
		base::WeakPtrFactory<base::MessageLoopForUI> factory(&loop);
		MsgThreadManager::GetInstance()->addUiThead(factory.GetWeakPtr());
		//启动常驻线程
		FileSearcherThread t;
		t.StartAndWaitForTesting();
		MsgThreadManager::GetInstance()->addOtherThread(ThreadKind::FileSearcherThread, t.AsWeakPtr());
		
		//**************************     测试异步检索文件夹代码

		//FileSearcherThread 线程调用的lambda回调函数，可以通知其他线程并且传递数据
		std::function<void(FileSearcherThread::SearcherDataList &&)> sssddd =
			std::bind([](FileSearcherThread::SearcherDataList && argsList) {
				//这里可以通知其他线程，把数据传递出去，也可以直接操作
				std::string ttt = argsList.at(0).AnyCast<std::string>();
				std::string zzz = argsList.at(1).AnyCast<std::string>();
				}, 
				std::placeholders::_1);
;
		//传递的目录，以及其他可能需要的参数
		FileSearcherThread::SearcherDataList list; 
		list.push_back(123);
		list.push_back(std::wstring(L"d:"));

		//传递给FileSearcherThread线程的闭包
		auto  closu = base::Bind(&FileSearcherThread::DoWork2, t.AsWeakPtr(),
			fileSearcherWorkId::eNumOneFolder, std::move(list), std::move(sssddd));

		//发送消息，传递闭包参数
		MSGPOSTTASK(ThreadKind::FileSearcherThread, FROM_HERE, std::move(closu));
		
		//******************************

		do
		{
			base::FilePath  path_current_dir;
			if (!base::PathProvider(base::BasePathKey::DIR_EXE, &path_current_dir))
			{
				break;
			}
#ifdef _DEBUG
			base::FilePath path_mb(L"..\\miniblink\\miniblink_x64.dll");// path_current_dir.AppendASCII("..\\..\\miniblink\\node.dll");
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
			base::FilePath pathIndexHtml = path_current_dir.AppendASCII("..\\webres\\index.html");
			if (!WebWindow::createWebWindow(GETRESSTRINGW(ResString::title_main), &mainWindow, pathIndexHtml.AsUTF16Unsafe(),
				WKE_WINDOW_TYPE_TRANSPARENT, NULL, 0, 0, 1920, 1048))
			{
				PostQuitMessage(0);
				break;
			}
			

			

			//runMessageLoop(&app);

			loop.Run();

		} while (0);

		wkeFinalize();
    }
    


    return 0;
}



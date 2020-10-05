#include "MainWnd.h"
#include "MsgThreadManager.h"
#include <base/path_service.h>
#include <base/files/file_path.h>

void MainWnd::initWebWindow(WebWindow* webWindow)
{
	wkeWebView view = webWindow->getWkeWebView();


	//wkeJsBindFunction("eMsg", &onMsg, nullptr, 5);
	//wkeJsBindFunction("eShellExec", &onShellExec, nullptr, 3);
	//wkeMoveToCenter(view);
	wkeLoadURLW(view, webWindow->getInitUrl());

	

}


bool MainWnd::handlerWindowClosing(WebWindow* webWindow)
{
	 return true; 
}

void MainWnd::handlerWindowDestroy(WebWindow* webWindow)
{
	PostQuitMessage(0);
}


void MainWnd::handlerDocumentReady(WebWindow* webWindow)
{
	
	wkeShowWindow(webWindow->getWkeWebView(), true);


#ifdef _DEBUG
	base::FilePath  path_current_dir;
	base::PathProvider(base::BasePathKey::DIR_EXE, &path_current_dir);
	base::FilePath pathIndexHtml = path_current_dir.AppendASCII("..\\miniblink\\front_end\\inspector.html");
	//wkeShowDevtools(webWindow->getWkeWebView(),
	//	L"file:///E:/HyacinthFolder/miniblink/front_end/inspector.html", 0, 0);
	wkeShowDevtools(webWindow->getWkeWebView(),
		pathIndexHtml.AsUTF16Unsafe().c_str(), 0, 0);
#endif // _DEBUG

}

jsValue MainWnd::handlerJsMsgloop(WebWindow* webWindow, jsExecState es)
{
	int argCount = jsArgCount(es);
	if (argCount < 1)
		return jsUndefined();

	jsValue arg0 = jsArg(es, 0);
	std::string msg = jsToTempString(es, arg0);

	if ("close" == msg)
	{
		HWND hwnd = wkeGetWindowHandle(webWindow->getWkeWebView());
		::PostMessageW(hwnd, WM_CLOSE, 0, 0);
	}
	else if ("getFilelist" == msg)
	{
		jsValue arg1 = jsArg(es, 1);
		std::string inputContent = jsToTempString(es, arg1);
		jsValue arg2 = jsArg(es, 2);
		//不查找了，直接异步回调，调用js试试
		MSGPOSTTASK(ThreadKind::UI, FROM_HERE, std::bind([webWindow,es, arg2] {
			//jsValue jsCall(jsExecState es, jsValue func, jsValue thisObject, jsValue * args, int argCount)
			//	执行页面中的js函数，
			//	func：要执行的函数，
			//	thisObject：如果此js函数是成员函数，则需要填thisValue，否则可以传jsUndefined，
			//	args：func的参数数组，
			//	argCount：参数个数。
			//void jsSetAt(jsExecState es, jsValue object, int index, jsValue v)
			//	设置js arrary的第index个成员的值，object必须是js array才有用。
			//jsValue jsEmptyArray(jsExecState es)
			//	创建一个表示js array的jsValue。
			jsValue val = jsEmptyArray(es);
			jsSetAt(es, val, 0, jsInt(123456));
			jsSetAt(es, val, 1, jsStringW(es, L"sdfkjdfsdf"));
			jsCall(es, arg2, jsUndefined(), &val, 1);
			int mmm = 0;
			}));
		
	}

	return jsUndefined();
}
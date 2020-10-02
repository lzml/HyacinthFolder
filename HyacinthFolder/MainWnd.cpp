#include "MainWnd.h"

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

	return jsUndefined();
}
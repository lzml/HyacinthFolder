#include "MainWnd.h"

void MainWnd::initWebWindow(WebWindow* webWindow)
{
	wkeWebView view = webWindow->getWkeWebView();


	//wkeJsBindFunction("eMsg", &onMsg, nullptr, 5);
	//wkeJsBindFunction("eShellExec", &onShellExec, nullptr, 3);
	//wkeMoveToCenter(view);
	wkeLoadURLW(view, webWindow->getInitUrl());

	

}


void MainWnd::handlerDocumentReady(WebWindow* webWindow)
{
	
	wkeShowWindow(webWindow->getWkeWebView(), true);


}

jsValue MainWnd::handlerJsMsgloop(WebWindow* webView, jsExecState es)
{
	int argCount = jsArgCount(es);
	if (argCount < 1)
		return jsUndefined();

	jsValue arg0 = jsArg(es, 0);
	std::string msg = jsToTempString(es, arg0);

	if ("close" == msg)
	{

	}

	return jsUndefined();
}
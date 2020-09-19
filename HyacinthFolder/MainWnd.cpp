#include "MainWnd.h"

void MainWnd::initWebWindow(WebWindow* webWindow)
{
	wkeWebView view = webWindow->getWkeWebView();


	//wkeJsBindFunction("eMsg", &onMsg, nullptr, 5);
	//wkeJsBindFunction("eShellExec", &onShellExec, nullptr, 3);
	wkeMoveToCenter(view);
	wkeLoadURLW(view, webWindow->getInitUrl());



}


void MainWnd::handlerDocumentReady(WebWindow* webWindow)
{
	
	wkeShowWindow(webWindow->getWkeWebView(), true);


}
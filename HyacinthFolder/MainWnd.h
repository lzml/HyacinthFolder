#pragma once
#include "WebWindow.h"


class MainWnd :  public IWebCallback
{
public:
	MainWnd() {};

	void initWebWindow(WebWindow* webWindow) final;
	
	void handlerDocumentReady(WebWindow* webWindow) final;

	jsValue handlerJsMsgloop(WebWindow* webWindow, jsExecState es) final;

	bool handlerWindowClosing(WebWindow* webWindow) final;
	void handlerWindowDestroy(WebWindow* webWindow) final;
};


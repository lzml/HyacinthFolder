#pragma once
#include "WebWindow.h"


class MainWnd :  public IWebCallback
{
public:
	MainWnd() {};

	void initWebWindow(WebWindow* webWindow) final;
	
	void handlerDocumentReady(WebWindow* webWindow) final;

};


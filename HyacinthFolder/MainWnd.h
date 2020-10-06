#pragma once
#include "WebWindow.h"
#include "JsFileArrayObject.h"
#include "FileSearcherThread.h"


class MainWnd :  public IWebCallback
	,  public base::SupportsWeakPtr<MainWnd>
{
public:
	MainWnd();

	void initWebWindow(WebWindow* webWindow) final;
	
	void handlerDocumentReady(WebWindow* webWindow) final;

	jsValue handlerJsMsgloop(WebWindow* webWindow, jsExecState es) final;

	bool handlerWindowClosing(WebWindow* webWindow) final;
	void handlerWindowDestroy(WebWindow* webWindow) final;


private:
	void fileSearcherResultCallback(jsValue jsCallback, const FileSearcherThread::SearcherDataList& list );

private:
	JsFileArrayObject* jsFileArrayObject_;
	WebWindow* webWnd_;
};


#include "WebWindow.h"


bool WebWindow::createWebWindow(std::wstring title, IWebCallback* webCallback,std::wstring url,
	wkeWindowType type, HWND parent, int x, int y, int width, int height)
{

	wkeWebView view = wkeCreateWebWindow(type, parent, x, y, width, height);
	if (!view)
	{
		return false;
	}

	//HWND hwnd = wkeGetWindowHandle(view);
	//LONG style = GetWindowLong(hwnd, GWL_STYLE);
	//SetWindowLong(hwnd, GWL_STYLE, style & ~WS_CAPTION  );

	WebWindow* webWnd = new WebWindow;
	webWnd->webWindow_ = view;
	webWnd->webCallback_ = webCallback;
	webWnd->init_url_ = url;

	wkeSetWindowTitleW(view, title.c_str());

	wkeOnDidCreateScriptContext(view, WebWindow::handDidCreateScriptContex, webWnd);
	wkeOnWindowClosing(view, WebWindow::handWindowClosing, webWnd);
	wkeOnWindowDestroy(view, WebWindow::handWindowDestroy, webWnd);
	wkeOnDocumentReady(view, WebWindow::handDocumentReady, webWnd);
	wkeOnTitleChanged(view, WebWindow::handTitleChanged, webWnd);
	wkeOnCreateView(view, WebWindow::handCreateView, webWnd);
	wkeOnLoadUrlBegin(view, WebWindow::handLoadUrlBegin, webWnd);
	wkeOnLoadUrlEnd(view, WebWindow::handLoadUrlEnd, webWnd);

	wkeJsBindFunction("eMsg", &WebWindow::handJsMsgloop, webWnd, 5);

	if (webCallback)
	{
		webCallback->initWebWindow(webWnd);
	}



	return true;
}

wkeWebView WebWindow::getWkeWebView() const
{
	return webWindow_;
}

const wchar_t* WebWindow::getInitUrl() 
{
	return init_url_.c_str();
}

WebWindow::WebWindow()
	:webCallback_(nullptr)
	, webWindow_(nullptr)
{

}



bool WebWindow::handWindowClosing(wkeWebView webWindow, void* param)
{
	WebWindow* pWebWindow = (WebWindow*)param;
	if (!pWebWindow)	return true;
	return pWebWindow->webCallback_->handlerWindowClosing(pWebWindow);
 }

 void WebWindow::handWindowDestroy(wkeWebView webWindow, void* param)
 {
	 WebWindow* pWebWindow = (WebWindow*)param;
	 if (!pWebWindow)	return ;
	 return pWebWindow->webCallback_->handlerWindowDestroy(pWebWindow);
 }

 void WebWindow::handDocumentReady(wkeWebView webWindow, void* param) 
 {
	 WebWindow* pWebWindow = (WebWindow*)param;
	 if (!pWebWindow)	return ;
	 return pWebWindow->webCallback_->handlerDocumentReady(pWebWindow);
 }

 void WebWindow::handTitleChanged(wkeWebView webWindow, void* param, const wkeString title)
 {
	 WebWindow* pWebWindow = (WebWindow*)param;
	 if (!pWebWindow)	return;
	 return pWebWindow->webCallback_->handlerTitleChanged(pWebWindow, title);
 }

 wkeWebView WebWindow::handCreateView(wkeWebView webWindow, void* param, wkeNavigationType navType,
	 const wkeString url, const wkeWindowFeatures* features)
 {
	 WebWindow* pWebWindow = (WebWindow*)param;
	 if (!pWebWindow)	return nullptr;
	 return pWebWindow->webCallback_->handlerCreateView(pWebWindow, navType, url, features);
 }

 //void WebWindow::handReadJsFile(const wchar_t* path, std::vector<char>* buffer)
 //{
	// WebWindow* pWebWindow = (WebWindow*)param;
	// if (!pWebWindow)	return ;
	// return pWebWindow->webCallback_->handlerReadJsFile(pWebWindow, path, buffer);
 //}

 bool WebWindow::handLoadUrlBegin(wkeWebView webView, void* param, const char* url, void* job)
{
	 WebWindow* pWebWindow = (WebWindow*)param;
	 if (!pWebWindow)	return false;
	 return pWebWindow->webCallback_->handlerLoadUrlBegin(pWebWindow,url,job);
}

 void WebWindow::handLoadUrlEnd(wkeWebView webView, void* param, const char* url, void* job, void* buf, int len)
{
	 WebWindow* pWebWindow = (WebWindow*)param;
	 if (!pWebWindow)	return ;
	 return pWebWindow->webCallback_->handlerLoadUrlEnd(pWebWindow,url,job, buf, len);
}

void  WebWindow::handDidCreateScriptContex(wkeWebView webView, void* param, wkeWebFrameHandle frameId, 
	void* context, int extensionGroup, int worldId)
{
	WebWindow* pWebWindow = (WebWindow*)param;
	if (!pWebWindow)	return ;
	return pWebWindow->webCallback_->handlerDidCreateScriptContex(pWebWindow, frameId, context, extensionGroup, worldId);
}


 jsValue WebWindow::handJsMsgloop(jsExecState es, void* param)
{
	 WebWindow* pWebWindow = (WebWindow*)param;
	 if (!pWebWindow)	return jsUndefined();
	 return pWebWindow->webCallback_->handlerJsMsgloop(pWebWindow, es);
}
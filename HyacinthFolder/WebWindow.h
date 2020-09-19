#pragma once
#include <string>
#include "IWebCallback.h"


class WebWindow
{
public:
	static bool createWebWindow(std::wstring title, IWebCallback* webCallback, std::wstring url,
		wkeWindowType type, HWND parent, int x, int y, int width, int height);


	//IWebCallback* getWebCallback() const;
	wkeWebView getWkeWebView() const;
	const wchar_t *  getInitUrl();

private:
	WebWindow();


	static bool WKE_CALL_TYPE handWindowClosing(wkeWebView webWindow, void* param);

	static void WKE_CALL_TYPE handWindowDestroy(wkeWebView webWindow, void* param) ;

	static void WKE_CALL_TYPE handDocumentReady(wkeWebView webWindow, void* param) ;

	static void WKE_CALL_TYPE handTitleChanged(wkeWebView webWindow, void* param, const wkeString title) ;

	static wkeWebView WKE_CALL_TYPE handCreateView(wkeWebView webWindow, void* param,
		wkeNavigationType navType, const wkeString url, const wkeWindowFeatures* features) ;

	//static void WKE_CALL_TYPE handReadJsFile(const wchar_t* path, std::vector<char>* buffer) ;

	static bool WKE_CALL_TYPE handLoadUrlBegin(wkeWebView webView, void* param, const char* url, void* job) ;
	static void WKE_CALL_TYPE handLoadUrlEnd(wkeWebView webView, void* param, const char* url, void* job,
		void* buf, int len) ;

	static void WKE_CALL_TYPE handDidCreateScriptContex(wkeWebView webView, void* param,
		wkeWebFrameHandle frameId, void* context, int extensionGroup, int worldId) ;


	static jsValue WKE_CALL_TYPE handJsMsgloop(jsExecState es, void* param);

private:
	IWebCallback* webCallback_;
	wkeWebView webWindow_;
	std::wstring init_url_;
};


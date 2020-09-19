#pragma once
#include "../miniblink/wke.h"
#include <vector>

class WebWindow;

class IWebCallback
{
	friend class WebWindow;
public:
	//初始化web，用于加载url，绑定js函数等等
	virtual void initWebWindow(WebWindow* webWindow) = 0;

	// 回调：点击了关闭、返回 true 将销毁窗口，返回 false 什么都不做。
	virtual bool handlerWindowClosing(WebWindow* webWindow) { return true; }
	// 回调：窗口已销毁
	virtual void handlerWindowDestroy(WebWindow* webWindow) {}
	// 回调：文档加载成功
	virtual void handlerDocumentReady(WebWindow* webWindow) {}
	// 回调：页面标题改变
	virtual void handlerTitleChanged(WebWindow* webWindow,  const wkeString title) {}
	// 回调：创建新的页面，比如说调用了 window.open 或者点击了 <a target="_blank" .../>
	virtual wkeWebView handlerCreateView(WebWindow* webWindow,
		wkeNavigationType navType, const wkeString url,
		const wkeWindowFeatures* features) { return nullptr;	}

	//virtual void handlerReadJsFile(const wchar_t* path, std::vector<char>* buffer) {}

	virtual bool handlerLoadUrlBegin(WebWindow* webView, const char* url, void* job) { return false; }
	virtual void handlerLoadUrlEnd(WebWindow* webView, const char* url, void* job, void* buf, int len) {}

	virtual void WKE_CALL_TYPE handlerDidCreateScriptContex(WebWindow* webView, wkeWebFrameHandle frameId, void* context, int extensionGroup, int worldId) {}

};


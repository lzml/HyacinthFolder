#pragma once
#include "../miniblink/wke.h"
#include <vector>

class WebWindow;

class IWebCallback
{
	friend class WebWindow;
public:
	//��ʼ��web�����ڼ���url����js�����ȵ�
	virtual void initWebWindow(WebWindow* webWindow) = 0;

	// �ص�������˹رա����� true �����ٴ��ڣ����� false ʲô��������
	virtual bool handlerWindowClosing(WebWindow* webWindow) { return true; }
	// �ص�������������
	virtual void handlerWindowDestroy(WebWindow* webWindow) {}
	// �ص����ĵ����سɹ�
	virtual void handlerDocumentReady(WebWindow* webWindow) {}
	// �ص���ҳ�����ı�
	virtual void handlerTitleChanged(WebWindow* webWindow,  const wkeString title) {}
	// �ص��������µ�ҳ�棬����˵������ window.open ���ߵ���� <a target="_blank" .../>
	virtual wkeWebView handlerCreateView(WebWindow* webWindow,
		wkeNavigationType navType, const wkeString url,
		const wkeWindowFeatures* features) { return nullptr;	}

	//virtual void handlerReadJsFile(const wchar_t* path, std::vector<char>* buffer) {}

	virtual bool handlerLoadUrlBegin(WebWindow* webView, const char* url, void* job) { return false; }
	virtual void handlerLoadUrlEnd(WebWindow* webView, const char* url, void* job, void* buf, int len) {}

	virtual void WKE_CALL_TYPE handlerDidCreateScriptContex(WebWindow* webView, wkeWebFrameHandle frameId, void* context, int extensionGroup, int worldId) {}

};


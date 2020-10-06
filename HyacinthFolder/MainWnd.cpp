#include "MainWnd.h"
#include "MsgThreadManager.h"
#include <base/path_service.h>
#include <base/files/file_path.h>
#include "FileSearcherThread.h"


MainWnd::MainWnd()
	: jsFileArrayObject_(nullptr)
	, webWnd_(nullptr)
{

}

void MainWnd::initWebWindow(WebWindow* webWindow)
{
	jsFileArrayObject_ = new JsFileArrayObject;

	wkeWebView view = webWindow->getWkeWebView();


	//wkeJsBindFunction("eMsg", &onMsg, nullptr, 5);
	//wkeJsBindFunction("eShellExec", &onShellExec, nullptr, 3);
	//wkeMoveToCenter(view);
	wkeLoadURLW(view, webWindow->getInitUrl());

	webWnd_ = webWindow;

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


#ifdef _DEBUG
	base::FilePath  path_current_dir;
	base::PathProvider(base::BasePathKey::DIR_EXE, &path_current_dir);
	base::FilePath pathIndexHtml = path_current_dir.AppendASCII("..\\miniblink\\front_end\\inspector.html");
	//wkeShowDevtools(webWindow->getWkeWebView(),
	//	L"file:///E:/HyacinthFolder/miniblink/front_end/inspector.html", 0, 0);
	wkeShowDevtools(webWindow->getWkeWebView(),
		pathIndexHtml.AsUTF16Unsafe().c_str(), 0, 0);
#endif // _DEBUG

	jsExecState es = wkeGlobalExec(webWindow->getWkeWebView());
	jsValue obj = jsObject(es, jsFileArrayObject_);
	jsSetGlobal(es, "nativeFileArray", obj);

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
	else if ("getFilelist" == msg)
	{
		jsValue arg1 = jsArg(es, 1);
		std::wstring inputContent = jsToTempStringW(es, arg1);
		jsValue arg2 = jsArg(es, 2);

		//异步查找文件夹
		FileSearcherThread::SearcherDataList list;
		list.emplace_back(inputContent);
		auto resultCallback = base::Bind(&MainWnd::fileSearcherResultCallback, this->AsWeakPtr(), arg2);
		//auto pThread = MsgThreadManager::GetInstance()->getThread(ThreadKind::FileSearcherThread);
		auto workClosure = base::Bind(&FileSearcherThread::DispatchTask, FROM_HERE,
			fileSearcherWorkId::eNumOneFolder,
			std::move(list),
			std::move(resultCallback));
		MSGPOSTTASK_C(FROM_HERE, ThreadKind::FileSearcherThread , std::move(workClosure));

		//auto findClosure = base::Bind(&FileSearcherThread::DoWork1,
		//	fileSearcherWorkId::eNumOneFolder,std::move(list), std::move(resultCallback));
		//MSGPOSTTASK_CT(typeid(typename std::decay<FileSearcherThread>::type ),ThreadKind::FileSearcherThread, FROM_HERE,
		//	&FileSearcherThread::DoWork1,std::move(list), std::move(resultCallback));

		//不查找了，直接异步回调，调用js试试
		//MSGPOSTTASK(ThreadKind::UI, FROM_HERE, std::bind([webWindow,es, arg2] {
		//	//jsValue jsCall(jsExecState es, jsValue func, jsValue thisObject, jsValue * args, int argCount)
		//	//	执行页面中的js函数，
		//	//	func：要执行的函数，
		//	//	thisObject：如果此js函数是成员函数，则需要填thisValue，否则可以传jsUndefined，
		//	//	args：func的参数数组，
		//	//	argCount：参数个数。
		//	//void jsSetAt(jsExecState es, jsValue object, int index, jsValue v)
		//	//	设置js arrary的第index个成员的值，object必须是js array才有用。
		//	//jsValue jsEmptyArray(jsExecState es)
		//	//	创建一个表示js array的jsValue。
		//	jsValue val = jsEmptyArray(es);
		//	jsSetAt(es, val, 0, jsInt(123456));
		//	jsSetAt(es, val, 1, jsStringW(es, L"sdfkjdfsdf"));
		//	jsCall(es, arg2, jsUndefined(), &val, 1);
		//	int mmm = 0;
		//	}));
		
	}

	return jsUndefined();
}


void MainWnd::fileSearcherResultCallback(jsValue jsCallback, const FileSearcherThread::SearcherDataList& list)
{
	DWORD id = GetCurrentThreadId();
	if (GETMsgThreadManager()->getUIthreadHandle() == id)
	{
		
		jsExecState es = wkeGlobalExec(webWnd_->getWkeWebView());
		jsValue val = jsEmptyArray(es);
		for (int i=0;i<list.size();i++ )
		{
			base::Any any  = list.at(i);
			pFileAttribute fileAttr = any.AnyCast<pFileAttribute>();
			jsFileArrayObject_->value_.emplace_back(fileAttr);

			
			jsSetAt(es, val, i, jsObject(es, fileAttr));
			//jsSetAt(es, val, 1, jsStringW(es, L"sdfkjdfsdf"));		
		}
		//FileAttribute* tt = new FileAttribute;
		//tt->dwFileAttributes = 111;
		//tt->ftLastAccessTime = 123445;
		//jsSetAt(es, val, 0, jsObject(es, tt));
		//jsSetAt(es, val, 0, jsInt(12344));
		jsCall(es, jsCallback, jsUndefined(), &val, 1);
	}
	else
	{
		base::Closure task = base::Bind(&MainWnd::fileSearcherResultCallback,
			this->AsWeakPtr(),jsCallback, std::move(list));
		MSGPOSTTASK_C(FROM_HERE, ThreadKind::UI, std::move(task));
	}
}
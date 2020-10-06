#include "FileSearcherThread.h"
#include <base/bind.h>
#include "MsgThreadManager.h"


FileSearcherThread::FileSearcherThread()
	: base::Thread("FileSearcherThread")
	, file_searcher_(nullptr)
{

}


void FileSearcherThread::Init()
{
	file_searcher_ = std::make_unique<FileSearcher>();
}


void FileSearcherThread::DispatchTask(const tracked_objects::Location& from_here,
	const fileSearcherWorkId workId, const SearcherDataList& args,
	const base::Callback<void(const SearcherDataList&)>& callback)
{
	MsgThreadInfo &&info =  MsgThreadManager::GetInstance()->getThread(ThreadKind::FileSearcherThread);
	
	if (info.base && info.base->IsRunning())
	{
		auto pWeakThread = info.real.AnyCast<base::WeakPtr<FileSearcherThread>>();
		auto p = pWeakThread.get();
		if (p)
		{
			p->DoWork1(workId, args, callback);
		}
	}

	
}

void FileSearcherThread::DoWork1(const fileSearcherWorkId workId, const SearcherDataList& args,
	const base::Callback<void(const SearcherDataList&)>& callback)
{
	std::vector<base::Any> result;
	if (fileSearcherWorkId::eNumOneFolder == workId)
	{
		if (args.size() > 0)
		{
			auto args0 = args.at(0);
			std::wstring strPath = args0.AnyCast<std::wstring>();

			std::vector<pFileAttribute> fileList;
			file_searcher_->findPath(strPath.c_str(), fileList);

			for (auto it = fileList.begin(); it != fileList.end(); it ++ )
			{
				base::Any a = *it;
				result.emplace_back(a);
			}
		}
		
	}
	else
	{
	}
	callback.Run(std::move(result));
}


void FileSearcherThread::DoWork2(const fileSearcherWorkId workId, SearcherDataList args,
	std::function<void(const SearcherDataList &)> callback)
{
	std::vector<base::Any> result;
	if (fileSearcherWorkId::eNumOneFolder == workId)
	{
		
		//**************************  测试代码
		base::Any ddd = args.at(0);
		int  dsdf = ddd.AnyCast<int>();
		//
		std::wstring zzz = args.at(1).AnyCast<std::wstring>();
		//**************************

		int m = 0;
	}
	else
	{
	}
	result.push_back(std::string("luo"));
	result.push_back(std::string("成了亿万富翁"));

	callback(std::move(result));
}
#include "FileSearcherThread.h"
#include "base/bind.h"



FileSearcherThread::FileSearcherThread()
	: base::Thread("FileSearcherThread")
	, file_searcher_(nullptr)
{

}


void FileSearcherThread::Init()
{
	file_searcher_ = std::make_unique<FileSearcher>();
}


void FileSearcherThread::DoWork1(const fileSearcherWorkId workId, SearcherDataList args,
	base::Callback<void(SearcherDataList&&)> callback)
{
	std::vector<base::Any> result;
	if (fileSearcherWorkId::eNumOneFolder == workId)
	{
		int m = 0;
		//file_searcher_->findPath(std::forward<Args>(args) ...);

	}
	else
	{
	}
	callback.Run(std::move(result));
}


void FileSearcherThread::DoWork2(const fileSearcherWorkId workId, SearcherDataList args,
	std::function<void(SearcherDataList &&)> callback)
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
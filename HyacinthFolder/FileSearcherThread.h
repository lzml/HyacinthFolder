#pragma once
#include "FileSearcher.h"
#include <base/memory/weak_ptr.h>
#include <base/threading/thread.h>
#include <memory>
#include <functional>
#include <vector>
#include "FileAttribute.h"
#include "Any.hpp"


enum class fileSearcherWorkId
{
	eNumOneFolder,	//枚举一个目录
};


class FileSearcherThread : public base::Thread
	,public base::SupportsWeakPtr<FileSearcherThread>
{
public:
	using SearcherDataList = std::vector<base::Any> ;
//	using pSearcherDataList = std::unique_ptr<SearcherDataList>;
public:
	explicit FileSearcherThread();
	virtual ~FileSearcherThread() {}

public:
	void Init() final;

	//DoWork1 不支持绑定lambda 表达式
	//DoWOrk2 不建议绑定类成员函数，大部分时候应该使用DoWork1,DoWork2基本只使用在lambda上

	void DoWork1(const fileSearcherWorkId workId, SearcherDataList args,
		 base::Callback<void(SearcherDataList && )>  callback  );

	void DoWork2(const fileSearcherWorkId workId, SearcherDataList args,
		 std::function<void(SearcherDataList &&)>  callback );

	
private:



private:
	//全部其他线程
	std::unique_ptr<FileSearcher> file_searcher_;
};


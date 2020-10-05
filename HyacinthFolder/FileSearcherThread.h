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
	eNumOneFolder,	//ö��һ��Ŀ¼
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

	//DoWork1 ��֧�ְ�lambda ���ʽ
	//DoWOrk2 ����������Ա�������󲿷�ʱ��Ӧ��ʹ��DoWork1,DoWork2����ֻʹ����lambda��

	void DoWork1(const fileSearcherWorkId workId, SearcherDataList args,
		 base::Callback<void(SearcherDataList && )>  callback  );

	void DoWork2(const fileSearcherWorkId workId, SearcherDataList args,
		 std::function<void(SearcherDataList &&)>  callback );

	
private:



private:
	//ȫ�������߳�
	std::unique_ptr<FileSearcher> file_searcher_;
};


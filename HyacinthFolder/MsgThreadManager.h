#pragma once
#include <base/threading/thread.h>
#include <base/memory/weak_ptr.h>
#include <base/message_loop/message_loop.h>
#include <map>
#include <base/callback_forward.h>

/**
	专门管理与整个程序生命期相同的线程
 */

enum class ThreadKind {
	UI,
	FileSearcherThread,
};


class MsgThreadManager
{
public: 
	explicit MsgThreadManager();
	~MsgThreadManager();

	static MsgThreadManager* GetInstance();

	void addUiThead(base::WeakPtr<base::MessageLoop> loop);
	void addOtherThread(ThreadKind id, base::WeakPtr<base::Thread> thread);


	void postTask(ThreadKind id, const tracked_objects::Location& from_here,
		const base::Closure& task);
private:
	base::WeakPtr<base::MessageLoop> uiLoop_;
	std::map<ThreadKind, base::WeakPtr<base::Thread>>  thread_list_;
};


void MSGPOSTTASK(ThreadKind id, const tracked_objects::Location& from_here,
	const base::Closure& task);
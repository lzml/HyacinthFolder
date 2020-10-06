#pragma once
#include <base/threading/thread.h>
#include <base/memory/weak_ptr.h>
#include <base/message_loop/message_loop.h>
#include <map>
#include <base/callback_forward.h>
#include "Any.hpp"
#include <typeindex>

/**
	专门管理与整个程序生命期相同的线程
 */

enum class ThreadKind {
	UI,
	FileSearcherThread,
};

struct MsgThreadInfo
{
	base::WeakPtr<base::Thread> base;  //基类指针
	base::Any	real; //原始弱指针
};


class MsgThreadManager
{
public: 
	explicit MsgThreadManager();
	~MsgThreadManager();

	static MsgThreadManager* GetInstance();

	void addUiThead(base::WeakPtr<base::MessageLoop> loop);
	//void addOtherThread(ThreadKind id, base::WeakPtr<base::Thread> thread);
	void addOtherThread(ThreadKind id, MsgThreadInfo thread);
	void addOtherThread(ThreadKind id, base::WeakPtr<base::Thread> pBase, base::Any pReal);

	MsgThreadInfo getThread(ThreadKind id);
	DWORD getUIthreadHandle() { return uiThreadId_; }

	void postTask(ThreadKind id,  const tracked_objects::Location& from_here,
		const base::Closure& task);
private:
	base::WeakPtr<base::MessageLoop> uiLoop_;
	DWORD uiThreadId_;
	//std::map<ThreadKind, base::WeakPtr<base::Thread>>  thread_list_;
	std::map<ThreadKind, MsgThreadInfo >  thread_list_;
};


void MSGPOSTTASK_C(const tracked_objects::Location& from_here, 
	ThreadKind id,  base::Closure&& task);

// threadClassType		base::thread的派生类类型
// Functor				threadClassType的成员函数
// Args					Functor成员函数的参数
// id					thraedClassType的ThreadKind编号
//template <typename Functor, typename... Args>
//void MSGPOSTTASK_CT(std::type_index threadClassType,ThreadKind id,
//	const tracked_objects::Location& from_here,
//	Functor functor, Args&&... args);

void MSGPOSTTASK(ThreadKind id, const tracked_objects::Location& from_here,
	std::function<void(void)> func);


#define  GETMsgThreadManager MsgThreadManager::GetInstance






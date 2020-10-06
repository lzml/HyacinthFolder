#include "MsgThreadManager.h"
#include <base/memory/singleton.h>
#include <base/bind.h>






MsgThreadManager::MsgThreadManager()
	:uiThreadId_(0)
{

}

MsgThreadManager::~MsgThreadManager()
{

}

MsgThreadManager* MsgThreadManager::GetInstance()
{
	return base::Singleton<MsgThreadManager,
		base::StaticMemorySingletonTraits<MsgThreadManager>>::get();
}


void MsgThreadManager::addUiThead(base::WeakPtr<base::MessageLoop> loop)
{
	uiLoop_ = loop;
	uiThreadId_ = ::GetCurrentThreadId();
}


//void MsgThreadManager::addOtherThread(ThreadKind id, base::WeakPtr<base::Thread> thread)
//{
//	
//	thread_list_.emplace(std::make_pair(id, thread));
//
//}
void MsgThreadManager::addOtherThread(ThreadKind id, MsgThreadInfo thread)
{

	thread_list_.emplace(std::make_pair(id, thread));

}

void MsgThreadManager::addOtherThread(ThreadKind id, base::WeakPtr<base::Thread> pBase, base::Any pReal)
{
	MsgThreadInfo thread;
	thread.base = pBase;
	thread.real = std::move(pReal);

	thread_list_.emplace(std::make_pair(id, thread));
}

void MsgThreadManager::postTask(ThreadKind id, 
	const tracked_objects::Location& from_here,
	const base::Closure& task)
{
	if (id == ThreadKind::UI)
	{
		auto p = uiLoop_.get();
		if (p)
		{
			p->PostTask(from_here, task);
			return;
		} 
	}
	else
	{
		MsgThreadInfo anyThread = thread_list_.at(id);
		auto p = anyThread.base;
		if (p && p->IsRunning())
		{
			p->task_runner()->PostTask(from_here, task);
			return;
		}
	}
}

MsgThreadInfo MsgThreadManager::getThread(ThreadKind id)
{
	if (ThreadKind::UI != id)
	{
		return thread_list_.at(id);
	}
	else if (ThreadKind::UI == id)
	{


	}


	MsgThreadInfo info;
	info.base = nullptr;
	return std::move(info);
}


void MSGPOSTTASK_C(const tracked_objects::Location& from_here,
	ThreadKind id,  base::Closure&& task)
{
	MsgThreadManager::GetInstance()->postTask(id, from_here, std::move(task));
}

//template <  typename Functor, typename... Args>
//void MSGPOSTTASK_CT(std::type_index threadClassType,ThreadKind id, 
//	const tracked_objects::Location& from_here,
//	Functor functor, Args&&... args)
//{
//	base::Any threadAny = MsgThreadManager::GetInstance()->getThread(id);
//	base::WeakPtr<threadClassType> pThread = threadAny.AnyCast<threadClassType>();
//	auto closu = base::Bind(std::forward<Functor>(functor), pThread,std::forward<Args>(args) ...);
//
//	MsgThreadManager::GetInstance()->postTask(id, from_here, std::move(closu));
//}


void FunctionToClosure(const std::function<void(void)>& func)
{
	func();
}

void MSGPOSTTASK(ThreadKind id, const tracked_objects::Location& from_here,
	std::function<void(void)> func)
{
	base::Closure closu = base::Bind(&FunctionToClosure, std::move(func));
	MsgThreadManager::GetInstance()->postTask(id, from_here, std::move(closu));
}
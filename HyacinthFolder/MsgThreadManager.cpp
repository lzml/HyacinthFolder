#include "MsgThreadManager.h"
#include <base/memory/singleton.h>
#include <base/bind.h>

MsgThreadManager::MsgThreadManager()
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
}


void MsgThreadManager::addOtherThread(ThreadKind id, base::WeakPtr<base::Thread> thread)
{
	
	thread_list_.emplace(std::make_pair(id, thread));

}

void MsgThreadManager::postTask(ThreadKind id, const tracked_objects::Location& from_here,
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
		auto p = thread_list_.at(id).get();
		if (p && p->IsRunning())
		{
			p->task_runner()->PostTask(from_here, task);
			return;
		}
	}
}


void MSGPOSTTASK(ThreadKind id, const tracked_objects::Location& from_here,
	const base::Closure& task)
{
	MsgThreadManager::GetInstance()->postTask(id, from_here, task);
}

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
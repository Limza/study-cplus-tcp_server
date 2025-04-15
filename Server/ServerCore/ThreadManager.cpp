#include "pch.h"
#include "ThreadManager.h"
#include "CoreTls.h"
#include "CoreGlobal.h"

using namespace std;

ThreadManager::ThreadManager()
{
	InitTls();
}

ThreadManager::~ThreadManager()
{
	Join();
}

void ThreadManager::Launch(const std::function<void()>& callback)
{
	LockGuard guard(_lock);

	_threads.emplace_back([callback]()
		{
			InitTls();
			callback();
			DestroyTls();
		});
}

void ThreadManager::Join()
{
	for (thread& t : _threads)
	{
		if (t.joinable())
		{
			t.join();
		}
	}
	_threads.clear();
}

void ThreadManager::InitTls()
{
	static Atomic<uint32> sThreadId{1};
	LThreadId = sThreadId.fetch_add(1);
}

void ThreadManager::DestroyTls()
{

}

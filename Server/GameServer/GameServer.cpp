﻿#include "pch.h"

#include "ThreadManager.h"
#include "Service.h"
#include "GameSession.h"

using namespace std;

int main()
{
	const ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777)
		, MakeShared<IocpCore>()
		, MakeShared<GameSession>,
		100);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 5; ++i)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}
	GThreadManager->Join();
}

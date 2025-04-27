﻿#include "pch.h"

#include "ThreadManager.h"
#include "Service.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ServerPacketHandler.h"
#include <tchar.h>
#include "Protocol.pb.h"

using namespace std;

class Player
{
public:
	int32 hp = 0;
	int32 attack = 0;
	Player* target = nullptr;
	vector<int32> buffs;
};

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

	WCHAR sendData3[1000] = L"가";

	while (true)
	{
		Protocol::S_TEST pkt;
		pkt.set_id(1000);
		pkt.set_hp(100);
		pkt.set_attack(10);

		{
			Protocol::BuffData* data = pkt.add_buffs();
			data->set_buffid(100);
			data->set_remaintime(1.2f);
			data->add_victims(4000);
		}
		{
			Protocol::BuffData* data = pkt.add_buffs();
			data->set_buffid(200);
			data->set_remaintime(2.5f);
			data->add_victims(1000);
			data->add_victims(2000);
		}

		SendBufferRef sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);

		GSessionManager.Broadcast(sendBuffer);

		this_thread::sleep_for(1s);
	}

	GThreadManager->Join();
}

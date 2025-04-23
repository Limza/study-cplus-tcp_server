#include "pch.h"

#include "ThreadManager.h"
#include "Service.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "BufferWriter.h"
#include "ServerPacketHandler.h"
#include <tchar.h>

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

	char sendData1[1000] = "가";
	char sendData2[1000] = u8"가";
	WCHAR sendData3[1000] = L"가";
	TCHAR sendData4[1000] = _T("가");

	while (true)
	{
		const std::vector<BuffData> buffs{
			{.buffId = 100, .remainTime = 1.5f },
			{.buffId = 200, .remainTime = 2.3f },
			{.buffId = 300, .remainTime = 0.7f },
		};
		const SendBufferRef sendBuffer =
			ServerPacketHandler::Make_S_TEST(1001, 100, 10
				, buffs, L"안녕하세요");

		GSessionManager.Broadcast(sendBuffer);

		this_thread::sleep_for(1s);
	}

	GThreadManager->Join();
}

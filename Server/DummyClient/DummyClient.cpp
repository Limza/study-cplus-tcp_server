#include "pch.h"
#include "Session.h"

#include <chrono>

#include "Service.h"
#include "ThreadManager.h"

using namespace std;

char sendData[] = "Hello World";

class ServerSession final : public Session
{
public:
	~ServerSession() override
	{
		cout << "ServerSession Destructor\n";
	}

protected:
	void OnConnected() override
	{
		cout << "Connected To Server" << '\n';

		const SendBufferRef sendBuffer = GSendBufferManager->Open(4096);
		::memcpy(sendBuffer->Buffer(), sendData, sizeof(sendData));
		sendBuffer->Close(sizeof(sendData));

		Send(sendBuffer);
	}

	void OnDisconnected() override
	{
		cout << "Disconnected\n";
	}

	int32 OnRecv(BYTE* buffer, const int32 len) override
	{
		// Echo
		cout << "OnRecv Len = " << len << '\n';

		this_thread::sleep_for(1s);

		const SendBufferRef sendBuffer = GSendBufferManager->Open(4096);
		::memcpy(sendBuffer->Buffer(), sendData, sizeof(sendData));
		sendBuffer->Close(sizeof(sendData));

		Send(sendBuffer);

		return len;
	}

	void OnSend(const int32 len) override
	{
		cout << "OnSend Len = " << len << '\n';
	}
};

int main()
{
	this_thread::sleep_for(1s);

	const ClientServiceRef service = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 7777)
		, MakeShared<IocpCore>()
		, MakeShared<ServerSession>,
		5);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 2; ++i)
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

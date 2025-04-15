#pragma once
#include "Session.h"

class GameSession final : public Session
{
public:
	~GameSession() override
	{
		std::cout << "GameSession Destructor\n";
	}
protected:
	void OnConnected() override;
	void OnDisconnected() override;
	int32 OnRecv(BYTE* buffer, const int32 len) override;
	void OnSend(const int32 len) override;
};


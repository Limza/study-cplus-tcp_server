#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"

void GameSession::OnConnected()
{
	GSessionManager.Add(
		std::static_pointer_cast<GameSession>(shared_from_this())
	);
}

void GameSession::OnDisconnected()
{
	GSessionManager.Remove(
		std::static_pointer_cast<GameSession>(shared_from_this())
	);
}

int32 GameSession::OnRecv(BYTE* buffer, const int32 len)
{
	// Echo
	std::cout << "OnRecv Len = " << len << '\n';

	const SendBufferRef sendBuffer = GSendBufferManager->Open(4096);
	::memcpy(sendBuffer->Buffer(), buffer, len);
	sendBuffer->Close(len);

	GSessionManager.Broadcast(sendBuffer);

	return len;
}

void GameSession::OnSend(const int32 len)
{
	std::cout << "OnSend Len = " << len << '\n';
}
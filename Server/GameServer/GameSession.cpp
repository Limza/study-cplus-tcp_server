#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ServerPacketHandler.h"

using namespace std;

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

void GameSession::OnRecvPacket(BYTE* buffer, const int32 len)
{
	ServerPacketHandler::HandlePacket(buffer, len);
}

void GameSession::OnSend(const int32 len)
{
}
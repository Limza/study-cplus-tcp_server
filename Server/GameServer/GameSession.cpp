#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"

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
	auto session = GetPacketSessionRef();

	// TODO : packetId 대역 체크
	ClientPacketHandler::HandlePacket(session, buffer, len);
}

void GameSession::OnSend(const int32 len)
{
}
#include "pch.h"
#include "Room.h"
#include <ranges>
#include "GameSession.h"
#include "Player.h"

Room GRoom;

void Room::Enter(PlayerRef player)
{
	WRITE_LOCK;
	_players[player->playerId] = player;
}

void Room::Leave(PlayerRef player)
{
	WRITE_LOCK;
	_players.erase(player->playerId);
}

void Room::Broadcast(SendBufferRef sendBuffer)
{
	WRITE_LOCK;
	for (const PlayerRef& player : _players | std::views::values)
	{
		player->ownerSession->Send(sendBuffer);
	}
}

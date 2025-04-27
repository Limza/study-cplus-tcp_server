#include "pch.h"
#include "ServerPacketHandler.h"

#include "BufferReader.h"
#include "BufferWriter.h"

using namespace std;

void ServerPacketHandler::HandlePacket(BYTE* buffer, const int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br.Peek(&header);

	switch (header.id)
	{
	default:
		break;
	}
}

SendBufferRef ServerPacketHandler::MakeSendBuffer(const Protocol::S_TEST& pkt)
{
	return _MakeSendBuffer(pkt, S_TEST);
}

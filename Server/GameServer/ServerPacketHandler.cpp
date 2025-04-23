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

SendBufferRef ServerPacketHandler::Make_S_TEST(uint64 id, uint32 hp, uint16 attack
	, std::vector<BuffData> buffs, wstring name)
{
	const SendBufferRef sendBuffer = GSendBufferManager->Open(4096);

	BufferWriter bw(sendBuffer->Buffer(), sendBuffer->AllocSize());
	PacketHeader* header = bw.Reserve<PacketHeader>();

	// id, 체력, 공격력,
	bw << id << hp << attack;

	// 가변 데이터
	bw << static_cast<uint16>(buffs.size());
	for (auto& [buffId, remainTime] : buffs)
	{
		bw << buffId << remainTime;
	}

	bw << static_cast<uint16>(name.size());
	bw.Write((void*)name.data(), name.size() * sizeof(WCHAR));

	header->size = bw.WriteSize();
	header->id = S_TEST; // 1 : Hello Msg

	sendBuffer->Close(bw.WriteSize());

	return sendBuffer;
}

#include "pch.h"
#include "ClientPacketHandler.h"

#include "BufferReader.h"

using namespace std;

void ClientPacketHandler::HandlePacket(BYTE* buffer, const int32 len)
{
	BufferReader br(buffer, len);
	PacketHeader header;
	br >> header;

	switch (header.id)
	{
	case S_TEST:
		Handle_S_TEST(buffer, len);
		break;
	}
}

struct BuffData
{
	uint64 buffId;
	float remainTime;
};

struct S_TEST
{
	uint64 id;
	uint32 hp;
	uint16 attack;
	std::vector<BuffData> buffs;
	wstring name;
};

void ClientPacketHandler::Handle_S_TEST(BYTE* buffer, const int32 len)
{
	BufferReader br(buffer, len);
	PacketHeader header;
	br >> header;

	uint64 id;
	uint32 hp;
	uint16 attack;
	br >> id >> hp >> attack;

	std::cout << "ID : " << id << "HP : " << hp << "ATT : " << attack << '\n';

	std::vector<BuffData> buffs;
	uint16 buffCount;
	br >> buffCount;
	buffs.resize(buffCount);
	for (int32 i = 0; i < buffCount; ++i)
	{
		br >> buffs[i].buffId >> buffs[i].remainTime;
	}

	std::cout << "Buff Count : " << buffCount << '\n';
	for (int32 i = 0; i < buffCount; ++i)
	{
		std::cout << "BuffInfo : " << buffs[i].buffId << " " << buffs[i].remainTime << '\n';
	}

	wstring name;
	uint16 nameLen;
	br >> nameLen;
	name.resize(nameLen);

	br.Read((void*)name.data(), nameLen * sizeof(WCHAR));

	wcout.imbue(std::locale("kor"));
	wcout << name << endl;
}

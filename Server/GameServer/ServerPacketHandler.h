#pragma once

enum : uint8
{
	S_TEST = 1
};

struct BuffData
{
	uint64 buffId;
	float remainTime;
};

class ServerPacketHandler
{
public:
	static void HandlePacket(BYTE* buffer, const int32 len);

	static SendBufferRef Make_S_TEST(uint64 id, uint32 hp, uint16 attack
		, std::vector<BuffData> buffs, std::wstring name);
};


#pragma once

enum : uint8
{
	S_TEST = 1,
};

class ClientPacketHandler
{
public:
	static void HandlePacket(BYTE* buffer,  const int32 len);

	static void Handle_S_TEST(const BYTE* buffer, const int32 len);
};


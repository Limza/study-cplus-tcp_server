#include "pch.h"
#include "ClientPacketHandler.h"

#include "BufferReader.h"
#include "Protocol.pb.h"

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

void ClientPacketHandler::Handle_S_TEST(const BYTE* buffer, const int32 len)
{
	Protocol::S_TEST pkt;

	ASSERT_CRASH(pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)));

	cout << pkt.id() << " " << pkt.hp() << " " << pkt.attack() << endl;

	cout << "BUFSIZE : " << pkt.buffs_size() << endl;

	for (auto& buf : pkt.buffs())
	{
		cout << "BUFFID : " << buf.buffid() << " REMAINTIME : " << buf.remaintime() << endl;
		cout << "VICTIM SIZE : " << buf.victims_size() << endl;
		for (auto& victim : buf.victims())
		{
			cout << "VICTIM : " << victim << endl;
		}

		cout << endl;
	}
}

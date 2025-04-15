#include "pch.h"
#include "SendBuffer.h"

/* --------------------------------
 * SendBuffer
 --------------------------------*/

SendBuffer::SendBuffer(const int32 bufferSize)
{
	_buffer.resize(bufferSize);
}

void SendBuffer::CopyData(const void* data, const int32 len)
{
	ASSERT_CRASH(Capacity() >= len);
	::memcpy(_buffer.data(), data, len);
	_writeSize = len;
}


/* --------------------------------------
 *	SendBufferManager
 -------------------------------------- */

SendBufferRef SendBufferManager::Open(uint32 size)
{
}

SendBufferChunkRef SendBufferManager::Pop()
{
	{
		WRITE_LOCK;
		if (_sendBufferChunks.empty() == false)
		{
			auto sendBufferChunk = _sendBufferChunks.back();
			_sendBufferChunks.pop_back();
			return sendBufferChunk;
		}
	}

	return {xnew<SendBufferChunk>(), PushGlobal};
}

void SendBufferManager::Push(SendBufferChunkRef buffer)
{
	WRITE_LOCK;
	_sendBufferChunks.push_back(buffer);
}

void SendBufferManager::PushGlobal(SendBufferChunk* buffer)
{
	GSendBufferManager->Push(SendBufferChunkRef(buffer, PushGlobal));
}

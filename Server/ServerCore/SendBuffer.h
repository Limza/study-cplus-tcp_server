#pragma once
#include "CoreMacro.h"

/* --------------------------------
 * SendBuffer
 --------------------------------*/
class SendBuffer : std::enable_shared_from_this<SendBuffer>
{
public:
	explicit SendBuffer(int32 bufferSize);
	~SendBuffer() = default;
	NON_COPYABLE_CLASS(SendBuffer);

public:
	BYTE* Buffer() { return _buffer.data(); }

	[[nodiscard]] int32 WriteSize() const { return _writeSize; }
	[[nodiscard]] int32 Capacity() const { return static_cast<int32>(_buffer.size()); }

	void CopyData(const void* data, int32 len);

private:
	Vector<BYTE>	_buffer;
	int32			_writeSize = 0;
};


/* --------------------------------------
 *	SendBufferChunk
 -------------------------------------- */
class SendBufferChunk
{
	
};


 /* --------------------------------------
  *	SendBufferManager
  -------------------------------------- */
class SendBufferManager
{
public:
	SendBufferRef		Open(uint32 size);

private:
	SendBufferChunkRef	Pop();
	void				Push(SendBufferChunkRef buffer);

	static void			PushGlobal(SendBufferChunk* buffer);

private:
	USE_LOCK;
	Vector<SendBufferChunkRef> _sendBufferChunks;
};
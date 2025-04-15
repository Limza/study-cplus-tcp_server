#pragma once
#include <stack>

extern thread_local uint32				LThreadId;

// 데드락 프로파일러에서 사용, 쓰레드마다 잡고 있는 락을 추적
extern thread_local std::stack<int32>	LLockStack;

extern thread_local SendBufferChunkRef	LSendBufferChunk;
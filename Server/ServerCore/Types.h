#pragma once

#include <cstdint>
#include <atomic>
#include <mutex>

// ReSharper disable CppInconsistentNaming
using byte = unsigned char;
using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;
using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

// ReSharper enable CppInconsistentNaming

template<typename T>
using Atomic		= std::atomic<T>;
using Mutex			= std::mutex;
using CondVar		= std::condition_variable;
using UniqueLock	= std::unique_lock<Mutex>;
using LockGuard		= std::lock_guard<Mutex>;

// shared ptr
using IocpCoreRef			= std::shared_ptr<class IocpCore>;
using IocpObjectRef			= std::shared_ptr<class IocpObject>;
using SessionRef			= std::shared_ptr<class Session>;
using ListenerRef			= std::shared_ptr<class Listener>;
using ServerServiceRef		= std::shared_ptr<class ServerService>;
using ClientServiceRef		= std::shared_ptr<class ClientService>;
using SendBufferRef			= std::shared_ptr<class SendBuffer>;
using SendBufferChunkRef	= std::shared_ptr<class SendBufferChunk>;

#define size16(val) static_cast<int16>(sizeof(val))
#define size32(val) static_cast<int32>(sizeof(val))
#define len16(arr)	static_cast<int16>(sizeof(arr) / sizeof((arr)[0]))
#define len32(arr)	static_cast<int32>(sizeof(arr) / sizeof((arr)[0]))

#define _STOMP
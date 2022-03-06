////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Telemetry Event Queue
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Container/SFCircularBufferQueue.h"
#include "IO/SFFile.h"


namespace SF
{

	//////////////////////////////////////////////////////////////////////////////////////////
	//
	//	TelemetryEventQueue
	//
	//              File      Data    Posting                                  File      Filled     Allocation
	//              Tail      Tail     Tail                                    Head       Head        Head
	//    -------------------------------------------------------------------------------------------------------------------------
	//                |         |        |                                        |          |           |                        
	//    -------------------------------------------------------------------------------------------------------------------------
	//    
	//

	class TelemetryEventQueue
	{
	public:

		static constexpr const char* BaseStorageFilePath = "TelemetryEvent.cache";

		static constexpr uint32_t FileSignature = "TelemetryEvent"_crc;
		static constexpr uint32_t FileVersion = 1;
		static constexpr uint32_t EventStorageSize = 1024 * 1024;

	#pragma pack(push,4)
		// Event cache file header
		struct EventFileHeader
		{
			uint32_t FileSignature = FileSignature;
			uint32_t FileVersion = FileVersion;
			int32_t Head = 0;
			int32_t Tail = 0;
		};
	#pragma pack(pop)

		using EventItem = CircularBufferQueue::BufferItem;

	public:

		// Constructor
		TelemetryEventQueue(IHeap& heap);
		virtual ~TelemetryEventQueue();

		// Initialize
		void Initialize();

		// Test whether it is empty
		bool IsEmpty();

		// read lock for manual control
		CriticalSection& GetReadLock() { return m_ReadLock; }


		//////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Event handling
		//

		// Enqueue
		bool EnqueueEvent(const Array<uint8_t>& eventData);

		// Get tail segment
		bool GetTailEvent(EventItem*& eventItem);

		// Get Next segment
		bool GetNextEvent(EventItem*& eventItem);

		// Free up to last accessed
		bool FreePostedEvents();



		//////////////////////////////////////////////////////////////////////////////////////////
		//
		//	File operations
		//

		// Save Delta
		void SaveDelta();

		// Load full memory space
		bool LoadFromFileStorage();

	private:

		void CreateStorageFile();
		void OpenStorageForWrite();

		bool WriteDataSection(int Start, int DataSize);

	private:

		// writ lock
		CriticalSection m_WriteLock;

		// Read lock
		CriticalSection m_ReadLock;

		// Posting tail
		Atomic<EventItem*> m_PostingTailPtr;

		// Event buffer
		uint8_t m_EventBuffer[EventStorageSize];
		CircularBufferQueue m_EventBufferQueue;

		// Event cache file header
		EventFileHeader m_StorageFileHeader{};

		String m_StorageFilePath;

		// File path to local storage
		File m_StorageFile;

	};

}

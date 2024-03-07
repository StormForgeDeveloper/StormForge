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

		static constexpr uint32_t FILE_SIGNATURE = "TelemetryEvent"_crc;
		static constexpr uint32_t FILE_VERSION = 1;
		static constexpr uint32_t EventStorageSize = 1024 * 1024;

	#pragma pack(push,4)
		// Event cache file header
		struct EventFileHeader
		{
			uint32_t FileSignature = FILE_SIGNATURE;
			uint32_t FileVersion = FILE_VERSION;
			int32_t Head = 0;
			int32_t Tail = 0;
		};
	#pragma pack(pop)

        using EventItem = CircularBufferQueue::BufferItem;
        using EventItemReadPtr = CircularBufferQueue::ItemReadPtr;
        using EventItemWritePtr = CircularBufferQueue::ItemWritePtr;

	public:

		// Constructor
		TelemetryEventQueue(IHeap& heap);
		virtual ~TelemetryEventQueue();

		// Initialize
		void Initialize(bool bUseFileCache);

		// Test whether it is empty
		bool IsEmpty();

		// read lock for manual control
		CriticalSection& GetReadLock() { return m_ReadLock; }


		//////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Event handling
		//

		// Enqueue
		bool EnqueueEvent(uint32_t eventId, const Array<const uint8_t>& eventDataBuffer);

		// Get tail segment
		EventItem* GetTailEvent();

		// Get Next segment
		EventItem* GetNextEvent(EventItem* eventItem);

		// Free up to last accessed
		bool FreePostedEvents(uint32_t eventId);



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
		//CriticalSection m_WriteLock;

		// Read lock
		CriticalSection m_ReadLock;

		// Event buffer
		CircularBufferQueue m_EventBufferQueue;

		// Event cache file header
		EventFileHeader m_StorageFileHeader{};

		String m_StorageFilePath;

		// File path to local storage
		File m_StorageFile;

        bool m_bUseFileCache = true;
	};

}

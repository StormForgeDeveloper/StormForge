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


#include "SFCorePCH.h"

#include "Online/Telemetry/SFTelemetryEventQueue.h"
#include "Online/Telemetry/SFTelemetryBR.h"
#include "IO/SFFileUtil.h"
#include "Util/SFPath.h"


namespace SF
{


	////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Implementations
	//
	TelemetryEventQueue::TelemetryEventQueue(IHeap& heap)
		: m_EventBufferQueue(heap)
	{
	}

	TelemetryEventQueue::~TelemetryEventQueue()
	{
		m_StorageFile.Close();
	}

	void TelemetryEventQueue::Initialize(bool bUseFileCache)
	{
        m_bUseFileCache = bUseFileCache;
		m_StorageFilePath = Util::Path::Combine(Util::Path::GetSaveDir(), BaseStorageFilePath);

		// No file cache for editor or tool mode
        if (m_bUseFileCache)
        {
            if (!LoadFromFileStorage())
                CreateStorageFile();
            else
                OpenStorageForWrite();
        }
	}

	bool TelemetryEventQueue::IsEmpty()
	{
		return m_EventBufferQueue.IsEmpty();
	}

	bool TelemetryEventQueue::EnqueueEvent(uint32_t eventId, const Array<const uint8_t>& eventDataBuffer)
	{
        if (eventDataBuffer.size() == 0)
            return false;

		//MutexScopeLock ScopeLock(m_WriteLock);

		auto allocationSize = eventDataBuffer.size() + sizeof(uint32_t);

        EventItemWritePtr newItemPtr = m_EventBufferQueue.AllocateWrite(allocationSize);
		for (;!newItemPtr; newItemPtr = m_EventBufferQueue.AllocateWrite(allocationSize))
		{
			// drop old item first
			MutexScopeLock ScopeReadLock(m_ReadLock);

			// Free up existing segment if we don't have enough space for the new one
            EventItemReadPtr itemPtr = m_EventBufferQueue.DequeueRead();
			if (!itemPtr)
			{
				SFLog(Telemetry, Error, "TelemetryEventQueue::EnqueueEvent, Failed to free item");
				return false;
			}
		}

        auto* pCurDataPtr = (uint8_t*)newItemPtr.data();
        memcpy(pCurDataPtr, &eventId, sizeof(eventId)); pCurDataPtr += sizeof(eventId);
        memcpy(pCurDataPtr, eventDataBuffer.data(), eventDataBuffer.size());

        newItemPtr.Reset();

		return true;
	}

	TelemetryEventQueue::EventItem* TelemetryEventQueue::GetTailEvent()
	{
		return m_EventBufferQueue.PeekTail();
	}

	TelemetryEventQueue::EventItem* TelemetryEventQueue::GetNextEvent(EventItem* eventItem)
	{
		return m_EventBufferQueue.PeekNext(eventItem);
	}

	bool TelemetryEventQueue::FreePostedEvents(uint32_t eventId)
	{
		{
			MutexScopeLock scopeLock(GetReadLock());

			EventItemReadPtr eventItem = m_EventBufferQueue.DequeueRead();
			for (; eventItem; eventItem = m_EventBufferQueue.DequeueRead())
			{
				auto curEventId = *(uint32_t*)eventItem.data();
				if (int32_t(curEventId - eventId) > 0)
				{
                    eventItem.CancelRead();
					break;
				}

                eventItem.Reset();
			}
		}

		SaveDelta();

		return true;
	}


	void TelemetryEventQueue::CreateStorageFile()
	{
		m_StorageFile.Close();

		if (FileUtil::IsFileExist(m_StorageFilePath))
			FileUtil::DeleteFile(m_StorageFilePath);

		m_StorageFile.Open(m_StorageFilePath, File::OpenMode::Create, File::SharingMode::Exclusive);
		if (!m_StorageFile.IsOpened())
		{
			SFLog(Telemetry, Error, "TelemetryEventQueue::CreateStorageFile, Failed to open file {0}", m_StorageFilePath);
			return;
		}

        m_StorageFileHeader = {};
		m_StorageFileHeader.Head = 0;
		m_StorageFileHeader.Tail = 0;


		// Reset the queue
		m_EventBufferQueue.Initialize(EventStorageSize);
		// being reset in Initialize
		//memset(m_EventBufferQueue.data(), 0, m_EventBufferQueue.size());


		size_t written{};
		auto hr = m_StorageFile.Write(reinterpret_cast<uint8_t*>(&m_StorageFileHeader), sizeof(m_StorageFileHeader), written);
		if (!hr)
		{
			SFLog(Telemetry, Error, "TelemetryEventQueue::CreateStorageFile, Failed to save header, file:{0}", m_StorageFilePath);
			m_StorageFile.Close();
			return;
		}

		hr = m_StorageFile.Write(m_EventBufferQueue.data(), m_EventBufferQueue.size(), written);
		if (!hr)
		{
			SFLog(Telemetry, Error, "TelemetryEventQueue::CreateStorageFile, Failed to save body, file:{0}", m_StorageFilePath);
			m_StorageFile.Close();
			return;
		}

		m_StorageFile.Flush();
	}

	void TelemetryEventQueue::OpenStorageForWrite()
	{
		m_StorageFile.Open(m_StorageFilePath, File::OpenMode::Append, File::SharingMode::Exclusive);
	}

	bool TelemetryEventQueue::WriteDataSection(int Start, int DataSize)
	{
		if (!m_StorageFile.IsOpened())
			return false;

		if (DataSize == 0)
			return true;

		size_t writenSize{};

		m_StorageFile.Seek(SeekMode::Begin, sizeof(m_StorageFileHeader) + Start);
		bool bRet = m_StorageFile.Write(m_EventBufferQueue.data() + Start, DataSize, writenSize);
		if (!bRet)
		{
			SFLog(Telemetry, Error, "TelemetryEventQueue::WriteDataSection, Failed, file:{0}", m_StorageFilePath);
		}

		return true;
	}

	void TelemetryEventQueue::SaveDelta()
	{
		if (!m_StorageFile.IsOpened())
			return;

		// We can't allow other operations during data save
		//MutexScopeLock ScopeWriteLock(m_WriteLock);
		MutexScopeLock ScopeReadLock(m_ReadLock);

		auto basePtr = intptr_t(m_EventBufferQueue.data());
		auto OldHead = m_StorageFileHeader.Head;
		auto OldTail = m_StorageFileHeader.Tail;

		auto NewHead = intptr_t(m_EventBufferQueue.GetHead()) - basePtr;
		auto NewTail = intptr_t(m_EventBufferQueue.GetTail()) - basePtr;


		if (NewHead >= OldHead)
		{
			WriteDataSection(OldHead, int(NewHead - OldHead));
		}
		else
		{
			WriteDataSection(OldHead, int(EventStorageSize - OldHead));
			WriteDataSection(0, int(NewHead));
		}

		// We are saving updated data section only, so header should be written after data section write.
		if (NewHead != OldHead || NewTail != OldTail)
		{
			m_StorageFileHeader.Head = (int)NewHead;
			m_StorageFileHeader.Tail = (int)NewTail;

			size_t writtern{};
			m_StorageFile.Seek(SeekMode::Begin, 0);
			bool bRet = m_StorageFile.Write(reinterpret_cast<uint8_t*>(&m_StorageFileHeader), sizeof(m_StorageFileHeader), writtern);
			if (!bRet)
			{
				SFLog(Telemetry, Error, "TelemetryEventQueue::WriteDataSection, Failed, file:{0}", m_StorageFilePath);
			}
		}
	}

	bool TelemetryEventQueue::LoadFromFileStorage()
	{
		FileUtil::CreatePath(m_StorageFilePath.data(), 1);
		m_StorageFile.Open(m_StorageFilePath, File::OpenMode::Read, File::SharingMode::Exclusive);
		if (!m_StorageFile.IsOpened())
		{
			// Might be access violation or first time. Cache files are ok to ignore those errors
			SFLog(Telemetry, Info, "TelemetryEventQueue: Failed to open cache file for read {0}.", m_StorageFilePath);
			return false;
		}

		if (m_StorageFile.GetFileSize() != (EventStorageSize + sizeof(EventFileHeader)))
		{
			// File buffer size might be changed
			SFLog(Telemetry, Info, "TelemetryEventQueue: Invalid cache file size read. resetting");

			return false;
		}

		size_t readSize{};
		bool ReadRes = m_StorageFile.Read(reinterpret_cast<uint8_t*>(&m_StorageFileHeader), sizeof(m_StorageFileHeader), readSize);
		if (!ReadRes)
		{
			SFLog(Telemetry, Error, "TelemetryEventQueue Failed to read cache file header {0}.", m_StorageFilePath);
			return false;
		}

		ReadRes = m_StorageFile.Read(m_EventBufferQueue.data(), m_EventBufferQueue.size(), readSize);
		if (!ReadRes)
		{
			SFLog(Telemetry, Error, "TelemetryEventQueue Failed to read cache file data {0}.", m_StorageFilePath);
			return false;
		}

		// Close the file again

		if (m_StorageFileHeader.FileSignature != FILE_SIGNATURE
			|| m_StorageFileHeader.FileVersion != FILE_VERSION)
		{
			SFLog(Telemetry, Error, "TelemetryEventQueue Failed to read cache file. invalid signature {0}.", m_StorageFilePath);
			return false;
		}

		if (!m_EventBufferQueue.ForceReset(m_StorageFileHeader.Head, m_StorageFileHeader.Tail))
			return false;

		return true;
	}

}

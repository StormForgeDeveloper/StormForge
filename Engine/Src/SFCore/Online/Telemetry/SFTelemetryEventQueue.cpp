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

	void TelemetryEventQueue::Initialize()
	{
		m_PostingTailPtr = nullptr;

		m_StorageFilePath = Util::Path::Combine(Util::Path::GetSaveDir(), BaseStorageFilePath);

		// No file cache for editor or tool mode
		if (!LoadFromFileStorage())
			CreateStorageFile();
		else
			OpenStorageForWrite();

	}

	bool TelemetryEventQueue::IsEmpty()
	{
		return m_EventBufferQueue.IsEmpty();
	}

	bool TelemetryEventQueue::EnqueueEvent(const Array<const uint8_t>& eventData)
	{
		MutexScopeLock ScopeLock(m_WriteLock);

		auto eventItem = m_EventBufferQueue.AllocateWrite(eventData.size());
		for (;!eventItem; eventItem = m_EventBufferQueue.AllocateWrite(eventData.size()))
		{
			// drop old item first
			MutexScopeLock ScopeReadLock(m_ReadLock);

			// Free up existing segment if we don't have enough space for the new one
			auto *pTail = m_EventBufferQueue.DequeueRead();
			if (!pTail)
			{
				SFLog(Telemetry, Error, "TelemetryEventQueue::EnqueueEvent, Failed to free item");
				return false;
			}

			m_EventBufferQueue.ReleaseRead(pTail);
		}

		memcpy(eventItem->GetDataPtr(), eventData.data(), eventData.size());

		return true;
	}

	bool TelemetryEventQueue::GetTailEvent(EventItem* &eventItem)
	{
		eventItem = m_EventBufferQueue.PeekTail();

		m_PostingTailPtr = eventItem;

		return eventItem != nullptr;
	}

	bool TelemetryEventQueue::GetNextEvent(EventItem*& eventItem)
	{
		eventItem = m_EventBufferQueue.PeekNext(eventItem);

		m_PostingTailPtr = eventItem;

		return eventItem != nullptr;
	}

	bool TelemetryEventQueue::FreePostedEvents()
	{
		// Posting should be done, we are safe to clean up the data
		auto postingTail = m_PostingTailPtr.exchange(nullptr);
		if (postingTail == nullptr)
			return true;

		m_EventBufferQueue.ForeachReadableItems([&](EventItem* pItem) 
			{
				return postingTail != pItem;
			});

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
		MutexScopeLock ScopeWriteLock(m_WriteLock);
		MutexScopeLock ScopeReadLock(m_ReadLock);

		auto OldHead = m_StorageFileHeader.Head;
		auto OldTail = m_StorageFileHeader.Tail;

		auto NewHead = (int)intptr_t(m_EventBufferQueue.GetHead());
		auto NewTail = (int)intptr_t(m_EventBufferQueue.GetTail());


		if (NewHead >= OldHead)
		{
			WriteDataSection(OldHead, NewHead - OldHead);
		}
		else
		{
			WriteDataSection(OldHead, EventStorageSize - OldHead);
			WriteDataSection(0, NewHead);
		}

		// We are saving updated data section only, so header should be written after data section write.
		if (NewHead != OldHead || NewTail != OldTail)
		{
			m_StorageFileHeader.Head = NewHead;
			m_StorageFileHeader.Tail = NewTail;

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
			SFLog(Telemetry, Error, "TelemetryEventQueue Failed to read cache file {0}.", m_StorageFilePath);
			return false;
		}

		ReadRes = m_StorageFile.Read(m_EventBufferQueue.data(), m_EventBufferQueue.size(), readSize);
		if (!ReadRes)
		{
			SFLog(Telemetry, Error, "TelemetryEventQueue Failed to read cache file {0}.", m_StorageFilePath);
			return false;
		}

		// Close the file again

		if (m_StorageFileHeader.FileSignature != FileSignature
			|| m_StorageFileHeader.FileVersion != FileVersion)
		{
			SFLog(Telemetry, Error, "TelemetryEventQueue Failed to read cache file {0}.", m_StorageFilePath);
			return false;
		}

		if (!m_EventBufferQueue.ForceReset(m_StorageFileHeader.Head, m_StorageFileHeader.Tail))
			return false;

		return true;
	}

}

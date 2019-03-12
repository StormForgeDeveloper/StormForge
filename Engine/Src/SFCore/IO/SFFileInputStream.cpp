////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : SFFileInputStream
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Variable/SFVariableBoxing.h"
#include "String/SFToString.h"
#include "IO/SFFileInputStream.h"



namespace SF {



	/////////////////////////////////////////////////////////////////////////////
	//
	//	FileInputStream
	//

	FileInputStream::FileInputStream()
	{

	}

	FileInputStream::FileInputStream(const char* filePath)
	{
		m_File.Open(filePath, File::OpenMode::Read);
	}

	Result FileInputStream::Open(const char* filePath)
	{
		return m_File.Open(filePath, File::OpenMode::Read);
	}

	Result FileInputStream::Close()
	{
		m_File.Close();
		return ResultCode::SUCCESS;
	}


	// return true if the stream is valid and have something read
	bool FileInputStream::CanRead()
	{
		return m_File.IsOpened();
	}

	// size of input
	size_t FileInputStream::GetSize() const
	{
		return m_File.GetFileSize();
	}

	size_t FileInputStream::GetPosition() const
	{
		return m_File.GetPosition();
	}

	size_t FileInputStream::Seek(SeekMode seekPos, int64_t offset)
	{
		m_File.Seek(seekPos, offset);
		return m_File.GetPosition();
	}

	// Read data
	Result FileInputStream::Read(void* buffer, size_t readSize)
	{
		size_t outReadSize;
		return m_File.Read((uint8_t*)buffer, readSize, outReadSize);
	}



}


////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : SFFileOutputStream
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "IO/SFFileOutputStream.h"




namespace SF {


	/////////////////////////////////////////////////////////////////////////////
	//
	//	OutputStream
	//


	FileOutputStream::FileOutputStream()
	{

	}

	FileOutputStream::FileOutputStream(const char* filePath)
	{
		m_File.Open(filePath, File::OpenMode::Create);
	}


	Result FileOutputStream::Open(const char* filePath)
	{
		return m_File.Open(filePath, File::OpenMode::Create);
	}

	Result FileOutputStream::Close()
	{
		m_File.Close();
		return ResultCode::SUCCESS;
	}

	// return true if the stream is valid and able to be written
	bool FileOutputStream::CanWrite()
	{
		return m_File.IsOpened();
	}

	// size of output
	size_t FileOutputStream::GetSize() const
	{
		return m_File.GetPosition();
	}

	// current write position
	size_t FileOutputStream::GetPosition() const
	{
		return m_File.GetPosition();
	}

	// Write data
	Result FileOutputStream::Write(const void* buffer, size_t writeSize)
	{
		size_t writen;
		return m_File.Write((const uint8_t*)buffer, writeSize, writen);
	}


}


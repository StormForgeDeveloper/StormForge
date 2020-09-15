////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : File
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Stream/SFStream.h"
#include "IO/SFFile.h"



namespace SF {



	/////////////////////////////////////////////////////////////////////////////
	//
	//	InputStream
	//

	class FileInputStream : public IInputStream
	{
	public:

		FileInputStream();
		FileInputStream(const char* filePath);

		Result Open(const char* filePath);
		Result Close();

		// return true if the stream is valid and have something read
		virtual bool CanRead() override;

		virtual Result Seek(SeekMode seekPos, int64_t offset) override;

		// size of input
		virtual size_t GetSize() const override;
		virtual size_t GetPosition() const override;

		// Read data
		virtual Result Read(void* buffer, size_t readSize) override;



	private:

		File m_File;

	};




}

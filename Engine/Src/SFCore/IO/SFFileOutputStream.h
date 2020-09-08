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
#include "String/SFStringCrc64.h"
#include "IO/SFFile.h"
#include "Stream/SFStream.h"



namespace SF {


	/////////////////////////////////////////////////////////////////////////////
	//
	//	OutputStream
	//

	class FileOutputStream : public IOutputStream
	{
	public:

		FileOutputStream();
		FileOutputStream(const char* filePath);

		Result Open(const char* filePath);
		Result Close();

		// return true if the stream is valid and able to be written
		virtual bool CanWrite() override;
		// size of output
		virtual size_t GetSize() const override;
		// current write position
		virtual size_t GetPosition() const override;

		// Write data
		virtual Result Write(const void* buffer, size_t writeSize) override;


	private:

		File m_File;


	};




}

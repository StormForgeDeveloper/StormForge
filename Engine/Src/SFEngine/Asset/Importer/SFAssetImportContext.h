////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Import context
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "MemoryManager/SFMemory.h"
#include "Stream/SFStream.h"
#include "Util/SFString.h"
#include "Util/SFStringCrc64.h"
#include "Variable/SFVariable.h"
#include "Variable/SFVariableTable.h"


namespace SF
{



	////////////////////////////////////////////////////////////////////
	//
	//	AssetImportContext
	//

	class AssetImportContext
	{
	private:
		// input stream
		IInputStream& m_InputStream;

		// Source
		String m_Source;

		// property table
		VariableTable m_Variables;

	public:

		AssetImportContext(IInputStream& inputStream, const String& source);
		virtual ~AssetImportContext();

		// Get input stream
		IInputStream& GetStream() { return m_InputStream; }

		// Get source string
		const String& GetSource() { return m_Source; }

		VariableTable& GetVariableTable() { return m_Variables; }
	};


}


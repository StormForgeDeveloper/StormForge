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

#include "Memory/SFMemory.h"
#include "Stream/SFStream.h"
#include "String/SFString.h"
#include "String/SFFixedString.h"
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
		// Heap for resource
		IHeap& m_Heap;

		// input stream
		IInputStream& m_InputStream;

		// Source
		String m_Source;

		// property table
		VariableTable m_Variables;

	public:

		AssetImportContext(IHeap& heap, IInputStream& inputStream, const String& source);
		virtual ~AssetImportContext();

		// Get heap for resource
		IHeap& GetHeap() { return m_Heap; }

		// Get input stream
		IInputStream& GetStream() { return m_InputStream; }

		// Get source string
		const String& GetSource() { return m_Source; }

		VariableTable& GetVariableTable() { return m_Variables; }
	};


}


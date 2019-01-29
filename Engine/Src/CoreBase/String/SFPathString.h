////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Path string
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Object/SFSharedObject.h"
#include "Object/SFSharedPointer.h"
#include "String/SFStrUtil.h"
#include "String/SFString.h"
#include "Container/SFArray.h"


namespace SF {

	class FixedString;
	class VariableBox;


	////////////////////////////////////////////////////////////////////////////////
	//
	//	PathString
	//

	class PathString
	{
	public:

		static const char* Root;			// Root path
		static const char* Separator;		// Path separator
		static const char* AltSeparator;	// Alternative Path separator

	private:

		// Heap for string operation
		IHeap* m_pHeap = nullptr;

		// string buffer
		StaticArray<String,10> m_DecomposedPath;

		// full path string
		String m_FullPath;

	private:

		void UpdateHeap();

	public:
		PathString();
		PathString(const char* strPath);
		PathString(const String& strPath);
		PathString(const PathString& path);
		PathString(IHeap& heap);
		PathString(IHeap& heap, const char* strPath);
		PathString(IHeap& heap, const String& strPath);
		PathString(IHeap& heap, const PathString& path);
		~PathString();

		IHeap& GetHeap() const { return *m_pHeap; }
		void SetHeap(IHeap& heap);

		// Set path string
		Result SetPathString(const char* strPath);

		// Get extension
		const char* GetExt() const;

		// Append path
		Result Combine(const String& pathString);
		Result Combine(const char* pathString);
		Result Combine(const PathString& pathString);

		// Get decomposed path length
		size_t size() const { return m_DecomposedPath.size(); }

		String& operator[](int iIndex);
		const String& operator[](int iIndex) const;

		operator const String&() const;

		bool operator == (const PathString& src) const;
		bool operator != (const PathString& src) const;

		PathString& operator = (const char* src);
		PathString& operator = (const String& src);
		PathString& operator = (const PathString& src);
	};




}; // namespace SF




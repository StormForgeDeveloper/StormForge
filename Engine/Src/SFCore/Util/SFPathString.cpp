////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : String
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFStrFormat.h"
#include "Variable/SFVariableBoxing.h"
#include "Util/SFStringCrc64.h"
#include "Util/SFString.h"
#include "Util/SFPathString.h"
#include "Util/SFUtility.h"
#include "Util/SFPath.h"

namespace SF
{
	

	////////////////////////////////////////////////////////////////////////////////
	//
	//	SharedStringBuffer
	//

	PathString::PathString()
		: m_pHeap(&GetSystemHeap())
		, m_DecomposedPath(GetHeap())
	{
	}

	PathString::PathString(const char* strPath)
		: m_pHeap(&GetSystemHeap())
		, m_DecomposedPath(GetHeap())
	{
		SetPathString(strPath);
	}

	PathString::PathString(const String& strPath)
		: m_pHeap(&GetSystemHeap())
		, m_DecomposedPath(GetHeap())
	{
		SetPathString(strPath);
	}

	PathString::PathString(const PathString& path)
		: m_pHeap(&GetSystemHeap())
		, m_DecomposedPath(GetHeap())
	{
		for (auto& itChunk : path.m_DecomposedPath)
		{
			m_DecomposedPath.push_back(String(GetHeap(), itChunk));
		}
	}

	PathString::PathString(IHeap& heap)
		: m_pHeap(&heap)
		, m_DecomposedPath(GetHeap())
	{
	}

	PathString::PathString(IHeap& heap, const char* strPath)
		: m_pHeap(&heap)
		, m_DecomposedPath(GetHeap())
	{
		SetPathString(strPath);
	}

	PathString::PathString(IHeap& heap, const String& strPath)
		: m_pHeap(&heap)
		, m_DecomposedPath(GetHeap())
	{
		SetPathString(strPath);
	}

	PathString::PathString(IHeap& heap, const PathString& path)
		: m_pHeap(&heap)
		, m_DecomposedPath(GetHeap())
	{
		for (auto& itChunk : path.m_DecomposedPath)
		{
			m_DecomposedPath.push_back(String(GetHeap(), itChunk));
		}
	}

	PathString::~PathString()
	{
	}

	void PathString::SetHeap(IHeap& heap)
	{
		m_pHeap = &heap;
		UpdateHeap();
	}

	// Set path string
	Result PathString::SetPathString(const char* strPath)
	{
		m_DecomposedPath.Clear();
		if (!String(GetHeap(), strPath).SplitAny("/\\", m_DecomposedPath))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}

	void PathString::UpdateHeap()
	{
		for (auto& itChunk : m_DecomposedPath)
		{
			itChunk.SetHeap(GetHeap());
		}
	}

	const char* PathString::GetExt() const
	{
		if (m_DecomposedPath.size() == 0)
			return nullptr;

		auto& lastChunk = m_DecomposedPath[m_DecomposedPath.size() - 1];
		if (lastChunk.GetLength() == 0)
			return nullptr;

		auto index = lastChunk.IndexOfFromEnd('.');
		if (index < 0)
			return nullptr;

		return lastChunk.data() + index;
	}


	// Append path
	Result PathString::Combine(const String& pathString)
	{
		StaticArray<String, 10> inputPath(GetHeap());
		if (!String(GetHeap(), pathString).SplitAny(Util::Path::DirectorySeparatorChars, inputPath))
			return ResultCode::FAIL;

		for (auto& itIter : inputPath)
		{
			m_DecomposedPath.push_back(itIter);
		}

		return ResultCode::SUCCESS;
	}

	Result PathString::Combine(const char* pathString)
	{
		StaticArray<String, 10> inputPath(GetHeap());
		if (!String(GetHeap(), pathString).SplitAny(Util::Path::DirectorySeparatorChars, inputPath))
			return ResultCode::FAIL;

		for (auto& itIter : inputPath)
		{
			m_DecomposedPath.push_back(itIter);
		}

		return ResultCode::SUCCESS;
	}

	Result PathString::Combine(const PathString& pathString)
	{
		for (auto& itIter : pathString.m_DecomposedPath)
		{
			m_DecomposedPath.push_back(itIter);
		}

		return ResultCode::SUCCESS;
	}

	static String _dummy;
	String& PathString::operator[](int iIndex)
	{
		if (iIndex < 0 || iIndex >= static_cast<int>(m_DecomposedPath.size()))
		{
			Assert(false);
			return _dummy;
		}

		return m_DecomposedPath[iIndex];
	}

	const String& PathString::operator[](int iIndex) const
	{
		if (iIndex < 0 || iIndex >= static_cast<int>(m_DecomposedPath.size()))
		{
			Assert(false);
			return _dummy;
		}

		return m_DecomposedPath[iIndex];
	}


	bool PathString::operator == (const PathString& src) const
	{
		if (m_DecomposedPath.size() != src.m_DecomposedPath.size())
			return false;

		for(size_t iChunk = 0; iChunk < src.m_DecomposedPath.size(); iChunk++)
		{
			if (!m_DecomposedPath[static_cast<int>(iChunk)].Equals(src[static_cast<int>(iChunk)], true))
				return false;
		}

		return true;
	}

	bool PathString::operator != (const PathString& src) const
	{
		if (m_DecomposedPath.size() != src.m_DecomposedPath.size())
			return true;

		for (size_t iChunk = 0; iChunk < src.m_DecomposedPath.size(); iChunk++)
		{
			if (!m_DecomposedPath[static_cast<int>(iChunk)].Equals(src[static_cast<int>(iChunk)], true))
				return true;
		}

		return false;
	}

	const String& PathString::ToString() const
	{
		m_FullPath = String::Join(m_DecomposedPath, Util::Path::DirectorySeparatorCharString);

		return m_FullPath;
	}

	PathString::operator const String&() const
	{
		m_FullPath = String::Join(m_DecomposedPath, Util::Path::DirectorySeparatorCharString);

		return m_FullPath;
	}

	PathString& PathString::operator = (const char* src)
	{
		SetPathString(src);
		return *this;
	}

	PathString& PathString::operator = (const String& src)
	{
		SetPathString(src);
		return *this;
	}

	PathString& PathString::operator = (const PathString& src)
	{
		m_DecomposedPath.Clear();
		for (auto& itChunk : src.m_DecomposedPath)
		{
			m_DecomposedPath.push_back(itChunk);
		}

		for (auto& itChunk : m_DecomposedPath)
		{
			itChunk.SetHeap(GetHeap());
		}

		return *this;
	}






} // namespace SF




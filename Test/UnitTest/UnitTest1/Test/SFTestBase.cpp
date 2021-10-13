// TestApp.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFTestBase.h"
#include "Service/SFService.h"
#include "Util/SFPath.h"
#include "IO/SFFile.h"

#include <filesystem>



// --gtest_catch_exceptions=0 to disable exception catch
//	--gtest_filter = ThreadTest.EntityTaskManager --gtest_catch_exceptions=0

//./foo_test --gtest_filter=* Also runs everything, due to the single match-everything * value.
//./foo_test --gtest_filter=FooTest.* Runs everything in test case FooTest.
//./foo_test --gtest_filter=*Null*:*Constructor* Runs any test whose full name contains either "Null" or "Constructor".
//./foo_test --gtest_filter=-*DeathTest.* Runs all non-death tests.
//./foo_test --gtest_filter=FooTest.*-FooTest.Bar Runs everything in test case FooTest except 

using namespace SF;

SF::Result MyTestBase::LoadJsonFile(const String& jsonPath, Json::Value& outValue)
{
	Result hr;
	File file;
	file.Open(jsonPath, File::OpenMode::Read);
	if (!file.IsOpened())
		return hr = ResultCode::FAIL;

	auto fileSize = file.GetFileSize();
	StaticArray<uint8_t, 1024> buffer(GetSystemHeap());
	buffer.resize(fileSize + 1);
	size_t readed = 0;
	hr = file.Read(buffer.data(), fileSize, readed);
	if (!hr)
		return hr;

	buffer[fileSize] = '\0';

	int readOffset = 0;
	constexpr uint8_t UTF8BOM[] = { 0xEF, 0xBB, 0xBF };
	if (buffer.size() >= 3 && memcmp(UTF8BOM, buffer.data(), 3) == 0)
		readOffset = 3;

	std::string errs;
	Json::CharReaderBuilder jsonBuilder;
	UniquePtr<Json::CharReader> jsonReader(jsonBuilder.newCharReader());
	auto readStart = reinterpret_cast<const char*>(buffer.data() + readOffset);
	bool bRes = jsonReader->parse(readStart, readStart + (buffer.size() - readOffset), &outValue, &errs);
	if (!bRes)
	{
		SFLog(Net, Error, "LoadJsonFile value parsing {0}, error:{1}", jsonPath, errs);
		return ResultCode::INVALID_STR_DATA;
	}

	return ResultCode::SUCCESS;
}

void MyTestBase::SetUp()
{
	auto dirPath = SF::Util::Path::GetFileDirectory(__FILE__);
	m_DataPath = SF::Util::Path::Combine(dirPath, "..", "data");

	auto jsonPath = SF::Util::Path::Combine(m_DataPath, "TestConfig.json");
	if (!std::filesystem::exists(jsonPath.data()))
	{
		auto samplePath = SF::Util::Path::Combine(m_DataPath, "SampleTestConfig.json");
		std::filesystem::copy_file(samplePath.data(), jsonPath.data());
	}

	LoadJsonFile(jsonPath, m_ConfigJson);
}

// TearDown() is invoked immediately after a test finishes.  Here we
void MyTestBase::TearDown()
{
	StopAllThread();

	SF::Service::LogModule->Flush();
}


// UnitTest1.cpp : Defines the entry point for the console application.
//

#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "Util/SFPath.h"
#include "Util/SFStrUtil.h"
#include "Util/SFStringCrc32.h"
#include "Util/SFStringCrc64.h"
#include "Util/SFStringCrcDB.h"
#include "IO/SFFileInputStream.h"
#include "IO/SFFileOutputStream.h"
#include "Util/AppConfig.h"

#include "SFEngine.h"


// Test parameters
//-in=D:\work\FishingOnlineServer\Data\stringcrc\string_list.txt -out=D:\work\FishingOnlineServer\Contents\string_list.crcbin
//
//-in=D:\work\FishingOnlineServer\Contents\string_list.crcbin -out=D:\work\FishingOnlineServer\Contents\string_list2.crcbin


static int Process()
{
	SF::DynamicArray<const char*> inputPaths;
	SF::AppConfig::GetSettingArray("in", inputPaths);
	const char* outputPath = SF::AppConfig::GetSetting("out");
	const char* outputTxtPath = SF::AppConfig::GetSetting("outtxt");

	if (inputPaths.size() == 0 || outputPath == nullptr)
	{
		SFLog(Engine, Error, "SFStringCrcBin: invalid argument");
		return -1;
	}

	SF::StringCrcDB stringDB;

	for (auto inputPath : inputPaths)
	{
		SFLog(Engine, Error, "SFStringCrcBin: Loading input file {0}", inputPath);


		SF::FileInputStream readFrom(inputPath);
		auto testResult = stringDB.CheckFileHeader(readFrom);

		// Seek back to start position
		readFrom.Seek(SF::SeekMode::Begin, 0);

		if (testResult == SF::StringCrcDB::FileHeaderCheckResult::Successed)
		{
			// binary merge
			if (!stringDB.LoadStringTable(readFrom))
			{
				SFLog(Engine, Error, "SFStringCrcBin: Failed to read input binary {0}", inputPath);
				return -1;
			}

			stringDB.DumpStringList();
		}
		else if (testResult == SF::StringCrcDB::FileHeaderCheckResult::InvalidVersion)
		{
			SFLog(Engine, Error, "SFStringCrcBin: Failed to read input binary, invalid file version {0}", inputPath);
			return -2;
		}
		else
		{
			// text to bin
			SF::DynamicArray<char> readBuffer;
			readBuffer.reserve(16 * 1024);


			SF::Result res = readFrom.ReadAppend(readBuffer);
			if (!res && res != SF::ResultCode::END_OF_STREAM)
			{
				SFLog(Engine, Error, "SFStringCrcBin: Failed to read data from input text {0}", inputPath);
				return -2;
			}


			const char trimStartEnd[] = { '\"' };

			int iPos = 0;
			while (readBuffer.size() > 0 || res != SF::ResultCode::END_OF_STREAM)
			{
				auto crIndex = readBuffer.FindIndex(iPos, [](const char x) { return x == '\n'; });
				if (crIndex >= 0 || res == SF::ResultCode::END_OF_STREAM)
				{
					if (readBuffer.size() == 0)
						break;

					if (crIndex < 0)
						crIndex = int(readBuffer.size() - 1);
					readBuffer[crIndex] = '\0';

					SF::String str(readBuffer.data() + iPos);
					str = str.Trim();
					if (str.StartsWith('\"') && str.EndsWith('\"'))
					{
						str = str.TrimStart(trimStartEnd);
						str = str.TrimEnd(trimStartEnd);
					}

					if (str.length() > 0)
						stringDB.AddString(str);

					if (res == SF::ResultCode::END_OF_STREAM)
						break;
					else
						iPos = crIndex + 1; // next string start
				}
				else // no
				{
					if (readBuffer.size() > iPos)
					{
						auto remainSize = readBuffer.size() - iPos;
						memmove(readBuffer.data(), readBuffer.data() + iPos, remainSize);
						readBuffer.resize(remainSize);
					}
					else
					{
						readBuffer.Reset();
					}

					iPos = 0;
					res = readFrom.ReadAppend(readBuffer);
					if (!res && res != SF::ResultCode::END_OF_STREAM)
					{
						SFLog(Engine, Error, "SFStringCrcBin: Failed to read data from input text {0}", inputPath);
						return -2;
					}
				}
			}


			stringDB.DumpStringList();
		}
		readFrom.Close();

	}


	SFLog(Engine, Info, "SFStringCrcBin: Writing output table {0}", outputPath);
	SF::FileOutputStream saveTo(outputPath);
	if (!stringDB.SaveStringTable(saveTo))
	{
		SFLog(Engine, Error, "SFStringCrcBin: Failed to write output table {0}", outputPath);
		return -1;
	}
	saveTo.Close();


	if (outputTxtPath)
	{
		SFLog(Engine, Info, "SFStringCrcBin: Writing output table {0}", outputTxtPath);
		SF::FileOutputStream saveToTxt(outputTxtPath);
		if (!stringDB.DumpToTextFile(saveToTxt))
		{
			SFLog(Engine, Error, "SFStringCrcBin: Failed to write output table {0}", outputTxtPath);
			return -1;
		}
		saveToTxt.Close();
	}

	return 0;
}

int main(int argc, const char* argv[])
{
	SF::AppConfig::ProcessParameter(argc, argv);


	SF::EngineInitParam initParam;
	initParam.GlobalLogOutputMask.Factal = 1;
	initParam.GlobalLogOutputMask.Error = 1;
	initParam.GlobalLogOutputMask.Warning = 1;
	initParam.GlobalLogOutputMask.Info = 1;
	initParam.GlobalLogOutputMask.Debug = 1;
	initParam.GlobalLogOutputMask.Debug1 = 1;
	initParam.LogOutputDebugger.Composited = uint32_t(-1);
	initParam.LogOutputConsole.Composited = uint32_t(-1);
	initParam.EnableMemoryLeakDetection = true;
	initParam.GraphicSystem = "Vulkan";

	SF::Engine::Start(initParam);

	SF::Log::System.ChannelMask.Composited = uint32_t(-1);

	int iRet = Process();

	SF::Service::LogModule->Flush();

	SF::Engine::Stop();

	return iRet;
}


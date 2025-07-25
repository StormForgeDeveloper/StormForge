////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Package serializer
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Asset/Package/SFAssetPackageSerializer.h"
#include "Asset/Package/SFAssetPackage.h"
#include "Asset/Serializer/SFAssetSerializer.h"
#include "Service/SFEngineService.h"
#include "Stream/SFMemoryStream.h"
#include "Stream/SFCompressedStream.h"


namespace SF
{

	inline Result operator >> (IInputStream& input, AssetPackageSerializer::PackageHeader& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const AssetPackageSerializer::PackageHeader& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, AssetPackageSerializer::ObjectHeader& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const AssetPackageSerializer::ObjectHeader& data) { return output.Write(&data, sizeof(data)); }

	


	////////////////////////////////////////////////////////////////////
	//
	//	AssetPackageSerializer
	//

	constexpr StringCrc64 AssetPackageSerializer::HEADER_MAGIC;
	constexpr uint32_t AssetPackageSerializer::HEADER_VERSION;



	AssetPackageSerializer::AssetPackageSerializer()
	{
	}


	AssetPackageSerializer::~AssetPackageSerializer()
	{
	}



	// Serialize stream
	Result AssetPackageSerializer::Serialize(IOutputStream& stream, AssetPackage& package)
	{
		PackageHeader header;
		header.Magic = HEADER_MAGIC;
		header.Version = HEADER_VERSION;
		header.OffsetToDependency = sizeof(PackageHeader);
		header.OffsetToData = (decltype(header.OffsetToData))(header.OffsetToDependency + package.GetDependencies().size() * sizeof(StringCrc64));
		header.NumberOfDependency = (decltype(header.NumberOfDependency))(package.GetDependencies().size());
		header.NumberOfObject = (decltype(header.NumberOfObject))(package.GetAssetList().size());

		Result result = stream << header;
		if (!result)
			return result;

		for (auto& itDependency : package.GetDependencies())
		{
			result = stream.Write(itDependency.GetValue()->GetName());
			if (!result)
				return result;
		}


		for (auto& itAsset : package.GetAssetList())
		{
			ObjectHeader objHeader;
			ResourcePtr assetPtr = itAsset.GetValue();

			objHeader.ObjectType = assetPtr->GetResourceType();
			objHeader.ObjectName = assetPtr->GetName();
			objHeader.Version = 1;
			objHeader.Encoding = 1; // compressed

			OutputMemoryStream memoryStream;
			CompressedOutputStream objectStream(memoryStream);

			AssetSerializer *pSerializer = nullptr;
			result = Service::AssetSerializerFactory->FindSerializer(assetPtr->GetResourceType(), pSerializer);
			if(!result)
				return result;

			// serialize object data
			result = pSerializer->Serialize(objectStream, assetPtr);
			if (!result)
				return result;

			objectStream.Flush();
			objHeader.DataSize = (decltype(objHeader.DataSize))(objectStream.GetCompressedSize());

			result = stream << objHeader;
			if (!result)
				return result;

			result = stream.Write(memoryStream.GetBuffer().data(), memoryStream.GetSize());
			if (!result)
				return result;
		}

		return ResultCode::SUCCESS;
	}



	// Deserialize stream
	Result AssetPackageSerializer::Deserialize(IInputStream& stream, AssetPackage& package)
	{
		PackageHeader header;

		auto startPos = stream.GetPosition();

		Result result = stream >> header;
		if (!result)
			return result;

		if (header.Magic != HEADER_MAGIC)
			return ResultCode::INVALID_FORMAT;

		if (header.Version != HEADER_VERSION)
			return ResultCode::VERSION_NOT_AVAIL;


		if (header.OffsetToDependency != sizeof(PackageHeader))
		{
			if (header.OffsetToDependency < sizeof(PackageHeader))
				return ResultCode::INVALID_FORMAT;

			stream.Skip(header.OffsetToDependency - sizeof(PackageHeader));
		}


		for (int iDep = 0; iDep < header.NumberOfDependency; iDep++)
		{
			StringCrc64 dependencyName;
			result = stream >> dependencyName;
			if (!result)
				return result;

			// TODO: add the dependency
		}

		// Move to object start
		auto curPos = stream.GetPosition() - startPos;
		if (header.OffsetToData < curPos)
			return ResultCode::INVALID_FORMAT;

		if (header.OffsetToData > curPos)
			stream.Skip(header.OffsetToData - curPos);

		// load objects
		for (int iObj = 0; iObj < (int)header.NumberOfObject; iObj++)
		{
			auto objStartPos = stream.GetPosition();

			ObjectHeader objHeader;
			result = stream >> objHeader;
			if (!result)
				return result;

			ResourcePtr resultRes;

			AssetSerializer *pSerializer = nullptr;
			result = Service::AssetSerializerFactory->FindSerializer(objHeader.ObjectType, pSerializer);
			if (!result)
				return result;

			if (objHeader.Encoding != 0)
			{
				DynamicArray<uint8_t> memBuffer;
				memBuffer.resize(objHeader.DataSize);
				result = stream.Read(memBuffer.data(), memBuffer.size());
				if (!result)
					return result;

				InputMemoryStream memStream(memBuffer);
				CompressedInputStream objStream(memStream, objHeader.DataSize, objHeader.UncompressedDataSize);

				result = pSerializer->Deserialize(objStream, resultRes);
				if (!result)
					return result;
			}
			else
			{

				result = pSerializer->Deserialize(stream, resultRes);
				if (!result)
					return result;
			}

			resultRes->SetName(objHeader.ObjectName);


			if ((sizeof(ObjectHeader) + objHeader.DataSize) != (stream.GetPosition() - objStartPos))
			{
				Assert(false);
				return ResultCode::INVALID_FORMAT;
			}
		}


		return ResultCode::SUCCESS;
	}




}


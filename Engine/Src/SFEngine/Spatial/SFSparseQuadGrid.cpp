
////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author: Kyungkun Ko
//
// Description : Fishing zone Area data
//
////////////////////////////////////////////////////////////////////////////////


#include "FishingGameLibPch.h"
#include "FishingGameZoneAreaData.h"
#include "Util/SFPath.h"
#include "Avro/SFAvro.h"
#include "IO/SFFileInputStream.h"
#include "SvrTrace.h"
#include "Service/ServerService.h"
#include "Util/SFRandom.h"


namespace SF {



	//////////////////////////////////////////////////////////////////////////////////
	//
	//	class TriangleRegion
	//

	TriangleRegion::TriangleRegion(StringCrc32 dataId, const ArrayView<const Vector4>& InVertices)
	{
		DataId = dataId;
		int iMinY = 0;
		float minY = std::numeric_limits<float>::max();

		for (int iVert = 0; iVert < 3; iVert++)
		{
			Vertices[iVert] = Vector2(InVertices[iVert].x, InVertices[iVert].z);

			HeightMin = std::min(HeightMax, InVertices[iVert].y);
			HeightMax = std::max(HeightMax, InVertices[iVert].y);

			if (minY > Vertices[iVert].y)
			{
				iMinY = iVert;
				minY = Vertices[iVert].y;
			}
		}

		// put vertex with min Y at 0
		if (iMinY != 0)
		{
			if (iMinY == 1)
			{
				std::swap(Vertices[0], Vertices[2]);
				std::swap(Vertices[0], Vertices[1]);
			}
			else // iMinY == 2
			{
				std::swap(Vertices[0], Vertices[1]);
				std::swap(Vertices[0], Vertices[2]);
			}
		}
	}

	bool TriangleRegion::IsInArea(const Vector4& value) const
	{
		if (value.y < HeightMin || value.y > HeightMax)
			return false;

		// 2D projection
		Vector2 P(value.x, value.z);

		Vector2 V0 = P - Vertices[0];
		Vector2 V1 = Vertices[1] - Vertices[0];
		Vector2 V2 = Vertices[2] - Vertices[0];
		Vector4 V12(V1.x, V1.y, V2.x, V2.y);

		// Compute dot products
		float dot21 = V2.Dot(V1);
		float dot11 = V1.Dot(V1);

		float dot22 = V2.Dot(V2);
		float dot12 = dot21; // == V1.Dot(V2);

		// Compute barycentric coordinates
		float invDet = 1 / (dot22 * dot11 - dot21 * dot21);


		float dot10 = V1.Dot(V0);
		float dot20 = V2.Dot(V0);

		//u    -dot21,  dot11     dot10
		//v  =  dot22, -dot12  X  dot20
		float u = (-dot21 * dot10 + dot11 * dot20) * invDet;
		float v = (dot22 * dot10 - dot12 * dot20) * invDet;

		// Check if point is in triangle
		return (u >= 0) && (v >= 0) && (u + v < 1);
	}



	//////////////////////////////////////////////////////////////////////////////////
	//
	//	class TriangleRegionPrecalculated
	//

	TriangleRegionPrecalculated::TriangleRegionPrecalculated(const TriangleRegionPrecalculated& src)
		: Vc(src.Vc)
		, V12(src.V12)
		, Equation(src.Equation)
		, InvDet(src.InvDet)
		, HeightMin(src.HeightMin)
		, HeightMax(src.HeightMax)
		, DataId(src.DataId)
	{
	}

	TriangleRegionPrecalculated::TriangleRegionPrecalculated(const TriangleRegion& triangleRegion)
	{
		Init(triangleRegion);
	}

	TriangleRegionPrecalculated& TriangleRegionPrecalculated::operator = (const TriangleRegionPrecalculated& src)
	{
		Vc = src.Vc;
		V12 = src.V12;
		Equation = src.Equation;
		InvDet = src.InvDet;
		HeightMin = src.HeightMin;
		HeightMax = src.HeightMax;
		DataId = src.DataId;

		return *this;
	}

	void TriangleRegionPrecalculated::Init(const TriangleRegion& triangleRegion)
	{
		DataId = triangleRegion.DataId;
		HeightMin = triangleRegion.HeightMin;
		HeightMax = triangleRegion.HeightMax;


		Vc = Vector4(triangleRegion.Vertices[0].x, triangleRegion.Vertices[0].y, triangleRegion.Vertices[0].x, triangleRegion.Vertices[0].y);
		Vector4 V21 = Vector4(
			triangleRegion.Vertices[2].x, triangleRegion.Vertices[2].y,
			triangleRegion.Vertices[1].x, triangleRegion.Vertices[1].y) - Vc;

#if defined(SF_SIMD_SSE42)
		V12 = _SF_SWIZZLE(V21.Packed, 1, 0, 3, 2);
		Vector4 Sign(-1, 1, 1, -1);
		//Vector4 V11 = Vector4(V1.x, V1.y, V1.x, V1.y);
		//Vector4 V22 = Vector4(V2.x, V2.y, V2.x, V2.y);
		Vector4 V11 = _SF_SWIZZLE_2323(V21.Packed);
		Vector4 V22 = _SF_SWIZZLE_0101(V21.Packed);

		// Compute dot products
		Vector4 V2111 = V21 * V11;
		Vector4 V2122 = V21 * V22;

		//float dot21 = V2111.x + V1211.y; // V2.Dot(V1);
		//float dot11 = V2111.z + V1211.w; // V1.Dot(V1);
		//float dot22 = V2122.x + V1222.y; // V2.Dot(V2);
		//float dot12 = V2122.z + V1222.w; // V1.Dot(V2);
		Vector4 Dots = _mm_hadd_ps(V2111.Packed, V2122.Packed);
		Equation.Vec = Dots * Sign;

		// Compute barycentric coordinates
		float det = -Determinent2x2SSE(Equation.Vec.Packed);
#else
		V12 = Vector4(V21.y, V21.w, V21.x, V21.y);
		Vector4 V22 = Vector4(V21.x, V21.y, V21.x, V21.y);
		Vector4 V11 = Vector4(V21.z, V21.w, V21.z, V21.w);

		// Compute dot products
		Vector4 V2111 = V21 * V11;
		Vector4 V2122 = V21 * V22;

		float dot21 = V2122.x + V2122.y; // V2.Dot(V1);
		float dot11 = V2122.z + V2122.w; // V1.Dot(V1);
		float dot22 = V2122.x + V2122.y; // V2.Dot(V2);
		float dot12 = V2122.z + V2122.w; // V1.Dot(V2);
		Equation.a00 = -dot21;
		Equation.a01 = dot11;
		Equation.a10 = dot22;
		Equation.a11 = -dot12;

		// Compute barycentric coordinates
		float det = -Equation.GetDeterminent();
#endif
		if (std::abs(det) <= std::numeric_limits<float>::epsilon())
		{
			// Unsolvable equation, disable it
			SFLog(System, Error, "Invalid region triangle data, skipping...");
			memset(this, 0, sizeof(TriangleRegionPrecalculated));
			return;
		}

		InvDet = 1 / det;
	}

	Vector4 TriangleRegionPrecalculated::PickRandomPosition() const
	{
		auto u = Util::Random.RandF();
		auto v = Util::Random.RandF() * (1.0f - u);
		auto Vpos = V12 * Vector4(u, u, v, v);
		Vpos = Vpos + Vpos.GetSwapLH() + Vc;

		return Vector4(Vpos.GetX(), HeightMax, Vpos.GetY());
	}


	//////////////////////////////////////////////////////////////////////////////////
	//
	//	class SparseQuadRegion
	//

	const Vector4 SparseQuadRegion::GridScale(10,10,10,10); // Sx, Sy, Sx, Sy

	SparseQuadRegion::SparseQuadRegion()
		: m_Heap(GetSystemHeap())
		, m_SortedNodeList(GetHeap())
	{
	}

	SparseQuadRegion::SparseQuadRegion(IHeap& heap)
		: m_Heap(heap)
		, m_SortedNodeList(GetHeap())
	{
	}

	SparseQuadRegion::~SparseQuadRegion()
	{
		Reset();
	}

	void SparseQuadRegion::Reset()
	{
		m_SortedNodeList.ForeachOrder(0, (uint32_t)m_SortedNodeList.size(), [](RegionID key, QuadNode* value)
			{
				delete value;
				return ResultCode::SUCCESS;
			});
		m_SortedNodeList.Reset();
	}

	Result SparseQuadRegion::AddTriangle(const TriangleRegionPrecalculated* triangleRegion)
	{
		const Vector4 Epsilon(std::numeric_limits<float>::epsilon());
		const Vector4 YEpsilon(0, std::numeric_limits<float>::epsilon(), 0, std::numeric_limits<float>::epsilon());

		if (triangleRegion == nullptr)
			return ResultCode::INVALID_POINTER;

		// we expect vertex 0 has min y
		assert(triangleRegion->V12.y >= 0);
		assert(triangleRegion->V12.w >= 0);

		auto Vc = triangleRegion->Vc / GridScale;
		auto Vlr = triangleRegion->V12 / GridScale; // Vlr is a delta(displacement) vector
		if (Vlr.x > Vlr.z)
			Vlr.SwapLH();


		struct SF_DECLARE_ALIGN_DOUBLE RegionSection {
			Vector4 dxdy; // dxdyL, 1, dxdyR, 1
			float Y;

			void Set(float y, const Vector4 Vlr)
			{
				Y = y;
				dxdy.x = Math::Abs(Vlr.y) > std::numeric_limits<float>::epsilon() ? Vlr.x / Vlr.y : 0;
				dxdy.y = 1;
				dxdy.z = Math::Abs(Vlr.w) > std::numeric_limits<float>::epsilon() ? Vlr.z / Vlr.w : 0;
				dxdy.w = 1;
			}
		};

		Vector4 Vcur = Vc;
		float Vcy = Vc.GetY();
		StaticArray<RegionSection, 3> Sections;
		if ((Vlr.GetY() + std::numeric_limits<float>::epsilon()) < Vlr.GetW())
		{
			RegionSection chunk;
			if (Vlr.GetY() > std::numeric_limits<float>::epsilon())
			{
				chunk.Set(Vcy + Vlr.GetY(), Vlr);
				Sections.push_back(chunk);
			}
			else
			{
				Vcur += Vector4(Vlr.GetX(), 0, Vlr.GetZ(), 0);
			}

#if defined(SF_SIMD_SSE42)
			auto VDiff = Vlr.GetSwapLH() - Vlr;
			Vector4 Vlr2(_mm_shuffle_ps(VDiff.Packed, Vlr.Packed, _MM_SHUFFLE(3, 2, 1, 0)));
#else
			Vector4 Vlr2(Vlr.z - Vlr.x, Vlr.w - Vlr.y, Vlr.z, Vlr.w);
#endif
			chunk.Set(Vcy + Vlr.GetW(), Vlr2);
			Sections.push_back(chunk);
		}
		else if ((Vlr.GetW() + std::numeric_limits<float>::epsilon()) < Vlr.GetY())
		{
			RegionSection chunk;
			if (Vlr.GetW() > std::numeric_limits<float>::epsilon())
			{
				chunk.Set(Vcy + Vlr.GetW(), Vlr);
				Sections.push_back(chunk);
			}
			else
			{
				Vcur += Vector4(Vlr.GetX(), 0, Vlr.GetZ(), 0);
			}

#if defined(SF_SIMD_SSE42)
			auto VDiff = Vlr.GetSwapLH() - Vlr;
			Vector4 Vlr2( _mm_shuffle_ps(Vlr.Packed, VDiff.Packed, _MM_SHUFFLE(3, 2, 1, 0)));
#else
			Vector4 Vlr2(Vlr.x, Vlr.y, Vlr.x - Vlr.z, Vlr.y - Vlr.w);
#endif
			chunk.Set(Vcy + Vlr.GetY(), Vlr2);
			Sections.push_back(chunk);
		}
		else // Vlr.w ~== Vlr.y
		{
			if (Vlr.GetW() > std::numeric_limits<float>::epsilon())
			{
				RegionSection chunk;
				chunk.Set(Vcy + Vlr.GetW(), Vlr);
				Sections.push_back(chunk);
			}
			else
			{
				Vcur += Vector4(Vlr.GetX(), 0, Vlr.GetZ(), 0);
			}
		}

		// section
		AddLineRegions(triangleRegion, (int)Vcur.GetY(), (int)Vcur.GetX(), (int)Vcur.GetZ());
		for (auto& itSection : Sections)
		{
			float nextY = Vcur.GetY();
			while (nextY < itSection.Y)
			{
				auto curY = Vcur.GetY();
				nextY = ceilf(curY + std::numeric_limits<float>::epsilon());
				nextY = std::min(nextY, itSection.Y);

				float dY = nextY - curY;
				if (dY < std::numeric_limits<float>::epsilon()) // break before it doesn't make any proceeding
					break;
				//Vector2 dx = itSection.dxdy* dY;
				//Vcur += Vector4(dx.x, dY, dx.y, dY);
				Vcur += itSection.dxdy * dY;

				auto Vcurm = Vcur - YEpsilon;
#if defined(SF_SIMD_SSE42)
				__m128i Vcuri = _mm_cvtps_epi32(Vcurm.Packed);
				auto x = _mm_cvtsi128_si32(Vcuri);
				auto y = _mm_extract_epi32(Vcuri, 1);
				auto z = _mm_extract_epi32(Vcuri, 2);
#else
				auto x = int(Vcurm.x);
				auto y = int(Vcurm.y);
				auto z = int(Vcurm.z);
#endif
				AddLineRegions(triangleRegion, y, x, z);
				AddLineRegions(triangleRegion, y+1, x, z); // The values are calculated at the edge. we need to add both side

			}
		}

		return ResultCode::SUCCESS;
	}

	const TriangleRegionPrecalculated* SparseQuadRegion::TestIntersection(StringCrc32 filter, const Vector4& pos) const
	{
		const TriangleRegionPrecalculated* pFound{};

		auto testPos = pos / GridScale;
#if defined(SF_SIMD_SSE42)
		__m128i Vi = _mm_cvtps_epi32(testPos.Packed);
		auto x = _mm_cvtsi128_si32(Vi);
		auto y = _mm_extract_epi32(Vi, 2);
#else
		auto x = int(Vi.x);
		auto y = int(Vi.z);
#endif
		RegionID regionId;
		regionId.Components.RegionX = (int16_t)x;
		regionId.Components.RegionY = (int16_t)y;

		QuadNode* pQuadNode{};
		int64_t iOrder{};
		if (m_SortedNodeList.Find(regionId, pQuadNode, &iOrder))
		{
			for (auto itTriangleArea : pQuadNode->TriangleAreas)
			{
				if (itTriangleArea->DataId != filter)
					continue;

				if (itTriangleArea->IsInArea(testPos))
				{
					pFound = itTriangleArea;
				}
			}
		}

		return pFound;
	}

	void SparseQuadRegion::AddLineRegions(const TriangleRegionPrecalculated* triangleRegion, int curY, int lX, int rX)
	{
		RegionID regionId;
		regionId.Components.RegionY = (int16_t)curY;

		for (int curX = lX; curX <= rX; curX++)
		{
			regionId.Components.RegionX = (int16_t)curX;

			QuadNode* pQuad{};
			if (!m_SortedNodeList.Find(regionId, pQuad))
			{
				pQuad = new QuadNode(GetHeap(), regionId);
				m_SortedNodeList.Insert(regionId, pQuad);
				m_SortedNodeList.CommitChanges();
			}

			pQuad->AddTriangleRegion(triangleRegion);
		}
	}


	//////////////////////////////////////////////////////////////////////////////////
	//
	//	class FishingGameZoneAreaData
	//

	FishingGameZoneAreaData::FishingGameZoneAreaData()
		: m_SparseQuadRegion(GetHeap())
	{

	}

	FishingGameZoneAreaData::~FishingGameZoneAreaData()
	{
		m_SparseQuadRegion.Reset();
		m_TriangleRegions.Reset();
	}

	namespace FishingGameZoneAreaDataImpl
	{
		using SeatInfo = FishingGameZoneAreaData::SeatInfo;

		Result LoadSchema(const char* schemaPath, AvroSchema& outSchema)
		{
			Result hr;

			SF::DynamicArray<char> schemaData;
			SF::FileInputStream schemaStream;
			svrCheck(schemaStream.Open(schemaPath));

			schemaData.resize(schemaStream.GetSize());
			svrCheck(schemaStream.Read(schemaData.data(), schemaData.size()));

			return outSchema.Init(schemaData);
		}


		Result ProcessTriangles(StringCrc32 dataType, const Array<Vector4>& Vertices, const Array<int>& TriangleIndices, Array<TriangleRegionPrecalculated>& triangleRegions)
		{
			for (int iTri = 0; iTri < TriangleIndices.size(); iTri += 3)
			{
				Vector4 Vert[3] = {
					Vertices[TriangleIndices[iTri]],
					Vertices[TriangleIndices[iTri + 1]],
					Vertices[TriangleIndices[iTri + 2]]
				};

				TriangleRegion region(dataType, Vert);
				TriangleRegionPrecalculated preCalculated(region);

				if (!preCalculated.IsValid())
					continue;

				triangleRegions.push_back(preCalculated);
			}

			return ResultCode::SUCCESS;
		}


		Result LoadTriangleMeshFile(StringCrc32 dataType, const char* dataPath, const AvroSchema& schema, const Vector4& worldOffset, Array<TriangleRegionPrecalculated>& triangleRegions)
		{
			Result hr;
			DynamicArray<Vector4> Vertices;
			DynamicArray<int> TriangleIndices;


			SF::DynamicArray<char> binData;
			{
				SF::FileInputStream dataStream;
				svrCheck(dataStream.Open(dataPath));

				binData.resize(dataStream.GetSize());
				svrCheck(dataStream.Read(binData.data(), binData.size()));
			}

			SF::AvroReader memoryReader(binData);
			SF::AvroValue dataValue(schema);

			// read value
			hr = memoryReader.ReadValue(dataValue);
			if (!hr)
			{
				SFLog(System, Error, "Error reading value: {0}", SF::Avro::GetErrorString());
				return ResultCode::INVALID_FORMAT;
			}

			if (dataValue.GetType() != SF::Avro::ValueType::Record)
			{
				return ResultCode::INVALID_FORMAT;
			}


			SF::AvroValue MeshNameValue;
			hr = dataValue.GetField("MeshName", MeshNameValue);
			if (!hr)
			{
				SFLog(System, Error, "Error reading value: {0}", SF::Avro::GetErrorString());
				return ResultCode::INVALID_FORMAT;
			}
			//m_Name = MeshNameValue.AsString();


			SF::AvroValue VerticesValue;
			hr = dataValue.GetField("Vertices", VerticesValue);
			if (!hr)
			{
				SFLog(System, Error, "Error reading value: {0}", SF::Avro::GetErrorString());
				return ResultCode::INVALID_FORMAT;
			}

			if (VerticesValue.GetType() != SF::Avro::ValueType::Array)
			{
				return ResultCode::INVALID_FORMAT;
			}

			Vertices.Clear();
			auto numChild = VerticesValue.GetElementCount();
			for (int iChild = 0; iChild < numChild; iChild++)
			{
				SF::AvroValue VertexValue;
				hr = VerticesValue.GetElement(iChild, VertexValue);
				if (!hr)
					return ResultCode::INVALID_FORMAT;

				if (VertexValue.GetType() != SF::Avro::ValueType::Record)
				{
					return ResultCode::INVALID_FORMAT;
				}

				const char* FieldNames[] = {
					"X", "Y", "Z", "NX", "NY", "NZ"
				};
				float fieldValues[6]{};

				for (int iField = 0; iField < SF::countof(FieldNames); iField++)
				{
					fieldValues[iField] = VertexValue.GetFieldValue<float>(FieldNames[iField]);
				}

				int vertexIndex = VertexValue.GetFieldValue<int>("Index");
				if (iChild != vertexIndex)
				{
					SFLog(System, Warning, "FishingGameZoneAreaData: invalid vertex index has found in {0}", dataPath);
				}

				Vertices.push_back(Vector4(fieldValues[0], fieldValues[1], fieldValues[2]) + worldOffset);
			}


			SF::AvroValue TrianglesValue;
			hr = dataValue.GetField("Triangles", TrianglesValue);
			if (!hr)
			{
				SFLog(System, Error, "Error reading value: {0}", SF::Avro::GetErrorString());
				return ResultCode::INVALID_FORMAT;
			}

			if (TrianglesValue.GetType() != SF::Avro::ValueType::Array)
			{
				return ResultCode::INVALID_FORMAT;
			}


			numChild = TrianglesValue.GetElementCount();
			for (int iChild = 0; iChild < numChild; iChild++)
			{
				SF::AvroValue TriangleValue;
				hr = TrianglesValue.GetElement(iChild, TriangleValue);
				if (!hr)
					return ResultCode::INVALID_FORMAT;

				if (TriangleValue.GetType() != SF::Avro::ValueType::Record)
				{
					return ResultCode::INVALID_FORMAT;
				}

				const char* FieldNames[] = {
					"A", "B", "C"
				};
				int fieldValues[3]{};

				for (int iField = 0; iField < SF::countof(FieldNames); iField++)
				{
					fieldValues[iField] = TriangleValue.GetFieldValue<int>(FieldNames[iField]);
				}

				TriangleIndices.push_back(fieldValues[0]);
				TriangleIndices.push_back(fieldValues[1]);
				TriangleIndices.push_back(fieldValues[2]);
			}

			hr = ProcessTriangles(dataType, Vertices, TriangleIndices, triangleRegions);
			if (!hr)
				return hr;

			return ResultCode::SUCCESS;
		}

		Result LoadMeshItem(const String& dataBasePath, const AvroSchema& schema, const Json::Value& itemValue, StringCrc32 dataId, Array<TriangleRegionPrecalculated>& outArray)
		{
			auto fileName = itemValue.get("File", Json::Value(""));
			auto binPath = SF::Util::Path::Combine(dataBasePath, fileName.asCString());
			if (Util::Path::GetExt(binPath) == nullptr)
				binPath.Append(".avro");

			auto worldPos = itemValue.get("WorldPos", Json::Value(Json::objectValue));
			if (worldPos.type() != Json::objectValue)
				return ResultCode::INVALID_FORMAT;

			Vector4 worldOffset(
				worldPos.get("x", Json::Value(0.0)).asFloat(),
				worldPos.get("y", Json::Value(0.0)).asFloat(),
				worldPos.get("z", Json::Value(0.0)).asFloat());

			return FishingGameZoneAreaDataImpl::LoadTriangleMeshFile(dataId, binPath, schema, worldOffset, outArray);
		}

		Result LoadJsonFile(const String& jsonPath, Json::Value& outValue)
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

		Result LoadSeatInfo(const String& seatInfoPath, DynamicArray<SeatInfo>& SeatInfoList)
		{
			Result hr;
			Json::Value seatObject;

			svrCheck(LoadJsonFile(seatInfoPath, seatObject));

			auto SeatDataArrayObject = seatObject.get("SeatData", Json::Value(Json::arrayValue));
			if (SeatDataArrayObject.type() != Json::arrayValue)
				return ResultCode::INVALID_FORMAT;

			SeatInfoList.reserve(SeatDataArrayObject.size());
			for (int iItem = 0; iItem < (int)SeatDataArrayObject.size(); iItem++)
			{
				auto itemValue = SeatDataArrayObject.get(iItem, Json::Value(Json::objectValue));
				auto instanceIDValue = itemValue.get("instanceID", Json::Value(Json::uintValue));
				auto SeatIDValue = itemValue.get("SeatID", Json::Value(Json::uintValue));
				auto WorldPosValue = itemValue.get("WorldPos", Json::Value(Json::objectValue));
				auto PosXValue = WorldPosValue.get("x", Json::Value(Json::realValue));
				auto PosYValue = WorldPosValue.get("y", Json::Value(Json::realValue));
				auto PosZValue = WorldPosValue.get("z", Json::Value(Json::realValue));

				FishingGameZoneAreaData::SeatInfo seatInfo;
				seatInfo.SeatInstanceId = instanceIDValue.asUInt();
				seatInfo.SeatId = SeatIDValue.asUInt();
				seatInfo.Position = Vector4(PosXValue.asFloat(), PosYValue.asFloat(), PosZValue.asFloat());
				SeatInfoList.push_back(seatInfo);
			}

			return ResultCode::SUCCESS;
		}

		Result LoadZoneDataJson(const String& jsonPath, Json::Value& outJsonValue)
		{
			Result hr;

			svrCheck(LoadJsonFile(jsonPath, outJsonValue));

			//File file;
			//file.Open(jsonPath, File::OpenMode::Read);
			//if (!file.IsOpened())
			//	return hr = ResultCode::FAIL;

			//auto fileSize = file.GetFileSize();
			//StaticArray<uint8_t, 1024> buffer(GetSystemHeap());
			//buffer.resize(fileSize + 1);
			//size_t readed = 0;
			//hr = file.Read(buffer.data(), fileSize, readed);
			//if (!hr)
			//	return hr;

			//buffer[fileSize] = '\0';

			//std::string errs;
			//Json::CharReaderBuilder jsonBuilder;
			//UniquePtr<Json::CharReader> jsonReader(jsonBuilder.newCharReader());
			//auto readStart = reinterpret_cast<const char*>(buffer.data());
			//bool bRes = jsonReader->parse(readStart, readStart + buffer.size(), &outJsonValue, &errs);
			//if (!bRes)
			//{
			//	SFLog(Net, Error, "LoadZoneDataJson value parsing error:{0}", errs);
			//	return ResultCode::INVALID_STR_DATA;
			//}

			return ResultCode::SUCCESS;
		}
	}

	Result FishingGameZoneAreaData::LoadZoneAreaData(const char* ZoneDataSchemaPath, const char* ZoneDataPath)
	{
		Result hr;

		auto schemaPath = ZoneDataSchemaPath;
		auto jsonPath = ZoneDataPath;
		auto dataBasePath = Util::Path::GetFileDirectory(jsonPath);

		svrCheck(FishingGameZoneAreaDataImpl::LoadSchema(schemaPath, m_Schema));

		Json::Value zoneDataJson;
		svrCheck(FishingGameZoneAreaDataImpl::LoadZoneDataJson(jsonPath, zoneDataJson));

		auto gatheringVolumes = zoneDataJson.get("HarvestVolumes", Json::Value(Json::arrayValue));
		if (gatheringVolumes.type() != Json::arrayValue)
			return ResultCode::INVALID_FORMAT;

		for (int iItem = 0; iItem < (int)gatheringVolumes.size(); iItem++)
		{
			auto itemValue = gatheringVolumes.get(iItem, Json::Value(Json::objectValue));
			svrCheck(FishingGameZoneAreaDataImpl::LoadMeshItem(dataBasePath, m_Schema, itemValue, "harvest", m_TriangleRegions));
		}

		auto respawnVolumes = zoneDataJson.get("RespwanVolumes", Json::Value(Json::arrayValue));
		if (respawnVolumes.type() != Json::arrayValue)
			return ResultCode::INVALID_FORMAT;

		for (int iItem = 0; iItem < (int)respawnVolumes.size(); iItem++)
		{
			auto itemValue = respawnVolumes.get(iItem, Json::Value(Json::objectValue));
			svrCheck(FishingGameZoneAreaDataImpl::LoadMeshItem(dataBasePath, m_Schema, itemValue, "respawn", m_RespawnRegions));
		}

		auto navigationVolume = zoneDataJson.get("NavigationMeshVolume", Json::Value(Json::objectValue));
		svrCheck(FishingGameZoneAreaDataImpl::LoadMeshItem(dataBasePath, m_Schema, navigationVolume, "navigation", m_NavigationMeshs));

		// QuadRegion only uses pointer, so we need to add them after array is fully created
		for (auto& itRegion : m_TriangleRegions)
		{
			m_SparseQuadRegion.AddTriangle(&itRegion);
		}

		// Seat
		auto seatIDFile = zoneDataJson.get("SeatIDFile", Json::Value(Json::stringValue));
		if (seatIDFile.type() != Json::stringValue)
			return ResultCode::INVALID_FORMAT;

		m_SeatInfoList.Reset();

		auto seatInfoPath = Util::Path::Combine(dataBasePath, seatIDFile.asCString()) + ".json";
		svrCheck(FishingGameZoneAreaDataImpl::LoadSeatInfo(seatInfoPath, m_SeatInfoList));

		return ResultCode::SUCCESS;
	}


	StringCrc32 FishingGameZoneAreaData::TestIntersection(StringCrc32 filter, const Vector4& pos) const
	{
		const TriangleRegionPrecalculated* pIntersectedTriangle = m_SparseQuadRegion.TestIntersection(filter, pos);
		if (pIntersectedTriangle != nullptr)
			return pIntersectedTriangle->DataId;

		return "";
	}

	Vector4 FishingGameZoneAreaData::PickRandomSpawnPosition() const
	{
		if (m_RespawnRegions.size() == 0)
		{
			return Vector4(119, 2, 45); // from test data
		}

		auto& selectedRegion = m_RespawnRegions[Util::Random.Rand() % m_RespawnRegions.size()];

		return selectedRegion.PickRandomPosition();
	}
}

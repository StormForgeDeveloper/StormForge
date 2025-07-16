////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Protocol parser helper
//	
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Types/SFEngineTypedefs.h"
#include "Util/SFGuid.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Stream/SFMemoryStream.h"
#include "Container/SFArraySerialization.h"

#include "Net/SFNetDef.h"
#include "Util/SFStrUtil.h"
#include "Util/SFString.h"
#include "Util/SFLog.h"
#include "Util/SFToStringEngineTypes.h"
#include "Util/SFStringSerialization.h"
#include "Types/SFEngineTypeSerialization.h"
#include "Types/SFEngineTypeVariable.h"
#include "Variable/SFVariableToString.h"
#include "Variable/SFVariableSerialization.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Math/SF3DMathSerialization.h"

#include "Protocol/SFTypes_generated.h"

namespace SF {
	namespace Protocol {

		#define protocolCheck(e)		do{ hr = e; if(hr.IsFailure()) return hr; } while(0)
		#define protocolCheckPtr(e)		do{ if( e == nullptr ) { hr = ResultCode::INVALID_POINTER; return hr; } } while(0)
		#define protocolCheckMem(a)		do{ if( (a) == nullptr ) { hr = ResultCode::OUT_OF_MEMORY; return hr; } } while(0)


	} // namespace Protocol

    namespace Flat
    {
        // Helper for flatbuffer struct type
        template<class FlatType>
        struct FlatValueHolder
        {
        public:
            FlatType Value;

            FlatValueHolder(FlatType value)
                : Value(value)
            {
            }

            FlatValueHolder(const FlatValueHolder& src)
                : Value(src.m_Value)
            {
            }

            operator const FlatType* () const
            {
                return &Value;
            }

            FlatValueHolder& operator = (const FlatValueHolder& src)
            {
                Value = src.Value;
                return *this;
            }
            FlatValueHolder& operator = (FlatValueHolder&& src)
            {
                Value = std::forward<FlatType>(src.Value);
                return *this;
            }
        };

        // Helper class
        namespace Helper
        {
            using namespace flatbuffers;

            inline FlatValueHolder<SF::Flat::Result> CreateResult(FlatBufferBuilder& fbb, const SF::Result& value)
            {
                return FlatValueHolder<SF::Flat::Result>(SF::Flat::Result((int)value));
            }

            inline Offset<flatbuffers::String> CreateString(FlatBufferBuilder& fbb, const char* value)
            {
                if (value == nullptr)
                    return fbb.CreateString("");
                else
                    return fbb.CreateString(value);
            }

            inline Offset<Vector<Offset<::flatbuffers::String>>> CreateStringVector(FlatBufferBuilder& fbb, const Array<const char*>& value)
            {
                return fbb.CreateVectorOfStrings(value.data(), value.data() + value.size());
            }

            inline Offset<::flatbuffers::Vector<int8_t>> Createint8Vector(FlatBufferBuilder& fbb, const Array<int8_t>& value)
            {
                return fbb.CreateVector(value.data(), value.size());
            }
            inline Offset<::flatbuffers::Vector<uint8_t>> Createuint8Vector(FlatBufferBuilder& fbb, const Array<uint8_t>& value)
            {
                return fbb.CreateVector(value.data(), value.size());
            }
            inline Offset<::flatbuffers::Vector<uint8_t>> CreatebyteVector(FlatBufferBuilder& fbb, const Array<uint8_t>& value)
            {
                return fbb.CreateVector(value.data(), value.size());
            }

            inline Offset<::flatbuffers::Vector<int16_t>> Createint16Vector(FlatBufferBuilder& fbb, const Array<int16_t>& value)
            {
                return fbb.CreateVector(value.data(), value.size());
            }
            inline Offset<::flatbuffers::Vector<uint16_t>> Createuint16Vector(FlatBufferBuilder& fbb, const Array<uint16_t>& value)
            {
                return fbb.CreateVector(value.data(), value.size());
            }

            inline Offset<::flatbuffers::Vector<int32_t>> Createint32Vector(FlatBufferBuilder& fbb, const Array<const int32_t>& value)
            {
                return fbb.CreateVector(value.data(), value.size());
            }
            inline Offset<::flatbuffers::Vector<uint32_t>> Createuint32Vector(FlatBufferBuilder& fbb, const Array<uint32_t>& value)
            {
                return fbb.CreateVector(value.data(), value.size());
            }

            inline Offset<::flatbuffers::Vector<int64_t>> Createint16Vector(FlatBufferBuilder& fbb, const Array<int64_t>& value)
            {
                return fbb.CreateVector(value.data(), value.size());
            }
            inline Offset<::flatbuffers::Vector<uint64_t>> Createuint16Vector(FlatBufferBuilder& fbb, const Array<uint64_t>& value)
            {
                return fbb.CreateVector(value.data(), value.size());
            }

            inline Offset<::flatbuffers::Vector<float>> CreatefloatVector(FlatBufferBuilder& fbb, const Array<float>& value)
            {
                return fbb.CreateVector(value.data(), value.size());
            }
            inline Offset<::flatbuffers::Vector<double>> CreatedoubleVector(FlatBufferBuilder& fbb, const Array<double>& value)
            {
                return fbb.CreateVector(value.data(), value.size());
            }


            inline FlatValueHolder<SF::Flat::Vector4> CreateVector4(FlatBufferBuilder& fbb, const SF::Vector4& value)
            {
                return FlatValueHolder<SF::Flat::Vector4>(SF::Flat::Vector4(value.x, value.y, value.z, value.w));
            }

            inline SF::Vector4 ParseVector4(const SF::Flat::Vector4* value)
            {
                if (value == nullptr)
                    return {};
                else
                    return SF::Vector4(value->x(), value->y(), value->z(), value->w());
            }


            inline FlatValueHolder<SF::Flat::Quaternion> CreateQuaternion(FlatBufferBuilder& fbb, const SF::Quaternion& value)
            {
                return FlatValueHolder<SF::Flat::Quaternion>(SF::Flat::Quaternion(value.x, value.y, value.z, value.w));
            }

            inline SF::Quaternion ParseQuaternion(const SF::Flat::Quaternion* value)
            {
                if (value == nullptr)
                    return {};
                else
                    return SF::Quaternion(value->x(), value->y(), value->z(), value->w());
            }


            inline FlatValueHolder<SF::Flat::Time32> CreateTime32(FlatBufferBuilder& fbb, const SF::Time32& value)
            {
                return FlatValueHolder<SF::Flat::Time32>(SF::Flat::Time32(value));
            }

            inline FlatValueHolder<SF::Flat::Time64> CreateTime64(FlatBufferBuilder& fbb, const SF::Time64& value)
            {
                return FlatValueHolder<SF::Flat::Time64>(SF::Flat::Time64(value));
            }

            inline FlatValueHolder<SF::Flat::TimeSpan> CreateTimeSpan(FlatBufferBuilder& fbb, const SF::TimeSpan& value)
            {
                return FlatValueHolder<SF::Flat::TimeSpan>(SF::Flat::TimeSpan(value.Milliseconds));
            }

            inline SF::TimeSpan ParseTimeSpan(const SF::Flat::TimeSpan& value)
            {
                return SF::TimeSpan(value.milliseconds());
            }


            inline FlatValueHolder<SF::Flat::TransactionID> CreateTransactionID(FlatBufferBuilder& fbb, const SF::TransactionID& value)
            {
                return FlatValueHolder<SF::Flat::TransactionID>(SF::Flat::TransactionID(value.ID));
            }

            inline SF::TransactionID ParseTransactionID(const SF::Flat::TransactionID* value)
            {
                if (value == nullptr)
                    return {};
                else
                    return SF::TransactionID(value->transaction_id());
            }

            inline FlatValueHolder<SF::Flat::GameInstanceUID> CreateGameInstanceUID(FlatBufferBuilder& fbb, const SF::GameInstanceUID& value)
            {
                return FlatValueHolder<SF::Flat::GameInstanceUID>(SF::Flat::GameInstanceUID(value.ID));
            }

            inline SF::GameInstanceUID ParseGameInstanceUID(const SF::Flat::GameInstanceUID* value)
            {
                if (value == nullptr)
                    return {};
                else
                    return SF::GameInstanceUID(value->uid());
            }

            inline FlatValueHolder<SF::Flat::EntityUID> CreateEntityUID(FlatBufferBuilder& fbb, const SF::EntityUID& value)
            {
                return FlatValueHolder<SF::Flat::EntityUID>(SF::Flat::EntityUID(value.ID));
            }

            inline SF::EntityUID ParseEntityUID(const SF::Flat::EntityUID* value)
            {
                if (value == nullptr)
                    return {};
                else
                    return SF::EntityUID(value->entity_id());
            }


            inline SF::Flat::EAccountRole CreateAccountRole(FlatBufferBuilder& fbb, SF::EAccountRole value)
            {
                return (SF::Flat::EAccountRole)value;
            }

            inline FlatValueHolder<SF::Flat::AccountID> CreateAccountID(FlatBufferBuilder& fbb, const SF::AccountID& value)
            {
                const uint64_t low = value.ToLow64();
                const uint64_t high = value.ToHigh64();

                return FlatValueHolder<SF::Flat::AccountID>(SF::Flat::AccountID(low, high));
            }

            inline Offset<Vector<const SF::Flat::AccountID*>> CreateAccountIDVector(FlatBufferBuilder& fbb, const Array<SF::AccountID>& value)
            {
                std::vector< SF::Flat::AccountID> elems;
                elems.reserve(value.size());
                for (SF::AccountID item : value)
                {
                    elems.push_back(*CreateAccountID(fbb, item));
                }
                auto offset = fbb.CreateVectorOfStructs(elems);
                return offset;
            }

            inline SF::EAccountRole ParseAccountRole(const SF::Flat::EAccountRole value)
            {
                return (SF::EAccountRole)(value);
            }

            inline SF::AccountID ParseAccountID(const SF::Flat::AccountID* value)
            {
                if (value == nullptr)
                    return {};
                else
                    return SF::AccountID(value->low(), value->high());
            }

            inline SF::Result ParseAccountIDVector(const Vector<const SF::Flat::AccountID*>* value, Array<SF::AccountID>& outValue)
            {
                if (value == nullptr)
                    return SF::ResultCode::INVALID_POINTER;

                outValue.reserve(value->size());
                for (const SF::Flat::AccountID* srcValue : *value)
                {
                    outValue.push_back(ParseAccountID(srcValue));
                }

                return SF::ResultCode::SUCCESS;
            }

            inline FlatValueHolder<SF::Flat::AccountID> CreatePlayerID(FlatBufferBuilder& fbb, const SF::AccountID& value)
            {
                return CreateAccountID(fbb, value);
            }

            inline Offset<Vector<const SF::Flat::AccountID*>> CreatePlayerIDVector(FlatBufferBuilder& fbb, const Array<SF::AccountID>& value)
            {
                return CreateAccountIDVector(fbb, value);
            }

            inline FlatValueHolder<SF::Flat::Guid> CreateGuid(FlatBufferBuilder& fbb, const SF::Guid& value)
            {
                const uint64_t low = value.ToLow64();
                const uint64_t high = value.ToHigh64();

                return FlatValueHolder<SF::Flat::Guid>(SF::Flat::Guid(low, high));
            }

            inline Offset<Vector<const SF::Flat::Guid*>> CreateGuidVector(FlatBufferBuilder& fbb, const Array<SF::Guid>& value)
            {
                std::vector<SF::Flat::Guid> elems;
                elems.reserve(value.size());
                for (SF::Guid item : value)
                {
                    elems.push_back(*CreateGuid(fbb, item));
                }
                auto offset = fbb.CreateVectorOfStructs(elems);
                return offset;
            }

            inline SF::Guid ParseGuid(const SF::Flat::Guid* value)
            {
                if (value == nullptr)
                    return {};

                uint64_t low = value->low();
                uint64_t high = value->high();
                return SF::Guid(low, high);
            }

            inline FlatValueHolder<SF::Flat::CharacterID> CreateCharacterID(FlatBufferBuilder& fbb, const SF::CharacterID& value)
            {
                const uint64_t low = value.ToLow64();
                const uint64_t high = value.ToHigh64();

                return FlatValueHolder<SF::Flat::CharacterID>(SF::Flat::CharacterID(low, high));
            }

            inline SF::CharacterID ParseCharacterID(const SF::Flat::CharacterID* value)
            {
                if (value == nullptr)
                    return {};

                uint64_t low = value->low();
                uint64_t high = value->high();
                return SF::CharacterID(low, high);
            }

            inline SF::Flat::Platform CreatePlatform(FlatBufferBuilder& fbb, SF::EPlatform value)
            {
                switch (value)
                {
                case EPlatform::BR:
                    return SF::Flat::Platform::BR;
                case EPlatform::Steam:
                    return SF::Flat::Platform::Steam;
                case EPlatform::Facebook:
                    return SF::Flat::Platform::Facebook;
                default:
                    assert(false);
                }
                return SF::Flat::Platform::BR;
            }

            inline SF::EPlatform ParsePlatform(SF::Flat::Platform value)
            {
                switch (value)
                {
                case Flat::Platform::BR:
                    return SF::EPlatform::BR;
                case Flat::Platform::Steam:
                    return SF::EPlatform::Steam;
                case Flat::Platform::Facebook:
                    return SF::EPlatform::Facebook;
                default:
                    assert(false);
                }
                return SF::EPlatform::BR;
            }

            inline ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<SF::Flat::AttributeString>>> CreateAttributeStringVector(FlatBufferBuilder& fbb, const Array<SF::AttributeString>& value)
            {
                std::vector<::flatbuffers::Offset<SF::Flat::AttributeString>> attributesOffset;
                attributesOffset.reserve(value.size());
                for (const SF::AttributeString& item : value)
                {
                    auto nameOffset = fbb.CreateString(item.Name);
                    auto valueOffset = fbb.CreateString(item.Value);
                    auto attrStrOffset = CreateAttributeString(fbb, nameOffset, valueOffset);
                    attributesOffset.emplace_back(attrStrOffset);
                }
                return std::move(fbb.CreateVector(attributesOffset));
            }

            inline Offset<SF::Flat::UGCContentInfo> CreateUGCContentInfo(FlatBufferBuilder& fbb, const SF::UGCContentInfo& value)
            {
                SF::Flat::UGCContentInfoBuilder builder(fbb);

                auto categoryOffset = fbb.CreateString(value.Category);
                auto dataPathOffset = fbb.CreateString(value.DataPath);

                builder.add_ugc_content_id(CreateGuid(fbb, value.UGCContentId));
                builder.add_category(categoryOffset);
                builder.add_data_path(dataPathOffset);
                builder.add_data_id(value.DataId);

                return builder.Finish();
            }

            inline SF::UGCContentInfo ParseUGCContentInfo(const SF::Flat::UGCContentInfo* value)
            {
                SF::UGCContentInfo contentInfo;
                contentInfo.UGCContentId = ParseGuid(value->ugc_content_id());
                contentInfo.Category = value->category()->c_str();
                contentInfo.DataPath = value->data_path()->c_str();
                contentInfo.DataId = value->data_id();
                
                return contentInfo;
            }

            inline Offset<Vector<Offset<SF::Flat::UGCContentInfo>>> CreateUGCContentInfoVector(FlatBufferBuilder& fbb, const Array<SF::UGCContentInfo>& value)
            {
                std::vector<Offset<SF::Flat::UGCContentInfo>> elems;
                elems.reserve(value.size());
                for (const SF::UGCContentInfo& item : value)
                {
                    elems.push_back(CreateUGCContentInfo(fbb, item));
                }
                return fbb.CreateVector(elems.data(), elems.size());
            }

            inline FlatValueHolder<SF::Flat::UGCItemInfo> CreateUGCItemInfo(FlatBufferBuilder& fbb, const SF::SUGCItemInfo& value)
            {
                return FlatValueHolder<SF::Flat::UGCItemInfo>(SF::Flat::UGCItemInfo(value.ItemTableId, value.UTCExpire, value.EffectIds[0], value.EffectIds[1]));
            }

            inline FlatValueHolder<SF::Flat::PlayerPlatformID> CreatePlayerPlatformID(FlatBufferBuilder& fbb, const SF::PlayerPlatformID& value)
            {
                return FlatValueHolder<SF::Flat::PlayerPlatformID>(
                    SF::Flat::PlayerPlatformID(*CreateAccountID(fbb, value.PlayerId), CreatePlatform(fbb, value.Platform))
                );
            }

            inline SF::PlayerPlatformID ParsePlayerPlatformID(const SF::Flat::PlayerPlatformID* value)
            {
                return SF::PlayerPlatformID(ParsePlatform(value->platform_data()), ParseAccountID(&value->player_id()));
            }

            inline FlatValueHolder<SF::Flat::ActorMovement> CreateActorMovement(FlatBufferBuilder& fbb, const SF::ActorMovement& value)
            {
                return FlatValueHolder<SF::Flat::ActorMovement>(
                    SF::Flat::ActorMovement(
                        *CreateVector4(fbb, value.Position),
                        *CreateVector4(fbb, value.LinearVelocity),
                        value.ActorId,
                        value.AngularYaw,
                        value.MoveFrame,
                        value.MovementState
                    )
                );
            }

            inline Offset<Vector<const SF::Flat::ActorMovement*>> CreateActorMovementVector(FlatBufferBuilder& fbb, const Array<SF::ActorMovement>& value)
            {
                std::vector<SF::Flat::ActorMovement> elems;
                elems.reserve(value.size());
                for (const SF::ActorMovement& item : value)
                {
                    elems.push_back(*CreateActorMovement(fbb, item));
                }
                return fbb.CreateVectorOfStructs(elems.data(), elems.size());
            }

            inline SF::ActorMovement ParseActorMovement(const SF::Flat::ActorMovement* value)
            {
                if (value == nullptr)
                    return {};

                SF::ActorMovement actorMovement{};
                actorMovement.ActorId = value->actor_id();
                actorMovement.AngularYaw = value->angular_yaw();
                actorMovement.Position = ParseVector4(&value->position());
                actorMovement.LinearVelocity = ParseVector4(&value->linear_velocity());
                actorMovement.MoveFrame = value->move_frame();
                actorMovement.MovementState = value->movement_state();

                return actorMovement;
            }

            inline Offset<::flatbuffers::Vector<uint8_t>> CreateVariableTable(FlatBufferBuilder& fbb, const SF::VariableTable& value)
            {
                SF::OutputMemoryStream out(GetSystemHeap());

                out << value;

                return fbb.CreateVector(out.data(), out.size());
            }

            inline Offset<::flatbuffers::Vector<uint8_t>> CreateVariableTableVector(FlatBufferBuilder& fbb, const Array<SF::VariableTable>& value)
            {
                SF::OutputMemoryStream out(GetSystemHeap());

                out << value;

                return fbb.CreateVector(out.data(), out.size());
            }

            inline SF::Result ParseVariableTable(const flatbuffers::Vector<uint8_t>* value, SF::VariableTable& outValue)
            {
                outValue.Clear();

                if (value == nullptr)
                    return SF::ResultCode::INVALID_POINTER;

                InputMemoryStream in(ArrayView<const uint8_t>(value->size(), value->data()));
                return in >> outValue;
            }

            inline SF::Result ParseVariableTableVector(const flatbuffers::Vector<uint8_t>* value, Array<SF::VariableTable>& outValue)
            {
                outValue.Clear();

                if (value == nullptr)
                    return SF::ResultCode::INVALID_POINTER;

                InputMemoryStream in(ArrayView<const uint8_t>(value->size(), value->data()));
                
                return in >> outValue;
            }


            inline FlatValueHolder<SF::Flat::MatchingQueueTicket> CreateMatchingQueueTicket(FlatBufferBuilder& fbb, const SF::MatchingQueueTicket& value)
            {
                return FlatValueHolder<SF::Flat::MatchingQueueTicket>(SF::Flat::MatchingQueueTicket(
                    value.QueueUID.ID, value.QueueItemID
                ));
            }

            inline Offset<Vector<const SF::Flat::MatchingQueueTicket*>> CreateMatchingQueueTicketVector(FlatBufferBuilder& fbb, const Array<SF::MatchingQueueTicket>& value)
            {
                std::vector<SF::Flat::MatchingQueueTicket> elems;
                elems.reserve(value.size());
                for (const SF::MatchingQueueTicket& item : value)
                {
                    ;
                    elems.push_back(*CreateMatchingQueueTicket(fbb, item));
                }

                return fbb.CreateVectorOfNativeStructs<SF::Flat::MatchingQueueTicket>(elems);
            }

            inline FlatValueHolder<SF::Flat::AchievementStat> CreateAchievementStat(FlatBufferBuilder& fbb, const SF::AchievementStat& value)
            {
                return FlatValueHolder<SF::Flat::AchievementStat>(
                    SF::Flat::AchievementStat(
                        value.AchievementStatId, value.StatValue
                    )
                );
            }

            inline Offset<Vector<const SF::Flat::AchievementStat*>> CreateAchievementStatVector(FlatBufferBuilder& fbb, const Array<SF::AchievementStat>& value)
            {
                std::vector<SF::Flat::AchievementStat> elems;
                elems.reserve(value.size());
                for (const SF::AchievementStat& item : value)
                {
                    elems.push_back(*CreateAchievementStat(fbb, item));
                }
                return fbb.CreateVectorOfStructs(elems.data(), elems.size());
            }

            inline Offset<SF::Flat::PlayerInformation> CreatePlayerInformation(FlatBufferBuilder& fbb, const SF::PlayerInformation& value)
            {
                SF::Flat::PlayerInformationBuilder builder(fbb);

                builder.add_player_id(CreatePlayerID(fbb, value.PlayerID));
                builder.add_player_platform_id(CreatePlayerPlatformID(fbb, value.PlayerPlatformId));
                builder.add_profile_name(CreateString(fbb, value.NickName));
                builder.add_last_active_time(value.LastActiveTime);

                return builder.Finish();
            }

            inline Offset<::flatbuffers::Vector<Offset<SF::Flat::PlayerInformation>>> CreatePlayerInformationVector(FlatBufferBuilder& fbb, const Array<SF::PlayerInformation>& value)
            {
                std::vector<Offset<SF::Flat::PlayerInformation>> elems;
                elems.reserve(value.size());
                for (const SF::PlayerInformation& item : value)
                {
                    elems.push_back(CreatePlayerInformation(fbb, item));
                }
                return fbb.CreateVector(elems.data(), elems.size());
            }

            inline SF::Result ParsePlayerInformation(const SF::Flat::PlayerInformation* value, SF::PlayerInformation& outPlayerInfo)
            {
                SF::Result hr;
                if (value == nullptr || value->profile_name() == nullptr)
                    return SF::ResultCode::INVALID_POINTER;

                outPlayerInfo.PlayerID = ParseAccountID(value->player_id());
                outPlayerInfo.PlayerPlatformId = ParsePlayerPlatformID(value->player_platform_id());
                StrUtil::StringCopy(outPlayerInfo.NickName, value->profile_name()->c_str());
                outPlayerInfo.LastActiveTime = value->last_active_time();

                return hr;
            }

            inline Offset<SF::Flat::TotalRankingPlayerInformation> CreateTotalRankingPlayerInformation(FlatBufferBuilder& fbb, const SF::TotalRankingPlayerInformation& value)
            {
                SF::Flat::TotalRankingPlayerInformationBuilder builder(fbb);

                builder.add_ranking_id(value.RankingID);
                builder.add_ranking(value.Ranking);
                builder.add_level(value.Level);
                builder.add_score_high(value.ScoreHigh);
                builder.add_score_low(value.ScoreLow);
                builder.add_player_id(CreatePlayerID(fbb, value.PlayerID));
                builder.add_player_platform_id(CreatePlayerPlatformID(fbb, value.PlayerPlatformId));
                builder.add_profile_name(CreateString(fbb, value.NickName));

                return builder.Finish();
            }

            inline Offset<::flatbuffers::Vector<Offset<SF::Flat::TotalRankingPlayerInformation>>> CreateTotalRankingPlayerInformationVector(FlatBufferBuilder& fbb, const Array<SF::TotalRankingPlayerInformation>& value)
            {
                std::vector<Offset<SF::Flat::TotalRankingPlayerInformation>> elems;
                elems.reserve(value.size());
                for (const SF::TotalRankingPlayerInformation& item : value)
                {
                    elems.push_back(CreateTotalRankingPlayerInformation(fbb, item));
                }
                return fbb.CreateVector(elems.data(), elems.size());
            }


            inline SF::Flat::GameStateID CreateGameStateID(FlatBufferBuilder& fbb, const SF::GameStateID& value)
            {
                return (SF::Flat::GameStateID)value;
            }

            inline SF::Flat::NotificationType CreateNotificationType(FlatBufferBuilder& fbb, const SF::NotificationType& value)
            {
                return (SF::Flat::NotificationType)value;
            }

            inline SF::Flat::PlayerRole CreatePlayerRole(FlatBufferBuilder& fbb, const SF::PlayerRole& value)
            {
                return (SF::Flat::PlayerRole)value;
            }

            inline SF::Flat::RankingType CreateRankingType(FlatBufferBuilder& fbb, const SF::RankingType& value)
            {
                return (SF::Flat::RankingType)value;
            }

            
        }
    }
} // SF



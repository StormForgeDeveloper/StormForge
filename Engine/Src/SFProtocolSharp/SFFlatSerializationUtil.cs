////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Flatbuffer serialization utility
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.IO;
using Google.FlatBuffers;


#nullable enable
namespace SF
{

    public static class SerializationUtil
    {
        public static VectorOffset CreateStringVector(this Google.FlatBuffers.FlatBufferBuilder builder, string[] data)
        {
            int[] offsets = new int[data.Length];
            for (int i = 0; i < data.Length; i++)
            {
                offsets[i] = builder.CreateString(data[i]).Value;
            }

            builder.StartVector(4, data.Length, 4);

            builder.Add(offsets);

            return builder.EndVector();
        }

        public static VectorOffset CreatebyteVector(this Google.FlatBuffers.FlatBufferBuilder builder, byte[] data)
        {
            builder.StartVector(1, data.Length, 1);

            builder.Add(data);

            return builder.EndVector();
        }

        public static VectorOffset Createuint32Vector(this Google.FlatBuffers.FlatBufferBuilder builder, UInt32[] data)
        {
            builder.StartVector(4, data.Length, 4);

            builder.Add(data);

            return builder.EndVector();
        }

        public static VectorOffset Createuint64Vector(this Google.FlatBuffers.FlatBufferBuilder builder, UInt64[] data)
        {
            builder.StartVector(4, data.Length, 4);

            builder.Add(data);

            return builder.EndVector();
        }

        public struct FlatValueTime32
        {
            public Google.FlatBuffers.FlatBufferBuilder Builder;
            public UInt32 Value;

            public FlatValueTime32(Google.FlatBuffers.FlatBufferBuilder builder, UInt32 value)
            {
                Builder = builder;
                Value = value;
            }

            public static implicit operator Offset<SF.Flat.Time32>(FlatValueTime32 value)
            {
                return SF.Flat.Time32.CreateTime32(value.Builder, value.Value);
            }
        }

        public static FlatValueTime32 CreateTime32(this Google.FlatBuffers.FlatBufferBuilder builder, UInt32 value)
        {
            return new FlatValueTime32(builder, value);
        }

        public static UInt32 Parse(this SF.Flat.Time32? value)
        {
            if (value == null)
                return 0;

            return value.Value.Time;
        }

        public struct FlatValueTime64
        {
            public Google.FlatBuffers.FlatBufferBuilder Builder;
            public UInt64 Value;

            public FlatValueTime64(Google.FlatBuffers.FlatBufferBuilder builder, UInt64 value)
            {
                Builder = builder;
                Value = value;
            }

            public static implicit operator Offset<SF.Flat.Time64>(FlatValueTime64 value)
            {
                return SF.Flat.Time64.CreateTime64(value.Builder, value.Value);
            }
        }

        public static FlatValueTime64 CreateTime64(this Google.FlatBuffers.FlatBufferBuilder builder, UInt64 value)
        {
            return new FlatValueTime64(builder, value);
        }

        public static UInt64 Parse(this SF.Flat.Time64? value)
        {
            if (value == null)
                return 0;

            return value.Value.Time;
        }


        public struct FlatValueTimeSpan
        {
            public Google.FlatBuffers.FlatBufferBuilder Builder;
            public SF.TimeSpan Value;

            public FlatValueTimeSpan(Google.FlatBuffers.FlatBufferBuilder builder, SF.TimeSpan value)
            {
                Builder = builder;
                Value = value;
            }

            public static implicit operator Offset<SF.Flat.TimeSpan>(FlatValueTimeSpan value)
            {
                return SF.Flat.TimeSpan.CreateTimeSpan(value.Builder, value.Value.MilliSeconds);
            }
        }

        public static FlatValueTimeSpan CreateTimeSpan(this Google.FlatBuffers.FlatBufferBuilder builder, SF.TimeSpan value)
        {
            return new FlatValueTimeSpan(builder, value);
        }

        public static SF.TimeSpan Parse(this SF.Flat.TimeSpan? value)
        {
            if (value == null)
                return default(SF.TimeSpan);

            return new SF.TimeSpan(value.Value.Milliseconds);
        }


        public struct FlatValueResult
        {
            public Google.FlatBuffers.FlatBufferBuilder Builder;
            public int Value;

            public FlatValueResult(Google.FlatBuffers.FlatBufferBuilder builder, int value)
            {
                Builder = builder;
                Value = value;
            }

            public static implicit operator Offset<SF.Flat.Result>(FlatValueResult value)
            {
                return SF.Flat.Result.CreateResult(value.Builder, value.Value);
            }
        }

        public static FlatValueResult CreateResult(this Google.FlatBuffers.FlatBufferBuilder builder, SF.Result value)
        {
            return new FlatValueResult(builder, value.Code);
        }

        public static SF.Result Parse(this SF.Flat.Result? value)
        {
            if (value == null)
                return default(SF.Result);

            return new SF.Result(value.Value.Value);
        }

        public struct FlatValueGameInstanceUID
        {
            public Google.FlatBuffers.FlatBufferBuilder Builder;
            public UInt32 Value;

            public FlatValueGameInstanceUID(Google.FlatBuffers.FlatBufferBuilder builder, UInt32 value)
            {
                Builder = builder;
                Value = value;
            }

            public static implicit operator Offset<SF.Flat.GameInstanceUID>(FlatValueGameInstanceUID value)
            {
                return SF.Flat.GameInstanceUID.CreateGameInstanceUID(value.Builder, value.Value);
            }
        }


        public static FlatValueGameInstanceUID CreateGameInstanceUID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.GameInstanceUID data)
        {
            return new FlatValueGameInstanceUID(builder, data.UID);
        }

        public static SF.GameInstanceUID Parse(this SF.Flat.GameInstanceUID? data)
        {
            if (data == null)
                return default(SF.GameInstanceUID);

            return new SF.GameInstanceUID(data.Value.Uid);
        }

        public static FlatValueGameInstanceUID CreateGameInsUID(this Google.FlatBuffers.FlatBufferBuilder builder, UInt32 data)
        {
            return new FlatValueGameInstanceUID(builder, data);
        }


        public struct FlatValueEntityUID
        {
            public Google.FlatBuffers.FlatBufferBuilder Builder;
            public UInt32 Value;

            public FlatValueEntityUID(Google.FlatBuffers.FlatBufferBuilder builder, UInt32 value)
            {
                Builder = builder;
                Value = value;
            }

            public static implicit operator Offset<SF.Flat.EntityUID>(FlatValueEntityUID value)
            {
                return SF.Flat.EntityUID.CreateEntityUID(value.Builder, value.Value);
            }
        }

        public static FlatValueEntityUID CreateEntityUID(this Google.FlatBuffers.FlatBufferBuilder builder, UInt32 data)
        {
            return new FlatValueEntityUID(builder, data);
        }

        public static SF.EntityUID Parse(this SF.Flat.EntityUID? data)
        {
            if (data == null)
                return default(SF.EntityUID);

            return new SF.EntityUID(data.Value.EntityId);
        }

        public static SF.GameInstanceUID ParseGameInstanceUID(this SF.Flat.EntityUID? data)
        {
            if (data == null)
                return default(SF.GameInstanceUID);

            return new SF.GameInstanceUID(data.Value.EntityId);
        }


        public struct FlatValueTransactionID
        {
            public Google.FlatBuffers.FlatBufferBuilder Builder;
            public SF.TransactionID Value;

            public FlatValueTransactionID(Google.FlatBuffers.FlatBufferBuilder builder, SF.TransactionID value)
            {
                Builder = builder;
                Value = value;
            }

            public static implicit operator Offset<SF.Flat.TransactionID>(FlatValueTransactionID value)
            {
                return SF.Flat.TransactionID.CreateTransactionID(value.Builder, value.Value.TransactionId);
            }
        }

        public static FlatValueTransactionID CreateTransactionID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.TransactionID data)
        {
            return new FlatValueTransactionID(builder, data);
        }

        public static SF.TransactionID Parse(this SF.Flat.TransactionID? data)
        {
            if (data == null)
                return default(SF.TransactionID);

            return new SF.TransactionID(data.Value.TransactionId);
        }


        public struct FlatValueAccountID
        {
            public Google.FlatBuffers.FlatBufferBuilder Builder;
            public SF.AccountID Value;

            public FlatValueAccountID(Google.FlatBuffers.FlatBufferBuilder builder, SF.AccountID value)
            {
                Builder = builder;
                Value = value;
            }

            public static implicit operator Offset<SF.Flat.AccountID>(FlatValueAccountID value)
            {
                var u128 = value.Value.ToUInt128();
                return SF.Flat.AccountID.CreateAccountID(value.Builder, u128.Low, u128.High);
            }
        }

        public static SF.Flat.EAccountRole CreateEAccountRole(this Google.FlatBuffers.FlatBufferBuilder builder, SF.EAccountRole value)
        {
            return (SF.Flat.EAccountRole)value;
        }

        public static FlatValueAccountID CreateAccountID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.AccountID accountId)
        {
            return new FlatValueAccountID(builder, accountId);
        }

        public static SF.AccountID Parse(this SF.Flat.AccountID value)
        {
            return new SF.AccountID(GuidHelper.FromLowHigh(value.Low, value.High));
        }

        public static SF.AccountID Parse(this SF.Flat.AccountID? value)
        {
            if (value.HasValue)
            {
                return Parse(value.Value);
            }
            else
            {
                return new SF.AccountID();
            }
        }


        public struct FlatValueCharacterID
        {
            public Google.FlatBuffers.FlatBufferBuilder Builder;
            public SF.CharacterID Value;

            public FlatValueCharacterID(Google.FlatBuffers.FlatBufferBuilder builder, SF.CharacterID value)
            {
                Builder = builder;
                Value = value;
            }

            public static implicit operator Offset<SF.Flat.CharacterID>(FlatValueCharacterID value)
            {
                var u128 = value.Value.ToUInt128();
                return SF.Flat.CharacterID.CreateCharacterID(value.Builder, u128.Low, u128.High);
            }
        }

        public static FlatValueCharacterID CreateCharacterID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.CharacterID characterId)
        {
            return new FlatValueCharacterID(builder, characterId);
        }

        public static SF.CharacterID Parse(this SF.Flat.CharacterID value)
        {
            return new SF.CharacterID(GuidHelper.FromLowHigh(value.Low, value.High));
        }

        public static SF.CharacterID Parse(this SF.Flat.CharacterID? value)
        {
            if (value.HasValue)
            {
                return Parse(value.Value);
            }
            else
            {
                return new SF.CharacterID();
            }
        }

        public static VectorOffset CreateAccountIDVector(this Google.FlatBuffers.FlatBufferBuilder builder, SF.AccountID[] data)
        {
            int[] offsets = new int[data.Length];
            for (int i = 0; i < data.Length; i++)
            {
                Offset<SF.Flat.AccountID> offset = CreateAccountID(builder, data[i]);
                offsets[i] = offset.Value;
            }
            builder.StartVector(4, data.Length, 4);

            builder.Add(offsets);

            return builder.EndVector();
        }

        public static byte[] ToByteArray(this SF.Flat.AccountID? value)
        {
            if (value.HasValue)
            {
                return GuidHelper.FromLowHigh(value.Value.Low, value.Value.High).ToByteArray();
            }
            else
            {
                return System.Guid.Empty.ToByteArray();
            }
        }

        public static SF.Flat.Platform CreatePlatform(this Google.FlatBuffers.FlatBufferBuilder builder, SF.EPlatform platform)
        {
            switch (platform)
            {
                case SF.EPlatform.Steam: return SF.Flat.Platform.Steam;
                case SF.EPlatform.BR: return SF.Flat.Platform.BR;
                case SF.EPlatform.Facebook: return SF.Flat.Platform.Facebook;
                default:
                    throw new NotImplementedException($"Unknown platform type:{platform}");
            }
        }
        public static SF.EPlatform Parse(this SF.Flat.Platform platform)
        {
            switch (platform)
            {
                case SF.Flat.Platform.Steam: return SF.EPlatform.Steam;
                case SF.Flat.Platform.BR: return SF.EPlatform.BR;
                case SF.Flat.Platform.Facebook: return SF.EPlatform.Facebook;
                default:
                    throw new NotImplementedException($"Unknown platform type:{platform}");
            }
        }


        public struct FlatValuePlayerPlatformID
        {
            public Google.FlatBuffers.FlatBufferBuilder Builder;
            public SF.PlayerPlatformID Value;

            public FlatValuePlayerPlatformID(Google.FlatBuffers.FlatBufferBuilder builder, SF.PlayerPlatformID value)
            {
                Builder = builder;
                Value = value;
            }

            public static implicit operator Offset<SF.Flat.PlayerPlatformID>(FlatValuePlayerPlatformID value)
            {
                var u128 = value.Value.PlayerID.ToUInt128();
                return SF.Flat.PlayerPlatformID.CreatePlayerPlatformID(value.Builder, u128.Low, u128.High, value.Builder.CreatePlatform(value.Value.Platform));
            }
        }

        public static FlatValuePlayerPlatformID CreatePlayerPlatformID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.PlayerPlatformID data)
        {
            return new FlatValuePlayerPlatformID(builder, data);
        }

        public static SF.PlayerPlatformID Parse(this SF.Flat.PlayerPlatformID? value)
        {
            if (value.HasValue)
            {
                return new SF.PlayerPlatformID()
                {
                    PlayerID = value.Value.PlayerId.Parse(),
                    Platform = value.Value.PlatformData.Parse()
                };
            }
            else
            {
                return new SF.PlayerPlatformID();
            }
        }

        public static FlatValueAccountID CreatePlayerID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.AccountID accountId)
        {
            return new FlatValueAccountID(builder, accountId);
        }

        //public static SF.AccountID Parse(this SF.Flat.AccountID? flatAccountId)
        //{
        //    return Parse(flatAccountId);
        //}

        public struct FlatValueGuid
        {
            public Google.FlatBuffers.FlatBufferBuilder Builder;
            public System.Guid Value;

            public FlatValueGuid(Google.FlatBuffers.FlatBufferBuilder builder, System.Guid value)
            {
                Builder = builder;
                Value = value;
            }

            public static implicit operator Offset<SF.Flat.Guid>(FlatValueGuid value)
            {
                var u128 = value.Value.ToUInt128();
                return SF.Flat.Guid.CreateGuid(value.Builder, u128.Low, u128.High);
            }
        }

        public static FlatValueGuid CreateGuid(this Google.FlatBuffers.FlatBufferBuilder builder, System.Guid guid)
        {
            return new FlatValueGuid(builder, guid);
        }

        public static System.Guid Parse(this SF.Flat.Guid? flatGuid)
        {
            if (flatGuid.HasValue)
            {
                return GuidHelper.FromLowHigh(flatGuid.Value.Low, flatGuid.Value.High);
            }
            else
            {
                return System.Guid.Empty;
            }
        }
        public static byte[] ToByteArray(this SF.Flat.Guid? value)
        {
            if (value.HasValue)
            {
                return GuidHelper.FromLowHigh(value.Value.Low, value.Value.High).ToByteArray();
            }
            else
            {
                return System.Guid.Empty.ToByteArray();
            }
        }


        public static VectorOffset Createuint8Vector(this Google.FlatBuffers.FlatBufferBuilder builder, byte[] data)
        {
            builder.StartVector(1, data.Length, 1);

            for (int i = data.Length - 1; i >= 0; i--)
                builder.AddByte(data[i]);

            return builder.EndVector();
        }

        public static Offset<SF.Flat.NamedVariable> CreateNamedVariable(this Google.FlatBuffers.FlatBufferBuilder builder, SF.NamedVariable data)
        {
            int valueOffset = 0;
            var nameOffset = builder.CreateString(data.Name);
            SF.Flat.NamedVariableValue ValueType = SF.Flat.NamedVariableValue.NONE;
            if (data.Value == null)
            {
                ValueType = SF.Flat.NamedVariableValue.NONE;
                valueOffset = 0;
            }
            else
            {
                switch (data.Value.GetType().Name.ToLower())
                {
                    case "string":
                        ValueType = SF.Flat.NamedVariableValue.NamedVariableInt;
                        valueOffset = SF.Flat.NamedVariableInt.CreateNamedVariableInt(builder, (int)data.Value).Value;
                        break;
                    case "int":
                    case "int32":
                    case "system.int32":
                        ValueType = SF.Flat.NamedVariableValue.NamedVariableInt;
                        valueOffset = SF.Flat.NamedVariableInt.CreateNamedVariableInt(builder, (int)data.Value).Value;
                        break;
                    case "uint":
                    case "uint32":
                    case "system.uint32":
                        ValueType = SF.Flat.NamedVariableValue.NamedVariableUInt;
                        valueOffset = SF.Flat.NamedVariableUInt.CreateNamedVariableUInt(builder, (uint)data.Value).Value;
                        break;
                    case "int64":
                    case "system.int64":
                    case "long":
                        ValueType = SF.Flat.NamedVariableValue.NamedVariableInt64;
                        valueOffset = SF.Flat.NamedVariableInt64.CreateNamedVariableInt64(builder, (long)data.Value).Value;
                        break;
                    case "uint64":
                    case "system.uint64":
                    case "ulong":
                        ValueType = SF.Flat.NamedVariableValue.NamedVariableUInt64;
                        valueOffset = SF.Flat.NamedVariableUInt64.CreateNamedVariableUInt64(builder, (ulong)data.Value).Value;
                        break;
                    case "float":
                        ValueType = SF.Flat.NamedVariableValue.NamedVariableFloat;
                        valueOffset = SF.Flat.NamedVariableFloat.CreateNamedVariableFloat(builder, (float)data.Value).Value;
                        break;
                    case "double":
                        ValueType = SF.Flat.NamedVariableValue.NamedVariableDouble;
                        valueOffset = SF.Flat.NamedVariableDouble.CreateNamedVariableDouble(builder, (double)data.Value).Value;
                        break;
                    default:
                        // UnknownType
                        return default(Offset<SF.Flat.NamedVariable>);
                }
            }

            SF.Flat.NamedVariable.StartNamedVariable(builder);
            SF.Flat.NamedVariable.AddName(builder, nameOffset);
            SF.Flat.NamedVariable.AddValueType(builder, ValueType);
            SF.Flat.NamedVariable.AddValue(builder, valueOffset);

            return SF.Flat.NamedVariable.EndNamedVariable(builder);
        }

        public static VectorOffset CreateNamedVariableVector(this Google.FlatBuffers.FlatBufferBuilder builder, SF.NamedVariable[] data)
        {
            Offset<SF.Flat.NamedVariable>[] offsets = new Offset<SF.Flat.NamedVariable>[data.Length];
            for (int i = 0; i < data.Length; i++)
            {
                offsets[i] = builder.CreateNamedVariable(data[i]);
            }

            builder.StartVector(4, data.Length, 4);

            builder.Add(offsets);

            return builder.EndVector();
        }
        public static Offset<SF.Flat.MatchingQueueTicket> CreateMatchingQueueTicket(this Google.FlatBuffers.FlatBufferBuilder builder, SF.MatchingQueueTicket data)
        {
            return SF.Flat.MatchingQueueTicket.CreateMatchingQueueTicket(builder, data.QueueUID, data.QueueItemID);
        }

        public static VectorOffset CreateMatchingQueueTicketVector(this Google.FlatBuffers.FlatBufferBuilder builder, SF.MatchingQueueTicket[]? value)
        {
            if (value == null)
                return default(VectorOffset);

            Offset<SF.Flat.MatchingQueueTicket>[] offsets = new Offset<SF.Flat.MatchingQueueTicket>[value.Length];
            for (int iObject = 0; iObject < value.Length; iObject++)
            {
                offsets[iObject] = builder.CreateMatchingQueueTicket(value[iObject]);
            }

            builder.StartVector(4, offsets.Length, 4);
            for (int iObject = 0; iObject < offsets.Length; iObject++)
            {
                builder.AddOffset(offsets[iObject].Value);
            }
            return builder.EndVector();
        }

        public static Offset<SF.Flat.AchievementStat> CreateAchievementStat(this Google.FlatBuffers.FlatBufferBuilder builder, SF.AchievementStat data)
        {
            return SF.Flat.AchievementStat.CreateAchievementStat(builder, data.AchievementStatId, data.StatValue);
        }

        public static SF.AchievementStat Parse(this SF.Flat.AchievementStat? value)
        {
            if (value.HasValue)
            {
                return new SF.AchievementStat()
                {
                    AchievementStatId = value.Value.AchievementStatId,
                    StatValue = value.Value.StatValue
                };
            }
            else
            {
                return default(SF.AchievementStat);
            }
        }

        public static VectorOffset CreateAchievementStatVector(this Google.FlatBuffers.FlatBufferBuilder builder, SF.AchievementStat[] data)
        {
            Offset<SF.Flat.AchievementStat>[] offsets = new Offset<SF.Flat.AchievementStat>[data.Length];
            for (int i = 0; i < data.Length; i++)
            {
                offsets[i] = builder.CreateAchievementStat(data[i]);
            }

            builder.StartVector(4, data.Length, 4);

            for (int i = data.Length - 1; i >= 0; i--)
            {
                builder.AddOffset(offsets[i].Value);
            }

            return builder.EndVector();
        }

        public static VectorOffset CreateVariableTable(this Google.FlatBuffers.FlatBufferBuilder builder, SF.VariableTable data)
        {
            byte[] binaryData = data.ToByteArray();

            builder.StartVector(1, binaryData.Length, 1);

            builder.Add(binaryData);

            return builder.EndVector();
        }

        public static SF.VariableTable ParseVariableTable(this byte[] value)
        {
            SF.VariableTable variableTable = new();
            variableTable.FromByteArray(value);
            return variableTable;
        }

        public static VectorOffset CreateVariableTableVector(this Google.FlatBuffers.FlatBufferBuilder builder, SF.VariableTable[] data)
        {
            byte[]? binaryData = null;
            using (MemoryStream outputStream = new MemoryStream())
            using (BinaryWriter writer = new BinaryWriter(outputStream))
            {
                writer.Write((ushort)data.Length);

                foreach (var varTable in data)
                {
                    varTable.ToBinary(writer);
                }

                writer.Flush();
                binaryData = outputStream.ToArray();
            }

            builder.StartVector(1, binaryData.Length, 1);

            builder.Add(binaryData);

            return builder.EndVector();
        }
        public static SF.VariableTable[] ParseVariableTableVector(this byte[] value)
        {
            using (BinaryReader reader = new BinaryReader(new MemoryStream(value)))
            {
                UInt16 numItems = reader.ReadUInt16();

                SF.VariableTable[] variableTables = new SF.VariableTable[numItems];
                for (int iItem = 0; iItem < numItems; iItem++)
                {
                    variableTables[iItem] = new VariableTable();
                    variableTables[iItem].FromBinary(reader);
                }

                return variableTables;
            }
        }

        public static Offset<SF.Flat.PlayerInformation> CreatePlayerInformation(this Google.FlatBuffers.FlatBufferBuilder builder, SF.PlayerInformation data)
        {
            var playerIdOffset = builder.CreateAccountID(data.PlayerID);
            var playerPlatformIdOffset = builder.CreatePlayerPlatformID(data.PlayerPlatformId);
            var playerNameOffset = builder.CreateString(data.NickName);

            SF.Flat.PlayerInformation.StartPlayerInformation(builder);
            SF.Flat.PlayerInformation.AddPlayerId(builder, playerIdOffset);
            SF.Flat.PlayerInformation.AddPlayerPlatformId(builder, playerPlatformIdOffset);
            SF.Flat.PlayerInformation.AddProfileName(builder, playerNameOffset);
            SF.Flat.PlayerInformation.AddLastActiveTime(builder, data.LastActiveTime);
            return SF.Flat.PlayerInformation.EndPlayerInformation(builder);
        }

        public static SF.PlayerInformation Parse(this SF.Flat.PlayerInformation? value)
        {
            if (value.HasValue)
            {
                return new SF.PlayerInformation()
                {
                    PlayerID = value.Value.PlayerId.Parse(),
                    PlayerPlatformId = value.Value.PlayerPlatformId.Parse(),
                    NickName = value.Value.ProfileName,
                    LastActiveTime = value.Value.LastActiveTime,
                };
            }
            else
            {
                return new SF.PlayerInformation();
            }
        }

        public static VectorOffset CreatePlayerInformationVector(this Google.FlatBuffers.FlatBufferBuilder builder, SF.PlayerInformation[] data)
        {
            Offset<SF.Flat.PlayerInformation>[] offsets = new Offset<SF.Flat.PlayerInformation>[data.Length];
            for (int i = 0; i < data.Length; i++)
            {
                offsets[i] = builder.CreatePlayerInformation(data[i]);
            }

            builder.StartVector(4, data.Length, 4);

            builder.Add(offsets);

            return builder.EndVector();
        }

        public static Offset<SF.Flat.TotalRankingPlayerInformation> CreateTotalRankingPlayerInformation(this Google.FlatBuffers.FlatBufferBuilder builder, SF.TotalRankingPlayerInformation data)
        {
            var playerIdOffset = builder.CreateAccountID(data.PlayerID);
            var playerPlatformIdOffset = builder.CreatePlayerPlatformID(data.PlayerPlatformId);
            var playerNameOffset = builder.CreateString(data.ProfileName);

            SF.Flat.TotalRankingPlayerInformation.StartTotalRankingPlayerInformation(builder);
            SF.Flat.TotalRankingPlayerInformation.AddPlayerId(builder, playerIdOffset);
            SF.Flat.TotalRankingPlayerInformation.AddPlayerPlatformId(builder, playerPlatformIdOffset);
            SF.Flat.TotalRankingPlayerInformation.AddProfileName(builder, playerNameOffset);
            // TODO: Other informations are planed to be changed
            return SF.Flat.TotalRankingPlayerInformation.EndTotalRankingPlayerInformation(builder);
        }

        public static VectorOffset CreateTotalRankingPlayerInformationVector(this Google.FlatBuffers.FlatBufferBuilder builder, SF.TotalRankingPlayerInformation[] data)
        {
            Offset<SF.Flat.TotalRankingPlayerInformation>[] offsets = new Offset<SF.Flat.TotalRankingPlayerInformation>[data.Length];
            for (int i = 0; i < data.Length; i++)
            {
                offsets[i] = builder.CreateTotalRankingPlayerInformation(data[i]);
            }

            builder.StartVector(4, data.Length, 4);

            builder.Add(offsets);

            return builder.EndVector();
        }

        public static SF.Flat.GameStateID CreateGameStateID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.GameStateID data)
        {
            return (SF.Flat.GameStateID)data;
        }


        public struct FlatValueVector4
        {
            public Google.FlatBuffers.FlatBufferBuilder Builder;
            public SF.SFVector4 Value;

            public FlatValueVector4(Google.FlatBuffers.FlatBufferBuilder builder, SF.SFVector4 value)
            {
                Builder = builder;
                Value = value;
            }

            public static implicit operator Offset<SF.Flat.Vector4>(FlatValueVector4 value)
            {
                return SF.Flat.Vector4.CreateVector4(value.Builder, value.Value.x, value.Value.y, value.Value.z, value.Value.w);
            }
        }

        public static FlatValueVector4 CreateVector4(this Google.FlatBuffers.FlatBufferBuilder builder, SF.SFVector4 data)
        {
            return new FlatValueVector4(builder, data);
        }

        public static SF.SFVector4 Parse(this SF.Flat.Vector4 value)
        {
            return new SF.SFVector4()
            {
                x = value.X,
                y = value.Y,
                z = value.Z,
                w = value.W
            };
        }

        public static SF.SFVector4 Parse(this SF.Flat.Vector4? value)
        {
            if (value == null)
                return default(SF.SFVector4);

            return Parse(value.Value);
        }

        public static Offset<SF.Flat.ActorMovement> CreateActorMovement(this Google.FlatBuffers.FlatBufferBuilder builder, SF.ActorMovement data)
        {
            //ActorMovement.StartActorMovement(builder);

            //ActorMovement.AddActorId(builder, data.ActorId);
            //ActorMovement.AddPosition(builder, CreateVector4(builder, data.Position));
            //ActorMovement.AddLinearVelocity(builder, CreateVector4(builder, data.LinearVelocity));
            //ActorMovement.AddAngularYaw(builder, data.AngularYaw);
            //ActorMovement.AddMoveFrame(builder, data.MoveFrame);
            //ActorMovement.AddMovementState(builder, data.MovementState);

            //return ActorMovement.EndActorMovement(builder);

            return SF.Flat.ActorMovement.CreateActorMovement(builder,
                data.Position.x, data.Position.y, data.Position.z, data.Position.w,
                data.LinearVelocity.x, data.LinearVelocity.y, data.LinearVelocity.z, data.LinearVelocity.w,
                data.ActorId, data.AngularYaw, data.MoveFrame, data.MovementState
                );
        }

        public static SF.ActorMovement Parse(this SF.Flat.ActorMovement? value)
        {
            if (value == null)
                return default(SF.ActorMovement);

            return new SF.ActorMovement()
            {
                Position = value.Value.Position.Parse(),
                LinearVelocity = value.Value.LinearVelocity.Parse(),
                ActorId = value.Value.ActorId,
                AngularYaw = value.Value.AngularYaw,
                MoveFrame = value.Value.MoveFrame,
                MovementState = value.Value.MovementState,
            };
        }

        public static VectorOffset CreateActorMovementVector(this Google.FlatBuffers.FlatBufferBuilder builder, SF.ActorMovement[] data)
        {
            Offset<SF.Flat.ActorMovement>[] offsets = new Offset<SF.Flat.ActorMovement>[data.Length];
            for (int i = 0; i < data.Length; i++)
            {
                offsets[i] = builder.CreateActorMovement(data[i]);
            }

            builder.StartVector(4, data.Length, 4);

            builder.Add(offsets);

            return builder.EndVector();
        }


    }


}

#nullable restore

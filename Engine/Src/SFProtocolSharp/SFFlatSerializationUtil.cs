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

        public static Offset<SF.Flat.Time32> CreateTime32(this Google.FlatBuffers.FlatBufferBuilder builder, UInt32 value)
        {
            return builder.CreateTime32(value);
        }

        public static UInt32 Parse(this SF.Flat.Time32? value)
        {
            if (value == null)
                return 0;

            return value.Value.Time;
        }

        public static Offset<SF.Flat.Time64> CreateTime64(this Google.FlatBuffers.FlatBufferBuilder builder, UInt64 value)
        {
            return builder.CreateTime64(value);
        }

        public static UInt64 Parse(this SF.Flat.Time64? value)
        {
            if (value == null)
                return 0;

            return value.Value.Time;
        }

        public static Offset<SF.Flat.TimeSpan> CreateTimeSpan(this Google.FlatBuffers.FlatBufferBuilder builder, SF.TimeSpan value)
        {
            return CreateTimeSpan(builder, value);
        }

        public static SF.TimeSpan Parse(this SF.Flat.TimeSpan? value)
        {
            if (value == null)
                return default(SF.TimeSpan);

            return new SF.TimeSpan(value.Value.Milliseconds);
        }

        public static Offset<SF.Flat.Result> CreateResult(this Google.FlatBuffers.FlatBufferBuilder builder, SF.Result value)
        {
            return SF.Flat.Result.CreateResult(builder, value.Code);
        }

        public static SF.Result Parse(this SF.Flat.Result? value)
        {
            if (value == null)
                return default(SF.Result);

            return new SF.Result(value.Value.Value);
        }


        public static Offset<SF.Flat.GameInstanceUID> CreateGameInstanceUID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.GameInstanceUID data)
        {
            return SF.Flat.GameInstanceUID.CreateGameInstanceUID(builder, data.UID);
        }

        public static SF.GameInstanceUID Parse(this SF.Flat.GameInstanceUID? data)
        {
            if (data == null)
                return default(SF.GameInstanceUID);

            return new SF.GameInstanceUID(data.Value.Uid);
        }


        public static Offset<SF.Flat.GameInstanceUID> CreateGameInsUID(this Google.FlatBuffers.FlatBufferBuilder builder, UInt32 data)
        {
            return SF.Flat.GameInstanceUID.CreateGameInstanceUID(builder, data);
        }

        public static Offset<SF.Flat.EntityUID> CreateEntityUID(this Google.FlatBuffers.FlatBufferBuilder builder, UInt32 data)
        {
            return SF.Flat.EntityUID.CreateEntityUID(builder, data);
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

        public static Offset<SF.Flat.TransactionID> CreateTransactionID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.TransactionID data)
        {
            return SF.Flat.TransactionID.CreateTransactionID(builder, data.TransactionId);
        }

        public static SF.TransactionID Parse(this SF.Flat.TransactionID? data)
        {
            if (data == null)
                return default(SF.TransactionID);

            return new SF.TransactionID(data.Value.TransactionId);
        }

        public static Offset<SF.Flat.AccountID> CreateAccountID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.AccountID accountId)
        {
            var u128 = accountId.ToUInt128();
            return SF.Flat.AccountID.CreateAccountID(builder, u128.Low, u128.High);
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
        public static Offset<SF.Flat.CharacterID> CreateCharacterID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.CharacterID characterId)
        {
            var u128 = characterId.ToUInt128();
            return SF.Flat.CharacterID.CreateCharacterID(builder, u128.Low, u128.High);
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
                offsets[i] = builder.CreateAccountID(data[i]).Value;
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


        public static Offset<SF.Flat.PlayerPlatformID> CreatePlayerPlatformID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.PlayerPlatformID data)
        {
            var u128 = data.PlayerID.ToUInt128();
            return SF.Flat.PlayerPlatformID.CreatePlayerPlatformID(builder, u128.Low, u128.High, builder.CreatePlatform(data.Platform));
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

        public static Offset<SF.Flat.AccountID> CreatePlayerID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.AccountID accountId)
        {
            return CreateAccountID(builder, accountId);
        }

        //public static SF.AccountID Parse(this SF.Flat.AccountID? flatAccountId)
        //{
        //    return Parse(flatAccountId);
        //}

        public static Offset<SF.Flat.Guid> CreateGuid(this Google.FlatBuffers.FlatBufferBuilder builder, System.Guid guid)
        {
            var u128 = guid.ToUInt128();
            return SF.Flat.Guid.CreateGuid(builder, u128.Low, u128.High);
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

        public static Offset<SF.Flat.Vector4> CreateVector4(this Google.FlatBuffers.FlatBufferBuilder builder, SF.SFVector4 data)
        {
            // TODO: optimize position data
            return SF.Flat.Vector4.CreateVector4(builder, data.x, data.y, data.z, data.w);
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

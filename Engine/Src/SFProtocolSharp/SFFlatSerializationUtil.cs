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
using System.Reflection.Metadata;
using System.Runtime.InteropServices;
using System.Text;
using Google.FlatBuffers;


#nullable enable
namespace SF.Flat
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

        public static Offset<SF.Flat.Time64> CreateTime64(this Google.FlatBuffers.FlatBufferBuilder builder, UInt64 value)
        {
            return builder.CreateTime64(value);
        }

        public static Offset<SF.Flat.TimeSpan> CreateTimeSpan(this Google.FlatBuffers.FlatBufferBuilder builder, SF.TimeSpan value)
        {
            return CreateTimeSpan(builder, value);
        }


        public static Offset<SF.Flat.GameInstanceUID> CreateGameInstanceUID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.GameInstanceUID data)
        {
            return GameInstanceUID.CreateGameInstanceUID(builder, data.UID);
        }

        public static Offset<SF.Flat.GameInstanceUID> CreateGameInsUID(this Google.FlatBuffers.FlatBufferBuilder builder, UInt32 data)
        {
            return GameInstanceUID.CreateGameInstanceUID(builder, data);
        }

        public static Offset<SF.Flat.EntityUID> CreateEntityUID(this Google.FlatBuffers.FlatBufferBuilder builder, UInt32 data)
        {
            return EntityUID.CreateEntityUID(builder, data);
        }

        public static Offset<SF.Flat.TransactionID> CreateTransactionID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.TransactionID data)
        {
            return TransactionID.CreateTransactionID(builder, data.TransactionId);
        }

        public static Offset<SF.Flat.AccountID> CreateAccountID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.AccountID accountId)
        {
            var u128 = accountId.ToUInt128();
            return AccountID.CreateAccountID(builder, u128.Low, u128.High);
        }

        public static Offset<SF.Flat.CharacterID> CreateCharacterID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.CharacterID characterId)
        {
            var u128 = characterId.ToUInt128();
            return CharacterID.CreateCharacterID(builder, u128.Low, u128.High);
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

        public static SF.AccountID ToSystemAccountID(this SF.Flat.AccountID? value)
        {
            if (value.HasValue)
            {
                return new SF.AccountID(SF.SFUInt128.ToGuid(value.Value.Low, value.Value.High));
            }
            else
            {
                return new SF.AccountID();
            }
        }
        public static byte[] ToByteArray(this SF.Flat.AccountID? value)
        {
            if (value.HasValue)
            {
                return SF.SFUInt128.ToGuid(value.Value.Low, value.Value.High).ToByteArray();
            }
            else
            {
                return System.Guid.Empty.ToByteArray();
            }
        }

        public static SF.Flat.Platform ToFlatPlatform(SF.EPlatform platform)
        {
            switch(platform)
            {
                case SF.EPlatform.Steam: return SF.Flat.Platform.Steam;
                case SF.EPlatform.BR: return SF.Flat.Platform.BR;
                case SF.EPlatform.Facebook: return SF.Flat.Platform.Facebook;
                default:
                    throw new NotImplementedException($"Unknown platform type:{platform}");
            }
        }
        public static SF.EPlatform ToSystemPlatform(SF.Flat.Platform platform)
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
            return PlayerPlatformID.CreatePlayerPlatformID(builder, u128.Low, u128.High, ToFlatPlatform(data.Platform));
        }

        public static Offset<SF.Flat.AccountID> CreatePlayerID(this Google.FlatBuffers.FlatBufferBuilder builder, SF.AccountID accountId)
        {
            return CreateAccountID(builder, accountId);
        }

        public static SF.AccountID ToSystemPlayerID(this SF.Flat.AccountID? flatAccountId)
        {
            return ToSystemAccountID(flatAccountId);
        }

        public static Offset<SF.Flat.Guid> CreateGuid(this Google.FlatBuffers.FlatBufferBuilder builder, System.Guid guid)
        {
            var u128 = SFUInt128.FromGuid(guid);
            return Guid.CreateGuid(builder, u128.Low, u128.High);
        }

        public static System.Guid ToSystemGuid(this SF.Flat.Guid? flatGuid)
        {
            if (flatGuid.HasValue)
            {
                return SF.SFUInt128.ToGuid(flatGuid.Value.Low, flatGuid.Value.High);
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
                return SF.SFUInt128.ToGuid(value.Value.Low, value.Value.High).ToByteArray();
            }
            else
            {
                return System.Guid.Empty.ToByteArray();
            }
        }

        public static Offset<SF.Flat.RouteContext> CreateRouteContext(this Google.FlatBuffers.FlatBufferBuilder builder, SFRouteContext context)
        {
            return RouteContext.CreateRouteContext(builder, (uint)context.From, (uint)(context.From >> 32), (uint)context.To, (uint)(context.To >> 32));
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
            NamedVariableValue ValueType = NamedVariableValue.NONE;
            if (data.Value == null)
            {
                ValueType = NamedVariableValue.NONE;
                valueOffset = 0;
            }
            else
            {
                switch (data.Value.GetType().Name.ToLower())
                {
                    case "string":
                        ValueType = NamedVariableValue.NamedVariableInt;
                        valueOffset = SF.Flat.NamedVariableInt.CreateNamedVariableInt(builder, (int)data.Value).Value;
                        break;
                    case "int":
                    case "int32":
                    case "system.int32":
                        ValueType = NamedVariableValue.NamedVariableInt;
                        valueOffset = SF.Flat.NamedVariableInt.CreateNamedVariableInt(builder, (int)data.Value).Value;
                        break;
                    case "uint":
                    case "uint32":
                    case "system.uint32":
                        ValueType = NamedVariableValue.NamedVariableUInt;
                        valueOffset = SF.Flat.NamedVariableUInt.CreateNamedVariableUInt(builder, (uint)data.Value).Value;
                        break;
                    case "int64":
                    case "system.int64":
                    case "long":
                        ValueType = NamedVariableValue.NamedVariableInt64;
                        valueOffset = SF.Flat.NamedVariableInt64.CreateNamedVariableInt64(builder, (long)data.Value).Value;
                        break;
                    case "uint64":
                    case "system.uint64":
                    case "ulong":
                        ValueType = NamedVariableValue.NamedVariableUInt64;
                        valueOffset = SF.Flat.NamedVariableUInt64.CreateNamedVariableUInt64(builder, (ulong)data.Value).Value;
                        break;
                    case "float":
                        ValueType = NamedVariableValue.NamedVariableFloat;
                        valueOffset = SF.Flat.NamedVariableFloat.CreateNamedVariableFloat(builder, (float)data.Value).Value;
                        break;
                    case "double":
                        ValueType = NamedVariableValue.NamedVariableDouble;
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
            return MatchingQueueTicket.CreateMatchingQueueTicket(builder, data.QueueUID, data.QueueItemID);
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
            return AchievementStat.CreateAchievementStat(builder, data.AchievementStatId, data.StatValue);
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

        public static Offset<SF.Flat.PlayerInformation> CreatePlayerInformation(this Google.FlatBuffers.FlatBufferBuilder builder, SF.PlayerInformation data)
        {
            var playerIdOffset = builder.CreateAccountID(data.PlayerID);
            var playerPlatformIdOffset = builder.CreatePlayerPlatformID(data.PlayerPlatformId);
            var playerNameOffset = builder.CreateString(data.NickName);

            PlayerInformation.StartPlayerInformation(builder);
            PlayerInformation.AddPlayerId(builder, playerIdOffset);
            PlayerInformation.AddPlayerPlatformId(builder, playerPlatformIdOffset);
            PlayerInformation.AddProfileName(builder, playerNameOffset);
            PlayerInformation.AddLastActiveTime(builder, data.LastActiveTime);
            return PlayerInformation.EndPlayerInformation(builder);
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

            TotalRankingPlayerInformation.StartTotalRankingPlayerInformation(builder);
            TotalRankingPlayerInformation.AddPlayerId(builder, playerIdOffset);
            TotalRankingPlayerInformation.AddPlayerPlatformId(builder, playerPlatformIdOffset);
            TotalRankingPlayerInformation.AddProfileName(builder, playerNameOffset);
            // TODO: Other informations are planed to be changed
            return TotalRankingPlayerInformation.EndTotalRankingPlayerInformation(builder);
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

        public static Offset<SF.Flat.Vector4> CreateVector4(this Google.FlatBuffers.FlatBufferBuilder builder, SF.Vector4 data)
        {
            // TODO: optimize position data
            return Vector4.CreateVector4(builder, data.x, data.y, data.z, data.w);
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

            return ActorMovement.CreateActorMovement(builder,
                data.Position.x, data.Position.y, data.Position.z, data.Position.w,
                data.LinearVelocity.x, data.LinearVelocity.y, data.LinearVelocity.z, data.LinearVelocity.w,
                data.ActorId, data.AngularYaw, data.MoveFrame, data.MovementState
                );
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

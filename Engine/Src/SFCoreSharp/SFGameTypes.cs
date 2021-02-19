////////////////////////////////////////////////////////////////////////////////
//
// CopyRight (c) 2016 Kyungkun Ko
//
// Author : KyungKun Ko
//
// Description : Game types not important
//
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.CodeDom;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;


namespace SF
{
    using GameInstanceID = System.UInt64;

    // structure data type attribute, this is used for message builder
    public class StructAttribute : Attribute
    {
    }

    public class NativeWrapperAttribute : Attribute
    {
    }

    [Struct()]
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector2
    {
        public float x;
        public float y;
    };

    [Struct()]
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector3
    {
        public float x;
        public float y;
        public float z;
    };


    // Manages pinned byte buffer
    public class PinnedByteBuffer : IDisposable
    {
        public GCHandle Handle { get; }
        public byte[] Data { get; private set; }

        public IntPtr Ptr
        {
            get
            {
                return Handle.AddrOfPinnedObject();
            }
        }

        public PinnedByteBuffer(byte[] bytes)
        {
            Data = bytes;
            Handle = GCHandle.Alloc(bytes, GCHandleType.Pinned);
        }

        public void Dispose()
        {
            Handle.Free();
            Data = null;
            GC.SuppressFinalize(this);
        }
    }


    // Player Role
    public enum PlayerRole
    {
        None,
        Villager,
        Werewolf,
        Seer,
    }


    // Ranking type
    public enum RankingType
    {
        //Friend,
        World,
    };


    // Notification message
    public enum NotificationType
    {
        None,				// Not used
		MessageNotify,
		FriendRequest,
		GiftStamina,
	};


    // Game flow state for Lupus in Tabula
    public enum GameStateID
    {
        None,
        FreeDebate,
        //FirstNightVote,
        //SecondNightVote, 
        NightVote,
        //Mythomaniac,
        MorningDebate,
        VoteForSuspects,
        DefenceOfSuspects,
        VoteForHanging,
        End,
        Hanging,
        Max,
    };

    // Game Winner
    public enum GameWinner
    {
        None,
        Werewolf,
        Villager,
        WereHamster,
    };

    // 
    public enum PlayerKilledReason
    {
        Unknown,
        BlockedByBoardGuard,
        ByWerewolf,
        ByHanging,
    };

    // 
    public enum PlayerRevealedReason
    {
        None,
        Werewolf,
        SeersChoice,
        Medium,
        GameEnd,
    };


    public enum ChatType// : UINT16
    {
        Normal,         // Normal chat message
        Whisper,        // Whisper
        Info,           // Information
        System,         // System
        Role,           // Role chat in game
    };




    public static class GameTypes
    {
        // cast enum array to int
        static public int[] ToIntArray<EnumType>(EnumType[] array) where EnumType : struct, IConvertible
        {
            var newArray = new int[array.Length];
            for (int iEle = 0; iEle < array.Length; iEle++)
            {
                newArray[iEle] = Convert.ToInt32(array[iEle]);
            }
            return newArray;
        }

    }


    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public struct SFUInt128
    {
        public UInt64 Low;
        public UInt64 High;
    }

    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public struct MatchingQueueTicket
    {
        public UInt64 QueueUID;
        public UInt64 QueueItemID;
    }

    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public class FriendInformation : RankingPlayerInformation
    {
        public ulong LastStaminaSent;

        public FriendInformation()
        {
        }

        public FriendInformation(ulong playerID, ulong fbUID, String nickName, ulong lastActiveTime, uint level, int playingGame, int weeklyWin, int weeklyLose, ulong lastStaminaSent)
            : base(playerID, fbUID, nickName, lastActiveTime, level, playingGame, weeklyWin, weeklyLose)
        {
            LastStaminaSent = lastStaminaSent;
        }
    }


    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public struct NetAddress
    {
        public enum SockFamilyType : byte
        {
            None,
            IPV4,// = AF_INET,
            IPV6,// = AF_INET6
        }

        //[MarshalAs(UnmanagedType.LPStr)]
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 70)]
        public String Address;
        public ushort Port;
        public SockFamilyType SockFamily;

        //public SFNetAddress()
        //{
        //    SockFamily = SockFamilyType.None;
        //    Address = "";
        //    Port = 0;
        //}

        public NetAddress(int sockFamily, String address, int port)
        {
            SockFamily = (SockFamilyType)Enum.GetValues(typeof(SockFamilyType)).GetValue(sockFamily);
            Address = address;
            Port = (ushort)port;
        }

        public bool Parse(string addressString)
        {
            var splited = addressString.Split(new char[] { ',', ':' });
            if (splited == null || splited.Length != 2)
                return false;

            Address = splited[0];
            return ushort.TryParse(splited[1], out Port);
        }

        public override string ToString()
        {
            return string.Format("{0},{1}", Address, Port);
        }

    }

    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public class PlayerInformation
    {
        public ulong PlayerID;
        public ulong FBUID;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] NickNameBytes;
        public ulong LastActiveTime;
        public uint Level;
        public int IsPlayingGame;

        public string NickName
        {
            get
            {
                if (NickNameBytes == null) return null;
                var index = Array.FindIndex(NickNameBytes, x => x == 0);
                if (index < 0) index = NickNameBytes.Length;
                return System.Text.Encoding.UTF8.GetString(NickNameBytes, 0, index);
            }
            set
            {
                if (NickNameBytes == null || NickNameBytes.Length != 64)
                    NickNameBytes = new byte[64];

                System.Text.Encoding.UTF8.GetBytes(value, 0, value.Length, NickNameBytes, 0);
            }
        }

        public PlayerInformation()
        {
        }

        public PlayerInformation(ulong playerID, ulong fbUID, string nickName, ulong lastActiveTime, uint level, int playingGame)
        {
            PlayerID = playerID;
            FBUID = fbUID;
            NickName = nickName;
            LastActiveTime = lastActiveTime;
            Level = level;
            IsPlayingGame = playingGame;
        }
    }


    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public struct GameInstanceInfo
    {
        GameInstanceID GameInstanceID;
        StringCrc32 Type;
        StringCrc32 Name;
    }


    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public struct Variable
    {
        public UInt32 TypeCrc;
        public IntPtr DataPtr;

        public Variable(UInt32 InTypeCrc, IntPtr InDataPtr)
        {
            TypeCrc = InTypeCrc;
            DataPtr = InDataPtr;
        }
    }

    public class VariableTable : Dictionary<StringCrc32, object>
    {
        struct TypeInfo
        {
            public delegate void SerializerFunc(BinaryWriter writer, object value);
            public delegate object DeserializerFunc(BinaryReader reader);

            public readonly Type Type;
            public readonly StringCrc32 TypeNameCrc;
            public readonly SerializerFunc Serializer;
            public readonly DeserializerFunc Deserializer;


            public TypeInfo(Type InType, StringCrc32 InTypeNameCrc, SerializerFunc InSerializer, DeserializerFunc InDeserializer)
            {
                Type = InType;
                TypeNameCrc = InTypeNameCrc;
                Serializer = InSerializer;
                Deserializer = InDeserializer;
            }

            public TypeInfo(Type InType, string InTypeName, SerializerFunc InSerializer, DeserializerFunc InDeserializer)
                : this(InType, new StringCrc32(InTypeName), InSerializer, InDeserializer)
            {
            }

        };

        static TypeInfo[] TypeInfoList = {
                new TypeInfo(typeof(Result), "Result",
                    (writer, value) => { writer.Write(((Result)value).Code); },
                    (reader) => { return new Result(reader.ReadInt32()); }
                ),
                new TypeInfo(typeof(bool), "bool",
                (writer, value) => { writer.Write(((Int32)value)); },
                (reader) => { return reader.ReadInt32() != 0 ? true : false; }),

        new TypeInfo(typeof(IntPtr), "void*",
            (writer, value) => { writer.Write((Int64)value); },
                (reader) => { return reader.ReadInt64(); }),

            new TypeInfo(typeof(int), "int",
                (writer, value) => { writer.Write((int)value); },
                (reader) => { return reader.ReadInt32(); }),

            new TypeInfo(typeof(uint), "uint",
                (writer, value) => { writer.Write((uint)value); },
                (reader) => { return reader.ReadUInt32(); }),

            new TypeInfo(typeof(Int32), "int32",
                (writer, value) => { writer.Write((Int32)value); },
                (reader) => { return reader.ReadInt32(); }),

            new TypeInfo(typeof(UInt32), "uint32",
                (writer, value) => { writer.Write((UInt32)value); },
                (reader) => { return reader.ReadUInt32(); }),

            new TypeInfo(typeof(SByte), "int8",
                (writer, value) => { writer.Write((SByte)value); },
                (reader) => { return reader.ReadSByte(); }),

            new TypeInfo(typeof(Byte), "uint8",
                (writer, value) => { writer.Write((Byte)value); },
                (reader) => { return reader.ReadByte(); }),

            new TypeInfo(typeof(Int16), "int16",
                (writer, value) => { writer.Write((Int16)value); },
                (reader) => { return reader.ReadInt16(); }),

            new TypeInfo(typeof(UInt16), "uint16",
                (writer, value) => { writer.Write((UInt16)value); },
                (reader) => { return reader.ReadUInt16(); }),

            new TypeInfo(typeof(Int64), "int64",
                (writer, value) => { writer.Write((Int64)value); },
                (reader) => { return reader.ReadInt64(); }),

            new TypeInfo(typeof(UInt64), "uint64",
                (writer, value) => { writer.Write((UInt64)value); },
                (reader) => { return reader.ReadUInt64(); }),

            new TypeInfo(typeof(SFUInt128), "uint128",
                (writer, value) => { var valueTemp = (SFUInt128)value; writer.Write(valueTemp.Low); writer.Write(valueTemp.High); },
                (reader) => { return new SFUInt128() { Low = reader.ReadUInt64(), High = reader.ReadUInt64() }; }),

            new TypeInfo(typeof(float), "float",
                (writer, value) => { writer.Write((float)value); },
                (reader) => { return reader.ReadSingle(); }),

            new TypeInfo(typeof(double), "double",
                (writer, value) => { writer.Write((double)value); },
                (reader) => { return reader.ReadDouble(); }),

            new TypeInfo(typeof(UInt32), "hex32",
                (writer, value) => { writer.Write((UInt32)value); },
                (reader) => { return reader.ReadUInt32(); }),

            new TypeInfo(typeof(UInt64), "hex64",
                (writer, value) => { writer.Write((UInt64)value); },
                (reader) => { return reader.ReadUInt64(); }),

            new TypeInfo(typeof(string),
                "String",
                    (writer, value) =>
                    {
                        var valueTemp = (string)value;
                        writer.Write((UInt16)(valueTemp.Length + 1));
                        writer.Write(System.Text.Encoding.UTF8.GetBytes(valueTemp + "\0"));
                    },
                    (reader) =>
                    {
                        var strLen = reader.ReadUInt16();
                        byte[] byteBuffer = reader.ReadBytes(strLen);
                        return System.Text.Encoding.UTF8.GetString(byteBuffer, 0, strLen-1);
                    }
                ),

            new TypeInfo(typeof(string),
                "string",
                    (writer, value) =>
                    {
                        var valueTemp = (string)value;
                        writer.Write((UInt16)(valueTemp.Length + 1));
                        writer.Write(System.Text.Encoding.UTF8.GetBytes(valueTemp + "\0"));
                    },
                    (reader) =>
                    {
                        var strLen = reader.ReadUInt16();
                        byte[] byteBuffer = reader.ReadBytes(strLen);
                        return System.Text.Encoding.UTF8.GetString(byteBuffer, 0, strLen-1);
                    }
                ),

            new TypeInfo(typeof(string),
                "const char*",
                    (writer, value) =>
                    {
                        var valueTemp = (string)value;
                        writer.Write((UInt16)(valueTemp.Length + 1));
                        writer.Write(System.Text.Encoding.UTF8.GetBytes(valueTemp + "\0"));
                    },
                    (reader) =>
                    {
                        var strLen = reader.ReadUInt16();
                        byte[] byteBuffer = reader.ReadBytes(strLen);
                        return System.Text.Encoding.UTF8.GetString(byteBuffer, 0, strLen-1);
                    }
                ),

            new TypeInfo(typeof(Vector2), "Vector2",
                (writer, value) => { var valueTemp = (Vector2)value; writer.Write(valueTemp.x); writer.Write(valueTemp.y); },
                (reader) => { return new Vector2() { x = reader.ReadSingle(), y = reader.ReadSingle() }; }),

            new TypeInfo(typeof(Vector3), "Vector3",
                (writer, value) => { var valueTemp = (Vector3)value; writer.Write(valueTemp.x); writer.Write(valueTemp.y); writer.Write(valueTemp.z); },
                (reader) => { return new Vector3() { x = reader.ReadSingle(), y = reader.ReadSingle(), z = reader.ReadSingle() }; }),

            new TypeInfo(typeof(UInt64), "StringCrc32",
                (writer, value) => { writer.Write(((StringCrc32)value).StringHash); },
                (reader) => { return new StringCrc32(reader.ReadUInt32()); }),

            new TypeInfo(typeof(UInt64), "StringCrc64",
                (writer, value) => { writer.Write(((StringCrc64)value).StringHash); },
                (reader) => { return new StringCrc64(reader.ReadUInt64()); }),

            new TypeInfo(typeof(byte[]), "BLOB",
                (writer, value) => { var byteArray = (byte[])value; writer.Write(byteArray); },
                (reader) =>
                {
                    var byteSize = reader.ReadUInt16();
                    var bytes = reader.ReadBytes(byteSize);
                    return bytes;
                }),


        };

        static Dictionary<Type, TypeInfo> TypeInfoByType;
        static Dictionary<UInt32, TypeInfo> TypeInfoByTypeName;

        static VariableTable()
        {
            TypeInfoByType = new Dictionary<Type, TypeInfo>();
            foreach(var itItem in TypeInfoList)
            {
                if (TypeInfoByType.ContainsKey(itItem.Type))
                    continue;
                TypeInfoByType.Add(itItem.Type, itItem);
            }


            TypeInfoByTypeName = new Dictionary<uint, TypeInfo>();
            foreach(var itItem in TypeInfoList)
            {
                if (TypeInfoByTypeName.ContainsKey(itItem.TypeNameCrc.StringHash))
                    continue;
                TypeInfoByTypeName.Add(itItem.TypeNameCrc.StringHash, itItem);
            }
        }

        public VariableTable()
        {
        }

        TypeInfo GetTypeInfo(object value)
        {
            TypeInfo typeInfo;
            if (!TypeInfoByType.TryGetValue(value.GetType(), out typeInfo))
                throw new Exception(string.Format("Unknown type {0}", value.GetType().Name));

            return typeInfo;
        }

        TypeInfo GetTypeInfo(StringCrc32 typeName)
        {
            TypeInfo typeInfo;
            if (!TypeInfoByTypeName.TryGetValue(typeName.StringHash, out typeInfo))
                throw new Exception(string.Format("Unknown type {0}", typeName));

            return typeInfo;
        }

        public byte[] ToByteArray()
        {
            UInt16 NumItems = (UInt16)Count;
            using (MemoryStream outputStream = new MemoryStream())
            using (BinaryWriter writer = new BinaryWriter(outputStream))
            {
                writer.Write(NumItems);

                foreach (var itItem in this)
                {
                    writer.Write(itItem.Key.StringHash);

                    var typeInfo = GetTypeInfo(itItem.Value);
                    writer.Write(typeInfo.TypeNameCrc.StringHash);

                    typeInfo.Serializer(writer, itItem.Value);
                }

                writer.Flush();
                return outputStream.ToArray();
            }
        }

        public void FromSerializedMemory(int byteSize, IntPtr InDataPtr)
        {
            if (byteSize < sizeof(UInt16))
                return;

            byte[] byteData = new byte[byteSize];
            Marshal.Copy(InDataPtr, byteData, 0, byteData.Length);

            FromSerializedMemory(byteData);
        }
        public void FromSerializedMemory(byte[] byteData)
        {
            if (byteData == null)
                return;

            try
            {
                using (BinaryReader reader = new BinaryReader(new MemoryStream(byteData)))
                {
                    FromSerializedMemory(reader);
                }
            }
            catch (Exception exp)
            {
                System.Diagnostics.Debug.Print(exp.Message);
            }
        }

        public void FromSerializedMemory(BinaryReader reader)
        {
            Clear();

            var numItems = reader.ReadUInt16();

            for (UInt16 iItem = 0; iItem < numItems; iItem++)
            {
                var variableName = new StringCrc32(reader.ReadUInt32());
                var typeName = new StringCrc32(reader.ReadUInt32());

                var typeInfo = GetTypeInfo(typeName);
                var value = typeInfo.Deserializer(reader);
                Add(variableName, value);
            }
        }
    }


    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public class RelayPlayerInfo
    {
        public ulong EndpointID;
        public ulong PlayerID;

        public RelayPlayerInfo()
        {
        }
    }

    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public struct SFRouteContext
    {
        public long From;
        public long To;

        //public SFRouteContext()
        //{
        //    From = 0;
        //    To = 0;
        //}

        public SFRouteContext(long from, long to)
        {
            From = from;
            To = to;
        }
    }



    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public class RankingPlayerInformation : PlayerInformation
    {
        public int WeeklyWin;
        public int WeeklyLose;

        public RankingPlayerInformation()
        {
        }

        public RankingPlayerInformation(ulong playerID, ulong fbUID, string nickName, ulong lastActiveTime, uint level, int playingGame, int weeklyWin, int weeklyLose)
            : base(playerID, fbUID, nickName, lastActiveTime, level, playingGame)
        {
            WeeklyWin = weeklyWin;
            WeeklyLose = weeklyLose;
        }
    }

    [Struct]
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto, Pack = 4)]
    public struct TotalRankingPlayerInformation
    {
        public UInt32 RankingID;
        public UInt32 Ranking;
        public UInt64 PlayerID;
        public UInt64 FBUID;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] NickNameBytes;
        public UInt32 Level;
        public UInt32 ScoreLow;
        public UInt32 ScoreHigh;


        public string NickName
        {
            get
            {
                if (NickNameBytes == null) return null;
                var index = Array.FindIndex(NickNameBytes, x => x == 0);
                if (index < 0) index = NickNameBytes.Length;
                return System.Text.Encoding.UTF8.GetString(NickNameBytes, 0, index);
            }
            set
            {
                if (NickNameBytes == null || NickNameBytes.Length != 64)
                    NickNameBytes = new byte[64];

                System.Text.Encoding.UTF8.GetBytes(value, 0, value.Length, NickNameBytes, 0);
            }
        }

        public UInt32 Win { get { return ScoreHigh; } set { ScoreHigh = value; } }
        public UInt32 Lose { get { return ScoreLow; } set { ScoreLow = value; } }

        public UInt64 Score
        {
            get { return (UInt64)ScoreLow | (((UInt64)ScoreHigh) << 32); }
            set
            {
                ScoreLow = (UInt32)value;
                ScoreHigh = (UInt32)(value >> 32);
            }
        }
        public override string ToString()
        {
            return string.Format("Rank:{0}, PlayerID:{1}, Nick:{2}, Score:{3}", Ranking, PlayerID, NickName, Score);
        }

    }

}


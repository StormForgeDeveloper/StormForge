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

    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public struct NamedVariable
    {
        public UInt32 NameCrc;
        public UInt32 TypeCrc;
        public IntPtr Data;

        public NamedVariable(UInt32 InNameCrc, UInt32 InTypeCrc, IntPtr InData)
        {
            NameCrc = InNameCrc;
            TypeCrc = InTypeCrc;
            Data = InData;
        }
    }

    public class VariableTable : Dictionary<StringCrc32, object>
    {
        struct TypeInfo
        {
            public delegate void SerializerFunc(BinaryWriter writer, object value);
            public delegate object DeserializerFunc(BinaryReader reader);

            public readonly StringCrc32 TypeNameCrc;
            public readonly SerializerFunc Serializer;
            public readonly DeserializerFunc Deserializer;


            public TypeInfo(StringCrc32 InTypeNameCrc, SerializerFunc InSerializer, DeserializerFunc InDeserializer)
            {
                TypeNameCrc = InTypeNameCrc;
                Serializer = InSerializer;
                Deserializer = InDeserializer;
            }

            public TypeInfo(string InTypeName, SerializerFunc InSerializer, DeserializerFunc InDeserializer)
                : this(new StringCrc32(InTypeName), InSerializer, InDeserializer)
            {
            }

        };

        static Dictionary<Type, TypeInfo> TypeInfoByType;
        static Dictionary<UInt32, TypeInfo> TypeInfoByTypeName;

        static VariableTable()
        {
            TypeInfoByType = new Dictionary<Type, TypeInfo>();

            TypeInfoByType.Add(typeof(Result), new TypeInfo("Result",
                (writer, value) => { writer.Write(((Result)value).Code); },
                (reader) => { return new Result(reader.ReadInt32()); }));

            TypeInfoByType.Add(typeof(int), new TypeInfo("int",
                (writer,value)=> { writer.Write((int)value); },
                (reader) => { return reader.ReadInt32(); }));

            TypeInfoByType.Add(typeof(uint), new TypeInfo("uint",
                (writer, value) => { writer.Write((uint)value); },
                (reader) => { return reader.ReadUInt32(); }));

            TypeInfoByType.Add(typeof(SByte), new TypeInfo("int8",
                (writer, value) => { writer.Write((SByte)value); },
                (reader) => { return reader.ReadSByte(); }));

            TypeInfoByType.Add(typeof(Byte), new TypeInfo("uint8",
                (writer, value) => { writer.Write((Byte)value); },
                (reader) => { return reader.ReadByte(); }));

            TypeInfoByType.Add(typeof(Int16), new TypeInfo("int16",
                (writer, value) => { writer.Write((Int16)value); },
                (reader) => { return reader.ReadInt16(); }));

            TypeInfoByType.Add(typeof(UInt16), new TypeInfo("uint16",
                (writer, value) => { writer.Write((UInt16)value); },
                (reader) => { return reader.ReadUInt16(); }));

            TypeInfoByType.Add(typeof(Int32), new TypeInfo("int32",
                (writer, value) => { writer.Write((Int32)value); },
                (reader) => { return reader.ReadInt32(); }));

            TypeInfoByType.Add(typeof(UInt32), new TypeInfo("uint32",
                (writer, value) => { writer.Write((UInt32)value); },
                (reader) => { return reader.ReadUInt32(); }));

            TypeInfoByType.Add(typeof(Int64), new TypeInfo("int64",
                (writer, value) => { writer.Write((Int64)value); },
                (reader) => { return reader.ReadInt64(); }));

            TypeInfoByType.Add(typeof(UInt64), new TypeInfo("uint64",
                (writer, value) => { writer.Write((UInt64)value); },
                (reader) => { return reader.ReadUInt64(); }));

            TypeInfoByType.Add(typeof(SFUInt128), new TypeInfo("uint128",
                (writer, value) => { var valueTemp = (SFUInt128)value; writer.Write(valueTemp.Low); writer.Write(valueTemp.High); },
                (reader) => { return new SFUInt128() { Low = reader.ReadUInt64(), High = reader.ReadUInt64() }; }));

            TypeInfoByType.Add(typeof(float), new TypeInfo("float",
                (writer, value) => { writer.Write((float)value); },
                (reader) => { return reader.ReadSingle(); }));

            TypeInfoByType.Add(typeof(double), new TypeInfo("double",
                (writer, value) => { writer.Write((double)value); },
                (reader) => { return reader.ReadDouble(); }));

            TypeInfoByType.Add(typeof(string), 
                new TypeInfo("String",
                    (writer, value) =>
                    {
                        var valueTemp = (string)value;
                        writer.Write((UInt16)(valueTemp.Length+1));
                        writer.Write(System.Text.Encoding.UTF8.GetBytes(valueTemp + "\0"));
                    },
                    (reader) =>
                    {
                        var strLen = reader.ReadUInt16();
                        byte[] byteBuffer = reader.ReadBytes(strLen);
                        return System.Text.Encoding.UTF8.GetString(byteBuffer, 0, strLen);
                    }
                )
            );

            TypeInfoByType.Add(typeof(Vector2), new TypeInfo("Vector2",
                (writer, value) => { var valueTemp = (Vector2)value; writer.Write(valueTemp.x); writer.Write(valueTemp.y); },
                (reader) => { return new Vector2() { x = reader.ReadSingle(), y = reader.ReadSingle() }; }));

            TypeInfoByType.Add(typeof(Vector3), new TypeInfo("Vector3",
                (writer, value) => { var valueTemp = (Vector3)value; writer.Write(valueTemp.x); writer.Write(valueTemp.y); writer.Write(valueTemp.z); },
                (reader) => { return new Vector3() { x = reader.ReadSingle(), y = reader.ReadSingle(), z = reader.ReadSingle() }; }));


            TypeInfoByTypeName = new Dictionary<uint, TypeInfo>();
            foreach(var itItem in TypeInfoByType)
            {
                TypeInfoByTypeName.Add(itItem.Value.TypeNameCrc.StringHash, itItem.Value);
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

        public void FromSerializedMemory(IntPtr InDataPtr)
        {
            Clear();

            UInt16 byteSize = (UInt16)Marshal.ReadInt16(InDataPtr); InDataPtr = (IntPtr)(InDataPtr.ToInt64() + sizeof(UInt16));
            byte[] byteData = new byte[byteSize];
            Marshal.Copy(InDataPtr, byteData, 0, byteData.Length);

            using (BinaryReader reader = new BinaryReader(new MemoryStream(byteData)))
            {
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


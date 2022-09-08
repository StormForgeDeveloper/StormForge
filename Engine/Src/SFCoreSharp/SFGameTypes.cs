////////////////////////////////////////////////////////////////////////////////
//
// CopyRight (c) Kyungkun Ko
//
// Author : KyungKun Ko
//
// Description : Game types not important
//
//
////////////////////////////////////////////////////////////////////////////////

using System;
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

    [Struct()]
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector4
    {
        public float x;
        public float y;
        public float z;
        public float w;
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

    // Game Chat message type
    public enum ChatMessageType
    {
        Zone,
		ZoneGlobal,
		Wisper,
		Channel,
		System,
		Max
    };


    // Platform types
    public enum Platform
    {
        BR,         // Braves player Id
        Steam,      // Steam player Id
        Facebook,   // Facebook player Id
    };

    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public struct PlayerPlatformID
    {
        public UInt32 PlatformData;
        public UInt64 PlayerID;
        public Platform Platform => (Platform)(PlatformData);
    }



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
    [StructLayout(LayoutKind.Sequential, Pack = 4)]
    public struct ActorMovement
    {
        public Vector4 Position;
        public Vector4 LinearVelocity;

        public UInt32 ActorId;
        // Look direction
        public float AngularYaw; // No pitch and roll
        public UInt32 MoveFrame;
        public UInt32 MovementState;
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

    public class VariableTable : Dictionary<StringCrc32, object>
    {
        public VariableTable()
        {
        }

        public bool HasValue(string ValueName)
        {
            return HasValue(new StringCrc32(ValueName));
        }
        public bool HasValue(StringCrc32 ValueName)
        {
            return ContainsKey(ValueName);
        }

        public T GetValue<T>(string ValueName, T defaultValue)
        {
            StringCrc32 ValueNameCrc32 = new StringCrc32(ValueName);

            System.Object obj;
            if (!TryGetValue(ValueNameCrc32, out obj))
            {
                System.Diagnostics.Debug.Print("SF.VariableTable Value not found Name = {0}", ValueName);
                return defaultValue;
            }

            return (T)Convert.ChangeType(obj, typeof(T));
        }

        public bool TryGetValue<T>(string ValueName, ref T outValue)
        {
            StringCrc32 ValueNameCrc32 = new StringCrc32(ValueName);
            //if (!Table.ContainsKey(new StringCrc32(ValueName)))
            //	return false;
            System.Object obj;
            if (!TryGetValue(ValueNameCrc32, out obj))
            {
                System.Diagnostics.Debug.Print("SF.VariableTable Value not found Name = {0}", ValueName);
                return false;
            }

            outValue = (T)Convert.ChangeType(obj, typeof(T));
            return true;
        }

        public byte[] ToByteArray()
        {
            UInt16 NumItems = (UInt16)Count;
            using (MemoryStream outputStream = new MemoryStream())
            using (BinaryWriter writer = new BinaryWriter(outputStream))
            {
                ToByteArray(writer);

                writer.Flush();
                return outputStream.ToArray();
            }
        }
        public void ToByteArray(BinaryWriter writer)
        {
            UInt16 NumItems = (UInt16)Count;
            writer.Write(NumItems);

            foreach (var itItem in this)
            {
                writer.Write(itItem.Key.StringHash);

                var typeInfo = TypeSerialization.GetTypeInfo(itItem.Value);
                writer.Write(typeInfo.TypeNameCrc.StringHash);

                typeInfo.Serializer(writer, itItem.Value);
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
                SF.Log.Error(exp.Message);
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

                var typeInfo = TypeSerialization.GetTypeInfo(typeName);
                var value = typeInfo.Deserializer(reader);
                Add(variableName, value);
            }
        }


    }

    public static class VariableTableUtil
    {
        public static byte[] ToByteArray(this VariableTable[] Tables)
        {
            using (MemoryStream outputStream = new MemoryStream())
            using (BinaryWriter writer = new BinaryWriter(outputStream))
            {
                if (Tables != null)
                {
                    UInt16 numItems = (UInt16)Tables.Length;
                    writer.Write(numItems);
                    foreach (var table in Tables)
                    {
                        table.ToByteArray(writer);
                    }
                }
                else
                {
                    UInt16 numItems = 0;
                    writer.Write(numItems);
                }

                writer.Flush();
                return outputStream.ToArray();
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


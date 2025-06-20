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

using Google.FlatBuffers;
using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.IO;
using System.Numerics;
using System.Runtime.InteropServices;

#nullable enable

namespace SF
{
    using LogEntryID = System.UInt64;
    using BinaryPrimitives = System.Buffers.Binary.BinaryPrimitives;

    // structure data type attribute, this is used for message builder
    public class StructAttribute : Attribute
    {
    }

    public enum EAccountRole
    {
        Player,
        Tester,
        Dev
    };

    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public struct GameInstanceUID
    {
        public static readonly GameInstanceUID Empty = new GameInstanceUID();

        public UInt32 UID;

        public GameInstanceUID(UInt32 uid)
        {
            UID = uid;
        }

        public bool IsValid => UID != 0;

        public static bool operator ==(GameInstanceUID op1, GameInstanceUID op2)
        {
            return op1.UID == op2.UID;
        }
        public static bool operator !=(GameInstanceUID op1, GameInstanceUID op2)
        {
            return op1.UID != op2.UID;
        }

        public override bool Equals(object? obj)
        {
            if (obj == null)
                return false;

            return UID == ((GameInstanceUID)obj).UID;
        }

        public override int GetHashCode()
        {
            return (int)UID;
        }

        public override string ToString()
        {
            return UID.ToString();
        }
    }

    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public struct EntityUID
    {
        public static readonly EntityUID Empty = new EntityUID();

        public UInt32 UID;

        public EntityUID(UInt32 uid)
        {
            UID = uid;
        }

        public bool IsValid => UID != 0;

        public static bool operator ==(EntityUID op1, EntityUID op2)
        {
            return op1.UID == op2.UID;
        }
        public static bool operator !=(EntityUID op1, EntityUID op2)
        {
            return op1.UID != op2.UID;
        }

        public override bool Equals(object? obj)
        {
            if (obj == null)
                return false;

            return UID == ((EntityUID)obj).UID;
        }

        public override int GetHashCode()
        {
            return (int)UID;
        }

        public override string ToString()
        {
            return UID.ToString();
        }
    }

    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public struct SFUInt128
    {
        public UInt64 Low;
        public UInt64 High;

        public SFUInt128(UInt64 low, UInt64 high)
        {
            Low = low; High = high;
        }
    }

    [Struct()]
    public struct AccountID
    {
        public static readonly AccountID Empty = new AccountID(Guid.Empty);

        public Guid Guid;

        public SFUInt128 ToUInt128()
        {
            return Guid.ToUInt128();
        }

        public ulong ToUInt64()
        {
            return Guid.ToUInt64();
        }

        public AccountID(byte[] b)
        {
            Guid = new Guid(b);
        }

        public AccountID(Guid guid)
        {
            Guid = guid;
        }

        public AccountID(ulong value)
        {
            Guid = GuidHelper.FromUInt64(value);
        }

        public AccountID(string b)
        {
            Guid = GuidHelper.Parse(b);
        }

        public static AccountID Parse(string b)
        {
            return new AccountID(b);
        }

        public bool IsValid => Guid != Guid.Empty;

        public static bool TryParse(string b, out AccountID accountId)
        {
            return GuidHelper.TryParse(b, out accountId.Guid);
        }

        public byte[] ToByteArray() { return Guid.ToByteArray(); }

        public static bool operator ==(AccountID op1, AccountID op2)
        {
            return op1.Guid == op2.Guid;
        }
        public static bool operator !=(AccountID op1, AccountID op2)
        {
            return op1.Guid != op2.Guid;
        }

        public override bool Equals(object? obj)
        {
            if (obj == null)
                return false;

            return Guid == ((AccountID)obj).Guid;
        }

        public override int GetHashCode()
        {
            return Guid.GetHashCode();
        }

        public override string ToString()
        {
            return Guid.ToString("D");
        }
    }

    public static class GuidHelper
    {
        public static AccountID ToAccountID(this System.Guid guid)
        {
            return new AccountID(guid);
        }

        public static CharacterID ToCharacterID(this System.Guid guid)
        {
            return new CharacterID(guid);
        }

        public static bool IsValid(this System.Guid guid)
        {
            return guid != Guid.Empty;
        }

        public static Guid Parse(string b)
        {
            Guid guid;
            if (!Guid.TryParse(b, out guid))
            {
                UInt64 longValue;
                // We uses low 64 bit mode, and those are not valid guid format.
                if (ulong.TryParse(b, out longValue))
                {
                    return FromUInt64(longValue);
                }
            }

            return guid;
        }

        public static bool TryParse(string b, out Guid guid)
        {
            if (!Guid.TryParse(b, out guid))
            {
                UInt64 longValue;
                // We uses low 64 bit mode, and those are not valid guid format.
                if (ulong.TryParse(b, out longValue))
                {
                    guid = FromUInt64(longValue);
                }
                else
                {
                    return false;
                }
            }

            return true;
        }

        public static SFUInt128 ToUInt128(this System.Guid guid)
        {
            // UUID binary form is defined with big endian system.
            // 4 bytes + 2 bytes + 2 bytes + 2 bytes + 8 X 1 bytes
            var bytes = guid.ToByteArray();
            return new SFUInt128()
            {
                Low = ((ulong)bytes[3 + 0] << (0 * 8)) | ((ulong)bytes[2 + 0] << (1 * 8)) | ((ulong)bytes[1 + 0] << (2 * 8)) | ((ulong)bytes[0 + 0] << (3 * 8))
                        | ((ulong)bytes[5 + 0] << (4 * 8)) | ((ulong)bytes[4 + 0] << (5 * 8)) | ((ulong)bytes[7 + 0] << (6 * 8)) | ((ulong)bytes[6 + 0] << (7 * 8)),

                High = ((ulong)bytes[0 + 8] << (0 * 8)) | ((ulong)bytes[1 + 8] << (1 * 8)) | ((ulong)bytes[2 + 8] << (2 * 8)) | ((ulong)bytes[3 + 8] << (3 * 8))
                        | ((ulong)bytes[4 + 8] << (4 * 8)) | ((ulong)bytes[5 + 8] << (5 * 8)) | ((ulong)bytes[6 + 8] << (6 * 8)) | ((ulong)bytes[7 + 8] << (7 * 8))
            };
        }

        public static ulong ToUInt64(this System.Guid guid)
        {
            // We are using low 64 bit
            const int baseOffset = 0;
            var bytes = guid.ToByteArray();
            return ((ulong)bytes[3 + baseOffset] << (0 * 8)) | ((ulong)bytes[2 + baseOffset] << (1 * 8)) | ((ulong)bytes[1 + baseOffset] << (2 * 8)) | ((ulong)bytes[0 + baseOffset] << (3 * 8))
                    | ((ulong)bytes[5 + baseOffset] << (4 * 8)) | ((ulong)bytes[4 + baseOffset] << (5 * 8)) | ((ulong)bytes[7 + baseOffset] << (6 * 8)) | ((ulong)bytes[6 + baseOffset] << (7 * 8));
        }

        public static Guid FromUInt64(UInt64 value)
        {
            value = BinaryPrimitives.ReverseEndianness(value);
            return new Guid((uint)((value >> 32) & 0xFFFFFFFF), (ushort)((value >> 16) & 0xFFFF), (ushort)((value >> 0) & 0xFFFF),
                0, 0, 0, 0,  0, 0, 0, 0 // high 64 bit
                );
        }

        public static Guid FromLowHigh(UInt64 low, UInt64 high)
        {
            low = BinaryPrimitives.ReverseEndianness(low);
            return new Guid((uint)((low >> 32) & 0xFFFFFFFF), (ushort)((low >> 16) & 0xFFFF), (ushort)((low >> 0) & 0xFFFF),
                (byte)((high >> (0 * 8)) & 0xFF), (byte)((high >> (1 * 8)) & 0xFF), (byte)((high >> (2 * 8)) & 0xFF), (byte)((high >> (3 * 8)) & 0xFF),
                (byte)((high >> (4 * 8)) & 0xFF), (byte)((high >> (5 * 8)) & 0xFF), (byte)((high >> (6 * 8)) & 0xFF), (byte)((high >> (7 * 8)) & 0xFF)
                );
        }
    }

    [Struct()]
    public struct CharacterID
    {
        public static readonly CharacterID Empty = new CharacterID(Guid.Empty);

        public Guid Guid;

        public SFUInt128 ToUInt128()
        {
            return Guid.ToUInt128();
        }


        public CharacterID(byte[] b)
        {
            Guid = new Guid(b);
        }

        public CharacterID(Guid guid)
        {
            Guid = guid;
        }

        public CharacterID(ulong value)
        {
            Guid = GuidHelper.FromUInt64(value);
        }

        public CharacterID(string b)
        {
            Guid.TryParse(b, out Guid);
        }

        public static CharacterID Parse(string b)
        {
            return new CharacterID(GuidHelper.Parse(b));
        }

        public bool IsValid => Guid != Guid.Empty;

        public byte[] ToByteArray() { return Guid.ToByteArray(); }

        public static bool TryParse(string b, out CharacterID value)
        {
            return GuidHelper.TryParse(b, out value.Guid);
        }

        public static bool operator ==(CharacterID op1, CharacterID op2)
        {
            return op1.Guid == op2.Guid;
        }
        public static bool operator !=(CharacterID op1, CharacterID op2)
        {
            return op1.Guid != op2.Guid;
        }

        public override bool Equals(object? obj)
        {
            if (obj == null)
                return false;

            return Guid == ((CharacterID)obj).Guid;
        }

        public override int GetHashCode()
        {
            return Guid.GetHashCode();
        }

        public override string ToString()
        {
            return Guid.ToString("D");
        }
    }

    public struct SGameInstanceInfo
    {
        public string InstanceName;
        public uint PlayerCount;
    };

    [Struct()]
    [StructLayout(LayoutKind.Sequential)]
    public struct SFVector2
    {
        public float x;
        public float y;
    };

    [Struct()]
    [StructLayout(LayoutKind.Sequential)]
    public struct SFVector3
    {
        public float x;
        public float y;
        public float z;
    };

    [Struct()]
    [StructLayout(LayoutKind.Sequential)]
    public struct SFVector4
    {
        public float x;
        public float y;
        public float z;
        public float w;
    };

    [Struct()]
    [StructLayout(LayoutKind.Sequential)]
    public struct SFQuaternion
    {
        public float x;
        public float y;
        public float z;
        public float w;
    };

    public struct UGCGameInfo
    {
        public Guid UGCContentId;
        public uint TableId;
        public string Name;
    };

    public struct SFUGCItemInfo
    {
        public uint TableId;
        public uint UTCExpire;
        public uint Effect0;
        public uint Effect1;
    };


    // Manages pinned byte buffer
    public class PinnedByteBuffer : IDisposable
    {
        public GCHandle Handle { get; }
        public byte[]? Data { get; private set; }

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

    [Struct]
    [StructLayout(LayoutKind.Sequential)]
    public struct TransactionID
    {
        public static readonly TransactionID Empty = new TransactionID();

        // Random Transid helper
        public static readonly Random TransactionIdRandom = new Random();
        public static TransactionID NewTransactionId()
        {
            lock(TransactionIdRandom)
            {
                return new TransactionID((uint)TransactionIdRandom.Next());
            }
        }

        public ulong TransactionId;

        public bool IsValid => TransactionId != 0;

        public TransactionID(ulong transactionId)
        {
            TransactionId = transactionId;
        }

        public new string ToString()
        {
            return $"{TransactionId:X16}";
        }

        public bool Equals(TransactionID other)
        {
            return TransactionId == other.TransactionId;
        }

        public override bool Equals(object? obj)
        {
            if (!(obj is TransactionID))
            {
                return false;
            }
            var other = (TransactionID)obj;

            return TransactionId == other.TransactionId;

        }

        public override int GetHashCode()
        {
            return TransactionId.GetHashCode();
        }

        public static bool operator ==(TransactionID c1, TransactionID c2)
        {
            return c1.Equals(c2);
        }

        public static bool operator !=(TransactionID c1, TransactionID c2)
        {
            return !c1.Equals(c2);
        }
    }

    [Struct()]
    [StructLayout(LayoutKind.Sequential)]
    public struct NamedVariable
    {
        public string Name;
        public object? Value;
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

    [Struct()]
    [StructLayout(LayoutKind.Sequential)]
    public struct MatchingPlayerInformation
    {
        UInt64 PlayerUID;
        AccountID PlayerID;
        byte RequestedRole;
    }


    // Notification message
    public enum NotificationType
    {
        None,               // Not used
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
        Whisper,
        Channel,
        System,
        Max
    };


    // Platform types
    public enum EPlatform
    {
        BR,         // Braves player Id
        Steam,      // Steam player Id
        Facebook,   // Facebook player Id
    };

    [Struct]
    [StructLayout(LayoutKind.Explicit, Size = 17)]
    public struct PlayerPlatformID
    {
        [FieldOffset(0)] public byte PlatformData;
        [FieldOffset(1)] public AccountID PlayerID;
        public EPlatform Platform
        {
            get => (EPlatform)(PlatformData);
            set => PlatformData = (byte)value;
        }

        bool Parse(string playformIdString)
        {
            if (string.IsNullOrEmpty(playformIdString))
                return false;

            string[] subStrings = playformIdString.Split(':');
            if (subStrings.Length != 2)
                return false;

            if (!byte.TryParse(subStrings[0], out PlatformData))
                return false;

            if (!AccountID.TryParse(subStrings[1], out PlayerID))
                return false;

            return true;
        }

        public override string ToString() { return $"{PlatformData}:{PlayerID}"; }
    }


    [Struct]
    [StructLayout(LayoutKind.Sequential, Pack = 4)]
    public struct AchievementStat
    {
        public UInt32 AchievementStatId;
        public Int32 StatValue;
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
    public struct MatchingQueueTicket
    {
        public UInt64 QueueUID;
        public UInt64 QueueItemID;
    }

    [Struct]
    [StructLayout(LayoutKind.Sequential, Pack = 4)]
    public struct ActorMovement
    {
        public SFVector4 Position;
        public SFVector4 LinearVelocity;

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

        public FriendInformation(AccountID playerID, ulong fbUID, String nickName, ulong lastActiveTime, uint level, int playingGame, int weeklyWin, int weeklyLose, ulong lastStaminaSent)
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

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 70)]
        public String Address;
        public ushort Port;
        public SockFamilyType SockFamily;

        public NetAddress(int sockFamily, String address, int port)
        {
            object? sockFamilyObj = Enum.GetValues(typeof(SockFamilyType)).GetValue(sockFamily);
            SockFamily = sockFamilyObj != null ? (SockFamilyType)sockFamilyObj : SockFamilyType.None;
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
        public AccountID PlayerID;
        public PlayerPlatformID PlayerPlatformId;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] NickNameBytes = new byte[64];
        public ulong LastActiveTime;
        public uint Level;
        public int IsPlayingGame;

        public string NickName
        {
            get
            {
                if (NickNameBytes == null) return string.Empty;
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

        public PlayerInformation(AccountID playerID, ulong fbUID, string nickName, ulong lastActiveTime, uint level, int playingGame)
        {
            PlayerID = playerID;
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

    public interface IBinarySerializable
    {
        public void FromByteArray(byte[]? bytes);
        public void FromBinary(BinaryReader reader);
        public byte[] ToByteArray();
        public void ToBinary(BinaryWriter writer);
    }

    public class VariableTable : Dictionary<StringCrc32, object?>, IBinarySerializable
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

            System.Object? obj;
            if (!TryGetValue(ValueNameCrc32, out obj))
            {
                System.Diagnostics.Debug.Print("SF.VariableTable Value not found Name = {0}", ValueName);
                return defaultValue;
            }

            if (obj != null)
                return (T)Convert.ChangeType(obj, typeof(T));
            else
                return defaultValue;
        }

        public void SetValue<T>(string ValueName, T value)
        {
            StringCrc32 ValueNameCrc32 = new StringCrc32(ValueName);

            this[ValueNameCrc32] = value;
        }

        public bool TryGetValue<T>(string ValueName, out T? outValue)
        {
            StringCrc32 ValueNameCrc32 = new StringCrc32(ValueName);

            System.Object? obj;
            if (!TryGetValue(ValueNameCrc32, out obj))
            {
                outValue = default(T);
                System.Diagnostics.Debug.Print("SF.VariableTable Value not found Name = {0}", ValueName);
                return false;
            }

            if (obj == null)
            {
                outValue = default(T);
                return false;
            }

            outValue = (T)Convert.ChangeType(obj, typeof(T));

            return true;
        }

        public bool TryGetValueBinary<T>(string ValueName, ref T defaultValue) where T : IBinarySerializable
        {
            System.Object? obj;
            if (!TryGetValue(new StringCrc32(ValueName), out obj) || obj == null)
            {
                return false;
            }

            byte[] byteData = (byte[])obj;
            defaultValue.FromByteArray(byteData);

            return true;
        }

        public byte[] ToByteArray()
        {
            using (MemoryStream outputStream = new MemoryStream())
            using (BinaryWriter writer = new BinaryWriter(outputStream))
            {
                ToBinary(writer);

                writer.Flush();
                return outputStream.ToArray();
            }
        }
        public void ToBinary(BinaryWriter writer)
        {
            UInt16 NumItems = (UInt16)Count;
            writer.Write(NumItems);

            foreach (var itItem in this)
            {
                writer.Write(itItem.Key.StringHash);

                if (itItem.Value != null)
                {
                    var typeInfo = TypeSerialization.GetTypeInfo(itItem.Value);
                    writer.Write(typeInfo.TypeNameCrc.StringHash);

                    typeInfo.Serializer(writer, itItem.Value);
                }
            }
        }

        public void FromByteArray(byte[]? byteData)
        {
            if (byteData == null)
                return;

            try
            {
                using (BinaryReader reader = new BinaryReader(new MemoryStream(byteData)))
                {
                    FromBinary(reader);
                }
            }
            catch (Exception exp)
            {
                SF.Log.Error(exp.Message);
            }
        }

        public void FromBinary(BinaryReader reader)
        {
            Clear();

            var numItems = reader.ReadUInt16();

            for (UInt16 iItem = 0; iItem < numItems; iItem++)
            {
                var variableName = new StringCrc32(reader.ReadUInt32());
                var typeName = new StringCrc32(reader.ReadUInt32());

                TypeSerialization.TypeInfo typeInfo = TypeSerialization.GetTypeInfo(typeName);
                object? value = typeInfo.Deserializer(reader);
                Add(variableName, value);
            }
        }

        public void FromSerializedMemory(int byteSize, IntPtr InDataPtr)
        {
            if (byteSize < sizeof(UInt16))
                return;

            byte[] byteData = new byte[byteSize];
            Marshal.Copy(InDataPtr, byteData, 0, byteData.Length);

            FromByteArray(byteData);
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
                        table.ToBinary(writer);
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
        public AccountID PlayerID;

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

        public RankingPlayerInformation(AccountID playerID, ulong fbUID, string nickName, ulong lastActiveTime, uint level, int playingGame, int weeklyWin, int weeklyLose)
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
        public AccountID PlayerID;
        public PlayerPlatformID PlayerPlatformId;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] NickNameBytes;
        public UInt32 Level;
        public UInt32 ScoreLow;
        public UInt32 ScoreHigh;


        public string ProfileName
        {
            get
            {
                if (NickNameBytes == null) return string.Empty;
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
            return string.Format("Rank:{0}, PlayerID:{1}, Nick:{2}, Score:{3}", Ranking, PlayerID, ProfileName, Score);
        }

    }

}

#nullable restore

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
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace SF
{

    // structure data type attribute, this is used for message builder
    public class StructAttribute : Attribute
    {
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


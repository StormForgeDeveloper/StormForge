////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : type information for source code generators
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Collections.Generic;
using ProtocolXml;

namespace SF
{
    using String = String;
    using INT8 = SByte;
    using UINT8 = Byte;
    using INT16 = Int16;
    using UINT16 = UInt16;
    using INT32 = Int32;
    using UINT32 = UInt32;
    using INT64 = Int64;
    using UINT64 = UInt64;
    using BYTE = Byte;
    using WORD = UInt16;
    using DWORD = UInt32;
    using QWORD = UInt64;
    using FLOAT = Single;
    using Context = UInt64;
    using AccountID = UInt64;
    using AuthTicket = UInt64;
    using GameInstanceID = UInt32;
    using GameInstanceUID = UInt64;
    using EntityID = UInt32;
    using EntityUID = UInt64;
    using ServerID = UInt32;
    using ServerUID = UInt64;
    using System.Runtime.InteropServices;




    // Clustering model
    enum ClusterType
	{
		Replication,
		Ring,
		Shard,
	};

	// Cluster Member ship mode
	enum ClusterMembership
	{
		Master,
		Slave,
		StatusWatcher,	// Service status watcher
		Watcher,			// Service data watcher, Only effect with replica model
	};
	
	// Cluster Service status
	enum ServiceStatus
	{
		Offline,
		Online,
		Ready,
	};


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



    [StructLayout(LayoutKind.Sequential)]
    public class ServerFriendInformation : FriendInformation
    {
        public UInt32 ShardID;
    }



    [Struct()]
    [StructLayout(LayoutKind.Sequential)]
    public struct ServiceInformation
    {
        public EntityUID EntityUID;
    }

    [Struct()]
    [StructLayout(LayoutKind.Sequential)]
    public struct MatchingPlayerInformation
    {
        EntityUID PlayerUID;
        AccountID PlayerID;
        byte RequestedRole;
    }



    [Struct()]
    [StructLayout(LayoutKind.Sequential)]
    public struct LocalUID
    {
        public UInt64 UID;
    }


    [Struct()]
    [StructLayout(LayoutKind.Sequential)]
    public struct PerformanceCounterInfo
    {
        UInt32 DateType;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
        string CounterName;
    }

    [Struct()]
    [StructLayout(LayoutKind.Sequential)]
    public struct PerformanceCounterInstanceInfo
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
        string InstanceName;
        EntityUID InstanceUID;
    }

    /// <summary>
    /// TypeUsage
    /// </summary>
    public enum TypeUsage
    {
        CPP,            // CPP only
        CPPFunction,    // Function definition
        CPPForSharp,    // CPP csharp native interfacing(function only)
        CSharp,         // CSharp only
        CSharpFunction, // CSharp Function
        CSharpNative,   // CSharp Native(function only)
    }

    public class SystemTypeInfo
    {

        public class TypeMap
        {
            public ParameterType XMLType;
            public int ByteSize;
            public Type CSharpType;
            public string CPPTypeName;

            public TypeMap(ParameterType xmlType, int byteSize, Type chType, string cppTypeName = null)
            {
                XMLType = xmlType;
                ByteSize = byteSize;
                CSharpType = chType;
                CPPTypeName = cppTypeName ?? xmlType.ToString();
            }
        };

        static string ToString(ParameterType type)
        {
            string name = Enum.GetName(typeof(ParameterType), type);
            switch(name)
            {
                case "int8":
                case "uint8":
                case "int16":
                case "uint16":
                case "int32":
                case "uint32":
                case "int64":
                case "uint64":
                    name = name + "_t";
                    break;
            }
            return name;
        }

        static TypeMap[] TypesMapList = new TypeMap[]{
            new TypeMap( ParameterType.String, -1, typeof(String), cppTypeName:"const char*" ),
            new TypeMap( ParameterType.int8, 1, typeof(SByte), cppTypeName:"int8_t" ),
            new TypeMap( ParameterType.uint8, 1, typeof(Byte), cppTypeName:"uint8_t" ),
            new TypeMap( ParameterType.int16, 2, typeof(Int16), cppTypeName:"int16_t" ),
            new TypeMap( ParameterType.uint16, 2, typeof(UInt16), cppTypeName:"uint16_t" ),
            new TypeMap( ParameterType.int32, 4, typeof(Int32), cppTypeName:"int32_t" ),
            new TypeMap( ParameterType.uint32, 4, typeof(UInt32), cppTypeName:"uint32_t" ),
            new TypeMap( ParameterType.int64, 8, typeof(Int64), cppTypeName:"int64_t" ),
            new TypeMap( ParameterType.uint64, 8, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( ParameterType.intptr, 8, typeof(IntPtr), cppTypeName:"intptr_t" ),
            new TypeMap( ParameterType.WORD, 2, typeof(UInt16), cppTypeName:"uint16_t" ),
            new TypeMap( ParameterType.DWORD, 4, typeof(UInt32), cppTypeName:"uint32_t" ),
            new TypeMap( ParameterType.QWORD, 8, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( ParameterType.@float, 4, typeof(float), cppTypeName:"float" ),
            new TypeMap( ParameterType.TransactionID, 8, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( ParameterType.AccountID, 8, typeof(UInt64) ),
            new TypeMap( ParameterType.PlayerID, 8, typeof(UInt64) ),
            new TypeMap( ParameterType.FacebookUID, 8, typeof(UInt64) ),
            new TypeMap( ParameterType.AuthTicket, 8, typeof(UInt64) ),
            new TypeMap( ParameterType.GameInsID, 4, typeof(UInt32) ),
            new TypeMap( ParameterType.GameInsUID, 8, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( ParameterType.EntityID, 4, typeof(UInt32) ),
            new TypeMap( ParameterType.EntityUID, 8, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( ParameterType.PartyUID, 8, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( ParameterType.ServerID, 4, typeof(UInt32) ),
            new TypeMap( ParameterType.ClusterID, 4, typeof(UInt32) ),
            new TypeMap( ParameterType.Result, 4, typeof(Int32) ),
            new TypeMap( ParameterType.NotificationType, 2, typeof(Int16) ),

            new TypeMap( ParameterType.RankingType, 1, typeof(RankingType) ),

            new TypeMap( ParameterType.PlayerRole, 1, typeof(PlayerRole), cppTypeName:"uint8_t" ),
            new TypeMap( ParameterType.GameStateID, 1, typeof(GameStateID), cppTypeName:"uint8_t" ),
            new TypeMap( ParameterType.GameWinner, 1, typeof(GameWinner), cppTypeName:"uint8_t" ),
            new TypeMap( ParameterType.PlayerKilledReason, 1, typeof(PlayerKilledReason), cppTypeName:"uint8_t" ),
            new TypeMap( ParameterType.PlayerRevealedReason, 1, typeof(PlayerRevealedReason), cppTypeName:"uint8_t" ),

            new TypeMap( ParameterType.GameID, 4, typeof(UInt32), cppTypeName:"uint32_t" ),

            new TypeMap( ParameterType.StringCrc32, 4, typeof(UInt32), cppTypeName:"StringCrc32" ),
            new TypeMap( ParameterType.StringCrc64, 8, typeof(UInt64), cppTypeName:"StringCrc64" ),

            new TypeMap( ParameterType.ClusterType, 4, typeof(ClusterType) ),
            new TypeMap( ParameterType.ClusterMembership, 4, typeof(ClusterMembership) ),
            new TypeMap( ParameterType.ServiceStatus, 4, typeof(ServiceStatus) ),

            new TypeMap( ParameterType.MatchingPlayerInformation, 16, typeof(MatchingPlayerInformation) ),
            new TypeMap( ParameterType.MatchingQueueTicket, 8, typeof(MatchingQueueTicket) ),
            new TypeMap( ParameterType.LocalUID, 8, typeof(LocalUID), cppTypeName:"uint64_t" ),

            new TypeMap( ParameterType.Variable, -1, typeof(Variable), cppTypeName:"Variable" ),
            new TypeMap( ParameterType.NamedVariable, -1, typeof(NamedVariable), cppTypeName:"NamedVariable" ),
            new TypeMap( ParameterType.VariableTable, -1, typeof(NamedVariable[]), cppTypeName:"VariableTable" ),

            new TypeMap( ParameterType.Vector2, 8, typeof(Vector2) ),
            new TypeMap( ParameterType.Vector3, 12, typeof(Vector3) ),
            new TypeMap( ParameterType.NetAddress, 18, typeof(NetAddress) ),
            new TypeMap( ParameterType.NetClass, 18, typeof(UInt32) ),
            new TypeMap( ParameterType.RouteContext, 8, typeof(SFRouteContext) ),
            new TypeMap( ParameterType.ServiceInformation, Marshal.SizeOf(typeof(ServiceInformation)), typeof(ServiceInformation) ),
            new TypeMap( ParameterType.PlayerInformation, Marshal.SizeOf(typeof(PlayerInformation)), typeof(PlayerInformation) ),
            new TypeMap( ParameterType.RankingPlayerInformation, Marshal.SizeOf(typeof(RankingPlayerInformation)), typeof(RankingPlayerInformation) ),
            new TypeMap( ParameterType.FriendInformation, Marshal.SizeOf(typeof(FriendInformation)), typeof(FriendInformation) ),
            new TypeMap( ParameterType.ServerFriendInformation, Marshal.SizeOf(typeof(ServerFriendInformation)), typeof(ServerFriendInformation) ),
            new TypeMap( ParameterType.TotalRankingPlayerInformation, Marshal.SizeOf(typeof(TotalRankingPlayerInformation)), typeof(TotalRankingPlayerInformation) ),
            new TypeMap( ParameterType.PerformanceCounterInfo, Marshal.SizeOf(typeof(PerformanceCounterInfo)), typeof(PerformanceCounterInfo) ),
            new TypeMap( ParameterType.PerformanceCounterInstanceInfo, Marshal.SizeOf(typeof(PerformanceCounterInstanceInfo)), typeof(PerformanceCounterInstanceInfo) ),
            new TypeMap( ParameterType.RelayPlayerInfo, Marshal.SizeOf(typeof(RelayPlayerInfo)), typeof(RelayPlayerInfo) ),
        };

        static Dictionary<ParameterType, TypeMap> MapToCSharp = new Dictionary<ParameterType, TypeMap>();

        static SystemTypeInfo()
        {
            foreach (TypeMap typeMap in TypesMapList)
            {
                MapToCSharp.Add(typeMap.XMLType, typeMap);
            }
        }

        public static ParameterType FindParameterTypeFromCSharpType(Type csType)
        {
            foreach(var itTypeInfo in MapToCSharp)
            {
                if (itTypeInfo.Value.CSharpType == csType)
                {
                    return itTypeInfo.Key;
                }
            }

            Console.Error.WriteLine("Can't find related cstype for {0}", csType.ToString());

            return ParameterType.intptr;
        }

        public static Type ToCSharpType(ParameterType type)
        {
            try
            {
                return MapToCSharp[type].CSharpType;
            }
            catch(Exception exp)
            {
                Console.WriteLine("Can't find csharp type {0}", type);
                throw exp;
            }
        }

        public static string ToCPPType(ParameterType type)
        {
            try
            {
                return MapToCSharp[type].CPPTypeName;
            }
            catch (Exception exp)
            {
                Console.WriteLine("Can't find cpp type {0}", type);
                throw exp;
            }
        }

        public static bool IsStruct(ParameterType type)
        {
            Type csType = SystemTypeInfo.ToCSharpType(type);
            return IsStruct(csType);
        }

        public static bool IsStruct(Type csType)
        {
            bool bIsStruct = false;
            foreach (Attribute attribute in Attribute.GetCustomAttributes(csType))
            {
                if (attribute.GetType() == typeof(StructAttribute))
                {
                    bIsStruct = true;
                    break;
                }
            }
            return bIsStruct;
        }

        public static string ToCPPTypeFromCSharp(Type csharpType)
        {
            foreach(var itTypeInfo in MapToCSharp)
            {
                if (itTypeInfo.Value.CSharpType == csharpType)
                {
                    return itTypeInfo.Value.CPPTypeName;
                }
            }

            throw new Exception(string.Format("Can't find cpp type for {0}", csharpType.ToString()));
        }

        // Ignore array option
        public static string ElementTypeNameFor(TypeUsage usage, Parameter param)
        {
            Type csType = SystemTypeInfo.ToCSharpType(param.Type);
            switch (usage)
            {
                case TypeUsage.CPP:
                    return MapToCSharp[param.Type].CPPTypeName;
                case TypeUsage.CPPFunction:
                    return MapToCSharp[param.Type].CPPTypeName;
                case TypeUsage.CPPForSharp:
                    {
                        var cppTypeName = SystemTypeInfo.ToCPPType(param.Type);
                        if (csType.IsArray)
                            return ToCPPTypeFromCSharp(csType.GetElementType());
                        else
                            return cppTypeName;
                    }
                case TypeUsage.CSharp:
                    return csType.ToString();
                case TypeUsage.CSharpFunction:
                    return csType.ToString();
                case TypeUsage.CSharpNative:
                    if (csType.IsEnum)
                        return "int";
                    else
                        return csType.ToString();
            }

            throw new Exception("Invalid type name:" + param.Type.ToString());
        }

        public static string TypeNameOnlyFor(TypeUsage usage, Parameter param)
        {
            string elementTypeName = ElementTypeNameFor(usage, param);
            Type csType = SystemTypeInfo.ToCSharpType(param.Type);
            bool bIsStruct = IsStruct(param.Type);

            switch (usage)
            {
                case TypeUsage.CPP:
                    if (param.IsArray)
                        return string.Format("Array<{0}>", elementTypeName);
                    else
                        return elementTypeName;
                case TypeUsage.CPPFunction:
                    if (param.IsArray)
                        return string.Format("Array<{0}>", elementTypeName);
                    else
                        return elementTypeName;
                case TypeUsage.CPPForSharp:
                    if (param.IsArray || csType.IsArray)
                        return elementTypeName + "*";
                    else
                        return elementTypeName;
                case TypeUsage.CSharp:
                case TypeUsage.CSharpFunction:
                case TypeUsage.CSharpNative:
                    if (param.IsArray)
                        return elementTypeName + "[]";
                    else
                        return elementTypeName;
            }

            throw new Exception("Invalid type name:" + param.Type.ToString());
        }

        public static string TypeNameFor(TypeUsage usage, Parameter param)
        {
            Type csType = SystemTypeInfo.ToCSharpType(param.Type);
            bool bIsStruct = IsStruct(param.Type);

            switch (usage)
            {
                case TypeUsage.CPP:
                    if(param.IsArray)
                        return string.Format("Array<{0}>", MapToCSharp[param.Type].CPPTypeName);
                    else
                        return MapToCSharp[param.Type].CPPTypeName;
                case TypeUsage.CPPFunction:
                    if (param.IsArray)
                        return string.Format("const Array<{0}>&", MapToCSharp[param.Type].CPPTypeName);
                    else if(bIsStruct)
                        return string.Format("const {0}&", MapToCSharp[param.Type].CPPTypeName);
                    else
                        return MapToCSharp[param.Type].CPPTypeName;
                case TypeUsage.CPPForSharp:
                    {
                        var cppTypeName = SystemTypeInfo.ToCPPType(param.Type);
                        if (csType == typeof(string))
                            return cppTypeName;
                        else if (param.IsArray)
                            return string.Format("const {0}*", cppTypeName);
                        else if (bIsStruct)
                            return string.Format("const {0}&", cppTypeName);
                        else if (csType.IsEnum)
                            return "int";
                        else
                            return cppTypeName;
                    }
                case TypeUsage.CSharp:
                    if (param.IsArray)
                        return csType.ToString() + "[]";
                    else
                        return csType.ToString();
                case TypeUsage.CSharpFunction:
                    if (param.IsArray)
                        return csType.ToString() + "[]";
                    else if(bIsStruct)
                        return "ref" + csType.ToString();
                    else
                        return csType.ToString();
                case TypeUsage.CSharpNative:
                    {
                        if (param.IsArray)
                        {
                            if (csType == typeof(string))
                                return "[MarshalAs(UnmanagedType.LPArray)] byte[]";
                            else if (bIsStruct)
                                return string.Format("{0}[]", csType.ToString());
                            else if (csType.IsEnum)
                                return "int[]";// TODO: actually I can't support this
                            else
                                return csType.ToString() + "[]";
                        }
                        else
                        {
                            if (csType == typeof(string))
                                return "[MarshalAs(UnmanagedType.LPArray)] byte[]";
                            else if (bIsStruct)
                                return string.Format("ref {0}", csType.ToString());
                            else if (csType.IsEnum)
                                return "int";
                            else
                                return csType.ToString();
                        }
                    }
            }

            throw new Exception("Invalid type name:"+ param.Type.ToString());
        }

        public static TypeMap GetParameterInfo(ParameterType type)
        {
            return MapToCSharp[type];
        }
    }

}

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
            //public ParameterType XMLType;
            public string XMLType;
            public int ByteSize;
            public string CSharpTypeName;
            public bool IsCSharpStruct;
            public bool IsEnum;
            public bool IsCSharpArray;
            public string CPPTypeName;

            public bool IsVariableSize => ByteSize < 0;
            public bool IsString => XMLType == "String";

            //public TypeMap(ParameterType xmlType, int byteSize, Type chType, string cppTypeName = null)
            //{
            //    XMLType = xmlType.ToString();
            //    ByteSize = byteSize;
            //    CSharpType = chType;
            //    CSharpTypeName = CSharpType.ToString();
            //    IsCSharpStruct = IsStruct(chType);
            //    IsEnum = chType.IsEnum;
            //    IsCSharpArray = chType.IsArray;
            //    CPPTypeName = cppTypeName ?? xmlType.ToString();
            //}

            public TypeMap(string xmlType, int byteSize, Type chType, string cppTypeName = null)
            {
                XMLType = xmlType;
                ByteSize = byteSize;
                CSharpTypeName = chType.ToString();
                IsCSharpStruct = IsStruct(chType);
                IsEnum = chType.IsEnum;
                IsCSharpArray = chType.IsArray;
                CPPTypeName = cppTypeName ?? xmlType.ToString();
            }
        };


        static TypeMap[] TypesMapList = new TypeMap[]{
            new TypeMap( "String", -1, typeof(String), cppTypeName:"const char*" ),
            new TypeMap( "int8", 1, typeof(SByte), cppTypeName:"int8_t" ),
            new TypeMap( "uint8", 1, typeof(Byte), cppTypeName:"uint8_t" ),
            new TypeMap( "int16", 2, typeof(Int16), cppTypeName:"int16_t" ),
            new TypeMap( "uint16", 2, typeof(UInt16), cppTypeName:"uint16_t" ),
            new TypeMap( "int32", 4, typeof(Int32), cppTypeName:"int32_t" ),
            new TypeMap( "uint32", 4, typeof(UInt32), cppTypeName:"uint32_t" ),
            new TypeMap( "int64", 8, typeof(Int64), cppTypeName:"int64_t" ),
            new TypeMap( "uint64", 8, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "intptr", 8, typeof(IntPtr), cppTypeName:"intptr_t" ),
            new TypeMap( "WORD", 2, typeof(UInt16), cppTypeName:"uint16_t" ),
            new TypeMap( "DWORD", 4, typeof(UInt32), cppTypeName:"uint32_t" ),
            new TypeMap( "QWORD", 8, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "float", 4, typeof(float), cppTypeName:"float" ),
            new TypeMap( "TransactionID", 8, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "AccountID", 8, typeof(UInt64) ),
            new TypeMap( "PlayerID", 8, typeof(UInt64) ),
            new TypeMap( "FacebookUID", 8, typeof(UInt64) ),
            new TypeMap( "AuthTicket", 8, typeof(UInt64) ),
            new TypeMap( "GameInsID", 4, typeof(UInt32) ),
            new TypeMap( "GameInsUID", 8, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "EntityID", 4, typeof(UInt32) ),
            new TypeMap( "EntityUID", 8, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "PartyUID", 8, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "ServerID", 4, typeof(UInt32) ),
            new TypeMap( "ClusterID", 4, typeof(UInt32) ),
            new TypeMap( "Result", 4, typeof(Int32) ),
            new TypeMap( "NotificationType", 2, typeof(Int16) ),
            new TypeMap( "RankingType", 1, typeof(RankingType) ),
            new TypeMap( "PlayerRole", 1, typeof(PlayerRole), cppTypeName:"uint8_t" ),
            new TypeMap( "GameStateID", 1, typeof(GameStateID), cppTypeName:"uint8_t" ),
            new TypeMap( "GameWinner", 1, typeof(GameWinner), cppTypeName:"uint8_t" ),
            new TypeMap( "PlayerKilledReason", 1, typeof(PlayerKilledReason), cppTypeName:"uint8_t" ),
            new TypeMap( "PlayerRevealedReason", 1, typeof(PlayerRevealedReason), cppTypeName:"uint8_t" ),
            new TypeMap( "GameID", 4, typeof(UInt32), cppTypeName:"uint32_t" ),
            new TypeMap( "StringCrc32", 4, typeof(UInt32), cppTypeName:"StringCrc32" ),
            new TypeMap( "StringCrc64", 8, typeof(UInt64), cppTypeName:"StringCrc64" ),
            new TypeMap( "ClusterType", 4, typeof(ClusterType) ),
            new TypeMap( "ClusterMembership", 4, typeof(ClusterMembership) ),
            new TypeMap( "ServiceStatus", 4, typeof(ServiceStatus) ),
            new TypeMap( "ActorMovement", Marshal.SizeOf(typeof(ActorMovement)), typeof(ActorMovement) ),
            new TypeMap( "MatchingPlayerInformation", 16, typeof(MatchingPlayerInformation) ),
            new TypeMap( "MatchingQueueTicket", 8, typeof(MatchingQueueTicket) ),
            new TypeMap( "LocalUID", 8, typeof(LocalUID), cppTypeName:"uint64_t" ),
            new TypeMap( "Variable", -1, typeof(Variable), cppTypeName:"Variable" ),
            new TypeMap( "VariableTable", -1, typeof(VariableTable), cppTypeName:"VariableTable" ),
            new TypeMap( "Vector2", 8, typeof(Vector2) ),
            new TypeMap( "Vector3", 12, typeof(Vector3) ),
            new TypeMap( "Vector4", 16, typeof(Vector4) ),
            new TypeMap( "NetAddress", 18, typeof(NetAddress) ),
            new TypeMap( "NetClass", 18, typeof(UInt32) ),
            new TypeMap( "RouteContext", 8, typeof(SFRouteContext) ),
            new TypeMap( "ServiceInformation", Marshal.SizeOf(typeof(ServiceInformation)), typeof(ServiceInformation) ),
            new TypeMap( "PlayerInformation", Marshal.SizeOf(typeof(PlayerInformation)), typeof(PlayerInformation) ),
            new TypeMap( "RankingPlayerInformation", Marshal.SizeOf(typeof(RankingPlayerInformation)), typeof(RankingPlayerInformation) ),
            new TypeMap( "FriendInformation", Marshal.SizeOf(typeof(FriendInformation)), typeof(FriendInformation) ),
            new TypeMap( "ServerFriendInformation", Marshal.SizeOf(typeof(ServerFriendInformation)), typeof(ServerFriendInformation) ),
            new TypeMap( "TotalRankingPlayerInformation", Marshal.SizeOf(typeof(TotalRankingPlayerInformation)), typeof(TotalRankingPlayerInformation) ),
            new TypeMap( "PerformanceCounterInfo", Marshal.SizeOf(typeof(PerformanceCounterInfo)), typeof(PerformanceCounterInfo) ),
            new TypeMap( "PerformanceCounterInstanceInfo", Marshal.SizeOf(typeof(PerformanceCounterInstanceInfo)), typeof(PerformanceCounterInstanceInfo) ),
            new TypeMap( "RelayPlayerInfo", Marshal.SizeOf(typeof(RelayPlayerInfo)), typeof(RelayPlayerInfo) ),
        };

        static Dictionary<string, TypeMap> MapToCSharp = new Dictionary<string, TypeMap>();

        static SystemTypeInfo()
        {
            foreach (TypeMap typeMap in TypesMapList)
            {
                MapToCSharp.Add(typeMap.XMLType, typeMap);
            }
        }

        public static void AddTypeInfo(TypeMap newType)
        {
            MapToCSharp.Add(newType.XMLType, newType);
        }

        //public static Type ToCSharpType(string paramTypeName)
        //{
        //    try
        //    {
        //        return MapToCSharp[paramTypeName].CSharpType;
        //    }
        //    catch(Exception exp)
        //    {
        //        Console.WriteLine("Can't find csharp type {0}", paramTypeName);
        //        throw exp;
        //    }
        //}

        public static string ToCPPType(string paramTypeName)
        {
            try
            {
                return MapToCSharp[paramTypeName].CPPTypeName;
            }
            catch (Exception exp)
            {
                Console.WriteLine("Can't find cpp type {0}", paramTypeName);
                throw exp;
            }
        }

        public static bool IsStruct(Parameter param)
        {
            var typeInfo = SystemTypeInfo.GetParameterInfo(param);
            return typeInfo.IsCSharpStruct;
        }

        private static bool IsStruct(Type csType)
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

        //public static string ToCPPTypeFromCSharp(Type csharpType)
        //{
        //    foreach(var itTypeInfo in MapToCSharp)
        //    {
        //        if (itTypeInfo.Value.CSharpType == csharpType)
        //        {
        //            return itTypeInfo.Value.CPPTypeName;
        //        }
        //    }

        //    throw new Exception(string.Format("Can't find cpp type for {0}", csharpType.ToString()));
        //}

        // Ignore array option
        public static string ElementTypeNameFor(TypeUsage usage, Parameter param)
        {
            var typeInfo = GetParameterInfo(param);
            //Type csType = SystemTypeInfo.ToCSharpType(param.Type.ToString());
            switch (usage)
            {
                case TypeUsage.CPP:
                    return typeInfo.CPPTypeName;
                case TypeUsage.CPPFunction:
                    return typeInfo.CPPTypeName;
                case TypeUsage.CPPForSharp:
                    {
                        var cppTypeName = typeInfo.CPPTypeName;
                        //if (csType.IsArray)
                        if (param.IsArray)
                            return cppTypeName;//ToCPPTypeFromCSharp(csType.GetElementType());
                        else
                            return cppTypeName;
                    }
                case TypeUsage.CSharp:
                    return typeInfo.CSharpTypeName;
                case TypeUsage.CSharpFunction:
                    return typeInfo.CSharpTypeName;
                case TypeUsage.CSharpNative:
                    if (typeInfo.IsEnum)
                        return "int";
                    else
                        return typeInfo.CSharpTypeName;
            }

            throw new Exception("Invalid type name:" + param.TypeName);
        }

        public static string TypeNameOnlyFor(TypeUsage usage, Parameter param)
        {
            string elementTypeName = ElementTypeNameFor(usage, param);
            var typeInfo = GetParameterInfo(param);
            //Type csType = SystemTypeInfo.ToCSharpType(param.Type);
            //bool bIsStruct = IsStruct(param.Type);

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
                    if (param.IsArray || typeInfo.IsCSharpArray)
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

            throw new Exception("Invalid type name:" + param.TypeName);
        }

        public static string TypeNameFor(TypeUsage usage, Parameter param)
        {
            var typeInfo = GetParameterInfo(param);

            //Type csType = SystemTypeInfo.ToCSharpType(param.Type);
            //bool bIsStruct = IsStruct(param.Type);

            switch (usage)
            {
                case TypeUsage.CPP:
                    if(param.IsArray)
                        if (param.TypeName == "String")
                            return string.Format("ArrayObject<{0}>", typeInfo.CPPTypeName);
                        else
                            return string.Format("Array<{0}>", typeInfo.CPPTypeName);
                    else
                        return typeInfo.CPPTypeName;
                case TypeUsage.CPPFunction:
                    if (param.IsArray)
                        if (param.TypeName == "String")
                            return string.Format("const ArrayObject<{0}>&", typeInfo.CPPTypeName);
                        else
                            return string.Format("const Array<{0}>&", typeInfo.CPPTypeName);
                    else if(typeInfo.IsCSharpStruct)
                        return string.Format("const {0}&", typeInfo.CPPTypeName);
                    else
                        return typeInfo.CPPTypeName;
                case TypeUsage.CPPForSharp:
                    {
                        var cppTypeName = typeInfo.CPPTypeName;// SystemTypeInfo.ToCPPType(param.Type);
                        if (param.IsArray)
                            if (param.TypeName == "String")
                                return string.Format("intptr_t", typeInfo.CPPTypeName);
                            else
                                return string.Format("const {0}*", cppTypeName);
                        else if (typeInfo.CSharpTypeName == "string")
                            return cppTypeName;
                        else if (typeInfo.IsCSharpStruct)
                            return string.Format("const {0}&", cppTypeName);
                        else if (typeInfo.IsEnum)
                            return "int";
                        else
                            return cppTypeName;
                    }
                case TypeUsage.CSharp:
                    if (param.IsArray)
                        return typeInfo.CSharpTypeName + "[]";
                    else
                        return typeInfo.CSharpTypeName;
                case TypeUsage.CSharpFunction:
                    if (param.IsArray)
                        return typeInfo.CSharpTypeName + "[]";
                    else if(typeInfo.IsCSharpStruct)
                        return "ref" + typeInfo.CSharpTypeName;
                    else
                        return typeInfo.CSharpTypeName;
                case TypeUsage.CSharpNative:
                    {
                        if (param.IsArray)
                        {
                            if (typeInfo.IsString)
                                return "IntPtr";
                            else if (typeInfo.IsCSharpStruct)
                                return string.Format("{0}[]", typeInfo.CSharpTypeName);
                            else if (typeInfo.IsEnum)
                                return "int[]";// TODO: actually I can't support this
                            else
                                return typeInfo.CSharpTypeName + "[]";
                        }
                        else
                        {
                            //if (csType == typeof(string))
                            if (typeInfo.IsString)
                                return "[MarshalAs(UnmanagedType.LPArray)] byte[]";
                            else if (typeInfo.IsCSharpStruct)
                                return string.Format("ref {0}", typeInfo.CSharpTypeName);
                            else if (typeInfo.IsEnum)
                                return "int";
                            else
                                return typeInfo.CSharpTypeName;
                        }
                    }
            }

            throw new Exception("Invalid type name:"+ param.TypeName);
        }

        public static TypeMap GetParameterInfo(string paramTypeName)
        {
            return MapToCSharp[paramTypeName];
        }
        public static TypeMap GetParameterInfo(Parameter param)
        {
            return MapToCSharp[param.TypeName];
        }
    }

}

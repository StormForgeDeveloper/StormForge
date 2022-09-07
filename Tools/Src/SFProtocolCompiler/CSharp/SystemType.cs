////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
            public bool IsVariableSize;
            public string CSharpTypeName;
            public bool IsCSharpStruct;
            public bool IsEnum;
            public bool IsCSharpArray;
            public bool UseGenericVariableBuilderInterface;
            public string CPPTypeName;

            public bool IsString => XMLType == "String";

            public TypeMap(string xmlType, bool InIsVariableSize, Type chType, string cppTypeName = null, bool InUseGenericVariableBuilderInterface = false)
            {
                XMLType = xmlType;
                IsVariableSize = InIsVariableSize;
                CSharpTypeName = chType.ToString();
                IsCSharpStruct = IsStruct(chType);
                IsEnum = chType.IsEnum;
                IsCSharpArray = chType.IsArray;
                UseGenericVariableBuilderInterface = InUseGenericVariableBuilderInterface;
                CPPTypeName = cppTypeName ?? XMLType;
            }

            public TypeMap(ProtocolXml.ProtocolTypesDataType newType)
            {
                XMLType = newType.TypeName;
                IsVariableSize = newType.IsVariableSize;
                CSharpTypeName = newType.CSharpTypeName;
                IsCSharpStruct = newType.IsCSharpStruct;
                IsEnum = newType.IsEnum;
                IsCSharpArray = newType.IsCSharpArray;
                UseGenericVariableBuilderInterface = newType.UseGenericVariableBuilderInterface;
                CPPTypeName = newType.CppTypeName ?? XMLType;
            }
        };


        static TypeMap[] TypesMapList = new TypeMap[]{
            new TypeMap( "String", true, typeof(String), cppTypeName:"const char*" ),
            new TypeMap( "int8", false, typeof(SByte), cppTypeName:"int8_t" ),
            new TypeMap( "uint8", false, typeof(Byte), cppTypeName:"uint8_t" ),
            new TypeMap( "int16", false, typeof(Int16), cppTypeName:"int16_t" ),
            new TypeMap( "uint16", false, typeof(UInt16), cppTypeName:"uint16_t" ),
            new TypeMap( "int32", false, typeof(Int32), cppTypeName:"int32_t" ),
            new TypeMap( "uint32", false, typeof(UInt32), cppTypeName:"uint32_t" ),
            new TypeMap( "int", false, typeof(Int32), cppTypeName:"int32_t" ),
            new TypeMap( "uint", false, typeof(UInt32), cppTypeName:"uint32_t" ),
            new TypeMap( "int64", false, typeof(Int64), cppTypeName:"int64_t" ),
            new TypeMap( "uint64", false, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "intptr", false, typeof(IntPtr), cppTypeName:"intptr_t" ),
            new TypeMap( "WORD", false, typeof(UInt16), cppTypeName:"uint16_t" ),
            new TypeMap( "DWORD", false, typeof(UInt32), cppTypeName:"uint32_t" ),
            new TypeMap( "QWORD", false, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "float", false, typeof(float), cppTypeName:"float" ),
            new TypeMap( "Time32", false, typeof(UInt32), cppTypeName:"uint32_t" ),
            new TypeMap( "Time64", false, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "TransactionID", false, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "AccountID", false, typeof(UInt64) ),
            new TypeMap( "PlayerID", false, typeof(UInt64) ),
            new TypeMap( "CharacterID", false, typeof(UInt32) ),
            new TypeMap( "FacebookUID", false, typeof(UInt64) ),
            new TypeMap( "PlayerPlatformID", false, typeof(PlayerPlatformID), InUseGenericVariableBuilderInterface:true ),
            new TypeMap( "AuthTicket", false, typeof(UInt64) ),
            new TypeMap( "GameInsID", false, typeof(UInt32) ),
            new TypeMap( "GameInsUID", false, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "EntityID", false, typeof(UInt32) ),
            new TypeMap( "EntityUID", false, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "PartyUID", false, typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "ServerID", false, typeof(UInt32) ),
            new TypeMap( "ClusterID", false, typeof(UInt32) ),
            new TypeMap( "Result", false, typeof(Int32) ),
            new TypeMap( "NotificationType", false, typeof(Int16) ),
            new TypeMap( "RankingType", false, typeof(RankingType) ),
            new TypeMap( "PlayerRole", false, typeof(PlayerRole), cppTypeName:"uint8_t" ),
            new TypeMap( "GameStateID", false, typeof(GameStateID), cppTypeName:"uint8_t" ),
            new TypeMap( "GameWinner", false, typeof(GameWinner), cppTypeName:"uint8_t" ),
            new TypeMap( "PlayerKilledReason", false, typeof(PlayerKilledReason), cppTypeName:"uint8_t" ),
            new TypeMap( "PlayerRevealedReason", false, typeof(PlayerRevealedReason), cppTypeName:"uint8_t" ),
            new TypeMap( "GameID", false, typeof(UInt32), cppTypeName:"uint32_t" ),
            new TypeMap( "StringCrc32", false, typeof(UInt32), cppTypeName:"StringCrc32" ),
            new TypeMap( "StringCrc64", false, typeof(UInt64), cppTypeName:"StringCrc64" ),
            new TypeMap( "ClusterType", false, typeof(ClusterType) ),
            new TypeMap( "ClusterMembership", false, typeof(ClusterMembership) ),
            new TypeMap( "ServiceStatus", false, typeof(ServiceStatus) ),
            new TypeMap( "ActorMovement", false, typeof(ActorMovement), InUseGenericVariableBuilderInterface:true ),
            new TypeMap( "MatchingPlayerInformation", false, typeof(MatchingPlayerInformation) ),
            new TypeMap( "MatchingQueueTicket", false, typeof(MatchingQueueTicket) ),
            new TypeMap( "LocalUID", false, typeof(LocalUID), cppTypeName:"uint64_t" ),
            new TypeMap( "Variable", true, typeof(Variable), cppTypeName:"Variable" ),
            new TypeMap( "VariableTable", true, typeof(VariableTable), cppTypeName:"VariableTable" ),
            new TypeMap( "Vector2", false, typeof(Vector2) ),
            new TypeMap( "Vector3", false, typeof(Vector3) ),
            new TypeMap( "Vector4", false, typeof(Vector4) ),
            new TypeMap( "NetAddress", false, typeof(NetAddress) ),
            new TypeMap( "NetClass", false, typeof(UInt32) ),
            new TypeMap( "RouteContext", false, typeof(SFRouteContext) ),
            new TypeMap( "ServiceInformation", false, typeof(ServiceInformation) ),
            new TypeMap( "PlayerInformation", false, typeof(PlayerInformation) ),
            new TypeMap( "RankingPlayerInformation", false, typeof(RankingPlayerInformation) ),
            new TypeMap( "FriendInformation", false, typeof(FriendInformation) ),
            new TypeMap( "ServerFriendInformation", false, typeof(ServerFriendInformation) ),
            new TypeMap( "TotalRankingPlayerInformation", false, typeof(TotalRankingPlayerInformation) ),
            new TypeMap( "PerformanceCounterInfo", false, typeof(PerformanceCounterInfo) ),
            new TypeMap( "PerformanceCounterInstanceInfo", false, typeof(PerformanceCounterInstanceInfo) ),
            new TypeMap( "RelayPlayerInfo", false, typeof(RelayPlayerInfo) ),
        };

        static Dictionary<string, TypeMap> MapToCSharp = new Dictionary<string, TypeMap>();
        static List<string> stm_CppTypeIncludes = new List<string>();
        static List<string> stm_CppTypeForwards = new List<string>();

        static SystemTypeInfo()
        {
            foreach (TypeMap typeMap in TypesMapList)
            {
                MapToCSharp.Add(typeMap.XMLType, typeMap);
            }
        }

        public static IReadOnlyList<string> CppTypeIncludes => stm_CppTypeIncludes;
        public static IReadOnlyList<string> CppTypeForwards => stm_CppTypeForwards;

        public static void AddTypeInfo(TypeMap newType)
        {
            MapToCSharp.Add(newType.XMLType, newType);
        }

        public static void AddTypeInfo(ProtocolXml.ProtocolTypesDataType newType)
        {
            var newTypeInfo = new SystemTypeInfo.TypeMap(newType);

            if (MapToCSharp.ContainsKey(newTypeInfo.XMLType))
                MapToCSharp.Remove(newTypeInfo.XMLType);

            MapToCSharp.Add(newTypeInfo.XMLType, newTypeInfo);

            if (!string.IsNullOrEmpty(newType.CppTypeInclude))
            {
                var includes = newType.CppTypeInclude.Split(',');

                foreach (var include in includes)
                {
                    if (stm_CppTypeIncludes.FindIndex((x) => x == include) < 0)
                        stm_CppTypeIncludes.Add(include);
                }
            }

            if (!string.IsNullOrEmpty(newType.CppTypeForward))
            {
                var forward = newType.CppTypeForward;
                if (stm_CppTypeForwards.FindIndex((x) => x == forward) < 0)
                    stm_CppTypeForwards.Add(forward);
                
            }
        }

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

        // Ignore array option
        public static string ElementTypeNameFor(TypeUsage usage, Parameter param)
        {
            var typeInfo = GetParameterInfo(param);

            switch (usage)
            {
                case TypeUsage.CPP:
                    return typeInfo.CPPTypeName;
                case TypeUsage.CPPFunction:
                    return typeInfo.CPPTypeName;
                case TypeUsage.CPPForSharp:
                    {
                        var cppTypeName = typeInfo.CPPTypeName;
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

            switch (usage)
            {
                case TypeUsage.CPP:
                    if(param.IsArray)
                        if (typeInfo.IsString)
                            return string.Format("ArrayObject<{0}>", typeInfo.CPPTypeName);
                        else
                            return string.Format("Array<{0}>", typeInfo.CPPTypeName);
                    else
                        return typeInfo.CPPTypeName;
                case TypeUsage.CPPFunction:
                    if (param.IsArray)
                        if (typeInfo.IsString)
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
                            if (typeInfo.IsString)
                                return string.Format("intptr_t", typeInfo.CPPTypeName);
                            else
                                return string.Format("const {0}*", cppTypeName);
                        else if (typeInfo.IsString)
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

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
    using AuthTicket = UInt64;
    using GameInstanceID = UInt32;
    using GameInstanceUID = UInt32;
    using EntityID = UInt32;
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
    public struct ServiceInformation
    {
        public EntityUID EntityUID;
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
            public string CSharpTypeName;
            public bool IsCSharpStruct;
            public bool IsEnum;
            public bool IsCSharpArray;
            public bool UseGenericVariableBuilderInterface;
            public string CPPTypeName;

            public bool IsString => XMLType == "String";

            public TypeMap(string xmlType, Type chType, string cppTypeName = null, bool InUseGenericVariableBuilderInterface = false)
            {
                XMLType = xmlType;
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
                CSharpTypeName = newType.CSharpTypeName;
                IsCSharpStruct = newType.IsCSharpStruct;
                IsEnum = newType.IsEnum;
                IsCSharpArray = newType.IsCSharpArray;
                UseGenericVariableBuilderInterface = newType.UseGenericVariableBuilderInterface;
                CPPTypeName = newType.CppTypeName ?? XMLType;
            }
        };


        static TypeMap[] TypesMapList = new TypeMap[]{
            new TypeMap( "String", typeof(String), cppTypeName:"const char*" ),
            new TypeMap( "int8", typeof(SByte), cppTypeName:"int8_t" ),
            new TypeMap( "uint8", typeof(Byte), cppTypeName:"uint8_t" ),
            new TypeMap( "byte", typeof(Byte), cppTypeName:"uint8_t" ),
            new TypeMap( "sbyte", typeof(SByte), cppTypeName:"int8_t" ),
            new TypeMap( "int16", typeof(Int16), cppTypeName:"int16_t" ),
            new TypeMap( "uint16", typeof(UInt16), cppTypeName:"uint16_t" ),
            new TypeMap( "int32", typeof(Int32), cppTypeName:"int32_t" ),
            new TypeMap( "uint32", typeof(UInt32), cppTypeName:"uint32_t" ),
            new TypeMap( "int", typeof(Int32), cppTypeName:"int32_t" ),
            new TypeMap( "uint", typeof(UInt32), cppTypeName:"uint32_t" ),
            new TypeMap( "int64", typeof(Int64), cppTypeName:"int64_t" ),
            new TypeMap( "uint64", typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "intptr", typeof(IntPtr), cppTypeName:"intptr_t" ),
            new TypeMap( "WORD", typeof(UInt16), cppTypeName:"uint16_t" ),
            new TypeMap( "DWORD", typeof(UInt32), cppTypeName:"uint32_t" ),
            new TypeMap( "QWORD", typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "float", typeof(float), cppTypeName:"float" ),
            new TypeMap( "Time32", typeof(UInt32), cppTypeName:"uint32_t" ),
            new TypeMap( "Time64", typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "TransactionID", typeof(SF.TransactionID), cppTypeName:"TransactionID" ),
            new TypeMap( "AccountID", typeof(SF.AccountID)),
            new TypeMap( "PlayerID",typeof(SF.AccountID) ),
            new TypeMap( "Guid",typeof(Guid) ),
            new TypeMap( "CharacterID", typeof(CharacterID) ),
            new TypeMap( "FacebookUID", typeof(UInt64) ),
            new TypeMap( "Platform", typeof(EPlatform), "EPlatform" ),
            new TypeMap( "PlayerPlatformID", typeof(PlayerPlatformID), InUseGenericVariableBuilderInterface:true ),
            new TypeMap( "AuthTicket", typeof(UInt64) ),
            new TypeMap( "GameInstanceUID", typeof(SF.GameInstanceUID) ),
            new TypeMap( "EntityID", typeof(UInt32)),
            new TypeMap( "EntityUID", typeof(UInt32)),
            new TypeMap( "PartyUID", typeof(UInt64), cppTypeName:"uint64_t" ),
            new TypeMap( "ServerID", typeof(UInt32) ),
            new TypeMap( "ClusterID", typeof(UInt32) ),
            new TypeMap( "Result", typeof(Result) ),
            new TypeMap( "NotificationType", typeof(Int16) ),
            new TypeMap( "RankingType", typeof(RankingType) ),
            new TypeMap( "PlayerRole", typeof(PlayerRole) ),
            new TypeMap( "GameStateID", typeof(GameStateID) ),
            new TypeMap( "GameWinner", typeof(GameWinner) ),
            new TypeMap( "PlayerKilledReason", typeof(PlayerKilledReason) ),
            new TypeMap( "PlayerRevealedReason", typeof(PlayerRevealedReason) ),
            new TypeMap( "GameID", typeof(UInt32), cppTypeName:"uint32_t" ),
            new TypeMap( "StringCrc32", typeof(UInt32), cppTypeName:"StringCrc32" ),
            new TypeMap( "StringCrc64"  , typeof(UInt64), cppTypeName:"StringCrc64" ),
            new TypeMap( "ClusterType", typeof(ClusterType) ),
            new TypeMap( "ClusterMembership", typeof(ClusterMembership) ),
            new TypeMap( "ServiceStatus", typeof(ServiceStatus) ),
            new TypeMap( "ActorMovement", typeof(ActorMovement), InUseGenericVariableBuilderInterface:true ),
            new TypeMap( "MatchingPlayerInformation", typeof(MatchingPlayerInformation) ),
            new TypeMap( "MatchingQueueTicket", typeof(MatchingQueueTicket) ),
            new TypeMap( "LocalUID", typeof(LocalUID), cppTypeName:"uint64_t" ),
            new TypeMap( "Variable", typeof(Variable), cppTypeName:"Variable" ),
            new TypeMap( "VariableTable", typeof(VariableTable), cppTypeName:"VariableTable" ),
            new TypeMap( "Vector2", typeof(SFVector2) ),
            new TypeMap( "Vector3", typeof(SFVector3) ),
            new TypeMap( "Vector4", typeof(SFVector4) ),
            new TypeMap( "NetAddress", typeof(NetAddress) ),
            new TypeMap( "NetClass", typeof(UInt32) ),
            new TypeMap( "RouteContext", typeof(SFRouteContext) ),
            new TypeMap( "ServiceInformation", typeof(ServiceInformation) ),
            new TypeMap( "PlayerInformation", typeof(PlayerInformation) ),
            new TypeMap( "RankingPlayerInformation", typeof(RankingPlayerInformation) ),
            new TypeMap( "FriendInformation", typeof(FriendInformation) ),
            new TypeMap( "TotalRankingPlayerInformation", typeof(TotalRankingPlayerInformation) ),
            new TypeMap( "PerformanceCounterInfo", typeof(PerformanceCounterInfo) ),
            new TypeMap( "PerformanceCounterInstanceInfo", typeof(PerformanceCounterInstanceInfo) ),
            new TypeMap( "RelayPlayerInfo", typeof(RelayPlayerInfo) ),
            new TypeMap( "AchievementStat", typeof(AchievementStat), InUseGenericVariableBuilderInterface:true ),
            new TypeMap( "LogEntryID", typeof(UInt32), InUseGenericVariableBuilderInterface:true ),
            new TypeMap( "TimeSpan", typeof(SF.TimeSpan), "TimeSpan", InUseGenericVariableBuilderInterface:true ),
            new TypeMap( "bool", typeof(bool), "bool", InUseGenericVariableBuilderInterface:true ),
            new TypeMap( "ObjectInformation", typeof(SF.ObjectInformation), InUseGenericVariableBuilderInterface:true ),
            new TypeMap( "NamedVariable", typeof(SF.NamedVariable), InUseGenericVariableBuilderInterface:true ),
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
                Console.WriteLine("Can't find cpp type {0}, error:{1}", paramTypeName, exp.Message);
                throw;
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

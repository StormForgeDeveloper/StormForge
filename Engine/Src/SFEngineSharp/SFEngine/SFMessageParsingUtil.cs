////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection interface
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;


namespace SF
{


    static internal class SFMessageParsingUtil
    {

#if UNITY_STANDALONE
        [AOT.MonoPInvokeCallback(typeof(SFConnectionGroup.SET_MESSAGE_FUNCTION))]
#endif
        static internal void MessageParseSetEventCallback(SFConnection.EventTypes eventType, int result, SFConnection.ConnectionState state)
        {
            System.Diagnostics.Debug.Assert(stm_Event.EventType == SFConnection.EventTypes.EVT_NONE);
            stm_Event.EventType = eventType;
            stm_Event.HResult.Code = result;
            stm_Event.State = state;
        }

#if UNITY_STANDALONE
        [AOT.MonoPInvokeCallback(typeof(SFConnectionGroup.SET_MESSAGE_FUNCTION))]
#endif
        static internal void MessageParseCreateCallback(UInt32 messageID)
        {
            System.Diagnostics.Debug.Assert(stm_ParsingMessage == null);
            stm_ParsingMessage = new SFMessage((int)messageID);
        }


#if UNITY_STANDALONE
        [AOT.MonoPInvokeCallback(typeof(SFConnectionGroup.SET_FUNCTION))]
#endif
        static internal void MessageParseSetValue(string stringHash, string typeNameHash, IntPtr Value)
        {
            System.Diagnostics.Debug.Assert(stm_ParsingMessage != null);
            switch (typeNameHash)
            {
                case "Result":
                    stm_ParsingMessage.SetValue(stringHash, new Result(Marshal.ReadInt32(Value)));
                    break;
                case "int":
                    stm_ParsingMessage.SetValue(stringHash, Marshal.ReadInt32(Value));
                    break;
                case "uint":
                    stm_ParsingMessage.SetValue(stringHash, (uint)Marshal.ReadInt32(Value));
                    break;
                case "int8":
                    stm_ParsingMessage.SetValue(stringHash, Marshal.ReadByte(Value));
                    break;
                case "uint8":
                    stm_ParsingMessage.SetValue(stringHash, (uint)Marshal.ReadByte(Value));
                    break;
                case "int16":
                    stm_ParsingMessage.SetValue(stringHash, Marshal.ReadInt16(Value));
                    break;
                case "uint16":
                    stm_ParsingMessage.SetValue(stringHash, (uint)Marshal.ReadInt16(Value));
                    break;
                case "int32":
                    stm_ParsingMessage.SetValue(stringHash, Marshal.ReadInt32(Value));
                    break;
                case "uint32":
                    stm_ParsingMessage.SetValue(stringHash, (uint)Marshal.ReadInt32(Value));
                    break;
                case "int64":
                    stm_ParsingMessage.SetValue(stringHash, Marshal.ReadInt64(Value));
                    break;
                case "uint64":
                    stm_ParsingMessage.SetValue(stringHash, (UInt64)Marshal.ReadInt64(Value));
                    break;
                case "uint128":
                    stm_ParsingMessage.SetValue(stringHash, Marshal.PtrToStructure(Value, typeof(SFUInt128)));
                    break;
                case "float":
                    stm_ParsingMessage.SetValue(stringHash, ReadFloat(Value));
                    break;
                case "double":
                    stm_ParsingMessage.SetValue(stringHash, ReadDouble(Value));
                    break;
                case "RouteContext":
                    stm_ParsingMessage.SetValue(stringHash, Marshal.PtrToStructure(Value, typeof(SFRouteContext)));
                    break;
                case "NetAddress":
                    stm_ParsingMessage.SetValue(stringHash, Marshal.PtrToStructure(Value, typeof(NetAddress)));
                    break;
                case "MatchingQueueTicket":
                    stm_ParsingMessage.SetValue(stringHash, Marshal.PtrToStructure(Value, typeof(MatchingQueueTicket)));
                    break;
                case "PlayerInformation":
                    stm_ParsingMessage.SetValue(stringHash, Marshal.PtrToStructure(Value, typeof(PlayerInformation)));
                    break;
                case "FriendInformation":
                    stm_ParsingMessage.SetValue(stringHash, Marshal.PtrToStructure(Value, typeof(FriendInformation)));
                    break;
                case "TotalRankingPlayerInformation":
                    stm_ParsingMessage.SetValue(stringHash, Marshal.PtrToStructure(Value, typeof(TotalRankingPlayerInformation)));
                    break;
                case "RelayPlayerInfo":
                    stm_ParsingMessage.SetValue(stringHash, Marshal.PtrToStructure(Value, typeof(RelayPlayerInfo)));
                    break;
                //case "ActorMovement":
                //    stm_ParsingMessage.SetValue(stringHash, Marshal.PtrToStructure(Value, typeof(ActorMovement)));
                //    break;
                //case "Vector2":
                //    stm_ParsingMessage.SetValue(stringHash, Marshal.PtrToStructure(Value, typeof(Vector2)));
                //    break;
                //case "Vector3":
                //    stm_ParsingMessage.SetValue(stringHash, Marshal.PtrToStructure(Value, typeof(Vector3)));
                //    break;
                //case "Vector4":
                //    stm_ParsingMessage.SetValue(stringHash, Marshal.PtrToStructure(Value, typeof(Vector4)));
                //    break;
                //case "VariableTable":
                //VariableTable parsedValue = new VariableTable();
                //parsedValue.FromSerializedMemory(arrayCount, Value);
                //stm_ParsingMessage.SetValue(stringHash, parsedValue);
                //break;
                default:
                    // TODO: gradually move to TypeSerialization
                    var typeInfo = TypeSerialization.GetTypeInfo(new StringCrc32(typeNameHash));
                    if (typeInfo != null)
                    {
                        stm_ParsingMessage.SetValue(stringHash, typeInfo.DeserializeNative(ref Value));
                    }
                    else
                    {
                        SF.Log.Error("MessageParseSetValue failed, type:{0}", stringHash);
                    }
                    break;
            }
        }


#if UNITY_STANDALONE
        [AOT.MonoPInvokeCallback(typeof(SFConnectionGroup.SET_ARRAY_FUNCTION))]
#endif
        static internal void MessageParseSetArray(string stringHash, string typeNameHash, int arrayCount, IntPtr Value)
        {
            switch (typeNameHash)
            {
                case "int8":
                    {
                        var newArray = new sbyte[arrayCount];
                        MarshalCopy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "uint8":
                    {
                        var newArray = new byte[arrayCount];
                        if (arrayCount > 0) Marshal.Copy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "int16":
                    {
                        var newArray = new Int16[arrayCount];
                        if (arrayCount > 0) Marshal.Copy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "uint16":
                    {
                        var newArray = new UInt16[arrayCount];
                        MarshalCopy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "int":
                case "int32":
                    {
                        var newArray = new int[arrayCount];
                        if (arrayCount > 0) Marshal.Copy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "uint":
                case "uint32":
                    {
                        var newArray = new uint[arrayCount];
                        MarshalCopy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "int64":
                    {
                        var newArray = new Int64[arrayCount];
                        if (arrayCount > 0) Marshal.Copy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "uint64":
                    {
                        var newArray = new UInt64[arrayCount];
                        MarshalCopy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "uint128":
                    {
                        var newArray = new SFUInt128[arrayCount];
                        MarshalCopy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "float":
                    {
                        var newArray = new float[arrayCount];
                        if (arrayCount > 0) Marshal.Copy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "double":
                    {
                        var newArray = new double[arrayCount];
                        MarshalCopy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "string":
                    {
                        var newArray = new string[arrayCount];
                        MarshalCopy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "single_string": // Regular string parameter comes here
                    {
                        stm_ParsingMessage.SetValue(stringHash, ReadString(arrayCount, Value));
                    }
                    break;
                case "RouteContext":
                    {
                        var newArray = new SFRouteContext[arrayCount];
                        MarshalCopy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "NetAddress":
                    {
                        var newArray = new NetAddress[arrayCount];
                        MarshalCopy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "PlayerInformation":
                    {
                        var newArray = new PlayerInformation[arrayCount];
                        MarshalCopy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "FriendInformation":
                    {
                        var newArray = new FriendInformation[arrayCount];
                        MarshalCopy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "TotalRankingPlayerInformation":
                    {
                        var newArray = new TotalRankingPlayerInformation[arrayCount];
                        MarshalCopy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "RelayPlayerInfo":
                    {
                        var newArray = new RelayPlayerInfo[arrayCount];
                        MarshalCopy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                //case "ActorMovement":
                //    {
                //        var newArray = new ActorMovement[arrayCount];
                //        MarshalCopy(Value, newArray, 0, arrayCount);
                //        stm_ParsingMessage.SetValue(stringHash, newArray);
                //    }
                //    break;
                case "Vector2":
                    {
                        var newArray = new Vector2[arrayCount];
                        MarshalCopy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "Vector3":
                    {
                        var newArray = new Vector3[arrayCount];
                        MarshalCopy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "Vector4":
                    {
                        var newArray = new Vector4[arrayCount];
                        MarshalCopy(Value, newArray, 0, arrayCount);
                        stm_ParsingMessage.SetValue(stringHash, newArray);
                    }
                    break;
                case "VariableTable":
                    {
                        VariableTable parsedValue = new VariableTable();
                        parsedValue.FromSerializedMemory(arrayCount, Value);
                        stm_ParsingMessage.SetValue(stringHash, parsedValue);
                    }
                    break;
                case "Array<VariableTable>":
                    {
                        byte[] byteData = new byte[arrayCount];
                        Marshal.Copy(Value, byteData, 0, byteData.Length);
                        List<VariableTable> tableList = new List<VariableTable>();
                        using (BinaryReader reader = new BinaryReader(new MemoryStream(byteData)))
                        {
                            var NumElement = reader.ReadInt16();
                            for (int iElement = 0; iElement < NumElement; iElement++)
                            {
                                VariableTable parsedValue = new VariableTable();
                                parsedValue.FromSerializedMemory(reader);
                                tableList.Add(parsedValue);
                            }
                        }

                        stm_ParsingMessage.SetValue(stringHash, tableList.ToArray());
                    }
                    break;

                default:
                    // TODO: gradually move to TypeSerialization
                    var typeInfo = TypeSerialization.GetTypeInfo(new StringCrc32(typeNameHash));
                    if (typeInfo != null)
                    {
                        var arrayValue = (Array)Array.CreateInstance(typeInfo.Type, arrayCount);
                        if (arrayValue != null)
                        {
                            for (int index = 0; index < arrayCount; index++)
                                arrayValue.SetValue(typeInfo.DeserializeNative(ref Value), index);
                        }
                        stm_ParsingMessage.SetValue(stringHash, arrayValue);
                    }
                    else
                    {
                        SF.Log.Error("MessageParseSetArray failed, type:{0}", stringHash);
                    }
                    break;
            }

        }


        internal static float ReadFloat(IntPtr value)
        {
            unsafe
            {
                return *(float*)value;
            }
        }

        internal static double ReadDouble(IntPtr value)
        {
            unsafe
            {
                return *(double*)value;
            }
        }

        static byte[] StringConvertBuffer = null;
        internal static string ReadString(int byteCount, IntPtr value)
        {
            if (StringConvertBuffer == null || StringConvertBuffer.Length < byteCount)
                StringConvertBuffer = new byte[(int)(byteCount * 1.5)];

            Marshal.Copy(value, StringConvertBuffer, 0, byteCount);
            return System.Text.Encoding.UTF8.GetString(StringConvertBuffer, 0, byteCount);
        }

        internal static void MarshalCopy(IntPtr source, sbyte[] destination, int startIndex, int length)
        {
            unsafe
            {
                sbyte* pCur = (sbyte*)source;
                for (int iIndex = 0; iIndex < length; iIndex++, pCur++)
                    destination[iIndex] = *pCur;
            }
        }

        internal static void MarshalCopy(IntPtr source, UInt16[] destination, int startIndex, int length)
        {
            unsafe
            {
                UInt16* pCur = (UInt16*)source;
                for (int iIndex = 0; iIndex < length; iIndex++, pCur++)
                    destination[iIndex] = *pCur;
            }
        }

        internal static void MarshalCopy(IntPtr source, uint[] destination, int startIndex, int length)
        {
            unsafe
            {
                uint* pCur = (uint*)source;
                for (int iIndex = 0; iIndex < length; iIndex++, pCur++)
                    destination[iIndex] = *pCur;
            }
        }

        internal static void MarshalCopy(IntPtr source, UInt64[] destination, int startIndex, int length)
        {
            unsafe
            {
                UInt64* pCur = (UInt64*)source;
                for (int iIndex = 0; iIndex < length; iIndex++, pCur++)
                    destination[iIndex] = *pCur;
            }
        }

        internal static void MarshalCopy(IntPtr source, double[] destination, int startIndex, int length)
        {
            unsafe
            {
                double* pCur = (double*)source;
                for (int iIndex = 0; iIndex < length; iIndex++, pCur++)
                    destination[iIndex] = *pCur;
            }
        }

        internal static void MarshalCopy(IntPtr source, string[] destination, int startIndex, int length)
        {
            unsafe
            {
                IntPtr* pCurStrStart = (IntPtr*)source;
                for (int iIndex = 0; iIndex < length; iIndex++, pCurStrStart++)
                {
                    IntPtr CurStrStart = *pCurStrStart;
                    int strLen = 0;
                    for (; strLen < StringDecodeBuffer.Length; strLen++)
                    {
                        var curByte = Marshal.ReadByte(CurStrStart, strLen);
                        StringDecodeBuffer[strLen] = curByte;
                        if (curByte == 0)
                            break;
                    }

                    destination[iIndex] = Encoding.UTF8.GetString(StringDecodeBuffer, 0, strLen);
                }
            }
        }

        internal static void MarshalCopy<DataType>(IntPtr source, DataType[] destination, int startIndex, int length)
        {
            unsafe
            {
                IntPtr pCur = source;
                int dataSize = 1;
                for (int iIndex = 0; iIndex < length; iIndex++, pCur = new IntPtr(pCur.ToInt64() + dataSize))
                {
                    destination[iIndex] = (DataType)Marshal.PtrToStructure(pCur, typeof(DataType));
                    dataSize = Marshal.SizeOf(destination[iIndex]);
                }
            }
        }

        // IOS IL2CPP doesn't support native callback of instance, so it has to be static
        static internal byte[] StringDecodeBuffer = new byte[32 * 1024];
        static internal SFMessage stm_ParsingMessage = null;
        static internal object stm_ParsingLock = new object();
        static internal SFConnection.Event stm_Event;


    }
}


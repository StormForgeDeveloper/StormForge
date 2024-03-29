////////////////////////////////////////////////////////////////////////////////
//
// CopyRight (c) Kyungkun Ko
//
// Author : KyungKun Ko
//
// Description : Type serialization
//
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;

#nullable enable

namespace SF
{

    public static class TypeSerialization
    {
        public class TypeInfo
        {
            public delegate void SerializerFunc(BinaryWriter writer, object value);
            public delegate object? DeserializerFunc(BinaryReader reader);
            public delegate object? DeserializeNativeFunc(ref IntPtr valuePtr);

            public readonly Type Type;
            public readonly StringCrc32 TypeNameCrc;
            public readonly SerializerFunc Serializer;
            public readonly DeserializerFunc Deserializer;
            public readonly DeserializeNativeFunc DeserializeNative;


            public TypeInfo(Type InType, StringCrc32 InTypeNameCrc, SerializerFunc InSerializer, DeserializerFunc InDeserializer, DeserializeNativeFunc InDeserializeNative)
            {
                Type = InType;
                TypeNameCrc = InTypeNameCrc;
                Serializer = InSerializer;
                Deserializer = InDeserializer;
                DeserializeNative = InDeserializeNative;
            }

            public TypeInfo(Type InType, string InTypeName, SerializerFunc InSerializer, DeserializerFunc InDeserializer, DeserializeNativeFunc InDeserializeNative)
                : this(InType, new StringCrc32(InTypeName), InSerializer, InDeserializer, InDeserializeNative)
            {
            }

        };

        public static Byte ReadUInt8(ref IntPtr valuePtr)
        {
            var value = Marshal.ReadByte(valuePtr);
            valuePtr += 1;
            return value;
        }

        public static SByte ReadInt8(ref IntPtr valuePtr)
        {
            var value = Marshal.ReadByte(valuePtr);
            valuePtr += 1;
            return (SByte)value;
        }

        public static UInt16 ReadUInt16(ref IntPtr valuePtr)
        {
            var value = Marshal.ReadInt16(valuePtr);
            valuePtr += 2;
            return (UInt16)value;
        }

        public static Int16 ReadInt16(ref IntPtr valuePtr)
        {
            var value = Marshal.ReadInt16(valuePtr);
            valuePtr += 2;
            return value;
        }

        public static UInt32 ReadUInt32(ref IntPtr valuePtr)
        {
            var value = Marshal.ReadInt32(valuePtr);
            valuePtr += 4;
            return (UInt32)value;
        }

        public static Int32 ReadInt32(ref IntPtr valuePtr)
        {
            var value = Marshal.ReadInt32(valuePtr);
            valuePtr += 4;
            return value;
        }

        public static UInt64 ReadUInt64(ref IntPtr valuePtr)
        {
            var value = Marshal.ReadInt64(valuePtr);
            valuePtr += 8;
            return (UInt64)value;
        }

        public static Int64 ReadInt64(ref IntPtr valuePtr)
        {
            var value = Marshal.ReadInt64(valuePtr);
            valuePtr += 8;
            return value;
        }

        public static float ReadFloat(ref IntPtr value)
        {
            unsafe
            {
                var ptr = (float*)value;
                value += 4;
                return *ptr;
            }
        }

        public static double ReadDouble(ref IntPtr value)
        {
            unsafe
            {
                var ptr = (double*)value;
                value += 8;
                return *ptr;
            }
        }

        static byte[]? StringConvertBuffer = null;
        public static string ReadString(int byteCount, ref IntPtr value)
        {
            if (StringConvertBuffer == null || StringConvertBuffer.Length < byteCount)
                StringConvertBuffer = new byte[(int)(byteCount * 1.5)];

            Marshal.Copy(value, StringConvertBuffer, 0, byteCount); value += byteCount;
            return System.Text.Encoding.UTF8.GetString(StringConvertBuffer, 0, byteCount);
        }

        public static T? ReadStruct<T>(ref IntPtr valuePtr)
        {
            Type type = typeof(T);
            var value = Marshal.PtrToStructure(valuePtr, type);
            if (value != null)
            {
                valuePtr += Marshal.SizeOf(type);
                return (T)value;
            }
            else
            {
                return default(T);
            }
        }

        public static SFVector4 ReadVector4(BinaryReader reader)
        {
            return new SFVector4()
            {
                x = reader.ReadSingle(),
                y = reader.ReadSingle(),
                z = reader.ReadSingle(),
                w = reader.ReadSingle()
            };
        }
        public static void WriteVector4(BinaryWriter writer, ref SFVector4 value)
        {
            writer.Write(value.x);
            writer.Write(value.y);
            writer.Write(value.z);
            writer.Write(value.w);
        }


        static TypeInfo[] TypeInfoList = {
                new TypeInfo(typeof(object), "Null",
                    (writer, value) => {  },
                    (reader) => { return null; },
                    (ref IntPtr valuePtr) => { return null; }
                ),
                new TypeInfo(typeof(Result), "Result",
                    (writer, value) => { writer.Write(((Result)value).Code); },
                    (reader) => { return new Result(reader.ReadInt32()); },
                    (ref IntPtr valuePtr) => { valuePtr += 4; return new Result(Marshal.ReadInt32(valuePtr - 4)); }
                ),
                new TypeInfo(typeof(bool), "bool",
                (writer, value) => { writer.Write(((Int32)value)); },
                (reader) => { return reader.ReadInt32() != 0 ? true : false; },
                (ref IntPtr valuePtr) => { return ReadInt32(ref valuePtr) != 0 ? true : false; }),

            new TypeInfo(typeof(IntPtr), "void*",
                (writer, value) => { writer.Write((Int64)value); },
                (reader) => { return reader.ReadInt64(); },
                (ref IntPtr valuePtr) => { return ReadInt64(ref valuePtr); }),

            new TypeInfo(typeof(int), "int",
                (writer, value) => { writer.Write((int)value); },
                (reader) => { return reader.ReadInt32(); },
                (ref IntPtr valuePtr) => { return ReadInt32(ref valuePtr); }),

            new TypeInfo(typeof(uint), "uint",
                (writer, value) => { writer.Write((uint)value); },
                (reader) => { return reader.ReadUInt32(); },
                (ref IntPtr valuePtr) => { return ReadUInt32(ref valuePtr); }),

            new TypeInfo(typeof(Int32), "int32",
                (writer, value) => { writer.Write((Int32)value); },
                (reader) => { return reader.ReadInt32(); },
                (ref IntPtr valuePtr) => { return ReadInt32(ref valuePtr); }),

            new TypeInfo(typeof(UInt32), "uint32",
                (writer, value) => { writer.Write((UInt32)value); },
                (reader) => { return reader.ReadUInt32(); },
                (ref IntPtr valuePtr) => { return ReadUInt32(ref valuePtr); }),

            new TypeInfo(typeof(SByte), "int8",
                (writer, value) => { writer.Write((SByte)value); },
                (reader) => { return reader.ReadSByte(); },
                (ref IntPtr valuePtr) => { return ReadInt8(ref valuePtr); }),

            new TypeInfo(typeof(Byte), "uint8",
                (writer, value) => { writer.Write((Byte)value); },
                (reader) => { return reader.ReadByte(); },
                (ref IntPtr valuePtr) => { return ReadUInt8(ref valuePtr); }),

            new TypeInfo(typeof(Int16), "int16",
                (writer, value) => { writer.Write((Int16)value); },
                (reader) => { return reader.ReadInt16(); },
                (ref IntPtr valuePtr) => { return ReadInt16(ref valuePtr); }),

            new TypeInfo(typeof(UInt16), "uint16",
                (writer, value) => { writer.Write((UInt16)value); },
                (reader) => { return reader.ReadUInt16(); },
                (ref IntPtr valuePtr) => { return ReadUInt16(ref valuePtr); }),

            new TypeInfo(typeof(Int64), "int64",
                (writer, value) => { writer.Write((Int64)value); },
                (reader) => { return reader.ReadInt64(); },
                (ref IntPtr valuePtr) => { return ReadInt64(ref valuePtr); }),

            new TypeInfo(typeof(UInt64), "uint64",
                (writer, value) => { writer.Write((UInt64)value); },
                (reader) => { return reader.ReadUInt64(); },
                (ref IntPtr valuePtr) => { return ReadUInt64(ref valuePtr); }),

            new TypeInfo(typeof(SFUInt128), "uint128",
                (writer, value) => { var valueTemp = (SFUInt128)value; writer.Write(valueTemp.Low); writer.Write(valueTemp.High); },
                (reader) => { return new SFUInt128() { Low = reader.ReadUInt64(), High = reader.ReadUInt64() }; },
                (ref IntPtr valuePtr) => { return ReadStruct<SFUInt128>(ref valuePtr); }),

            new TypeInfo(typeof(float), "float",
                (writer, value) => { writer.Write((float)value); },
                (reader) => { return reader.ReadSingle(); },
                (ref IntPtr valuePtr) => { return ReadFloat(ref valuePtr); }),

            new TypeInfo(typeof(double), "double",
                (writer, value) => { writer.Write((double)value); },
                (reader) => { return reader.ReadDouble(); },
                (ref IntPtr valuePtr) => { return ReadDouble(ref valuePtr); }),

            new TypeInfo(typeof(UInt32), "hex32",
                (writer, value) => { writer.Write((UInt32)value); },
                (reader) => { return reader.ReadUInt32(); },
                (ref IntPtr valuePtr) => { return ReadUInt32(ref valuePtr); }),

            new TypeInfo(typeof(UInt64), "hex64",
                (writer, value) => { writer.Write((UInt64)value); },
                (reader) => { return reader.ReadUInt64(); },
                (ref IntPtr valuePtr) => { return ReadUInt64(ref valuePtr); }),

            new TypeInfo(typeof(string),
                "String",
                    (writer, value) =>
                    {
                        var valueTemp = (string)value;
                        byte[] bytesValue = System.Text.Encoding.UTF8.GetBytes(valueTemp + "\0");
                        writer.Write((UInt16)bytesValue.Length);
                        writer.Write(bytesValue);
                    },
                    (reader) =>
                    {
                        var bytesLen = reader.ReadUInt16();
                        byte[] byteBuffer = reader.ReadBytes(bytesLen);
                        return System.Text.Encoding.UTF8.GetString(byteBuffer, 0, bytesLen-1);
                    },
                    (ref IntPtr valuePtr) =>
                    {
                        var strLen = Marshal.ReadInt16(valuePtr); valuePtr += 2;
                        return ReadString(strLen, ref valuePtr);
                    }
                ),

            new TypeInfo(typeof(string),
                "string",
                    (writer, value) =>
                    {
                        var valueTemp = (string)value;
                        byte[] bytesValue = System.Text.Encoding.UTF8.GetBytes(valueTemp + "\0");
                        writer.Write((UInt16)bytesValue.Length);
                        writer.Write(bytesValue);
                    },
                    (reader) =>
                    {
                        var strLen = reader.ReadUInt16();
                        byte[] byteBuffer = reader.ReadBytes(strLen);
                        return System.Text.Encoding.UTF8.GetString(byteBuffer, 0, strLen-1);
                    },
                    (ref IntPtr valuePtr) =>
                    {
                        var strLen = Marshal.ReadInt16(valuePtr); valuePtr += 2;
                        return ReadString(strLen, ref valuePtr);
                    }
                ),

            new TypeInfo(typeof(string),
                "const char*",
                    (writer, value) =>
                    {
                        var valueTemp = (string)value;
                       byte[] bytesValue = System.Text.Encoding.UTF8.GetBytes(valueTemp + "\0");
                        writer.Write((UInt16)bytesValue.Length);
                        writer.Write(bytesValue);
                    },
                    (reader) =>
                    {
                        var strLen = reader.ReadUInt16();
                        byte[] byteBuffer = reader.ReadBytes(strLen);
                        return System.Text.Encoding.UTF8.GetString(byteBuffer, 0, strLen-1);
                    },
                    (ref IntPtr valuePtr) =>
                    {
                        var strLen = Marshal.ReadInt16(valuePtr); valuePtr += 2;
                        return ReadString(strLen, ref valuePtr);
                    }
                ),

            new TypeInfo(typeof(TransactionID), "TransactionID",
                (writer, value) => { writer.Write(((TransactionID)value).TransactionId); },
                (reader) => { return new TransactionID(){ TransactionId = reader.ReadUInt64() }; },
                (ref IntPtr valuePtr) => { return new TransactionID(){ TransactionId = ReadUInt64(ref valuePtr) }; }),

            new TypeInfo(typeof(SFVector2), "Vector2",
                (writer, value) => { var valueTemp = (SFVector2)value; writer.Write(valueTemp.x); writer.Write(valueTemp.y); },
                (reader) => { return new SFVector2() { x = reader.ReadSingle(), y = reader.ReadSingle() }; },
                (ref IntPtr valuePtr) => { return ReadStruct<SFVector2>(ref valuePtr); }),

            new TypeInfo(typeof(SFVector3), "Vector3",
                (writer, value) => { var valueTemp = (SFVector3)value; writer.Write(valueTemp.x); writer.Write(valueTemp.y); writer.Write(valueTemp.z); },
                (reader) => { return new SFVector3() { x = reader.ReadSingle(), y = reader.ReadSingle(), z = reader.ReadSingle() }; },
                (ref IntPtr valuePtr) => { return ReadStruct<SFVector3>(ref valuePtr); }),

            new TypeInfo(typeof(SFVector4), "Vector4",
                (writer, value) => { var valueTemp = (SFVector4)value; writer.Write(valueTemp.x); writer.Write(valueTemp.y); writer.Write(valueTemp.z); writer.Write(valueTemp.w); },
                (reader) => { return new SFVector4() { x = reader.ReadSingle(), y = reader.ReadSingle(), z = reader.ReadSingle(), w = reader.ReadSingle() }; },
                (ref IntPtr valuePtr) => { return ReadStruct<SFVector4>(ref valuePtr); }),

            new TypeInfo(typeof(UInt64), "StringCrc32",
                (writer, value) => { writer.Write(((StringCrc32)value).StringHash); },
                (reader) => { return new StringCrc32(reader.ReadUInt32()); },
                (ref IntPtr valuePtr) => { return new StringCrc32(ReadUInt32(ref valuePtr)); }),

            new TypeInfo(typeof(UInt64), "StringCrc64",
                (writer, value) => { writer.Write(((StringCrc64)value).StringHash); },
                (reader) => { return new StringCrc64(reader.ReadUInt64()); },
                (ref IntPtr valuePtr) => { return new StringCrc64(ReadUInt64(ref valuePtr)); }),

            new TypeInfo(typeof(byte[]), "BLOB",
                (writer, value) => { var byteArray = (byte[])value; writer.Write(byteArray); },
                (reader) =>
                {
                    var byteSize = reader.ReadUInt16();
                    var bytes = reader.ReadBytes(byteSize);
                    return bytes;
                },
                (ref IntPtr valuePtr) =>
                {
                    var byteSize = Marshal.ReadInt16(valuePtr); valuePtr += 2;
                    var bytes = new byte[byteSize];
                    Marshal.Copy(valuePtr, bytes, 0, byteSize); valuePtr += byteSize;
                    return bytes;
                }),

            new TypeInfo(typeof(ActorMovement), "ActorMovement",
                (writer, value) =>
                {
                    var item = (ActorMovement)value;
                    WriteVector4(writer, ref item.Position);
                    WriteVector4(writer, ref item.LinearVelocity);
                    writer.Write(item.ActorId);
                    writer.Write(item.AngularYaw);
                    writer.Write(item.MoveFrame);
                    writer.Write(item.MovementState);
                },
                (reader) =>
                {
                    var item = new ActorMovement();
                    item.Position = ReadVector4(reader);
                    item.LinearVelocity = ReadVector4(reader);
                    item.ActorId = reader.ReadUInt32();
                    item.AngularYaw = reader.ReadSingle();
                    item.MoveFrame = reader.ReadUInt32();
                    item.MovementState = reader.ReadUInt32();
                    return item;
                },
                (ref IntPtr valuePtr) =>
                {
                    var item = Marshal.PtrToStructure(valuePtr, typeof(ActorMovement));
                    if (item != null)
                        valuePtr += Marshal.SizeOf(item);
                    return item;
                }),

        new TypeInfo(typeof(Guid), "Guid",
                (writer, value) =>
                {
                    var item = (Guid)value;
                    byte[] byteArray = item.ToByteArray();
                    Debug.Assert(byteArray.Length == 16);
                    writer.Write(byteArray);
                },
                (reader) =>
                {
                    var item = new Guid();
                    item = new Guid(reader.ReadBytes(16));
                    return item;
                },
                (ref IntPtr valuePtr) =>
                {
                    var bytes = new byte[16];
                    var item = new Guid();
                    Marshal.Copy(valuePtr, bytes, 0, bytes.Length); valuePtr += bytes.Length;
                    item = new Guid(bytes);
                    return item;
                }),

        new TypeInfo(typeof(AccountID), "AccountID",
                (writer, value) =>
                {
                    var item = (AccountID)value;
                    byte[] byteArray = item.Guid.ToByteArray();
                    Debug.Assert(byteArray.Length == 16);
                    writer.Write(byteArray);
                },
                (reader) =>
                {
                    var item = new AccountID();
                    item = new AccountID(reader.ReadBytes(16));
                    return item;
                },
                (ref IntPtr valuePtr) =>
                {
                    var bytes = new byte[16];
                    var item = new AccountID();
                    Marshal.Copy(valuePtr, bytes, 0, bytes.Length); valuePtr += bytes.Length;
                    item.Guid = new Guid(bytes);
                    return item;
                }),

        new TypeInfo(typeof(CharacterID), "CharacterID",
                (writer, value) =>
                {
                    var item = (CharacterID)value;
                    byte[] byteArray = item.Guid.ToByteArray();
                    Debug.Assert(byteArray.Length == 16);
                    writer.Write(byteArray);
                },
                (reader) =>
                {
                    var item = new CharacterID();
                    item = new CharacterID(reader.ReadBytes(16));
                    return item;
                },
                (ref IntPtr valuePtr) =>
                {
                    var bytes = new byte[16];
                    var item = new CharacterID();
                    Marshal.Copy(valuePtr, bytes, 0, bytes.Length); valuePtr += bytes.Length;
                    item.Guid = new Guid(bytes);
                    return item;
                }),

        new TypeInfo(typeof(PlayerPlatformID), "PlayerPlatformID",
                (writer, value) =>
                {
                    var item = (PlayerPlatformID)value;
                    writer.Write(item.PlatformData);
                    byte[] byteArray = item.PlayerID.Guid.ToByteArray();
                    Debug.Assert(byteArray.Length == 16);
                    writer.Write(byteArray);
                },
                (reader) =>
                {
                    var item = new PlayerPlatformID();
                    item.PlatformData = reader.ReadByte();
                    item.PlayerID = new AccountID(reader.ReadBytes(16));
                    return item;
                },
                (ref IntPtr valuePtr) =>
                {
                    var bytes = new byte[16];
                    var item = new PlayerPlatformID();
                    item.PlatformData = Marshal.ReadByte(valuePtr); valuePtr += 1;
                    Marshal.Copy(valuePtr, bytes, 0, bytes.Length); valuePtr += bytes.Length;
                    item.PlayerID.Guid = new Guid(bytes);
                    return item;
                }),

            new TypeInfo(typeof(AchievementStat), "AchievementStat",
                (writer, value) =>
                {
                    var item = (AchievementStat)value;
                    writer.Write(item.AchievementStatId);
                    writer.Write(item.StatValue);
                },
                (reader) =>
                {
                    var item = new AchievementStat();
                    item.AchievementStatId = reader.ReadUInt32();
                    item.StatValue = reader.ReadInt32();
                    return item;
                },
                (ref IntPtr valuePtr) =>
                {
                    var item = Marshal.PtrToStructure(valuePtr, typeof(AchievementStat));
                    if (item != null)
                        valuePtr += Marshal.SizeOf(item);
                    return item;
                }),

            new TypeInfo(typeof(UInt32), "LogEntryID",
                (writer, value) =>
                {
                    writer.Write((UInt32)value);
                },
                (reader) =>
                {
                    return reader.ReadUInt32();
                },
                (ref IntPtr valuePtr) =>
                {
                    return (UInt32)Marshal.ReadInt32(valuePtr);
                }),

            new TypeInfo(typeof(SF.TimeSpan), "TimeSpan",
                (writer, value) =>
                {
                    writer.Write(((SF.TimeSpan)value).MilliSeconds);
                },
                (reader) =>
                {
                    return new SF.TimeSpan(){ MilliSeconds = reader.ReadInt64() };
                },
                (ref IntPtr valuePtr) =>
                {
                    return new SF.TimeSpan(){ MilliSeconds = ReadInt64(ref valuePtr) };
                }
                ),

        };

        static Dictionary<Type, TypeInfo> TypeInfoByType;
        static Dictionary<UInt32, TypeInfo> TypeInfoByTypeName;

        static TypeSerialization()
        {
            TypeInfoByType = new Dictionary<Type, TypeInfo>();
            TypeInfoByTypeName = new Dictionary<uint, TypeInfo>();

            foreach (var itItem in TypeInfoList)
            {
                AddTypeInfo(itItem);
            }
        }

        public static void AddTypeInfo(TypeInfo itItem)
        {
            if (!TypeInfoByType.ContainsKey(itItem.Type))
                TypeInfoByType.Add(itItem.Type, itItem);

            if (!TypeInfoByTypeName.ContainsKey(itItem.TypeNameCrc.StringHash))
                TypeInfoByTypeName.Add(itItem.TypeNameCrc.StringHash, itItem);
        }


        static public TypeInfo GetTypeInfo(object? value)
        {
            var objType = value as Type;
            if (objType == null)
            {
                if (value != null)
                    objType = value.GetType();
                else
                    objType = typeof(object);
            }

            TypeInfo? typeInfo;
            if (!TypeInfoByType.TryGetValue(objType, out typeInfo))
            {
                if (value != null)
                {
                    Log.Error("TypeSerialization.GetTypeInfo: Unknown type {0}", value.GetType().Name);
                    throw new Exception(string.Format("Unknown type {0}", value.GetType().Name));

                }
                else
                {
                    Log.Error("TypeSerialization.GetTypeInfo: Unknown type null");
                    throw new Exception("Unknown type null");

                }
            }

            return typeInfo;
        }

        static public TypeInfo GetTypeInfo(StringCrc32 typeName)
        {
            TypeInfo? typeInfo;
            if (!TypeInfoByTypeName.TryGetValue(typeName.StringHash, out typeInfo))
            {
                Log.Error("TypeSerialization.GetTypeInfo: Unknown type {0}", typeName);
                throw new Exception(string.Format("Unknown type {0}", typeName));
            }

            return typeInfo;
        }

    }


}

#nullable restore

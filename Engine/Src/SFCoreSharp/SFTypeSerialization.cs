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
using System.CodeDom;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;


namespace SF
{
    
    public static class TypeSerialization
    {
        public class TypeInfo
        {
            public delegate void SerializerFunc(BinaryWriter writer, object value);
            public delegate object DeserializerFunc(BinaryReader reader);
            public delegate object DeserializeNativeFunc(IntPtr valuePtr);

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

        static TypeInfo[] TypeInfoList = {
                new TypeInfo(typeof(Result), "Result",
                    (writer, value) => { writer.Write(((Result)value).Code); },
                    (reader) => { return new Result(reader.ReadInt32()); },
                    (valuePtr) => { return new Result(Marshal.ReadInt32(valuePtr)); }
                ),
                new TypeInfo(typeof(bool), "bool",
                (writer, value) => { writer.Write(((Int32)value)); },
                (reader) => { return reader.ReadInt32() != 0 ? true : false; },
                (valuePtr) => { return Marshal.ReadInt32(valuePtr) != 0 ? true : false; }),

            new TypeInfo(typeof(IntPtr), "void*",
                (writer, value) => { writer.Write((Int64)value); },
                (reader) => { return reader.ReadInt64(); },
                (valuePtr) => { return Marshal.ReadInt64(valuePtr); }),

            new TypeInfo(typeof(int), "int",
                (writer, value) => { writer.Write((int)value); },
                (reader) => { return reader.ReadInt32(); },
                (valuePtr) => { return Marshal.ReadInt32(valuePtr); }),

            new TypeInfo(typeof(uint), "uint",
                (writer, value) => { writer.Write((uint)value); },
                (reader) => { return reader.ReadUInt32(); },
                (valuePtr) => { return (uint)Marshal.ReadInt32(valuePtr); }),

            new TypeInfo(typeof(Int32), "int32",
                (writer, value) => { writer.Write((Int32)value); },
                (reader) => { return reader.ReadInt32(); },
                (valuePtr) => { return Marshal.ReadInt32(valuePtr); }),

            new TypeInfo(typeof(UInt32), "uint32",
                (writer, value) => { writer.Write((UInt32)value); },
                (reader) => { return reader.ReadUInt32(); },
                (valuePtr) => { return (UInt32)Marshal.ReadInt32(valuePtr); }),

            new TypeInfo(typeof(SByte), "int8",
                (writer, value) => { writer.Write((SByte)value); },
                (reader) => { return reader.ReadSByte(); },
                (valuePtr) => { return (SByte)Marshal.ReadByte(valuePtr); }),

            new TypeInfo(typeof(Byte), "uint8",
                (writer, value) => { writer.Write((Byte)value); },
                (reader) => { return reader.ReadByte(); },
                (valuePtr) => { return Marshal.ReadByte(valuePtr); }),

            new TypeInfo(typeof(Int16), "int16",
                (writer, value) => { writer.Write((Int16)value); },
                (reader) => { return reader.ReadInt16(); },
                (valuePtr) => { return Marshal.ReadInt16(valuePtr); }),

            new TypeInfo(typeof(UInt16), "uint16",
                (writer, value) => { writer.Write((UInt16)value); },
                (reader) => { return reader.ReadUInt16(); },
                (valuePtr) => { return (UInt16)Marshal.ReadInt16(valuePtr); }),

            new TypeInfo(typeof(Int64), "int64",
                (writer, value) => { writer.Write((Int64)value); },
                (reader) => { return reader.ReadInt64(); },
                (valuePtr) => { return Marshal.ReadInt64(valuePtr); }),

            new TypeInfo(typeof(UInt64), "uint64",
                (writer, value) => { writer.Write((UInt64)value); },
                (reader) => { return reader.ReadUInt64(); },
                (valuePtr) => { return (UInt64)Marshal.ReadInt64(valuePtr); }),

            new TypeInfo(typeof(SFUInt128), "uint128",
                (writer, value) => { var valueTemp = (SFUInt128)value; writer.Write(valueTemp.Low); writer.Write(valueTemp.High); },
                (reader) => { return new SFUInt128() { Low = reader.ReadUInt64(), High = reader.ReadUInt64() }; },
                (valuePtr) => { return Marshal.PtrToStructure(valuePtr, typeof(SFUInt128)); }),

            new TypeInfo(typeof(float), "float",
                (writer, value) => { writer.Write((float)value); },
                (reader) => { return reader.ReadSingle(); },
                (valuePtr) => { return ReadFloat(valuePtr); }),

            new TypeInfo(typeof(double), "double",
                (writer, value) => { writer.Write((double)value); },
                (reader) => { return reader.ReadDouble(); },
                (valuePtr) => { return ReadDouble(valuePtr); }),

            new TypeInfo(typeof(UInt32), "hex32",
                (writer, value) => { writer.Write((UInt32)value); },
                (reader) => { return reader.ReadUInt32(); },
                (valuePtr) => { return (UInt32)Marshal.ReadInt32(valuePtr); }),

            new TypeInfo(typeof(UInt64), "hex64",
                (writer, value) => { writer.Write((UInt64)value); },
                (reader) => { return reader.ReadUInt64(); },
                (valuePtr) => { return (UInt64)Marshal.ReadInt64(valuePtr); }),

            new TypeInfo(typeof(string),
                "String",
                    (writer, value) =>
                    {
                        var valueTemp = (string)value;
                        writer.Write((UInt16)(valueTemp.Length + 1));
                        writer.Write(System.Text.Encoding.UTF8.GetBytes(valueTemp + "\0"));
                    },
                    (reader) =>
                    {
                        var strLen = reader.ReadUInt16();
                        byte[] byteBuffer = reader.ReadBytes(strLen);
                        return System.Text.Encoding.UTF8.GetString(byteBuffer, 0, strLen-1);
                    },
                    (valuePtr) =>
                    {
                        var strLen = Marshal.ReadInt16(valuePtr);
                        return ReadString(strLen,valuePtr+2);
                    }
                ),

            new TypeInfo(typeof(string),
                "string",
                    (writer, value) =>
                    {
                        var valueTemp = (string)value;
                        writer.Write((UInt16)(valueTemp.Length + 1));
                        writer.Write(System.Text.Encoding.UTF8.GetBytes(valueTemp + "\0"));
                    },
                    (reader) =>
                    {
                        var strLen = reader.ReadUInt16();
                        byte[] byteBuffer = reader.ReadBytes(strLen);
                        return System.Text.Encoding.UTF8.GetString(byteBuffer, 0, strLen-1);
                    },
                    (valuePtr) =>
                    {
                        var strLen = Marshal.ReadInt16(valuePtr);
                        return ReadString(strLen,valuePtr+2);
                    }
                ),

            new TypeInfo(typeof(string),
                "const char*",
                    (writer, value) =>
                    {
                        var valueTemp = (string)value;
                        writer.Write((UInt16)(valueTemp.Length + 1));
                        writer.Write(System.Text.Encoding.UTF8.GetBytes(valueTemp + "\0"));
                    },
                    (reader) =>
                    {
                        var strLen = reader.ReadUInt16();
                        byte[] byteBuffer = reader.ReadBytes(strLen);
                        return System.Text.Encoding.UTF8.GetString(byteBuffer, 0, strLen-1);
                    },
                    (valuePtr) =>
                    {
                        var strLen = Marshal.ReadInt16(valuePtr);
                        return ReadString(strLen,valuePtr+2);
                    }
                ),

            new TypeInfo(typeof(Vector2), "Vector2",
                (writer, value) => { var valueTemp = (Vector2)value; writer.Write(valueTemp.x); writer.Write(valueTemp.y); },
                (reader) => { return new Vector2() { x = reader.ReadSingle(), y = reader.ReadSingle() }; },
                (valuePtr) => { return Marshal.PtrToStructure(valuePtr, typeof(Vector2)); }),

            new TypeInfo(typeof(Vector3), "Vector3",
                (writer, value) => { var valueTemp = (Vector3)value; writer.Write(valueTemp.x); writer.Write(valueTemp.y); writer.Write(valueTemp.z); },
                (reader) => { return new Vector3() { x = reader.ReadSingle(), y = reader.ReadSingle(), z = reader.ReadSingle() }; },
                (valuePtr) => { return Marshal.PtrToStructure(valuePtr, typeof(Vector3)); }),

            new TypeInfo(typeof(Vector4), "Vector4",
                (writer, value) => { var valueTemp = (Vector4)value; writer.Write(valueTemp.x); writer.Write(valueTemp.y); writer.Write(valueTemp.z); writer.Write(valueTemp.w); },
                (reader) => { return new Vector4() { x = reader.ReadSingle(), y = reader.ReadSingle(), z = reader.ReadSingle(), w = reader.ReadSingle() }; },
                (valuePtr) => { return Marshal.PtrToStructure(valuePtr, typeof(Vector4)); }),

            new TypeInfo(typeof(UInt64), "StringCrc32",
                (writer, value) => { writer.Write(((StringCrc32)value).StringHash); },
                (reader) => { return new StringCrc32(reader.ReadUInt32()); },
                (valuePtr) => { return new StringCrc32((UInt32)Marshal.ReadInt32(valuePtr)); }),

            new TypeInfo(typeof(UInt64), "StringCrc64",
                (writer, value) => { writer.Write(((StringCrc64)value).StringHash); },
                (reader) => { return new StringCrc64(reader.ReadUInt64()); },
                (valuePtr) => { return new StringCrc64((UInt64)Marshal.ReadInt64(valuePtr)); }),

            new TypeInfo(typeof(byte[]), "BLOB",
                (writer, value) => { var byteArray = (byte[])value; writer.Write(byteArray); },
                (reader) =>
                {
                    var byteSize = reader.ReadUInt16();
                    var bytes = reader.ReadBytes(byteSize);
                    return bytes;
                },
                (valuePtr) =>
                {
                    var byteSize = Marshal.ReadInt16(valuePtr);
                    var bytes = new byte[byteSize];
                    Marshal.Copy(valuePtr+2, bytes, 0, byteSize);
                    return bytes;
                }),

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


        static public TypeInfo GetTypeInfo(object value)
        {
            TypeInfo typeInfo;
            if (!TypeInfoByType.TryGetValue(value.GetType(), out typeInfo))
            {
                Log.Error("TypeSerialization.GetTypeInfo: Unknown type {0}", value.GetType().Name);
                throw new Exception(string.Format("Unknown type {0}", value.GetType().Name));
            }

            return typeInfo;
        }

        static public TypeInfo GetTypeInfo(StringCrc32 typeName)
        {
            TypeInfo typeInfo;
            if (!TypeInfoByTypeName.TryGetValue(typeName.StringHash, out typeInfo))
            {
                Log.Error("TypeSerialization.GetTypeInfo: Unknown type {0}", typeName);
                throw new Exception(string.Format("Unknown type {0}", typeName));
            }

            return typeInfo;
        }

    }


}


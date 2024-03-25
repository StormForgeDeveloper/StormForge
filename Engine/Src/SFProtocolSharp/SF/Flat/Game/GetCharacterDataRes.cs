// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct GetCharacterDataRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static GetCharacterDataRes GetRootAsGetCharacterDataRes(ByteBuffer _bb) { return GetRootAsGetCharacterDataRes(_bb, new GetCharacterDataRes()); }
  public static GetCharacterDataRes GetRootAsGetCharacterDataRes(ByteBuffer _bb, GetCharacterDataRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public GetCharacterDataRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public byte PrivateData(int j) { int o = __p.__offset(4); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int PrivateDataLength { get { int o = __p.__offset(4); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetPrivateDataBytes() { return __p.__vector_as_span<byte>(4, 1); }
#else
  public ArraySegment<byte>? GetPrivateDataBytes() { return __p.__vector_as_arraysegment(4); }
#endif
  public byte[] GetPrivateDataArray() { return __p.__vector_as_array<byte>(4); }
  public byte EquipData(int j) { int o = __p.__offset(6); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int EquipDataLength { get { int o = __p.__offset(6); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetEquipDataBytes() { return __p.__vector_as_span<byte>(6, 1); }
#else
  public ArraySegment<byte>? GetEquipDataBytes() { return __p.__vector_as_arraysegment(6); }
#endif
  public byte[] GetEquipDataArray() { return __p.__vector_as_array<byte>(6); }

  public static Offset<SF.Flat.Game.GetCharacterDataRes> CreateGetCharacterDataRes(FlatBufferBuilder builder,
      VectorOffset private_dataOffset = default(VectorOffset),
      VectorOffset equip_dataOffset = default(VectorOffset)) {
    builder.StartTable(2);
    GetCharacterDataRes.AddEquipData(builder, equip_dataOffset);
    GetCharacterDataRes.AddPrivateData(builder, private_dataOffset);
    return GetCharacterDataRes.EndGetCharacterDataRes(builder);
  }

  public static void StartGetCharacterDataRes(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddPrivateData(FlatBufferBuilder builder, VectorOffset privateDataOffset) { builder.AddOffset(0, privateDataOffset.Value, 0); }
  public static VectorOffset CreatePrivateDataVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreatePrivateDataVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreatePrivateDataVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreatePrivateDataVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartPrivateDataVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static void AddEquipData(FlatBufferBuilder builder, VectorOffset equipDataOffset) { builder.AddOffset(1, equipDataOffset.Value, 0); }
  public static VectorOffset CreateEquipDataVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateEquipDataVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateEquipDataVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateEquipDataVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartEquipDataVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static Offset<SF.Flat.Game.GetCharacterDataRes> EndGetCharacterDataRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.GetCharacterDataRes>(o);
  }
}


static public class GetCharacterDataResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyVectorOfData(tablePos, 4 /*PrivateData*/, 1 /*byte*/, false)
      && verifier.VerifyVectorOfData(tablePos, 6 /*EquipData*/, 1 /*byte*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}

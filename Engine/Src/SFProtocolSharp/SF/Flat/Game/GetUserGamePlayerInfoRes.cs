// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct GetUserGamePlayerInfoRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static GetUserGamePlayerInfoRes GetRootAsGetUserGamePlayerInfoRes(ByteBuffer _bb) { return GetRootAsGetUserGamePlayerInfoRes(_bb, new GetUserGamePlayerInfoRes()); }
  public static GetUserGamePlayerInfoRes GetRootAsGetUserGamePlayerInfoRes(ByteBuffer _bb, GetUserGamePlayerInfoRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public GetUserGamePlayerInfoRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public byte Attributes(int j) { int o = __p.__offset(6); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int AttributesLength { get { int o = __p.__offset(6); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetAttributesBytes() { return __p.__vector_as_span<byte>(6, 1); }
#else
  public ArraySegment<byte>? GetAttributesBytes() { return __p.__vector_as_arraysegment(6); }
#endif
  public byte[] GetAttributesArray() { return __p.__vector_as_array<byte>(6); }

  public static Offset<SF.Flat.Game.GetUserGamePlayerInfoRes> CreateGetUserGamePlayerInfoRes(FlatBufferBuilder builder,
      uint result = 0,
      VectorOffset attributesOffset = default(VectorOffset)) {
    builder.StartTable(2);
    GetUserGamePlayerInfoRes.AddAttributes(builder, attributesOffset);
    GetUserGamePlayerInfoRes.AddResult(builder, result);
    return GetUserGamePlayerInfoRes.EndGetUserGamePlayerInfoRes(builder);
  }

  public static void StartGetUserGamePlayerInfoRes(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddResult(FlatBufferBuilder builder, uint result) { builder.AddUint(0, result, 0); }
  public static void AddAttributes(FlatBufferBuilder builder, VectorOffset attributesOffset) { builder.AddOffset(1, attributesOffset.Value, 0); }
  public static VectorOffset CreateAttributesVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateAttributesVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateAttributesVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateAttributesVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartAttributesVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static Offset<SF.Flat.Game.GetUserGamePlayerInfoRes> EndGetUserGamePlayerInfoRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.GetUserGamePlayerInfoRes>(o);
  }
}


static public class GetUserGamePlayerInfoResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*uint*/, 4, false)
      && verifier.VerifyVectorOfData(tablePos, 6 /*Attributes*/, 1 /*byte*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
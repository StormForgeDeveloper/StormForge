// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct GetGamePlayerInfoRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static GetGamePlayerInfoRes GetRootAsGetGamePlayerInfoRes(ByteBuffer _bb) { return GetRootAsGetGamePlayerInfoRes(_bb, new GetGamePlayerInfoRes()); }
  public static GetGamePlayerInfoRes GetRootAsGetGamePlayerInfoRes(ByteBuffer _bb, GetGamePlayerInfoRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public GetGamePlayerInfoRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public SF.Flat.AccountID? PlayerId { get { int o = __p.__offset(6); return o != 0 ? (SF.Flat.AccountID?)(new SF.Flat.AccountID()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public byte Attributes(int j) { int o = __p.__offset(8); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int AttributesLength { get { int o = __p.__offset(8); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetAttributesBytes() { return __p.__vector_as_span<byte>(8, 1); }
#else
  public ArraySegment<byte>? GetAttributesBytes() { return __p.__vector_as_arraysegment(8); }
#endif
  public byte[] GetAttributesArray() { return __p.__vector_as_array<byte>(8); }

  public static void StartGetGamePlayerInfoRes(FlatBufferBuilder builder) { builder.StartTable(3); }
  public static void AddResult(FlatBufferBuilder builder, int result) { builder.AddInt(0, result, 0); }
  public static void AddPlayerId(FlatBufferBuilder builder, Offset<SF.Flat.AccountID> playerIdOffset) { builder.AddStruct(1, playerIdOffset.Value, 0); }
  public static void AddAttributes(FlatBufferBuilder builder, VectorOffset attributesOffset) { builder.AddOffset(2, attributesOffset.Value, 0); }
  public static VectorOffset CreateAttributesVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateAttributesVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateAttributesVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateAttributesVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartAttributesVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static Offset<SF.Flat.Game.GetGamePlayerInfoRes> EndGetGamePlayerInfoRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.GetGamePlayerInfoRes>(o);
  }
}


static public class GetGamePlayerInfoResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*int*/, 4, false)
      && verifier.VerifyField(tablePos, 6 /*PlayerId*/, 16 /*SF.Flat.AccountID*/, 8, false)
      && verifier.VerifyVectorOfData(tablePos, 8 /*Attributes*/, 1 /*byte*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}

// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct UseMapObjectCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static UseMapObjectCmd GetRootAsUseMapObjectCmd(ByteBuffer _bb) { return GetRootAsUseMapObjectCmd(_bb, new UseMapObjectCmd()); }
  public static UseMapObjectCmd GetRootAsUseMapObjectCmd(ByteBuffer _bb, UseMapObjectCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public UseMapObjectCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public SF.Flat.EntityUID? PlayInstanceUid { get { int o = __p.__offset(4); return o != 0 ? (SF.Flat.EntityUID?)(new SF.Flat.EntityUID()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public SF.Flat.AccountID? PlayerId { get { int o = __p.__offset(6); return o != 0 ? (SF.Flat.AccountID?)(new SF.Flat.AccountID()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public uint MapObjectId { get { int o = __p.__offset(8); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public byte UseParameters(int j) { int o = __p.__offset(10); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int UseParametersLength { get { int o = __p.__offset(10); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetUseParametersBytes() { return __p.__vector_as_span<byte>(10, 1); }
#else
  public ArraySegment<byte>? GetUseParametersBytes() { return __p.__vector_as_arraysegment(10); }
#endif
  public byte[] GetUseParametersArray() { return __p.__vector_as_array<byte>(10); }

  public static void StartUseMapObjectCmd(FlatBufferBuilder builder) { builder.StartTable(4); }
  public static void AddPlayInstanceUid(FlatBufferBuilder builder, Offset<SF.Flat.EntityUID> playInstanceUidOffset) { builder.AddStruct(0, playInstanceUidOffset.Value, 0); }
  public static void AddPlayerId(FlatBufferBuilder builder, Offset<SF.Flat.AccountID> playerIdOffset) { builder.AddStruct(1, playerIdOffset.Value, 0); }
  public static void AddMapObjectId(FlatBufferBuilder builder, uint mapObjectId) { builder.AddUint(2, mapObjectId, 0); }
  public static void AddUseParameters(FlatBufferBuilder builder, VectorOffset useParametersOffset) { builder.AddOffset(3, useParametersOffset.Value, 0); }
  public static VectorOffset CreateUseParametersVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateUseParametersVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateUseParametersVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateUseParametersVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartUseParametersVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static Offset<SF.Flat.PlayInstance.UseMapObjectCmd> EndUseMapObjectCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.UseMapObjectCmd>(o);
  }
}


static public class UseMapObjectCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlayInstanceUid*/, 4 /*SF.Flat.EntityUID*/, 4, false)
      && verifier.VerifyField(tablePos, 6 /*PlayerId*/, 16 /*SF.Flat.AccountID*/, 8, false)
      && verifier.VerifyField(tablePos, 8 /*MapObjectId*/, 4 /*uint*/, 4, false)
      && verifier.VerifyVectorOfData(tablePos, 10 /*UseParameters*/, 1 /*byte*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}

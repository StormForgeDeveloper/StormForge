// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct JoinGameInstanceRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static JoinGameInstanceRes GetRootAsJoinGameInstanceRes(ByteBuffer _bb) { return GetRootAsJoinGameInstanceRes(_bb, new JoinGameInstanceRes()); }
  public static JoinGameInstanceRes GetRootAsJoinGameInstanceRes(ByteBuffer _bb, JoinGameInstanceRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public JoinGameInstanceRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public SF.Flat.GameInstanceUID? InsUid { get { int o = __p.__offset(4); return o != 0 ? (SF.Flat.GameInstanceUID?)(new SF.Flat.GameInstanceUID()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public byte ZoneCustomData(int j) { int o = __p.__offset(6); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int ZoneCustomDataLength { get { int o = __p.__offset(6); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetZoneCustomDataBytes() { return __p.__vector_as_span<byte>(6, 1); }
#else
  public ArraySegment<byte>? GetZoneCustomDataBytes() { return __p.__vector_as_arraysegment(6); }
#endif
  public byte[] GetZoneCustomDataArray() { return __p.__vector_as_array<byte>(6); }
  public string ServerPublicAddress { get { int o = __p.__offset(8); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetServerPublicAddressBytes() { return __p.__vector_as_span<byte>(8, 1); }
#else
  public ArraySegment<byte>? GetServerPublicAddressBytes() { return __p.__vector_as_arraysegment(8); }
#endif
  public byte[] GetServerPublicAddressArray() { return __p.__vector_as_array<byte>(8); }

  public static void StartJoinGameInstanceRes(FlatBufferBuilder builder) { builder.StartTable(3); }
  public static void AddInsUid(FlatBufferBuilder builder, Offset<SF.Flat.GameInstanceUID> insUidOffset) { builder.AddStruct(0, insUidOffset.Value, 0); }
  public static void AddZoneCustomData(FlatBufferBuilder builder, VectorOffset zoneCustomDataOffset) { builder.AddOffset(1, zoneCustomDataOffset.Value, 0); }
  public static VectorOffset CreateZoneCustomDataVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateZoneCustomDataVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateZoneCustomDataVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateZoneCustomDataVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartZoneCustomDataVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static void AddServerPublicAddress(FlatBufferBuilder builder, StringOffset serverPublicAddressOffset) { builder.AddOffset(2, serverPublicAddressOffset.Value, 0); }
  public static Offset<SF.Flat.Game.JoinGameInstanceRes> EndJoinGameInstanceRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.JoinGameInstanceRes>(o);
  }
}


static public class JoinGameInstanceResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*InsUid*/, 4 /*SF.Flat.GameInstanceUID*/, 4, false)
      && verifier.VerifyVectorOfData(tablePos, 6 /*ZoneCustomData*/, 1 /*byte*/, false)
      && verifier.VerifyString(tablePos, 8 /*ServerPublicAddress*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}

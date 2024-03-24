// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct ClientSyncC2SEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static ClientSyncC2SEvt GetRootAsClientSyncC2SEvt(ByteBuffer _bb) { return GetRootAsClientSyncC2SEvt(_bb, new ClientSyncC2SEvt()); }
  public static ClientSyncC2SEvt GetRootAsClientSyncC2SEvt(ByteBuffer _bb, ClientSyncC2SEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public ClientSyncC2SEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public SF.Flat.GameInstanceUID? PlayInstanceUid { get { int o = __p.__offset(4); return o != 0 ? (SF.Flat.GameInstanceUID?)(new SF.Flat.GameInstanceUID()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public SF.Flat.AccountID? PlayerId { get { int o = __p.__offset(6); return o != 0 ? (SF.Flat.AccountID?)(new SF.Flat.AccountID()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public byte SyncData(int j) { int o = __p.__offset(8); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int SyncDataLength { get { int o = __p.__offset(8); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetSyncDataBytes() { return __p.__vector_as_span<byte>(8, 1); }
#else
  public ArraySegment<byte>? GetSyncDataBytes() { return __p.__vector_as_arraysegment(8); }
#endif
  public byte[] GetSyncDataArray() { return __p.__vector_as_array<byte>(8); }

  public static void StartClientSyncC2SEvt(FlatBufferBuilder builder) { builder.StartTable(3); }
  public static void AddPlayInstanceUid(FlatBufferBuilder builder, Offset<SF.Flat.GameInstanceUID> playInstanceUidOffset) { builder.AddStruct(0, playInstanceUidOffset.Value, 0); }
  public static void AddPlayerId(FlatBufferBuilder builder, Offset<SF.Flat.AccountID> playerIdOffset) { builder.AddStruct(1, playerIdOffset.Value, 0); }
  public static void AddSyncData(FlatBufferBuilder builder, VectorOffset syncDataOffset) { builder.AddOffset(2, syncDataOffset.Value, 0); }
  public static VectorOffset CreateSyncDataVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateSyncDataVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateSyncDataVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateSyncDataVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartSyncDataVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static Offset<SF.Flat.PlayInstance.ClientSyncC2SEvt> EndClientSyncC2SEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.ClientSyncC2SEvt>(o);
  }
}


static public class ClientSyncC2SEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlayInstanceUid*/, 4 /*SF.Flat.GameInstanceUID*/, 4, false)
      && verifier.VerifyField(tablePos, 6 /*PlayerId*/, 16 /*SF.Flat.AccountID*/, 8, false)
      && verifier.VerifyVectorOfData(tablePos, 8 /*SyncData*/, 1 /*byte*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}

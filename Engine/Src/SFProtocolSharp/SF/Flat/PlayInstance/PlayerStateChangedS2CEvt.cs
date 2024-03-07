// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct PlayerStateChangedS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static PlayerStateChangedS2CEvt GetRootAsPlayerStateChangedS2CEvt(ByteBuffer _bb) { return GetRootAsPlayerStateChangedS2CEvt(_bb, new PlayerStateChangedS2CEvt()); }
  public static PlayerStateChangedS2CEvt GetRootAsPlayerStateChangedS2CEvt(ByteBuffer _bb, PlayerStateChangedS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public PlayerStateChangedS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong PlayInstanceUid { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public ulong PlayerId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public uint State { get { int o = __p.__offset(8); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public uint MoveFrame { get { int o = __p.__offset(10); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public SF.Flat.Vector4? Position { get { int o = __p.__offset(12); return o != 0 ? (SF.Flat.Vector4?)(new SF.Flat.Vector4()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public byte StateValues(int j) { int o = __p.__offset(14); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int StateValuesLength { get { int o = __p.__offset(14); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetStateValuesBytes() { return __p.__vector_as_span<byte>(14, 1); }
#else
  public ArraySegment<byte>? GetStateValuesBytes() { return __p.__vector_as_arraysegment(14); }
#endif
  public byte[] GetStateValuesArray() { return __p.__vector_as_array<byte>(14); }

  public static void StartPlayerStateChangedS2CEvt(FlatBufferBuilder builder) { builder.StartTable(6); }
  public static void AddPlayInstanceUid(FlatBufferBuilder builder, ulong playInstanceUid) { builder.AddUlong(0, playInstanceUid, 0); }
  public static void AddPlayerId(FlatBufferBuilder builder, ulong playerId) { builder.AddUlong(1, playerId, 0); }
  public static void AddState(FlatBufferBuilder builder, uint state) { builder.AddUint(2, state, 0); }
  public static void AddMoveFrame(FlatBufferBuilder builder, uint moveFrame) { builder.AddUint(3, moveFrame, 0); }
  public static void AddPosition(FlatBufferBuilder builder, Offset<SF.Flat.Vector4> positionOffset) { builder.AddStruct(4, positionOffset.Value, 0); }
  public static void AddStateValues(FlatBufferBuilder builder, VectorOffset stateValuesOffset) { builder.AddOffset(5, stateValuesOffset.Value, 0); }
  public static VectorOffset CreateStateValuesVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateStateValuesVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateStateValuesVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateStateValuesVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartStateValuesVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static Offset<SF.Flat.PlayInstance.PlayerStateChangedS2CEvt> EndPlayerStateChangedS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.PlayerStateChangedS2CEvt>(o);
  }
}


static public class PlayerStateChangedS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlayInstanceUid*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 6 /*PlayerId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 8 /*State*/, 4 /*uint*/, 4, false)
      && verifier.VerifyField(tablePos, 10 /*MoveFrame*/, 4 /*uint*/, 4, false)
      && verifier.VerifyField(tablePos, 12 /*Position*/, 16 /*SF.Flat.Vector4*/, 4, false)
      && verifier.VerifyVectorOfData(tablePos, 14 /*StateValues*/, 1 /*byte*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}

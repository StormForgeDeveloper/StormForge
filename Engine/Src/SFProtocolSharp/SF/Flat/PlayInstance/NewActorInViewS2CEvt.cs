// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct NewActorInViewS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static NewActorInViewS2CEvt GetRootAsNewActorInViewS2CEvt(ByteBuffer _bb) { return GetRootAsNewActorInViewS2CEvt(_bb, new NewActorInViewS2CEvt()); }
  public static NewActorInViewS2CEvt GetRootAsNewActorInViewS2CEvt(ByteBuffer _bb, NewActorInViewS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public NewActorInViewS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong PlayInstanceUid { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public ulong PlayerId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public SF.Flat.PlayerPlatformID? PlayerPlatformId { get { int o = __p.__offset(8); return o != 0 ? (SF.Flat.PlayerPlatformID?)(new SF.Flat.PlayerPlatformID()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public byte PublicData(int j) { int o = __p.__offset(10); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int PublicDataLength { get { int o = __p.__offset(10); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetPublicDataBytes() { return __p.__vector_as_span<byte>(10, 1); }
#else
  public ArraySegment<byte>? GetPublicDataBytes() { return __p.__vector_as_arraysegment(10); }
#endif
  public byte[] GetPublicDataArray() { return __p.__vector_as_array<byte>(10); }
  public byte EquipData(int j) { int o = __p.__offset(12); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int EquipDataLength { get { int o = __p.__offset(12); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetEquipDataBytes() { return __p.__vector_as_span<byte>(12, 1); }
#else
  public ArraySegment<byte>? GetEquipDataBytes() { return __p.__vector_as_arraysegment(12); }
#endif
  public byte[] GetEquipDataArray() { return __p.__vector_as_array<byte>(12); }
  public SF.Flat.ActorMovement? Movement { get { int o = __p.__offset(14); return o != 0 ? (SF.Flat.ActorMovement?)(new SF.Flat.ActorMovement()).__assign(__p.__indirect(o + __p.bb_pos), __p.bb) : null; } }
  public uint State { get { int o = __p.__offset(16); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public byte StateValues(int j) { int o = __p.__offset(18); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int StateValuesLength { get { int o = __p.__offset(18); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetStateValuesBytes() { return __p.__vector_as_span<byte>(18, 1); }
#else
  public ArraySegment<byte>? GetStateValuesBytes() { return __p.__vector_as_arraysegment(18); }
#endif
  public byte[] GetStateValuesArray() { return __p.__vector_as_array<byte>(18); }

  public static void StartNewActorInViewS2CEvt(FlatBufferBuilder builder) { builder.StartTable(8); }
  public static void AddPlayInstanceUid(FlatBufferBuilder builder, ulong playInstanceUid) { builder.AddUlong(0, playInstanceUid, 0); }
  public static void AddPlayerId(FlatBufferBuilder builder, ulong playerId) { builder.AddUlong(1, playerId, 0); }
  public static void AddPlayerPlatformId(FlatBufferBuilder builder, Offset<SF.Flat.PlayerPlatformID> playerPlatformIdOffset) { builder.AddStruct(2, playerPlatformIdOffset.Value, 0); }
  public static void AddPublicData(FlatBufferBuilder builder, VectorOffset publicDataOffset) { builder.AddOffset(3, publicDataOffset.Value, 0); }
  public static VectorOffset CreatePublicDataVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreatePublicDataVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreatePublicDataVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreatePublicDataVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartPublicDataVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static void AddEquipData(FlatBufferBuilder builder, VectorOffset equipDataOffset) { builder.AddOffset(4, equipDataOffset.Value, 0); }
  public static VectorOffset CreateEquipDataVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateEquipDataVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateEquipDataVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateEquipDataVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartEquipDataVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static void AddMovement(FlatBufferBuilder builder, Offset<SF.Flat.ActorMovement> movementOffset) { builder.AddOffset(5, movementOffset.Value, 0); }
  public static void AddState(FlatBufferBuilder builder, uint state) { builder.AddUint(6, state, 0); }
  public static void AddStateValues(FlatBufferBuilder builder, VectorOffset stateValuesOffset) { builder.AddOffset(7, stateValuesOffset.Value, 0); }
  public static VectorOffset CreateStateValuesVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateStateValuesVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateStateValuesVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateStateValuesVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartStateValuesVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static Offset<SF.Flat.PlayInstance.NewActorInViewS2CEvt> EndNewActorInViewS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.NewActorInViewS2CEvt>(o);
  }
}


static public class NewActorInViewS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlayInstanceUid*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 6 /*PlayerId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 8 /*PlayerPlatformId*/, 16 /*SF.Flat.PlayerPlatformID*/, 8, false)
      && verifier.VerifyVectorOfData(tablePos, 10 /*PublicData*/, 1 /*byte*/, false)
      && verifier.VerifyVectorOfData(tablePos, 12 /*EquipData*/, 1 /*byte*/, false)
      && verifier.VerifyTable(tablePos, 14 /*Movement*/, SF.Flat.ActorMovementVerify.Verify, false)
      && verifier.VerifyField(tablePos, 16 /*State*/, 4 /*uint*/, 4, false)
      && verifier.VerifyVectorOfData(tablePos, 18 /*StateValues*/, 1 /*byte*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
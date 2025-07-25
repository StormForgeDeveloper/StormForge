// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct InstanceIsReadyS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static InstanceIsReadyS2CEvt GetRootAsInstanceIsReadyS2CEvt(ByteBuffer _bb) { return GetRootAsInstanceIsReadyS2CEvt(_bb, new InstanceIsReadyS2CEvt()); }
  public static InstanceIsReadyS2CEvt GetRootAsInstanceIsReadyS2CEvt(ByteBuffer _bb, InstanceIsReadyS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public InstanceIsReadyS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public string InstanceName { get { int o = __p.__offset(4); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetInstanceNameBytes() { return __p.__vector_as_span<byte>(4, 1); }
#else
  public ArraySegment<byte>? GetInstanceNameBytes() { return __p.__vector_as_arraysegment(4); }
#endif
  public byte[] GetInstanceNameArray() { return __p.__vector_as_array<byte>(4); }
  public SF.Flat.GameInstanceUID? GameInstanceId { get { int o = __p.__offset(6); return o != 0 ? (SF.Flat.GameInstanceUID?)(new SF.Flat.GameInstanceUID()).__assign(o + __p.bb_pos, __p.bb) : null; } }

  public static void StartInstanceIsReadyS2CEvt(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddInstanceName(FlatBufferBuilder builder, StringOffset instanceNameOffset) { builder.AddOffset(0, instanceNameOffset.Value, 0); }
  public static void AddGameInstanceId(FlatBufferBuilder builder, Offset<SF.Flat.GameInstanceUID> gameInstanceIdOffset) { builder.AddStruct(1, gameInstanceIdOffset.Value, 0); }
  public static Offset<SF.Flat.Game.InstanceIsReadyS2CEvt> EndInstanceIsReadyS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.InstanceIsReadyS2CEvt>(o);
  }
}


static public class InstanceIsReadyS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyString(tablePos, 4 /*InstanceName*/, false)
      && verifier.VerifyField(tablePos, 6 /*GameInstanceId*/, 4 /*SF.Flat.GameInstanceUID*/, 4, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}

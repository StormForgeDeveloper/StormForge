// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct Dummy1Cmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static Dummy1Cmd GetRootAsDummy1Cmd(ByteBuffer _bb) { return GetRootAsDummy1Cmd(_bb, new Dummy1Cmd()); }
  public static Dummy1Cmd GetRootAsDummy1Cmd(ByteBuffer _bb, Dummy1Cmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public Dummy1Cmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public string ComplitionState { get { int o = __p.__offset(4); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetComplitionStateBytes() { return __p.__vector_as_span<byte>(4, 1); }
#else
  public ArraySegment<byte>? GetComplitionStateBytes() { return __p.__vector_as_arraysegment(4); }
#endif
  public byte[] GetComplitionStateArray() { return __p.__vector_as_array<byte>(4); }

  public static Offset<SF.Flat.Game.Dummy1Cmd> CreateDummy1Cmd(FlatBufferBuilder builder,
      StringOffset complition_stateOffset = default(StringOffset)) {
    builder.StartTable(1);
    Dummy1Cmd.AddComplitionState(builder, complition_stateOffset);
    return Dummy1Cmd.EndDummy1Cmd(builder);
  }

  public static void StartDummy1Cmd(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddComplitionState(FlatBufferBuilder builder, StringOffset complitionStateOffset) { builder.AddOffset(0, complitionStateOffset.Value, 0); }
  public static Offset<SF.Flat.Game.Dummy1Cmd> EndDummy1Cmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.Dummy1Cmd>(o);
  }
}


static public class Dummy1CmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyString(tablePos, 4 /*ComplitionState*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}

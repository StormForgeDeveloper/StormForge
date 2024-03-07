// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct SetNickNameCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static SetNickNameCmd GetRootAsSetNickNameCmd(ByteBuffer _bb) { return GetRootAsSetNickNameCmd(_bb, new SetNickNameCmd()); }
  public static SetNickNameCmd GetRootAsSetNickNameCmd(ByteBuffer _bb, SetNickNameCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public SetNickNameCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public string NickName { get { int o = __p.__offset(4); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetNickNameBytes() { return __p.__vector_as_span<byte>(4, 1); }
#else
  public ArraySegment<byte>? GetNickNameBytes() { return __p.__vector_as_arraysegment(4); }
#endif
  public byte[] GetNickNameArray() { return __p.__vector_as_array<byte>(4); }
  public byte IsCostFree { get { int o = __p.__offset(6); return o != 0 ? __p.bb.Get(o + __p.bb_pos) : (byte)0; } }

  public static Offset<SF.Flat.Game.SetNickNameCmd> CreateSetNickNameCmd(FlatBufferBuilder builder,
      StringOffset nick_nameOffset = default(StringOffset),
      byte is_cost_free = 0) {
    builder.StartTable(2);
    SetNickNameCmd.AddNickName(builder, nick_nameOffset);
    SetNickNameCmd.AddIsCostFree(builder, is_cost_free);
    return SetNickNameCmd.EndSetNickNameCmd(builder);
  }

  public static void StartSetNickNameCmd(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddNickName(FlatBufferBuilder builder, StringOffset nickNameOffset) { builder.AddOffset(0, nickNameOffset.Value, 0); }
  public static void AddIsCostFree(FlatBufferBuilder builder, byte isCostFree) { builder.AddByte(1, isCostFree, 0); }
  public static Offset<SF.Flat.Game.SetNickNameCmd> EndSetNickNameCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.SetNickNameCmd>(o);
  }
}


static public class SetNickNameCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyString(tablePos, 4 /*NickName*/, false)
      && verifier.VerifyField(tablePos, 6 /*IsCostFree*/, 1 /*byte*/, 1, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}

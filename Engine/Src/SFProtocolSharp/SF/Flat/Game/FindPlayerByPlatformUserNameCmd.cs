// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct FindPlayerByPlatformUserNameCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static FindPlayerByPlatformUserNameCmd GetRootAsFindPlayerByPlatformUserNameCmd(ByteBuffer _bb) { return GetRootAsFindPlayerByPlatformUserNameCmd(_bb, new FindPlayerByPlatformUserNameCmd()); }
  public static FindPlayerByPlatformUserNameCmd GetRootAsFindPlayerByPlatformUserNameCmd(ByteBuffer _bb, FindPlayerByPlatformUserNameCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public FindPlayerByPlatformUserNameCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public byte PlatformType { get { int o = __p.__offset(4); return o != 0 ? __p.bb.Get(o + __p.bb_pos) : (byte)0; } }
  public string PlatformUserName { get { int o = __p.__offset(6); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetPlatformUserNameBytes() { return __p.__vector_as_span<byte>(6, 1); }
#else
  public ArraySegment<byte>? GetPlatformUserNameBytes() { return __p.__vector_as_arraysegment(6); }
#endif
  public byte[] GetPlatformUserNameArray() { return __p.__vector_as_array<byte>(6); }

  public static Offset<SF.Flat.Game.FindPlayerByPlatformUserNameCmd> CreateFindPlayerByPlatformUserNameCmd(FlatBufferBuilder builder,
      byte platform_type = 0,
      StringOffset platform_user_nameOffset = default(StringOffset)) {
    builder.StartTable(2);
    FindPlayerByPlatformUserNameCmd.AddPlatformUserName(builder, platform_user_nameOffset);
    FindPlayerByPlatformUserNameCmd.AddPlatformType(builder, platform_type);
    return FindPlayerByPlatformUserNameCmd.EndFindPlayerByPlatformUserNameCmd(builder);
  }

  public static void StartFindPlayerByPlatformUserNameCmd(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddPlatformType(FlatBufferBuilder builder, byte platformType) { builder.AddByte(0, platformType, 0); }
  public static void AddPlatformUserName(FlatBufferBuilder builder, StringOffset platformUserNameOffset) { builder.AddOffset(1, platformUserNameOffset.Value, 0); }
  public static Offset<SF.Flat.Game.FindPlayerByPlatformUserNameCmd> EndFindPlayerByPlatformUserNameCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.FindPlayerByPlatformUserNameCmd>(o);
  }
}


static public class FindPlayerByPlatformUserNameCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlatformType*/, 1 /*byte*/, 1, false)
      && verifier.VerifyString(tablePos, 6 /*PlatformUserName*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}

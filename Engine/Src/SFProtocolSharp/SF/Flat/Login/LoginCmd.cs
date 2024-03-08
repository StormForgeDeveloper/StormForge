// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Login
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct LoginCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static LoginCmd GetRootAsLoginCmd(ByteBuffer _bb) { return GetRootAsLoginCmd(_bb, new LoginCmd()); }
  public static LoginCmd GetRootAsLoginCmd(ByteBuffer _bb, LoginCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public LoginCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public string UserId { get { int o = __p.__offset(4); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetUserIdBytes() { return __p.__vector_as_span<byte>(4, 1); }
#else
  public ArraySegment<byte>? GetUserIdBytes() { return __p.__vector_as_arraysegment(4); }
#endif
  public byte[] GetUserIdArray() { return __p.__vector_as_array<byte>(4); }
  public string Password { get { int o = __p.__offset(6); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetPasswordBytes() { return __p.__vector_as_span<byte>(6, 1); }
#else
  public ArraySegment<byte>? GetPasswordBytes() { return __p.__vector_as_arraysegment(6); }
#endif
  public byte[] GetPasswordArray() { return __p.__vector_as_array<byte>(6); }
  public string GameId { get { int o = __p.__offset(8); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetGameIdBytes() { return __p.__vector_as_span<byte>(8, 1); }
#else
  public ArraySegment<byte>? GetGameIdBytes() { return __p.__vector_as_arraysegment(8); }
#endif
  public byte[] GetGameIdArray() { return __p.__vector_as_array<byte>(8); }

  public static Offset<SF.Flat.Login.LoginCmd> CreateLoginCmd(FlatBufferBuilder builder,
      StringOffset user_idOffset = default(StringOffset),
      StringOffset passwordOffset = default(StringOffset),
      StringOffset game_idOffset = default(StringOffset)) {
    builder.StartTable(3);
    LoginCmd.AddGameId(builder, game_idOffset);
    LoginCmd.AddPassword(builder, passwordOffset);
    LoginCmd.AddUserId(builder, user_idOffset);
    return LoginCmd.EndLoginCmd(builder);
  }

  public static void StartLoginCmd(FlatBufferBuilder builder) { builder.StartTable(3); }
  public static void AddUserId(FlatBufferBuilder builder, StringOffset userIdOffset) { builder.AddOffset(0, userIdOffset.Value, 0); }
  public static void AddPassword(FlatBufferBuilder builder, StringOffset passwordOffset) { builder.AddOffset(1, passwordOffset.Value, 0); }
  public static void AddGameId(FlatBufferBuilder builder, StringOffset gameIdOffset) { builder.AddOffset(2, gameIdOffset.Value, 0); }
  public static Offset<SF.Flat.Login.LoginCmd> EndLoginCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Login.LoginCmd>(o);
  }
}


static public class LoginCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyString(tablePos, 4 /*UserId*/, false)
      && verifier.VerifyString(tablePos, 6 /*Password*/, false)
      && verifier.VerifyString(tablePos, 8 /*GameId*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Login
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct LoginRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static LoginRes GetRootAsLoginRes(ByteBuffer _bb) { return GetRootAsLoginRes(_bb, new LoginRes()); }
  public static LoginRes GetRootAsLoginRes(ByteBuffer _bb, LoginRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public LoginRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public string NickName { get { int o = __p.__offset(4); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetNickNameBytes() { return __p.__vector_as_span<byte>(4, 1); }
#else
  public ArraySegment<byte>? GetNickNameBytes() { return __p.__vector_as_arraysegment(4); }
#endif
  public byte[] GetNickNameArray() { return __p.__vector_as_array<byte>(4); }
  public SF.Flat.AccountID? AccountId { get { int o = __p.__offset(6); return o != 0 ? (SF.Flat.AccountID?)(new SF.Flat.AccountID()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public ulong AuthTicket { get { int o = __p.__offset(8); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public string BannedReason { get { int o = __p.__offset(10); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetBannedReasonBytes() { return __p.__vector_as_span<byte>(10, 1); }
#else
  public ArraySegment<byte>? GetBannedReasonBytes() { return __p.__vector_as_arraysegment(10); }
#endif
  public byte[] GetBannedReasonArray() { return __p.__vector_as_array<byte>(10); }
  public SF.Flat.EAccountRole Role { get { int o = __p.__offset(12); return o != 0 ? (SF.Flat.EAccountRole)__p.bb.GetSbyte(o + __p.bb_pos) : SF.Flat.EAccountRole.Player; } }
  public string GameServerAddress { get { int o = __p.__offset(14); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetGameServerAddressBytes() { return __p.__vector_as_span<byte>(14, 1); }
#else
  public ArraySegment<byte>? GetGameServerAddressBytes() { return __p.__vector_as_arraysegment(14); }
#endif
  public byte[] GetGameServerAddressArray() { return __p.__vector_as_array<byte>(14); }

  public static void StartLoginRes(FlatBufferBuilder builder) { builder.StartTable(6); }
  public static void AddNickName(FlatBufferBuilder builder, StringOffset nickNameOffset) { builder.AddOffset(0, nickNameOffset.Value, 0); }
  public static void AddAccountId(FlatBufferBuilder builder, Offset<SF.Flat.AccountID> accountIdOffset) { builder.AddStruct(1, accountIdOffset.Value, 0); }
  public static void AddAuthTicket(FlatBufferBuilder builder, ulong authTicket) { builder.AddUlong(2, authTicket, 0); }
  public static void AddBannedReason(FlatBufferBuilder builder, StringOffset bannedReasonOffset) { builder.AddOffset(3, bannedReasonOffset.Value, 0); }
  public static void AddRole(FlatBufferBuilder builder, SF.Flat.EAccountRole role) { builder.AddSbyte(4, (sbyte)role, 0); }
  public static void AddGameServerAddress(FlatBufferBuilder builder, StringOffset gameServerAddressOffset) { builder.AddOffset(5, gameServerAddressOffset.Value, 0); }
  public static Offset<SF.Flat.Login.LoginRes> EndLoginRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Login.LoginRes>(o);
  }
}


static public class LoginResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyString(tablePos, 4 /*NickName*/, false)
      && verifier.VerifyField(tablePos, 6 /*AccountId*/, 16 /*SF.Flat.AccountID*/, 8, false)
      && verifier.VerifyField(tablePos, 8 /*AuthTicket*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyString(tablePos, 10 /*BannedReason*/, false)
      && verifier.VerifyField(tablePos, 12 /*Role*/, 1 /*SF.Flat.EAccountRole*/, 1, false)
      && verifier.VerifyString(tablePos, 14 /*GameServerAddress*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}

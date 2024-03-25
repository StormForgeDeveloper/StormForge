// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct AcceptNotificationRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static AcceptNotificationRes GetRootAsAcceptNotificationRes(ByteBuffer _bb) { return GetRootAsAcceptNotificationRes(_bb, new AcceptNotificationRes()); }
  public static AcceptNotificationRes GetRootAsAcceptNotificationRes(ByteBuffer _bb, AcceptNotificationRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public AcceptNotificationRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint NotificationId { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }

  public static Offset<SF.Flat.Game.AcceptNotificationRes> CreateAcceptNotificationRes(FlatBufferBuilder builder,
      uint notification_id = 0) {
    builder.StartTable(1);
    AcceptNotificationRes.AddNotificationId(builder, notification_id);
    return AcceptNotificationRes.EndAcceptNotificationRes(builder);
  }

  public static void StartAcceptNotificationRes(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddNotificationId(FlatBufferBuilder builder, uint notificationId) { builder.AddUint(0, notificationId, 0); }
  public static Offset<SF.Flat.Game.AcceptNotificationRes> EndAcceptNotificationRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.AcceptNotificationRes>(o);
  }
}


static public class AcceptNotificationResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*NotificationId*/, 4 /*uint*/, 4, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
